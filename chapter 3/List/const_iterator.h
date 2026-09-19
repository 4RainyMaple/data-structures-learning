#ifndef LIST_CONST_ITERATOR_H
#define LIST_CONST_ITERATOR_H

#include "node.h"
#include <stdexcept>

template<typename Object>
class List;

//只读迭代器：可移动迭代位置，但不能通过它修改元素
template<typename Object>
class const_iterator
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
    const_iterator ( const ::List<Object> & lst, Node<Object> * p,
                     Node<Object> * first, Node<Object> * last );

    friend class ::List<Object>;

public:
    //默认构造的迭代器暂时不关联任何链表
    const_iterator ();

    const Object & operator * () const;

    //前置和后置自增
    const_iterator & operator ++ ();
    const_iterator operator ++ ( int );

    //前置和后置自减
    const_iterator & operator -- ();
    const_iterator operator -- ( int );

    //返回沿next方向移动k个位置后的迭代器，不改变当前迭代器（k为非负数）
    const_iterator operator + ( int k ) const;
    //返回沿prev方向移动k个位置后的迭代器，不改变当前迭代器（k为非负数）
    const_iterator operator - ( int k ) const;

    bool operator == ( const const_iterator & rhs ) const;
    bool operator != ( const const_iterator & rhs ) const;
};

//类模板的实现需要对使用者可见
#include "const_iterator.cpp"

#endif
