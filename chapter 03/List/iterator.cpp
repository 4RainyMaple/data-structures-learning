#ifndef LIST_ITERATOR_CPP_INCLUDED
#define LIST_ITERATOR_CPP_INCLUDED

#include "iterator.h"

template<typename Object>
iterator<Object>::iterator () : const_iterator<Object> {} {}

template<typename Object>
iterator<Object>::iterator ( const ::List<Object> & lst, Node<Object> * p,
                                        Node<Object> * first, Node<Object> * last ) :
const_iterator<Object> {lst, p, first, last} {}  //初始化列表调用基类构造函数更方便

template<typename Object>
Object & iterator<Object>::operator * ()
{
    return const_iterator<Object>::retrieve();
}

template<typename Object>
const Object & iterator<Object>::operator * () const
{
    return const_iterator<Object>::operator * ();
}

template<typename Object>
iterator<Object> & iterator<Object>::operator ++ ()
{
    const_iterator<Object>::operator ++ ();
    return *this;
}

template<typename Object>
iterator<Object> iterator<Object>::operator ++ ( int )
{
    iterator old = *this;
    ++(*this);
    return old;
}

//子类调用++或--，只操作，不接收返回值，也不改变子类自身类型，故可直接调用基类函数
template<typename Object>
iterator<Object> & iterator<Object>::operator -- ()
{
    const_iterator<Object>::operator -- ();
    return *this;
}

template<typename Object>
iterator<Object> iterator<Object>::operator -- ( int )
{
    iterator old = *this;
    --(*this);
    return old;
}

//下面两个函数需要创建副本，故不可直接调用基类接口，需要重新实现一遍
template<typename Object>
iterator<Object> iterator<Object>::operator + ( int k ) const
{
    iterator temp = *this;
    for ( int i = 0; i < k; ++i )
        ++temp;
    return temp;
}

template<typename Object>
iterator<Object> iterator<Object>::operator - ( int k ) const
{
    iterator temp = *this;
    for ( int i = 0; i < k; ++i )
        --temp;
    return temp;
}
#endif
