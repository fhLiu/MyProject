## 										Redis6.2.6 通信部份源码解读

### 1. Main 线程

​		遵循one loop one thread原则，在aeMain 函数中创建一个大的loop， loopevent为aeEventLoop

入参基本参数：

```c++
(gdb) p *eventLoop
$1 = {maxfd = 11, setsize = 10128, timeEventNextId = 1, events = 0x7ffff6cfc1c0, fired = 0x7ffff6d4d780, timeEventHead = 0x7ffff6c15140, stop = 0, apidata = 0x7ffff6ca0d80, beforesleep = 0x439ca1 <beforeSleep>, 
  aftersleep = 0x439e62 <afterSleep>, flags = 0}

(gdb) p *(eventLoop->events)
$2 = {mask = 0, rfileProc = 0x0, wfileProc = 0x0, clientData = 0x0}

(gdb) p *(eventLoop->fired)
$3 = {fd = 0, mask = 0}

(gdb) p *(eventLoop->timeEventHead)
$5 = {id = 0, when = 6326289892, timeProc = 0x4391f8 <serverCron>, finalizerProc = 0x0, clientData = 0x0, prev = 0x0, next = 0x0, refcount = 0}

(gdb) p *((aeApiState*)eventLoop->apidata)
$8 = {epfd = 9, events = 0x7ffff6d62940}
(gdb) p *(((aeApiState*)eventLoop->apidata)->events)
$9 = {events = 0, data = {ptr = 0x0, fd = 0, u32 = 0, u64 = 0}}

eventLoop = server.el
void aeMain(aeEventLoop *eventLoop) {
    eventLoop->stop = 0;
    while (!eventLoop->stop) {
        aeProcessEvents(eventLoop, AE_ALL_EVENTS|
                                   AE_CALL_BEFORE_SLEEP|
                                   AE_CALL_AFTER_SLEEP);
    }
}
```



```c++


Redis 消息的来龙去脉，以 set myname xxx为例讲述：set myname fhLiu
大部分都是围绕eventLoop 整个循环事件触发的
1. 首先讲解创建客户端连接

2. 连接创建之后，客户端发送数据，可读事件触发


epoll_wait						//等待客户端发送可读事件，及客户端命令
aeProcessEvents
    fe->rfileProc(eventLoop,fd,fe->clientData,mask);
	回调函数为：
    (gdb) p *fe
	$5 = {mask = 1, rfileProc = 0x50316c <connSocketEventHandler>, wfileProc = 0x0, 			clientData = 0x7ffff6c15180}
connSocketEventHandler			//收到客户端可读事件后，回调该函数处理具体的客户端信息
/*
    int invert = conn->flags & CONN_FLAG_WRITE_BARRIER;

    int call_write = (mask & AE_WRITABLE) && conn->write_handler;
    int call_read = (mask & AE_READABLE) && conn->read_handler;

    /* Handle normal I/O flows */
    if (!invert && call_read) {
        if (!callHandler(conn, conn->read_handler)) return;
*/
readQueryFromClient			//callHandler = readQueryFromClient
processInputBuffer			//具体处理输入数据
processMultibulkBuffer
processCommandAndResetClient
processCommand
commandProcessed
```

