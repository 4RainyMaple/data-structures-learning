#ifndef QUEUE_CPP_INCLUDED
#define QUEUE_CPP_INCLUDED

#include "queue.h"
#include<utility>
#include<stdexcept>

template<typename Object>
void Queue<Object>::reserve ( int newCapacity )
{
    if ( newCapacity <= theCapacity )
        return;

    Object * newObjects = new Object [ newCapacity ];
    for ( int i = frontIndex; i < backIndex; ++i )
    {
        //只搬运还在队列中的元素，并放到新数组的相同位置
        newObjects[i] = std::move( objects[i] );
    }
    delete [] objects;
    objects = newObjects;
    theCapacity = newCapacity;
    //元素的位置没有改变，所以队头和队尾下标也不用改变
}

template<typename Object>
Queue<Object>::Queue() :
objects {nullptr} , theSize {0} , theCapacity {0} ,
frontIndex {0} , backIndex {0}
{}

template<typename Object>
Queue<Object>::Queue ( const Queue & rhs ) :
objects {nullptr} , theSize {rhs.theSize} , theCapacity {rhs.theCapacity} ,
frontIndex {rhs.frontIndex} , backIndex {rhs.backIndex}
{
    //空队列也可能有保留的容量，分配空间要与记录的容量一致
    if ( theCapacity > 0 )
        objects = new Object [theCapacity];

    for ( int i = frontIndex; i < backIndex; ++i )
    {
        //有效元素保留原来的位置，复制后的下标也与原队列一致
        objects[i] = rhs.objects[i];
    }
}
template<typename Object>
Queue<Object>::Queue ( Queue && rhs ) :
objects {rhs.objects} , theSize {rhs.theSize} , theCapacity {rhs.theCapacity} ,
frontIndex {rhs.frontIndex} , backIndex {rhs.backIndex}
{
    rhs.theSize = 0;
    rhs.theCapacity = 0;
    rhs.backIndex = 0;
    rhs.frontIndex = 0;
    rhs.objects = nullptr;
}

template<typename Object>
Queue<Object>::~Queue()
{
    delete [] objects;
}

template<typename Object>
Queue<Object> & Queue<Object>::operator = ( const Queue & rhs )
{
    if ( this != &rhs ) //不要比较内容，要比较地址！！！！
    {
        //不能破坏rhs才要找temp
        Queue temp = rhs;
        std::swap( objects, temp.objects );
        std::swap( theCapacity, temp.theCapacity );
        std::swap( theSize, temp.theSize );
        std::swap( frontIndex, temp.frontIndex );
        std::swap( backIndex, temp.backIndex );
    }
    return *this;
}

template<typename Object>
Queue<Object> & Queue<Object>::operator = ( Queue && rhs )
{
    std::swap( objects, rhs.objects);
    std::swap( theCapacity, rhs.theCapacity );
    std::swap( theSize, rhs.theSize );
    std::swap( frontIndex, rhs.frontIndex );
    std::swap( backIndex, rhs.backIndex );
    return *this;
}

template<typename Object>
bool Queue<Object>::empty() const
{
    return size() == 0;
}

template<typename Object>
int Queue<Object>::size() const
{
    return theSize;
}

template<typename Object>
void Queue<Object>::clear()
{
    while ( size() != 0 )
    {
        dequeue();
    }
    //此时队头和队尾下标相等，下次入队继续往后写
}

template<typename Object>
void Queue<Object>::enqueue ( const Object & ele )
{
    //出队不会让队尾后退，因此要根据写入位置判断是否需要扩容
    if ( backIndex == theCapacity )
    {
        //ele可能引用本队列的元素，扩容前先保存，避免旧数组释放后引用失效
        Object temp = ele;
        reserve( 2*theCapacity + 1 );
        objects[backIndex] = std::move( temp );
    }
    else
        objects[backIndex] = ele;

    //先写入，再将下一次写入位置向后移动
    ++backIndex;
    ++theSize;
}

template<typename Object>
void Queue<Object>::enqueue ( Object && ele )
{
    if ( backIndex == theCapacity )
    {
        //右值也可能来自本队列，先接住它的资源再扩容
        Object temp = std::move( ele );
        reserve( 2*theCapacity + 1 );
        objects[backIndex] = std::move( temp );
    }
    else
        objects[backIndex] = std::move( ele );

    ++backIndex;
    ++theSize;
}

template<typename Object>
void Queue<Object>::dequeue()
{
    if ( size() == 0 )
        throw std::out_of_range("dequeue(): empty queue");
    --theSize;
    //不用删除数组中的对象，队头后移后，该位置就不再属于队列
    ++frontIndex;
}

template<typename Object>
Object & Queue<Object>::front()
{
    if ( size() == 0 )
        throw std::out_of_range("front(): empty queue");
    return objects[frontIndex];
}

template<typename Object>
const Object & Queue<Object>::front() const
{
    if ( size() == 0 )
        throw std::out_of_range("front(): empty queue");
    return objects[frontIndex];
}

#endif
