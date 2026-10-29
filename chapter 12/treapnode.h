#ifndef TREAPNODE_H
#define TREAPNODE_H

#include<climits>
#include<utility>

template<typename Comparable>
struct TreapNode
{
    Comparable element;
    int priority;
    TreapNode * left;
    TreapNode * right;

    // 拷贝构造
    TreapNode( const Comparable & ele, int p, TreapNode * l = nullptr, TreapNode * r = nullptr ) :
    element { ele } , priority { p } , left { l } , right { r } {}

    // 移动构造
    TreapNode( Comparable && ele, int p, TreapNode * l = nullptr, TreapNode * r = nullptr ) :
    element { std::move(ele) } , priority { p } , left { l } , right { r } {}
};

#endif
