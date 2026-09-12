#ifndef VECTOR_CPP_INCLUDED
#define VECTOR_CPP_INCLUDED

#include "vector.h"     //单独编译本文件时也能拿到类的声明

template<typename Object>
Vector<Object>::Vector ( int initSize ) :
    theSize { initSize },
    theCapacity { initSize + SPARE_CAPACITY }
{
    objects = new Object [ theCapacity ];
}

template<typename Object>
Vector<Object>::Vector ( const Vector & rhs ) :
//能用初始化列表就用初始化列表
    theSize { rhs.theSize }, theCapacity { rhs.theCapacity },
    objects { nullptr }    //不要指向传入参数的地址，要重新开辟一块内存
{
    objects = new Object [ theCapacity ];
    for ( int i = 0; i < theSize; i++ )
    {
        objects[i] = rhs.objects[i];    //p[i] <=> *(p + i)
    }
}

template<typename Object>
Vector<Object>::Vector ( Vector && rhs ) :
    theSize { rhs.theSize }, theCapacity { rhs.theCapacity },
    objects { rhs.objects }
{
    //把参数清空
    rhs.objects = nullptr;
    rhs.theSize = 0;
    rhs.theCapacity = 0;
}

template<typename Object>
Vector<Object> & Vector<Object>::operator = ( const Vector & rhs )
{
    //不可修改传入参数，故定义新的变量
    if ( this != &rhs )      //自赋值检查
    {
        Vector temp = rhs;
        swap( *this, temp );    //不可以返回temp因为这是局部变量
    }
    //=运算返回值是左值，*this也是左值，返回引用是为了避免深拷贝浪费资源
    return *this;
}

template<typename Object>
Vector<Object> & Vector<Object>::operator= ( Vector && rhs )
{
    swap( theSize, rhs.theSize );
    swap( theCapacity, rhs.theCapacity );
    swap( objects, rhs.objects );
    return *this;
}

template<typename Object>
Vector<Object>::~Vector()
{
    delete [] objects;    //数组要用 delete []
}

template<typename Object>
void Vector<Object>::reserve(int newCapacity)
{
    if ( newCapacity < theSize )    //新容量不可以比容器大小还要小
        return;

    Object * newPoint = new Object[ newCapacity ];  //申请新内存
    for (int i = 0; i < theSize; i++)
    {
        newPoint [i] = move( objects[i] );
    }

    theCapacity = newCapacity;
    swap(objects,newPoint);     //交换指针
    delete [] newPoint;         //删除旧地址
}

template<typename Object>
void Vector<Object>::resize(int newSize)
{
    if ( newSize < 0 )              //尺寸不可能为负：直接忽略，保住 0 <= theSize
        return;
    if ( newSize > theCapacity )
        reserve ( 2*newSize );
    theSize = newSize;
}

template<typename Object>
Object & Vector<Object>::operator [] (int idx)
{
    return objects[idx];
}

template<typename Object>
const Object & Vector<Object>::operator [] (int idx) const
{
    return objects[idx];
}

template<typename Object>
bool Vector<Object>::empty() const
{
    return size() == 0;
}

template<typename Object>
int Vector<Object>::size() const
{
    return theSize;
}

template<typename Object>
int Vector<Object>::capacity() const
{
    return theCapacity;
}

template<typename Object>
void Vector<Object>::push_back(const Object & ele)
{
    if ( theSize == theCapacity )
        reserve( 2*theCapacity + 1 );   //+1是为了防止清空容器后无法扩容
    objects[theSize++] = ele;
}

template<typename Object>
void Vector<Object>::push_back(Object && ele)
{
    if ( theSize == theCapacity )
        reserve( 2*theCapacity + 1 );
    //move函数本身不搬运资源，只是将有名字的右值引用转换为右值
    objects[theSize++] = move(ele);
}

template<typename Object>
void Vector<Object>::pop_back()
{
    if ( empty() )      //空容器直接不操作，防止 theSize 变成 -1
        return;
    theSize--;
}

template<typename Object>
const Object & Vector<Object>::back () const
{
    if ( empty() )      //引用必须绑定到真实对象，没法"什么都不返回"，只能报错
        throw out_of_range( "back(): empty vector" );
    return objects[theSize - 1];
}

template<typename Object>
typename Vector<Object>::iterator Vector<Object>::begin()
{
    return & objects[0];
}

template<typename Object>
typename Vector<Object>::const_iterator Vector<Object>::begin() const
{
    return & objects[0];
}

template<typename Object>
typename Vector<Object>::iterator Vector<Object>::end()
{
    return & objects[ theSize ];
    //本质上是 &*( objects + theSize ) = objects + theSize，故不是UB
}

template<typename Object>
typename Vector<Object>::const_iterator Vector<Object>::end() const
{
    return & objects[ theSize ];
}

#endif