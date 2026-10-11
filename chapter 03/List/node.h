#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <utility>

//双向链表中的节点
template<typename Object>
struct Node
{
    Object data;
    Node * prev;
    Node * next;

    //默认+有参构造函数，Object{}是Object的默认值，比如int{} = 0
    Node ( const Object & d = Object{}, Node * p = nullptr, Node * n = nullptr ):
    data {d}, prev {p}, next {n}    {}

    //参数为右值引用
    //“默认构造”这个能力只能由其中一个重载承担
    Node ( Object && d, Node * p = nullptr, Node * n = nullptr ):
    data {std::move(d)}, prev {p}, next {n}    {}
};

#endif
