#ifndef LIST_CONST_ITERATOR_CPP_INCLUDED
#define LIST_CONST_ITERATOR_CPP_INCLUDED

#include "const_iterator.h"

namespace ListDetail
{
    template<typename Object>
    Object & ConstIterator<Object>::retrieve() const
    {
        assertIsValid();
        //end()指向尾哨兵节点，不能解引用
        if ( current == tail )
            throw IteratorOutOfBoundsException{};
        return current->data;
    }

    template<typename Object>
    void ConstIterator<Object>::assertIsValid() const
    {
        if ( theList == nullptr || current == nullptr || current == head )
            throw IteratorOutOfBoundsException{};
    }

    template<typename Object>
    ConstIterator<Object>::ConstIterator () :
    theList {nullptr}, current {nullptr}, head {nullptr}, tail {nullptr} {}

    template<typename Object>
    ConstIterator<Object>::ConstIterator ( const ::List<Object> & lst, Node<Object> * p,
                                           Node<Object> * first, Node<Object> * last ) :
    theList {&lst}, current {p}, head {first}, tail {last} {}

    template<typename Object>
    const Object & ConstIterator<Object>::operator * () const
    {
        return retrieve();
    }

    template<typename Object>
    ConstIterator<Object> & ConstIterator<Object>::operator ++ ()
    {
        assertIsValid();
        //end()已经是尾哨兵，不能再向后移动
        if ( current == tail )
            throw IteratorOutOfBoundsException{};
        current = current->next;
        return *this;
    }

    template<typename Object>
    ConstIterator<Object> ConstIterator<Object>::operator ++ ( int )
    {
        ConstIterator old = *this;
        ++(*this);
        return old;
    }

    template<typename Object>
    ConstIterator<Object> & ConstIterator<Object>::operator -- ()
    {
        assertIsValid();
        //--begin()和--end()位于不同边界；空链表的end()也不能递减
        if ( current->prev == head )
            throw IteratorOutOfBoundsException{};
        current = current->prev;
        return *this;
    }

    template<typename Object>
    ConstIterator<Object> ConstIterator<Object>::operator -- ( int )
    {
        ConstIterator old = *this;
        --(*this);
        return old;
    }

    template<typename Object>
    bool ConstIterator<Object>::operator == ( const ConstIterator & rhs ) const
    {
        return current == rhs.current;
    }

    template<typename Object>
    bool ConstIterator<Object>::operator != ( const ConstIterator & rhs ) const
    {
        return !( *this == rhs );
    }
}

#endif
