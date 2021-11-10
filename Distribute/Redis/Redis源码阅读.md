#### 1.4 压缩列表

PS: 本次源码版本为 6.2.6 稳定版本

Redis使用字节数组表示一个压缩列表，压缩列表结构示意如图1-2所示。  

![image-20211013150847600](D:\Ebook\读后感\Resid源码\zipList_pic.png)

​																						图1-2　压缩列表结构示意  

图1-2中各字段的含义如下。
1）zlbytes： 压缩列表的字节长度，占4个字节，因此压缩列表最多有232 -1个字节。
2）zltail： 压缩列表尾元素相对于压缩列表起始地址的偏移量，占4个字节。
3）zllen： 压缩列表的元素个数，占2个字节。zllen无法存储元素个数超过65535（216 -1）的压缩列表，必须遍历整个压缩列表才能获取到元素个数。
4）entryX： 压缩列表存储的元素，可以是字节数组或者整数，长度不限。entry的编码结构将在后面详细介绍。
5）zlend： 压缩列表的结尾，占1个字节，恒为0xFF。  

压缩列表元素的编码结构，如图1-3所示。  

![image-20211013151658246](E:\Work\Document\Distribute\Redis\picture\ZipListElemStructorPic.png)

​																								图1-3　压缩列表元素的结构示意  

previous_entry_length字段表示前一个元素的字节长度，占1个或者5个字节，当前一个元素的长度小于254字节时，用1个字节表示；当前一个元素的长度大于或等于254字节时，用5个字节来表示。而此时previous_entry_length字段的第1个字节是固定的0xFE，后面4个字节才真正表示前一个元素的长度。假设已知当前元素的首地址为p，那么p-previous_entry_length就是前一个元素的首地址，从而实现压缩列表从尾到头的遍历。  

encoding字段表示当前元素的编码，即content字段存储的数据类型（整数或者字节数组），数据内容存储在content字段。为了节约内存，encoding字段同样长度可变。压缩列表元素的编码如表1-1所示。  

![image-20211013151956905](E:\Work\Document\Distribute\Redis\picture\ZipListElemEncodingType.png)

​																										表1-1　压缩列表元素的编码  

可以看出，根据encoding字段第1个字节的前2位，可以判断content字段存储的是整数或者字节数组（及其最大长度）。当content存储的是字节数组时，后续字节标识字节数组的实际长度；当content存储的是整数时，可根据第3、第4位判断整数的具体类型。而当encoding字段标识当前元素存储的是0～12的立即数时，数据直接存储在encoding字段的最后4位，此时没有content字段。参照encoding字段的编码表格，Redis预定义了以下常量对应encoding字段的各编码类型 。

```c++
定义了结构体zlentry，用于表示解码后的压缩列表元素
typedef struct zlentry {
unsigned int prevrawlensize;
unsigned int prevrawlen;
unsigned int lensize;
unsigned int len;
unsigned char encoding;
unsigned int headersize;
unsigned char *p;
} zlentry;

结构体zlentry定义了7个字段，而4.1节显示每个元素只包含3个字段。回顾压缩列表元素的编码结构，可变因素实际上不止3个：previous_entry_length字段的长度（prevrawlensize）、previous_entry_length字段存储的内容（prevrawlen）、encoding字段的长度（lensize）、encoding字段的内容（len表示元素数据内容的长度，encoding表示数据类型）和当前元素首地址（p）；而headersize则表示当前元素的首部长度，即previous_entry_length字
段长度与encoding字段长度之和。
```

``` c++
函数zipEntry用来解码压缩列表的元素，存储于zlentry结构体。

#define ZIP_DECODE_PREVLENSIZE(ptr, prevlensize) do {                          \
    if ((ptr)[0] < ZIP_BIG_PREVLEN) {                                          \
        (prevlensize) = 1;                                                     \
    } else {                                                                   \
        (prevlensize) = 5;                                                     \
    }                                                                          \
} while(0)
    
#define ZIP_DECODE_PREVLEN(ptr, prevlensize, prevlen) do {                     \
    ZIP_DECODE_PREVLENSIZE(ptr, prevlensize);                                  \
    if ((prevlensize) == 1) {                                                  \
        (prevlen) = (ptr)[0];                                                  \
    } else { /* prevlensize == 5 */                                            \
        (prevlen) = ((ptr)[4] << 24) |                                         \
                    ((ptr)[3] << 16) |                                         \
                    ((ptr)[2] <<  8) |                                         \
                    ((ptr)[1]);                                                \
    }                                                                          \
} while(0)

#define ZIP_ENTRY_ENCODING(ptr, encoding) do {  \
    (encoding) = ((ptr)[0]); \
    if ((encoding) < ZIP_STR_MASK) (encoding) &= ZIP_STR_MASK; \
} while(0)

#define ZIP_ENCODING_SIZE_INVALID 0xff
    
#define ZIPLIST_ENTRY_ZERO(zle) { \
    (zle)->prevrawlensize = (zle)->prevrawlen = 0; \
    (zle)->lensize = (zle)->len = (zle)->headersize = 0; \
    (zle)->encoding = 0; \
    (zle)->p = NULL; \
}
    
static inline void zipEntry(unsigned char *p, zlentry *e) {
    ZIP_DECODE_PREVLEN(p, e->prevrawlensize, e->prevrawlen);
    ZIP_ENTRY_ENCODING(p + e->prevrawlensize, e->encoding);
    ZIP_DECODE_LENGTH(p + e->prevrawlensize, e->encoding, e->lensize, e->len);
    assert(e->lensize != 0); /* check that encoding was valid. */
    e->headersize = e->prevrawlensize + e->lensize;
    e->p = p;
}	
```



##### 1.4.1 基本操作

​		主要介绍压缩列表的基本操作，包括创建压缩列表、插入元素、删除元素及遍历压缩列表，让读者从源码层次进一步理解压缩列表。  

###### 1.4.1.1 创建

```c++
	主要介绍压缩列表的基本操作，包括创建压缩列表、插入元素、删除元素及遍历压缩列表，让读者从源码层次进一步理解压缩列表。 创建空的压缩列表，只需要分配初始存储空间11(4+4+2+1)个字节，并对zlbytes、zltail、zllen和zlend字段初始化即可。
        
#define ZIPLIST_HEADER_SIZE     (sizeof(uint32_t)*2+sizeof(uint16_t))
#define ZIPLIST_END_SIZE        (sizeof(uint8_t))

unsigned char *ziplistNew(void) {
    unsigned int bytes = ZIPLIST_HEADER_SIZE+ZIPLIST_END_SIZE;		//11 Bytes
    unsigned char *zl = zmalloc(bytes);
    ZIPLIST_BYTES(zl) = intrev32ifbe(bytes);
    ZIPLIST_TAIL_OFFSET(zl) = intrev32ifbe(ZIPLIST_HEADER_SIZE);
    ZIPLIST_LENGTH(zl) = 0;
    zl[bytes-1] = ZIP_END;
    return zl;
}
```
###### 1.4.1.2 插入元素

压缩列表插入元素的API定义如下，函数输入参数zl表示压缩列表首地址，p指向元素插入位置，s表示数据内容，slen表示数据长度，返回参数为压缩列表首地址。  

```c++
unsigned char *ziplistInsert(unsigned char *zl, unsigned char *p, unsigned char *s, unsigned int slen) {
    return __ziplistInsert(zl,p,s,slen);
}

/* Insert item at "p". */
unsigned char *__ziplistInsert(unsigned char *zl, unsigned char *p, unsigned char *s, unsigned int slen) {
    size_t curlen = intrev32ifbe(ZIPLIST_BYTES(zl)), reqlen, newlen;
    unsigned int prevlensize, prevlen = 0;
    size_t offset;
    int nextdiff = 0;
    unsigned char encoding = 0;
    long long value = 123456789; /* initialized to avoid warning. Using a value
                                    that is easy to see if for some reason
                                    we use it uninitialized. */
    zlentry tail;

    /* Find out prevlen for the entry that is inserted. */
    if (p[0] != ZIP_END) {
        ZIP_DECODE_PREVLEN(p, prevlensize, prevlen);
    } else {
        unsigned char *ptail = ZIPLIST_ENTRY_TAIL(zl);
        if (ptail[0] != ZIP_END) {
            prevlen = zipRawEntryLengthSafe(zl, curlen, ptail);
        }
    }

    /* See if the entry can be encoded */
    if (zipTryEncoding(s,slen,&value,&encoding)) {
        /* 'encoding' is set to the appropriate integer encoding */
        reqlen = zipIntSize(encoding);
    } else {
        /* 'encoding' is untouched, however zipStoreEntryEncoding will use the
         * string length to figure out how to encode it. */
        reqlen = slen;
    }
    /* We need space for both the length of the previous entry and
     * the length of the payload. */
    reqlen += zipStorePrevEntryLength(NULL,prevlen);
    reqlen += zipStoreEntryEncoding(NULL,encoding,slen);

    /* When the insert position is not equal to the tail, we need to
     * make sure that the next entry can hold this entry's length in
     * its prevlen field. */
    int forcelarge = 0;
    nextdiff = (p[0] != ZIP_END) ? zipPrevLenByteDiff(p,reqlen) : 0;
    if (nextdiff == -4 && reqlen < 4) {
        nextdiff = 0;
        forcelarge = 1;
    }

    /* Store offset because a realloc may change the address of zl. */
    offset = p-zl;
    newlen = curlen+reqlen+nextdiff;
    zl = ziplistResize(zl,newlen);
    p = zl+offset;

    /* Apply memory move when necessary and update tail offset. */
    if (p[0] != ZIP_END) {
        /* Subtract one because of the ZIP_END bytes */
        memmove(p+reqlen,p-nextdiff,curlen-offset-1+nextdiff);

        /* Encode this entry's raw length in the next entry. */
        if (forcelarge)
            zipStorePrevEntryLengthLarge(p+reqlen,reqlen);
        else
            zipStorePrevEntryLength(p+reqlen,reqlen);

        /* Update offset for tail */
        ZIPLIST_TAIL_OFFSET(zl) =
            intrev32ifbe(intrev32ifbe(ZIPLIST_TAIL_OFFSET(zl))+reqlen);

        /* When the tail contains more than one entry, we need to take
         * "nextdiff" in account as well. Otherwise, a change in the
         * size of prevlen doesn't have an effect on the *tail* offset. */
        assert(zipEntrySafe(zl, newlen, p+reqlen, &tail, 1));
        if (p[reqlen+tail.headersize+tail.len] != ZIP_END) {
            ZIPLIST_TAIL_OFFSET(zl) =
                intrev32ifbe(intrev32ifbe(ZIPLIST_TAIL_OFFSET(zl))+nextdiff);
        }
    } else {
        /* This element will be the new tail. */
        ZIPLIST_TAIL_OFFSET(zl) = intrev32ifbe(p-zl);
    }

    /* When nextdiff != 0, the raw length of the next entry has changed, so
     * we need to cascade the update throughout the ziplist */
    if (nextdiff != 0) {
        offset = p-zl;
        zl = __ziplistCascadeUpdate(zl,p+reqlen);
        p = zl+offset;
    }

    /* Write the entry */
    p += zipStorePrevEntryLength(p,prevlen);
    p += zipStoreEntryEncoding(p,encoding,slen);
    if (ZIP_IS_STR(encoding)) {
        memcpy(p,s,slen);
    } else {
        zipSaveInteger(p,value,encoding);
    }
    ZIPLIST_INCR_LENGTH(zl,1);
    return zl;
}
```

#### 1.5 字典

​		Redis字典实现依赖的数据结构主要包含了三部分：字典、Hash表、Hash表节点。字典中嵌入了两个Hash表，Hash表中的table字段存放着Hash表节点，Hash表节点对应存储的是键值对。  

##### 1.5.1 Hash表

```c++
Hash表，与设计的字典结构体类似，在Redis源码中取名为Hash表，其数据结构如下：

typedef struct dictEntry {
    void *key;
    union {
        void *val;
        uint64_t u64;
        int64_t s64;
        double d;
    } v;
    struct dictEntry *next;
} dictEntry;

typedef struct dictType {
    uint64_t (*hashFunction)(const void *key);
    void *(*keyDup)(void *privdata, const void *key);
    void *(*valDup)(void *privdata, const void *obj);
    int (*keyCompare)(void *privdata, const void *key1, const void *key2);
    void (*keyDestructor)(void *privdata, void *key);
    void (*valDestructor)(void *privdata, void *obj);
    int (*expandAllowed)(size_t moreMem, double usedRatio);
} dictType;    
    
typedef struct dictht {
	dictEntry **table; /*指针数组，用于存储键值对*/
	unsigned long size; /*table数组的大小*/
	unsigned long sizemask; /*掩码 = size - 1 */
	unsigned long used; /*table数组已存元素个数，包含next单链表的数据*/
} dictht;

typedef struct dict {
	dictType *type; /*该字典对应的特定操作函数*/
	void *privdata; /*该字典依赖的数据*/
	dictht ht[2]; /*Hash表，键值对存储在此*/
	long rehashidx; /*rehash标识。默认值为-1，代表没进行rehash操作；不为-1时，
代表正进行rehash操作，存储的值表示Hash表ht[0]的rehash操作进行到了哪个索引值*/
	unsigned long iterators; /* 当前运行的迭代器数*/
} dict;
```

![image-20211026095715996](E:\Work\Document\Distribute\Redis\picture\emptyDictStruct.png)

​																	图1.5.1　空Hash表结构示意图  

![image-20211026101437460](E:\Work\Document\Distribute\Redis\picture\FullDictStruct.png)

​																图1.5.2  Redis字典结构示意图  



#### 1.6 快速链表 quicklist

##### 1.6.1 数据结构define

```c++
typedef struct quicklistNode {
    struct quicklistNode *prev;
    struct quicklistNode *next;
    unsigned char *zl;
    unsigned int sz;             /* ziplist size in bytes */
    unsigned int count : 16;     /* count of items in ziplist */
    unsigned int encoding : 2;   /* RAW==1 or LZF==2 */
    unsigned int container : 2;  /* NONE==1 or ZIPLIST==2 */
    unsigned int recompress : 1; /* was this node previous compressed? */
    unsigned int attempted_compress : 1; /* node can't compress; too small */
    unsigned int extra : 10; /* more bits to steal for future usage */
} quicklistNode;

/* quicklistLZF is a 4+N byte struct holding 'sz' followed by 'compressed'.
 * 'sz' is byte length of 'compressed' field.
 * 'compressed' is LZF data with total (compressed) length 'sz'
 * NOTE: uncompressed length is stored in quicklistNode->sz.
 * When quicklistNode->zl is compressed, node->zl points to a quicklistLZF */
typedef struct quicklistLZF {
    unsigned int sz; /* LZF size in bytes*/
    char compressed[];
} quicklistLZF;

/* Bookmarks are padded with realloc at the end of of the quicklist struct.
 * They should only be used for very big lists if thousands of nodes were the
 * excess memory usage is negligible, and there's a real need to iterate on them
 * in portions.
 * When not used, they don't add any memory overhead, but when used and then
 * deleted, some overhead remains (to avoid resonance).
 * The number of bookmarks used should be kept to minimum since it also adds
 * overhead on node deletion (searching for a bookmark to update). */
typedef struct quicklistBookmark {
    quicklistNode *node;
    char *name;
} quicklistBookmark;

#if UINTPTR_MAX == 0xffffffff
/* 32-bit */
#   define QL_FILL_BITS 14
#   define QL_COMP_BITS 14
#   define QL_BM_BITS 4
#elif UINTPTR_MAX == 0xffffffffffffffff
/* 64-bit */
#   define QL_FILL_BITS 16
#   define QL_COMP_BITS 16
#   define QL_BM_BITS 4 /* we can encode more, but we rather limit the user
                           since they cause performance degradation. */
#else
#   error unknown arch bits count
#endif

/* quicklist is a 40 byte struct (on 64-bit systems) describing a quicklist.
 * 'count' is the number of total entries.
 * 'len' is the number of quicklist nodes.
 * 'compress' is: 0 if compression disabled, otherwise it's the number
 *                of quicklistNodes to leave uncompressed at ends of quicklist.
 * 'fill' is the user-requested (or default) fill factor.
 * 'bookmakrs are an optional feature that is used by realloc this struct,
 *      so that they don't consume memory when not used. */
typedef struct quicklist {
    quicklistNode *head;
    quicklistNode *tail;
    unsigned long count;        /* total count of all entries in all ziplists */
    unsigned long len;          /* number of quicklistNodes */
    int fill : QL_FILL_BITS;              /* fill factor for individual nodes */
    unsigned int compress : QL_COMP_BITS; /* depth of end nodes not to compress;0=off */
    unsigned int bookmark_count: QL_BM_BITS;
    quicklistBookmark bookmarks[];
} quicklist;

typedef struct quicklistIter {
    const quicklist *quicklist;
    quicklistNode *current;
    unsigned char *zi;
    long offset; /* offset in current ziplist */
    int direction;
} quicklistIter;

typedef struct quicklistEntry {
    const quicklist *quicklist;
    quicklistNode *node;
    unsigned char *zi;
    unsigned char *value;
    long long longval;
    unsigned int sz;
    int offset;
} quicklistEntry;
```

![image-20211108151414983](E:\Work\Document\Distribute\Redis\picture\Quicklist StructPic.png)

​																						图1.6.1　quicklist结构图  

#### 1.7 Stream

##### 1.7.1 listpack

##### 1.7.2 Rax

​		只有一个key(foo)的Rax树如图1.7.2-1所示，其中中括号代表非压缩节点，双引号代表压缩节点（压缩节点，非压缩节点下文将详细介绍），(iskey=1)代表该节点存储了一个key，如无特别说明，后续部分的图，也是如此  

![image-20211108192608834](E:\Work\Document\Distribute\Redis\picture\Rax-TwoNodeStruct.png)

​													图1.7.2-1　含有foobar、footer两个key的Rax  

​		值得注意的是，对于非压缩节点，其内部字符是按照字典序排序的，例如上述第二个节点，含有2个字符b、t，二者是按照字典序排列的。  

###### 1.7.2.1  关键结构介绍

​		rax结构代表一个Rax树，它包含3个字段，指向头节点的指针，元素个数（即key的个数）以及节点个数。  

```c++
#define RAX_NODE_MAX_SIZE ((1<<29)-1)
typedef struct raxNode {
    uint32_t iskey:1;     /* Does this node contain a key? */
    uint32_t isnull:1;    /* Associated value is NULL (don't store it). */
    uint32_t iscompr:1;   /* Node is compressed. */
    uint32_t size:29;     /* Number of children, or compressed string len. */
    unsigned char data[];
} raxNode;

typedef struct rax {
    raxNode *head;
    uint64_t numele;
    uint64_t numnodes;
} rax;
raxNode分为2类，压缩节点和非压缩节点，下面分别进行介绍。
```

1）压缩节点 。我们假设该节点存储的内容为字符串ABC，其结构图如图1.7.2-2所示。



xxx



#### 1.9 命令处理周期

##### 1.9.1 基本知识

​		Redis服务器是典型的事件驱动程序，因此事件处理显得尤为重要，而Redis将事件分为两大类：文件事件与时间事件。文件事件即socket的读写事件，时间事件用于处理一些需要周期性执行的定时任务，本章将对这两种事件作详细介绍。

###### 1.9.1.1 对象结构体

Redis是一个key-value型数据库，key只能是字符串，value可以是字符串、列表、集合、有序集合和散列表，这5种数据类型用结构体robj表示，我们称之为Redis对象。结构体robj的type字段表示对象类型，5种Redis是一个key-value型数据库，key只能是字符串，value可以是字符串、列表、集合、有序集合和散列表，这5种数据类型用结构体robj表示，我们称之为Redis对象。结构体robj的type字段表示对象类型，5种对象类型在server.h文件中定义：  对象类型在server.h文件中定义：  

```c++
#define OBJ_STRING 0
#define OBJ_LIST 1
#define OBJ_SET 2
#define OBJ_ZSET 3
#define OBJ_HASH 4
```

![image-20211110195859458](E:\Work\Document\Distribute\Redis\picture\RedisStructEncoding.png)

  																								表1.9.1-1　对象编码类型表  
