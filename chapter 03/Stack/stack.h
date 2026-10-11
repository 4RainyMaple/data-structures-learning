#ifndef STACK_H
#define STACK_H

template<typename Object>
class Stack
{
private:
    Object * objects;
    int theSize;
    int theCapacity;

    // ==================== ⚙️ 内部辅助函数 ====================
    //扩容时重新申请内存，再把原来的元素搬过去
    void reserve ( int newCapacity );

public:
    // ==================== 🔵 构造与析构 ====================
    //默认构造函数
    Stack();

    //拷贝构造函数
    Stack ( const Stack & rhs );

    //移动构造函数：接管原栈的数组，再把原栈置空
    Stack ( Stack && rhs );

    //析构函数：释放动态申请的数组
    ~Stack();

    // ==================== 🟢 赋值操作 ====================
    //拷贝赋值：先复制，再交换内容
    Stack & operator = ( const Stack & rhs );

    //移动赋值
    Stack & operator = ( Stack && rhs );

    // ==================== 🟠 容量查询 ====================
    //判断栈是否为空
    bool empty() const;

    //返回栈中元素个数
    int size() const;

    // ==================== 🟣 元素访问 ====================
    //返回栈顶元素；空栈没有栈顶，抛出异常提醒调用者
    Object & top();

    //常量栈只能读取栈顶元素
    const Object & top() const;

    // ==================== 🔴 增删元素 ====================
    //添加栈顶元素
    void push ( const Object & ele );

    //添加栈顶元素，右值可以移动其中的资源
    void push ( Object && ele );

    //删除栈顶元素
    void pop();
};

//类模板的实现需要对使用者可见
#include "stack.cpp"

#endif
