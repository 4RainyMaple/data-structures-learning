#ifndef CHAPTER6_SKEWHEAP_H
#define CHAPTER6_SKEWHEAP_H


// 6.7 斜堆：参照左式堆补充练习接口，不保存零路径长。
template <typename Comparable>
class SkewHeap
{
public:
    SkewHeap();
    SkewHeap(const SkewHeap &rhs);
    SkewHeap(SkewHeap &&rhs);
    ~SkewHeap();
    SkewHeap &operator=(const SkewHeap &rhs);
    SkewHeap &operator=(SkewHeap &&rhs);
    bool isEmpty() const;
    const Comparable &findMin() const;
    void insert(const Comparable &x);
    void insert(Comparable &&x);
    Comparable deleteMin();
    void makeEmpty();
    void merge(SkewHeap &rhs);

private:
    struct SkewNode
    {
        Comparable element;
        SkewNode *left;
        SkewNode *right;

        SkewNode(const Comparable &e, SkewNode *lt = nullptr, SkewNode *rt = nullptr);
        SkewNode(Comparable &&e, SkewNode *lt = nullptr, SkewNode *rt = nullptr);
    };

    SkewNode *root;
    SkewNode *merge(SkewNode *h1, SkewNode *h2);
    void swapChildren(SkewNode *t);
    void reclaimMemory(SkewNode *t);
    SkewNode *clone(SkewNode *t) const;
};

#include "SkewHeap.cpp"
#endif
