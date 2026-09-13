#ifndef LIST_CONST_ITERATOR_H
#define LIST_CONST_ITERATOR_H

#include "node.h"
#include <stdexcept>

template<typename Object>
class List;

namespace ListDetail
{
    //迭代器保护机制使用的异常
    class IteratorOutOfBoundsException : public std::out_of_range
    {
    public:
        IteratorOutOfBoundsException () : std::out_of_range ( "Iterator out of bounds" ) {}
    };

    //只读迭代器：可移动迭代位置，但不能通过它修改元素
    template<typename Object>
    class ConstIterator
    {
    protected:
        //记录所属链表、当前节点和两端哨兵
        const ::List<Object> * theList;
        Node<Object> * current;
        Node<Object> * head;
        Node<Object> * tail;

        Object & retrieve() const;
        void assertIsValid() const;

        //只有List能把节点位置构造成迭代器
        ConstIterator ( const ::List<Object> & lst, Node<Object> * p,
                        Node<Object> * first, Node<Object> * last );

        friend class ::List<Object>;

    public:
        //默认构造的迭代器暂时不关联任何链表
        ConstIterator ();

        const Object & operator * () const;

        //前置和后置自增
        ConstIterator & operator ++ ();
        ConstIterator operator ++ ( int );

        //前置和后置自减
        ConstIterator & operator -- ();
        ConstIterator operator -- ( int );

        bool operator == ( const ConstIterator & rhs ) const;
        bool operator != ( const ConstIterator & rhs ) const;
    };
}

//类模板的实现需要对使用者可见
#include "const_iterator.cpp"

#endif
