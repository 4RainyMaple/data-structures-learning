#ifndef CHAPTER6_BINOMIALQUEUE_CPP
#define CHAPTER6_BINOMIALQUEUE_CPP

#include "BinomialQueue.h"
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <cmath>

template <typename Comparable>
BinomialQueue<Comparable>::BinomialQueue():
theTrees (DEFAULT_TREES) , currentSize {0}  {}


template <typename Comparable>
BinomialQueue<Comparable>::BinomialQueue(const Comparable &item):
theTrees (DEFAULT_TREES) , currentSize {1}
{
    theTrees[0] = new BinomialNode(item, nullptr, nullptr);
}

template <typename Comparable>
BinomialQueue<Comparable>::BinomialQueue(const BinomialQueue &rhs):
currentSize {rhs.currentSize} , theTrees (rhs.theTrees.size())
{
    for ( size_t i = 0; i < rhs.theTrees.size(); i++ )
        theTrees[i] = clone(rhs.theTrees[i]);
}

template <typename Comparable>
BinomialQueue<Comparable>::BinomialQueue(BinomialQueue &&rhs):
currentSize {rhs.currentSize} , theTrees {std::move(rhs.theTrees)} 
{
    rhs.currentSize = 0;
}

template <typename Comparable>
BinomialQueue<Comparable>::~BinomialQueue()
{
    makeEmpty();
}

template <typename Comparable>
BinomialQueue<Comparable> & BinomialQueue<Comparable>::operator=(const BinomialQueue &rhs)
{
    if ( this == &rhs )
        return *this;

    BinomialQueue temp(rhs);
    std::swap( temp.theTrees, this->theTrees );
    std::swap( temp.currentSize, this->currentSize );
    return *this;
}

template <typename Comparable>
BinomialQueue<Comparable> & BinomialQueue<Comparable>::operator=(BinomialQueue &&rhs)
{
    if ( this == &rhs )
        return *this;

    std::swap( rhs.theTrees, this->theTrees );
    std::swap( rhs.currentSize, this->currentSize );
    return *this;
}

template <typename Comparable>
bool BinomialQueue<Comparable>::isEmpty() const
{
    return currentSize == 0;
}

template <typename Comparable>
const Comparable & BinomialQueue<Comparable>::findMin() const
{
    if ( isEmpty() )
        throw std::underflow_error("empty heap");

    int index = findMinIndex();

    return theTrees[index]->element;
}

template <typename Comparable>
void BinomialQueue<Comparable>::insert(const Comparable &x)
{
    BinomialQueue temp(x);
    merge(temp);
}

template <typename Comparable>
void BinomialQueue<Comparable>::insert(Comparable &&x)
{
    BinomialQueue temp;
    temp.theTrees[0] = new BinomialNode(std::move(x), nullptr, nullptr);
    temp.currentSize = 1;
    merge(temp);
}

template <typename Comparable>
Comparable BinomialQueue<Comparable>::deleteMin()
{
    if ( isEmpty() )
        throw std::underflow_error("empty heap");

    int minIndex = findMinIndex();
    Comparable minItem = theTrees[minIndex]->element;

    //建立一个删除根节点后被打散的二项树的集合
    BinomialQueue deletedQueue;
    deletedQueue.theTrees.resize(minIndex);
    // B_k 有 2^k 个结点，删除根后剩下 2^k - 1 个。
    deletedQueue.currentSize = (int)(std::pow(2, minIndex)) - 1;

    // 孩子依次是 B_(k-1)、B_(k-2)、……、B_0。
    BinomialNode *child = theTrees[minIndex]->firstChild;
    // 从最高阶孩子开始，依次放到新队列对应阶数的下标中。
    for (int i = minIndex - 1; i >= 0; --i)
    {
        // 当前孩子是 B_i 的根，放入下标 i。
        deletedQueue.theTrees[i] = child;
        // 先沿兄弟指针找到下一个孩子，避免断开连接后找不到它。
        child = child->nextSibling;
        // 断开当前树与下一棵树的连接，使各棵树的根彼此独立。
        deletedQueue.theTrees[i]->nextSibling = nullptr;
    }

    delete theTrees[minIndex];
    theTrees[minIndex] = nullptr;
    // 从原队列扣除整棵树：孩子的数量加上一个根。
    currentSize -= (int)(std::pow(2, minIndex));

    merge(deletedQueue);
    return minItem;
}


template <typename Comparable>
void BinomialQueue<Comparable>::makeEmpty()
{
    for ( auto & node : theTrees )
        makeEmpty(node);

    currentSize = 0;
}

template <typename Comparable>
void BinomialQueue<Comparable>::merge(BinomialQueue &rhs)
{
    if ( this == &rhs )
        return;

    currentSize += rhs.currentSize;

    if ( currentSize > capacity() )
    {
        int oldNumTrees = theTrees.size();
        int newNumTrees = std::max( theTrees.size(), rhs.theTrees.size() ) + 1;     //加一是为了防止二进制数进位
        theTrees.resize( newNumTrees );
        for ( size_t i = oldNumTrees; i < newNumTrees; i++ )
            theTrees[i] = nullptr;
    }

    BinomialNode * carry = nullptr;
    /* i：当前阶数，依次处理 B_0、B_1、B_2。
    j：这一阶树的结点数，依次为 1、2、4。
    t1、t2：两个队列当前阶的树；没有则为 nullptr。
    carry：上一阶两棵树合并产生的进位树，阶数与当前 i 相同。
    whichCase 用 1、2、4 标记三棵树是否存在：*/
    for ( size_t i = 0, j = 1; j <= currentSize; i++, j*= 2 )
    {
        //这两行就是说，有就填入，没有就置空
        BinomialNode * t1 = theTrees[i];
        BinomialNode * t2 = i < rhs.theTrees.size() ? rhs.theTrees[i] : nullptr;
        
        //这里很巧妙地采用了二进制给出8种情况
        int whichCase = 0;
        whichCase += t1 ? 1 : 0;
        whichCase += t2 ? 2 : 0;
        whichCase += carry ? 4 : 0;

        //把指针转移后要将原指针置空
        switch (whichCase)
        {
            case 0: break;  //无树的情况
            case 1: break;  //只有this的情况
            case 2:         //只有rhs的情况：直接搬给t1
                theTrees[i] = t2;
                rhs.theTrees[i] = nullptr;
                break;
            case 3:         //同时有this和rhs的情况：合并
                carry = combineTrees(t1,t2);
                theTrees[i] = rhs.theTrees[i] = nullptr;
                break;
            case 4:         //只有carry的情况：直接搬给t1
                theTrees[i] = carry;
                carry = nullptr;
                break;
            case 5:         //同时有this和carry的情况：合并
                carry = combineTrees(t1,carry);
                theTrees[i] = nullptr;
                break;
            case 6:         //同时有rhs和carry的情况：合并
                carry = combineTrees(t2,carry);
                rhs.theTrees[i] = nullptr;
                break;
            case 7:         //三个都有的情况：任取一棵留在当阶，另外两棵进位
                theTrees[i] = carry;
                carry = combineTrees(t1,t2);
                rhs.theTrees[i] = nullptr;
                break;
            default:
                break;
        }
    }

    rhs.currentSize = 0;
}

template <typename Comparable>
BinomialQueue<Comparable>::BinomialNode::BinomialNode(const Comparable &e, BinomialNode *lt, BinomialNode *rt):
element {e} , firstChild {lt} , nextSibling {rt} {}

template <typename Comparable>
BinomialQueue<Comparable>::BinomialNode::BinomialNode(Comparable &&e, BinomialNode *lt, BinomialNode *rt):
element {std::move(e)} , firstChild {lt} , nextSibling {rt}  {}

template <typename Comparable>
int BinomialQueue<Comparable>::findMinIndex() const
{
    int index = -1;
    for (int i = 0; i < theTrees.size(); ++i)
    {
        if (theTrees[i] == nullptr)
            continue;
        if (index == -1 || theTrees[i]->element < theTrees[index]->element)
            index = i;
    }
    return index;
}

template <typename Comparable>
int BinomialQueue<Comparable>::capacity() const
{
    int nums = theTrees.size();
    return (int)(pow(2,nums) - 1);
}

template <typename Comparable>
typename BinomialQueue<Comparable>::BinomialNode * BinomialQueue<Comparable>::combineTrees(BinomialNode *t1, BinomialNode *t2)
{
    if ( t2->element < t1->element )
        return combineTrees(t2,t1);

    t2->nextSibling = t1->firstChild;
    t1->firstChild = t2;
    return t1;
}

template <typename Comparable>
void BinomialQueue<Comparable>::makeEmpty(BinomialNode *&t)
{
    if ( !t )
        return;
    makeEmpty(t->firstChild);
    makeEmpty(t->nextSibling);
    delete t;
    t = nullptr;
}

template <typename Comparable>
typename BinomialQueue<Comparable>::BinomialNode * BinomialQueue<Comparable>::clone(BinomialNode *t) const
{
    if ( !t )
        return nullptr;
    BinomialNode * temp = new BinomialNode( t->element, nullptr, nullptr );
    temp->firstChild = clone(t->firstChild);
    temp->nextSibling = clone(t->nextSibling);
    return temp;
}

#endif
