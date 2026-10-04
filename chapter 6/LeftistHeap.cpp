#ifndef CHAPTER6_LEFTISTHEAP_CPP
#define CHAPTER6_LEFTISTHEAP_CPP

#include "LeftistHeap.h"
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <functional>

template <typename Comparable>
LeftistHeap<Comparable>::LeftistHeap():root{nullptr}{}

template <typename Comparable>
LeftistHeap<Comparable>::LeftistHeap(const LeftistHeap &rhs)
{
    //中括号内要捕获自身才能调用自身实现递归
    std::function<LeftistNode *(LeftistNode *)> clone = [&clone](LeftistNode *t) -> LeftistNode *
    {
        if (t == nullptr)
            return nullptr;
        LeftistNode *temp = new LeftistNode(t->element, nullptr, nullptr, t->npl);
        temp->left = clone(t->left);
        temp->right = clone(t->right);
        return temp;
    };
    root = clone(rhs.root);
}

template <typename Comparable>
LeftistHeap<Comparable>::LeftistHeap(LeftistHeap &&rhs):
root{std::move(rhs.root)} 
{
    rhs.root = nullptr;
}

template <typename Comparable>
LeftistHeap<Comparable>::~LeftistHeap()
{
    if ( root != nullptr )
        reclaimMemory(root);
}

template <typename Comparable>
LeftistHeap<Comparable> & LeftistHeap<Comparable>::operator=(const LeftistHeap &rhs)
{
    if ( this == &rhs )
        return *this;

    auto temp = rhs;
    std::swap( temp.root, this->root );
    return *this;
}

template <typename Comparable>
LeftistHeap<Comparable> & LeftistHeap<Comparable>::operator=(LeftistHeap &&rhs)
{
    if ( this == &rhs )
        return *this;

    std::swap( this->root, rhs.root );  //需要交换后再释放原内存，否则造成内存泄漏
    return *this;
}

template <typename Comparable>
bool LeftistHeap<Comparable>::isEmpty() const
{
    return root == nullptr;
}

template <typename Comparable>
const Comparable & LeftistHeap<Comparable>::findMin() const
{
    if ( isEmpty() )
        throw std::underflow_error("empty heap");
    return root->element;
}

template <typename Comparable>
void LeftistHeap<Comparable>::insert(const Comparable &x)
{
    //需要修改root
    root = merge( root, new LeftistNode(x) );
}

template <typename Comparable>
void LeftistHeap<Comparable>::insert(Comparable &&x)
{
    root = merge( root, new LeftistNode(std::move(x)) );
}

template <typename Comparable>
Comparable LeftistHeap<Comparable>::deleteMin()
{
    if ( isEmpty() )
        throw std::underflow_error("empty heap");
    Comparable temp = root->element;
    LeftistNode * oldroot = root;
    root = merge ( root->left, root->right );
    delete oldroot;
    return temp;
}

template <typename Comparable>
void LeftistHeap<Comparable>::makeEmpty()
{
    reclaimMemory(root);
    root = nullptr;
}

template <typename Comparable>
void LeftistHeap<Comparable>::merge(LeftistHeap &rhs)
{
    //防止合并自己
    if ( this == &rhs )
        return;
    root = merge( root, rhs.root );
    rhs.root = nullptr;
}

template <typename Comparable>
LeftistHeap<Comparable>::LeftistNode::LeftistNode(const Comparable &e, LeftistNode *lt, LeftistNode *rt, int np):
element {e} , left {lt} , right {rt} , npl {np} {}

template <typename Comparable>
LeftistHeap<Comparable>::LeftistNode::LeftistNode(Comparable &&e, LeftistNode *lt, LeftistNode *rt, int np):
element {std::move(e)} , left {lt} , right {rt} , npl {np} {}

template <typename Comparable>
typename LeftistHeap<Comparable>::LeftistNode * LeftistHeap<Comparable>::merge(LeftistNode *h1, LeftistNode *h2)
{
    if ( h1 == nullptr || h2 == nullptr )
        return h1 ? h1 : h2;

    if ( h1->element > h2->element )
        return merge1( h2, h1 );
    else 
        return merge1( h1, h2 );
}

template <typename Comparable>
typename LeftistHeap<Comparable>::LeftistNode * LeftistHeap<Comparable>::merge1(LeftistNode *h1, LeftistNode *h2)
{
    LeftistNode * temp = h1->right;
    h1->right = merge( h2, temp );
    if ( h1->left == nullptr )
    {
        h1->left = h1->right;
        h1->right = nullptr;
        h1->npl = 0;
        return h1;
    }
    if ( h1->left->npl < h1->right->npl )
        swapChildren(h1);

    h1->npl = h1->right->npl + 1;
    return h1;
}

template <typename Comparable>
void LeftistHeap<Comparable>::swapChildren(LeftistNode *t)
{
    if ( t == nullptr )
        return;
    std::swap( t->right, t->left );
}

template <typename Comparable>
void LeftistHeap<Comparable>::reclaimMemory(LeftistNode *t)
{
    if ( t == nullptr )
        return;
    reclaimMemory(t->left);
    reclaimMemory(t->right);
    delete t;
}

#endif
