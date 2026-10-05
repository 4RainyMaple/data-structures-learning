#ifndef CHAPTER6_SKEWHEAP_CPP
#define CHAPTER6_SKEWHEAP_CPP

#include "SkewHeap.h"
#include <utility>
#include <algorithm>
#include <stdexcept>

template <typename Comparable>
SkewHeap<Comparable>::SkewHeap():root{nullptr} {}

template <typename Comparable>
SkewHeap<Comparable>::SkewHeap(const SkewHeap &rhs):
root {clone(rhs.root)}   {}

template <typename Comparable>
SkewHeap<Comparable>::SkewHeap(SkewHeap &&rhs):
root {std::move(rhs.root)}  
{
    rhs.root = nullptr; //指针不再需要
}

template <typename Comparable>
SkewHeap<Comparable>::~SkewHeap()
{
    reclaimMemory(root);
}

template <typename Comparable>
SkewHeap<Comparable> & SkewHeap<Comparable>::operator=(const SkewHeap &rhs)
{
    if ( this == &rhs )
        return *this;

    SkewHeap temp(rhs);
    std::swap(temp.root,this->root);
    return *this;
}

template <typename Comparable>
SkewHeap<Comparable> & SkewHeap<Comparable>::operator=(SkewHeap &&rhs)
{
    if ( this == &rhs )
        return *this;

    std::swap(this->root,rhs.root);
    return *this;
}

template <typename Comparable>
bool SkewHeap<Comparable>::isEmpty() const
{
    return root == nullptr;
}

template <typename Comparable>
const Comparable & SkewHeap<Comparable>::findMin() const
{
    if ( isEmpty() )
        throw std::underflow_error("empty heap");
    return root->element;
}

template <typename Comparable>
void SkewHeap<Comparable>::insert(const Comparable &x)
{
    //开辟新内存
    SkewNode * temp = new SkewNode(x);
    root = merge(temp,root);
}

template <typename Comparable>
void SkewHeap<Comparable>::insert(Comparable &&x)
{
    SkewNode * temp = new SkewNode(std::move(x));
    root = merge(temp,root);
}

template <typename Comparable>
Comparable SkewHeap<Comparable>::deleteMin()
{
    if ( isEmpty() )
        throw std::underflow_error("empty heap");
    Comparable ret = root->element;
    SkewNode * oldroot = root;
    root = merge ( root->left, root->right );
    delete oldroot;     //把旧节点的内存删掉
    return ret;
}

template <typename Comparable>
void SkewHeap<Comparable>::makeEmpty()
{
    reclaimMemory(root);
    root = nullptr;     //旧的根指针不再需要
}

template <typename Comparable>
void SkewHeap<Comparable>::merge(SkewHeap &rhs)
{
    if ( this == &rhs )
        return;
    root = merge(root, rhs.root);
    rhs.root = nullptr; //防止公用节点重复释放
}

template <typename Comparable>
SkewHeap<Comparable>::SkewNode::SkewNode(const Comparable &e, SkewNode *lt, SkewNode *rt):
element{e} , left {lt} , right {rt} {}

template <typename Comparable>
SkewHeap<Comparable>::SkewNode::SkewNode(Comparable &&e, SkewNode *lt, SkewNode *rt):
element{std::move(e)} , left {lt} , right {rt} {}

template <typename Comparable>
typename SkewHeap<Comparable>::SkewNode * SkewHeap<Comparable>::merge(SkewNode *h1, SkewNode *h2)
{
    if ( !h1 )
        return h2;
    if ( !h2 )
        return h1;

    //保证h1的根更小
    if ( h1->element > h2->element )
        std::swap(h1,h2);

    h1->right = merge(h1->right,h2);
    swapChildren(h1);
    return h1;
}

template <typename Comparable>
void SkewHeap<Comparable>::swapChildren(SkewNode *t)
{
    if ( t == nullptr )
        return;
    std::swap( t->left, t->right );
}

template <typename Comparable>
void SkewHeap<Comparable>::reclaimMemory(SkewNode *t)
{
    if ( !t )
        return;
    
    reclaimMemory(t->left);
    reclaimMemory(t->right);
    //内存和指针都不再需要
    delete t;
    t = nullptr;
}

template <typename Comparable>
typename SkewHeap<Comparable>::SkewNode * SkewHeap<Comparable>::clone(SkewNode *t) const
{
    if ( !t )
        return nullptr;
    SkewNode * temp = new SkewNode(t->element);
    temp->left = clone(t->left);
    temp->right = clone(t->right);
    return temp;
}

#endif
