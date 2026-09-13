#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include "const_iterator.h"

namespace ListDetail
{
    //可读写迭代器继承只读迭代器的移动和比较功能
    template<typename Object>
    class Iterator : public ConstIterator<Object>
    {
    protected:
        //只有List能构造指向具体节点的迭代器
        Iterator ( const ::List<Object> & lst, Node<Object> * p,
                   Node<Object> * first, Node<Object> * last );

        friend class ::List<Object>;

    public:
        Iterator ();

        Object & operator * ();
        const Object & operator * () const;

        Iterator & operator ++ ();
        Iterator operator ++ ( int );
        Iterator & operator -- ();
        Iterator operator -- ( int );
    };
}

//类模板的实现需要对使用者可见
#include "iterator.cpp"

#endif
