#include"treap.h"
#include<climits>
#include<random>
#include<utility>

template<typename Comparable>
Treap<Comparable>::Treap() : root {nullptr} {}

template<typename Comparable>
Treap<Comparable>::Treap(const Treap & rhs) : root { clone(rhs.root) } {}

template<typename Comparable>
Treap<Comparable>::Treap(Treap && rhs) noexcept : root{rhs.root}
{
    rhs.root = nullptr;
}

template<typename Comparable>
Treap<Comparable>::~Treap()
{
    makeEmpty();
}

template<typename Comparable>
Treap<Comparable> & Treap<Comparable>::operator = (const Treap & rhs)
{
    if ( this != &rhs )
    {
        Treap<Comparable> tmp{ rhs };       // 先深拷贝一份，失败时 *this 保持不变
        std::swap( root, tmp.root );        // tmp 析构时释放原来那棵树
    }
    return *this;
}

template<typename Comparable>
Treap<Comparable> & Treap<Comparable>::operator = (Treap && rhs) noexcept
{
    if ( this != &rhs )
    {
        makeEmpty();                        // 先释放原来那棵树
        root = rhs.root;
        rhs.root = nullptr;
    }
    return *this;
}

template<typename Comparable>
void Treap<Comparable>::makeEmpty()
{
    makeEmpty(root);
    root = nullptr;     // 私有的递归版本按值接收指针，不会把 root 置空，这里必须补上
}

template<typename Comparable>
void Treap<Comparable>::makeEmpty(TreapNode<Comparable> * t)
{
    if ( !t )
        return;
    makeEmpty( t->left );
    makeEmpty( t->right );
    delete t;
}

template<typename Comparable>
TreapNode<Comparable> * Treap<Comparable>::clone( const TreapNode<Comparable> * t )
{
    if ( !t )
        return nullptr;
    return new TreapNode<Comparable>( t->element, t->priority,
                                      clone( t->left ), clone( t->right ) );
}

template<typename Comparable>
void Treap<Comparable>::insert( const Comparable & x )
{
    insert( x, root );
}

template<typename Comparable>
void Treap<Comparable>::remove( const Comparable & x )
{
    remove( x, root );
}

template<typename Comparable>
void Treap<Comparable>::insert( const Comparable & x, TreapNode<Comparable> * & t )
{
    if ( !t )
    {
        t = new TreapNode<Comparable>( x, randomPriority() );
        return;
    }
    if ( x == t->element )
        return;
    if ( x < t->element )
    {
        insert( x, t->left );
        if ( t->left->priority < t->priority )
            rotateWithLeftChild( t );
    }
    else
    {
        insert( x, t->right );
        if ( t->right->priority < t->priority )
            rotateWithRightChild( t );
    }
}

template<typename Comparable>
void Treap<Comparable>::remove( const Comparable & x, TreapNode<Comparable> * & t )
{
    if ( !t )
        return;
    if ( x == t->element )
    {
        if ( t->left && t->right )
        {
            if ( t->left->priority < t->right->priority )
                rotateWithLeftChild( t );
            else
                rotateWithRightChild( t );
            remove( x, t );
        }
        else
        {
            // 让唯一的孩子代替自己，然后删除原节点
            TreapNode<Comparable> * old = t;
            t = t->left ? t->left : t->right;
            delete old;
        }
    }
    else if ( x < t->element )
        remove( x, t->left );
    else
        remove( x, t->right );
}

template<typename Comparable>
void Treap<Comparable>::rotateWithLeftChild( TreapNode<Comparable> * & t )
{
    TreapNode<Comparable> * k1 = t->left;   // 左孩子将成为新的子树根
    t->left = k1->right;                    // k1 原来的右子树改挂到 t 的左边
    k1->right = t;
    t = k1;                                 // 让父结点（或 root）指向新的子树根
}

template<typename Comparable>
void Treap<Comparable>::rotateWithRightChild( TreapNode<Comparable> * & t )
{
    TreapNode<Comparable> * k1 = t->right;
    t->right = k1->left;
    k1->left = t;
    t = k1;
}

template<typename Comparable>
int Treap<Comparable>::randomPriority()
{
    // 函数内 static：整个程序只初始化一次，插入时不会重复播种
    static std::mt19937 gen{ std::random_device{}() };
    static std::uniform_int_distribution<int> dist{ 0, INT_MAX - 1 };
    return dist(gen);
}