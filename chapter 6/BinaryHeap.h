#ifndef CHAPTER6_BINARYHEAP_H
#define CHAPTER6_BINARYHEAP_H

#include <vector>
// 6.3 二叉最小堆；array[1] 为堆顶，array[0] 预留。
template <typename Comparable>
class BinaryHeap
{
public:
    explicit BinaryHeap(int capacity = 100);
    explicit BinaryHeap(const std::vector<Comparable> &items);
    bool isEmpty() const;
    const Comparable &findMin() const;
    void insert(const Comparable &x);
    void insert(Comparable &&x);
    Comparable deleteMin();
    void makeEmpty();

private:
    int currentSize;
    std::vector<Comparable> array;
    void buildHeap();
    void percolateDown(int hole);
};

// 模板定义需要对使用者可见，只需包含本头文件。
#include "BinaryHeap.cpp"
#endif
