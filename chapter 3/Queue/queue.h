#ifndef QUEUE_H
#define QUEUE_H

template<typename Object>
class Queue
{
private:
    Object * objects;
    int theSize;
    int theCapacity;
    int frontIndex;   //队头元素的位置
    int backIndex;    //下一次入队写入的位置，到达数组末尾就扩容

    //扩容时保留有效元素原来的下标，前面已经出队的位置不再使用
    void reserve ( int newCapacity );

public:
    //构造、复制、移动和析构
    Queue();
    //拷贝构造需要申请自己的数组，再逐个复制元素
    Queue ( const Queue & rhs );
    //移动构造直接接管数组和下标，再把原队列置空
    Queue ( Queue && rhs );
    ~Queue();
    Queue & operator = ( const Queue & rhs );
    Queue & operator = ( Queue && rhs );

    //容量和清空
    bool empty() const;
    int size() const;
    void clear();

    //入队和出队，下标一直向后移动
    void enqueue ( const Object & ele );
    void enqueue ( Object && ele );
    void dequeue();

    //访问队头元素，空队列抛出out_of_range异常
    Object & front();
    const Object & front() const;
};

//类模板的实现需要对使用者可见
#include "queue.cpp"

#endif
