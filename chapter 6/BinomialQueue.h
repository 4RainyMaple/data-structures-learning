#ifndef CHAPTER6_BINOMIALQUEUE_H
#define CHAPTER6_BINOMIALQUEUE_H

#include <vector>
// 6.8 二项队列，接口参照图 6.52。
template <typename Comparable>
class BinomialQueue
{
public:
    BinomialQueue();
    BinomialQueue(const Comparable &item);
    BinomialQueue(const BinomialQueue &rhs);
    BinomialQueue(BinomialQueue &&rhs);
    ~BinomialQueue();
    BinomialQueue &operator=(const BinomialQueue &rhs);
    BinomialQueue &operator=(BinomialQueue &&rhs);
    bool isEmpty() const;
    const Comparable & findMin() const;
    void insert(const Comparable &x);
    void insert(Comparable &&x);
    Comparable deleteMin();
    void makeEmpty();
    void merge(BinomialQueue &rhs);

private:
    struct BinomialNode
    {
        Comparable element;
        BinomialNode *firstChild;   //最高阶孩子
        BinomialNode *nextSibling;
        BinomialNode(const Comparable &e, BinomialNode *lt, BinomialNode *rt);
        BinomialNode(Comparable &&e, BinomialNode *lt, BinomialNode *rt);
    };

    //创建二项队列时默认有一棵树的位置
    static const int DEFAULT_TREES = 1;
    std::vector<BinomialNode *> theTrees;
    int currentSize;

    int findMinIndex() const;
    int capacity() const;
    //要求t1和t2大小相同
    BinomialNode *combineTrees(BinomialNode *t1, BinomialNode *t2);
    void makeEmpty(BinomialNode *&t);
    BinomialNode *clone(BinomialNode *t) const;
};

#include "BinomialQueue.cpp"
#endif
