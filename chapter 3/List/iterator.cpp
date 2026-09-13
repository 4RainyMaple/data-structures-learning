#ifndef LIST_ITERATOR_CPP_INCLUDED
#define LIST_ITERATOR_CPP_INCLUDED

#include "iterator.h"

    template<typename Object>
    ListIterator<Object>::ListIterator () : const_iterator<Object> {} {}

    template<typename Object>
    ListIterator<Object>::ListIterator ( const ::List<Object> & lst, Node<Object> * p,
                                         Node<Object> * first, Node<Object> * last ) :
    const_iterator<Object> {lst, p, first, last} {}  //初始化列表调用基类构造函数更方便

    template<typename Object>
    Object & ListIterator<Object>::operator * ()
    {
        return const_iterator<Object>::retrieve();
    }

    template<typename Object>
    const Object & ListIterator<Object>::operator * () const
    {
        return const_iterator<Object>::operator * ();
    }

    template<typename Object>
    ListIterator<Object> & ListIterator<Object>::operator ++ ()
    {
        const_iterator<Object>::operator ++ ();
        return *this;
    }

    template<typename Object>
    ListIterator<Object> ListIterator<Object>::operator ++ ( int )
    {
        ListIterator old = *this;
        ++(*this);
        return old;
    }

    template<typename Object>
    ListIterator<Object> & ListIterator<Object>::operator -- ()
    {
        const_iterator<Object>::operator -- ();
        return *this;
    }

    template<typename Object>
    ListIterator<Object> ListIterator<Object>::operator -- ( int )
    {
        ListIterator old = *this;
        --(*this);
        return old;
    }
#endif
