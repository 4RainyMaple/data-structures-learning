#ifndef LIST_ITERATOR_CPP_INCLUDED
#define LIST_ITERATOR_CPP_INCLUDED

#include "iterator.h"

namespace ListDetail
{
    template<typename Object>
    Iterator<Object>::Iterator () : ConstIterator<Object> {} {}

    template<typename Object>
    Iterator<Object>::Iterator ( const ::List<Object> & lst, Node<Object> * p,
                                 Node<Object> * first, Node<Object> * last ) :
    ConstIterator<Object> {lst, p, first, last} {}

    template<typename Object>
    Object & Iterator<Object>::operator * ()
    {
        return ConstIterator<Object>::retrieve();
    }

    template<typename Object>
    const Object & Iterator<Object>::operator * () const
    {
        return ConstIterator<Object>::operator * ();
    }

    template<typename Object>
    Iterator<Object> & Iterator<Object>::operator ++ ()
    {
        ConstIterator<Object>::operator ++ ();
        return *this;
    }

    template<typename Object>
    Iterator<Object> Iterator<Object>::operator ++ ( int )
    {
        Iterator old = *this;
        ++(*this);
        return old;
    }

    template<typename Object>
    Iterator<Object> & Iterator<Object>::operator -- ()
    {
        ConstIterator<Object>::operator -- ();
        return *this;
    }

    template<typename Object>
    Iterator<Object> Iterator<Object>::operator -- ( int )
    {
        Iterator old = *this;
        --(*this);
        return old;
    }
}

#endif
