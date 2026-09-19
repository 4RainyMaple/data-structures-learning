#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include "const_iterator.h"

//可读写迭代器继承只读迭代器的移动和比较功能
template<typename Object>
class iterator : public const_iterator<Object>
{
protected:
    //只有List能构造指向具体节点的迭代器
    iterator ( const ::List<Object> & lst, Node<Object> * p,
                   Node<Object> * first, Node<Object> * last );

    friend class ::List<Object>;

public:
    iterator ();

    Object & operator * ();
    const Object & operator * () const;

    iterator & operator ++ ();
    iterator operator ++ ( int );
    iterator & operator -- ();
    iterator operator -- ( int );

    //返回沿next方向移动k个位置后的可读写迭代器，不改变当前迭代器（k为非负数）
    iterator operator + ( int k ) const;
    //返回沿prev方向移动k个位置后的可读写迭代器，不改变当前迭代器（k为非负数）
    iterator operator - ( int k ) const;
};

//类模板的实现需要对使用者可见
#include "iterator.cpp"

#endif
