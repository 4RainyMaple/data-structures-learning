#ifndef LIST_CONST_ITERATOR_CPP_INCLUDED
#define LIST_CONST_ITERATOR_CPP_INCLUDED

#include "const_iterator.h"

    template<typename Object>
    Object & const_iterator<Object>::retrieve() const
    {
        assertIsValid();
        //end()指向尾哨兵节点，不能解引用
        if ( current == tail )
            throw IteratorOutOfBoundsException{};
        return current->data;
    }

    template<typename Object>
    void const_iterator<Object>::assertIsValid() const
    {
        if ( theList == nullptr || current == nullptr || current == head )
            throw IteratorOutOfBoundsException{};
    }

    template<typename Object>
    const_iterator<Object>::const_iterator () :
    theList {nullptr}, current {nullptr}, head {nullptr}, tail {nullptr} {}

    template<typename Object>
    const_iterator<Object>::const_iterator ( const ::List<Object> & lst, Node<Object> * p,
                                             Node<Object> * first, Node<Object> * last ) :
    theList {&lst}, current {p}, head {first}, tail {last} {}

    template<typename Object>
    const Object & const_iterator<Object>::operator * () const
    {
        return retrieve();
    }

    template<typename Object>
    const_iterator<Object> & const_iterator<Object>::operator ++ ()
    {
        assertIsValid();
        //end()已经是尾哨兵，不能再向后移动
        if ( current == tail )
            throw IteratorOutOfBoundsException{};
        current = current->next;
        return *this;
    }

    template<typename Object>
    const_iterator<Object> const_iterator<Object>::operator ++ ( int )
    {
        const_iterator old = *this;
        ++(*this);
        return old;
    }

    template<typename Object>
    const_iterator<Object> & const_iterator<Object>::operator -- ()
    {
        assertIsValid();
        //--begin()和--end()位于不同边界；空链表的end()也不能递减
        if ( current->prev == head )
            throw IteratorOutOfBoundsException{};
        current = current->prev;
        return *this;
    }

    template<typename Object>
    const_iterator<Object> const_iterator<Object>::operator -- ( int )
    {
        const_iterator old = *this;
        --(*this);
        return old;
    }

    template<typename Object>
    bool const_iterator<Object>::operator == ( const const_iterator & rhs ) const
    {
        return current == rhs.current;
    }

    template<typename Object>
    bool const_iterator<Object>::operator != ( const const_iterator & rhs ) const
    {
        return !( *this == rhs );
    }
#endif
