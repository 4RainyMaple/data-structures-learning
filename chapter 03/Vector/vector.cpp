#ifndef VECTOR_CPP_INCLUDED
#define VECTOR_CPP_INCLUDED

#include "vector.h"     //单独编译本文件时也能拿到类的声明

// ==================== 🔵 构造与析构 ====================
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
Vector<Object>::~Vector()
{
    delete [] objects;    //数组要用 delete []
}

// ==================== 🟢 赋值操作 ====================
template<typename Object>
Vector<Object> & Vector<Object>::operator = ( const Vector & rhs )
{
    //不可修改传入参数，故定义新的变量
    if ( this != &rhs )      //自赋值检查
    {
        Vector temp = rhs;
        swap( theSize, temp.theSize );
        swap( theCapacity, temp.theCapacity );
        swap( objects, temp.objects );
        //temp析构时会释放原来*this所持有的数组
    }
    //=运算返回值是左值，*this也是左值，返回引用是为了避免深拷贝浪费资源
    return *this;
}

template<typename Object>
Vector<Object> & Vector<Object>::operator = ( Vector && rhs )
{
    swap( theSize, rhs.theSize );
    swap( theCapacity, rhs.theCapacity );
    swap( objects, rhs.objects );
    return *this;
}

// ==================== 🟠 容量管理 ====================
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

// ==================== 🟣 元素访问 ====================
template<typename Object>
Object & Vector<Object>::operator [] (int idx)
{
    if ( idx > theSize - 1 || idx < 0 )
        throw std::out_of_range("operator[]:out of range");
    return objects[idx];
}

template<typename Object>
const Object & Vector<Object>::operator [] (int idx) const
{
    if ( idx > theSize - 1 || idx < 0 )
        throw std::out_of_range("operator[]:out of range");
    return objects[idx];
}

template<typename Object>
const Object & Vector<Object>::back () const
{
    if ( empty() )      //引用必须绑定到真实对象，没法"什么都不返回"，只能报错
        throw out_of_range( "back(): empty vector" );
    return objects[theSize - 1];
}

// ==================== 🟡 迭代器访问 ====================
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

// ==================== 🔴 增删元素 ====================
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
typename Vector<Object>::iterator Vector<Object>::insert ( iterator pos, const Object & ele )
{
    //扩容会导致原数组（指针）丢失，进而pos也失效
    int index = pos - begin();  //这里的迭代器就是指针，指针做差得到相隔元素个数
    
    if ( theSize == theCapacity )
        reserve( 2*theCapacity + 1 );

    for ( int i = theSize; i > index; --i )
        objects[i] = std::move( objects[i-1] );    
    objects[index] = ele;

    ++theSize;      //必须先赋值再增大theSize，因为循环里涉及
    return begin() + index;
}

template<typename Object>
typename Vector<Object>::iterator Vector<Object>::insert ( iterator pos, Object && ele )
{
    int index = pos - begin();

    if ( theSize == theCapacity )
        reserve( 2*theCapacity + 1 );

    for ( int i = theSize; i > index; --i )
        objects[i] = std::move( objects[i-1] );
    objects[index] = std::move(ele);

    ++theSize;
    return begin() + index;
    
}

template<typename Object>
typename Vector<Object>::iterator Vector<Object>::erase ( iterator pos )
{
    //调用该函数后pos地址不变而指向元素改变，认为失效
    int index = pos - begin();
    for ( int i = index; i < theSize - 1; ++i )
        objects[i] = std::move( objects[i+1] );

    --theSize;
    return begin() + index;
}

template<typename Object>
typename Vector<Object>::iterator Vector<Object>::erase ( iterator from, iterator to )
{
    //先保存[from, to)中的元素个数，空区间的删除数量为0
    int count = to - from;
    for ( int i = 1; i <= count; ++i )
    {
        //删除后，后面的元素会左移到当前位置，返回的迭代器仍指向这个位置
        //因此不用再++from，也不能用原来的to作为循环终点
        from = erase(from);
    }
    //返回删除区间后第一个元素的新位置；如果删除到末尾，则这里就是新的end()
    return from;
}

// ==================== 🔷 比较操作 ====================
template<typename Object>
bool Vector<Object>:: operator == (const Vector & rhs) const
{
    auto itr1 = this->begin();
    auto itr2 = rhs.begin();
    while ( itr1 != this->end() && itr2 != rhs.end() )
    {
        if ( *itr1 != *itr2 )
            return false;

        ++itr1;
        ++itr2;
    }
    return itr1 == this->end() && itr2 == rhs.end();
}

template<typename Object>
bool Vector<Object>:: operator != (const Vector & rhs) const
{
    return ! ( *this == rhs );
}
#endif
