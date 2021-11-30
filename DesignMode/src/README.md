本示例代码不包含原型设计模式，C++中原型设计模式感觉意义不是很大，类似于重载=操作符，拷贝构造函数

注意浅拷贝和深拷贝
T& operator=(const T& rh)
{
    if(this == &rh)
        return *this;
    this.A = rh.A;
    this.B = rh.B;
    if(th.C)
    {
        this.C = new C();
        this.C = rh.C;  //type C 实现了自己的拷贝构造函数
    }
}