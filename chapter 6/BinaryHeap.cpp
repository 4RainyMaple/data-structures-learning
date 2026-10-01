#ifndef CHAPTER6_BINARYHEAP_CPP
#define CHAPTER6_BINARYHEAP_CPP

#include "BinaryHeap.h"
#include <utility>
#include <algorithm>
#include <stdexcept>

template <typename Comparable>
BinaryHeap<Comparable>::BinaryHeap(int capacity):
currentSize{0} , array(capacity + 1)    {}

template <typename Comparable>
BinaryHeap<Comparable>::BinaryHeap(const std::vector<Comparable> &items):
currentSize {(int)items.size()} , array ( items.size() + 1 ) //预留0占位
{
    for ( int i = 0; i < items.size(); i++ )
        array[i+1] = items[i];
    buildHeap();
}

template <typename Comparable>
bool BinaryHeap<Comparable>::isEmpty() const
{
    return currentSize == 0;
}

template <typename Comparable>
const Comparable & BinaryHeap<Comparable>::findMin() const
{
    if ( isEmpty() )
        throw std::underflow_error("empty heap");
    return array[1];
}

template <typename Comparable>
void BinaryHeap<Comparable>::insert(const Comparable &x)
{ 
    if ( currentSize >= array.size() - 1 )  //注意0不占位
        array.resize( 2*array.size() );
    currentSize++;

    int hole = currentSize; //把空穴初始化再最下面
    array[0] = x;           //堆从1开始，给0号位赋值是为了给循环提供终止条件
    //只要新元素比空穴的父节点小，就把父节点向下搬，空穴向上移。
    while ( x < array[hole/2] )
    {
        array[hole] = array[hole/2];    //父节点往下搬  
        hole /= 2;                      //空穴上移
    }
    array[hole] = x;
}

template <typename Comparable>
void BinaryHeap<Comparable>::insert(Comparable &&x)
{
    if ( currentSize >= array.size() - 1 )
        array.resize( 2*array.size() );
    currentSize++;

    int hole = currentSize; 
    array[0] = std::move(x);           
    
    while ( array[0] < array[hole/2] )  //对于字符串等类型，x的资源已被转移
    {
        array[hole] = array[hole/2];  
        hole /= 2;                     
    }
    array[hole] = std::move(array[0]);  
}

template <typename Comparable>
Comparable BinaryHeap<Comparable>::deleteMin()
{
    if ( isEmpty() )
        throw std::underflow_error("empty heap");

    Comparable minItem = std::move(array[1]);
    //元素数减一，再将最后一个元素放到根
    array[1] = std::move(array[currentSize--]);
    percolateDown(1);

    return minItem;
}

template <typename Comparable>
void BinaryHeap<Comparable>::makeEmpty()
{
    currentSize = 0;
    array.resize(1);
}

template <typename Comparable>
void BinaryHeap<Comparable>::buildHeap()
{
    //只需下滤非树叶节点，下标大于currentSize / 2的节点没有孩子
    for ( int i = currentSize / 2; i > 0; i-- )
        percolateDown(i);   //调用这个函数的要求是左右子树都是堆，而树叶是堆
}

template <typename Comparable>
void BinaryHeap<Comparable>::percolateDown(int hole)    //空穴是下滤开始的下标
{
    int child;
    Comparable temp = std::move(array[hole]);   //将当前元素存入temp，原位当做空穴

    //给hole选一个合适的位置来填temp
    while ( 2 * hole <= currentSize )   //只要还有左孩子
    {
        //选出左右孩子（若存在）中最小的元素
        child = 2 * hole;   //先暂定为左孩子
        if ( child != currentSize && array[child+1] < array[child] )
            child++;        //若右孩子更小就定为右孩子

        //若孩子比temp小就把孩子搬上来，把空穴沉下去
        if ( array[child] < temp )
        {
            array[hole] = std::move(array[child]);
            hole = child;
        }
        else
            break;
    }
    //把temp填入空穴
    array[hole] = std::move(temp);
}

#endif
