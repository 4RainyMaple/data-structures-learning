#ifndef CHAPTER6_LEFTISTHEAP_H
#define CHAPTER6_LEFTISTHEAP_H


// 6.6 左式堆，接口参照图 6.25。
template <typename Comparable>
class LeftistHeap
{
public:
    LeftistHeap();
    LeftistHeap(const LeftistHeap &rhs);
    LeftistHeap(LeftistHeap &&rhs);
    ~LeftistHeap();
    LeftistHeap &operator=(const LeftistHeap &rhs);
    LeftistHeap &operator=(LeftistHeap &&rhs);
    bool isEmpty() const;
    const Comparable &findMin() const;
    void insert(const Comparable &x);
    void insert(Comparable &&x);
    Comparable deleteMin();
    void makeEmpty();
    void merge(LeftistHeap &rhs);

private:
    struct LeftistNode
    {
        Comparable element;
        LeftistNode *left;
        LeftistNode *right;
        int npl; // 零路径长

        LeftistNode(const Comparable &e, LeftistNode *lt = nullptr, LeftistNode *rt = nullptr, int np = 0);
        LeftistNode(Comparable &&e, LeftistNode *lt = nullptr, LeftistNode *rt = nullptr, int np = 0);
    };

    LeftistNode *root;
    LeftistNode *merge(LeftistNode *h1, LeftistNode *h2);
    LeftistNode *merge1(LeftistNode *h1, LeftistNode *h2);  //已保证 h1 的根不大于 h2
    void swapChildren(LeftistNode *t);
    void reclaimMemory(LeftistNode *t);
};

#include "LeftistHeap.cpp"
#endif
