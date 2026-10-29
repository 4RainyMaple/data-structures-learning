#ifndef TREAP_H
#define TREAP_H

#include"treapnode.h"

template<typename Comparable>
class Treap
{
public:
    // 构造与赋值函数
    Treap();
    Treap(const Treap & rhs);
    Treap(Treap && rhs) noexcept;
    ~Treap();
    Treap & operator = (const Treap & rhs);
    Treap & operator = (Treap && rhs) noexcept;

    // 插入与删除
    void insert( const Comparable & x );
    void remove( const Comparable & x );
    void makeEmpty();
private:
    TreapNode<Comparable> * root;

    // 辅助清空函数
    void makeEmpty(TreapNode<Comparable> * t);

    // 插入与删除
    void insert( const Comparable & x, TreapNode<Comparable> * & t );
    void remove( const Comparable & x, TreapNode<Comparable> * & t );

    // 深拷贝（拷贝构造与拷贝赋值使用）
    static TreapNode<Comparable> * clone( const TreapNode<Comparable> * t );

    // 旋转：参数是"父结点里指向这棵子树的那个指针"（也可能是 root 本身）
    void rotateWithLeftChild( TreapNode<Comparable> * & t );    // 左孩子旋上来（即通常说的右旋）
    void rotateWithRightChild( TreapNode<Comparable> * & t );   // 右孩子旋上来（即通常说的左旋）

    // 随机优先级：每个新结点创建时调用一次
    static int randomPriority();
};

#include"treap.cpp"
#endif
