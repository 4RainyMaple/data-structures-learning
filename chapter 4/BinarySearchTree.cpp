#ifndef BINARY_SEARCH_TREE_CPP
#define BINARY_SEARCH_TREE_CPP

#include "BinarySearchTree.h"
#include<utility>
#include<stdexcept> //调用异常类型

// ==================== 🔵 构造与析构 ====================

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree() : root {nullptr} 
{}

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree & rhs)
{
    root = clone(rhs.root);
}

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(BinarySearchTree && rhs) : 
    root {rhs.root}
{
    rhs.root = nullptr;
}

template <typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree()
{
    makeEmpty();
}

// ==================== 🟢 赋值操作 ====================

template <typename Comparable>
BinarySearchTree<Comparable> & BinarySearchTree<Comparable>::operator=(const BinarySearchTree & rhs)
{
    //还是先判断自赋值
    if ( this == &rhs )
        return *this;

    BinaryNode<Comparable> * temp;
    temp = clone(rhs.root);
    makeEmpty();
    root = temp;
    return *this;
}

template <typename Comparable>
BinarySearchTree<Comparable> & BinarySearchTree<Comparable>::operator=(BinarySearchTree && rhs)
{
    if ( this == &rhs )
        return *this;
    
    //右值就没必要创建临时变量了
    makeEmpty();
    root = rhs.root;
    rhs.root = nullptr;
    return *this;
}

// ==================== 🟠 判空与清空 ====================

template <typename Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const
{
    return root == nullptr;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty()
{
    makeEmpty(root);
}

// ==================== 🟣 元素查询 ====================

template <typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMin() const
{
    //先检查是否为空树
    if ( root == nullptr )
        throw std::underflow_error("empty tree");
    //注意公开接口返回值，私有接口返回指针
    return findMin(root)->element;
}

template <typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax() const
{
    if ( root == nullptr )
        throw std::underflow_error("empty tree");
    return findMax(root)->element;
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable & x) const
{
    return contains( x, root );
}

// ==================== 🔴 增删元素 ====================

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable & x)
{
    insert( x, root );
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable && x)
{
    insert( std::move(x), root );
}

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable & x)
{
    remove( x, root );
}

// ==================== 📄 遍历输出 ====================

template <typename Comparable>
void BinarySearchTree<Comparable>::printTree() const
{
    // 从整棵树的根节点开始输出。
    printTree(root);
}

// ==================== ⚙️ 内部辅助：查询 ====================

template <typename Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::findMin(BinaryNode<Comparable> * t) const
{
    if ( t == nullptr )
        return nullptr;
    //基准情形
    if ( t->left == nullptr )
        return t;
    return findMin(t->left);
}

template <typename Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::findMax(BinaryNode<Comparable> * t) const
{
    if ( t == nullptr )
        return nullptr;
    //基准情形
    if ( t->right == nullptr )
        return t;
    return findMax(t->right);
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable & x, BinaryNode<Comparable> * t) const
{
    //递归查找
    if ( t == nullptr ) //空节点直接返回
        return false;
    else if ( x > t->element )
        return contains( x, t->right );
    else if ( x < t->element )
        return contains( x, t->left );
    else
        return true;
}

// ==================== ⚙️ 内部辅助：增删 ====================

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable & x, BinaryNode<Comparable> * & t)
{
    //基准情形：递归到符合的位置，建立新指针
    if ( t == nullptr )
        t = new BinaryNode<Comparable>{ x, nullptr, nullptr };
    else if ( x > t->element )
        insert( x, t->right );
    else if ( x < t->element )
        insert( x, t->left );
    else
        return;   //本质上也走了一次遍历，故不需要先判断是否存在
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable && x, BinaryNode<Comparable> * & t)
{
    if ( t == nullptr )
        t = new BinaryNode<Comparable>{ std::move(x), nullptr, nullptr };
    else if ( x > t->element )
        insert( std::move(x), t->right );
    else if ( x < t->element )
        insert( std::move(x), t->left );
    else 
        return;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable & x, BinaryNode<Comparable> * & t)
{
    if ( t == nullptr )
        return;
    if ( x < t->element )
        remove( x, t->left );
    else if ( x > t->element )
        remove( x, t->right );
    else if ( t->left != nullptr && t->right != nullptr )   //两个儿子
    {
        
        t->element = findMin(t->right)->element;    //用右子树里最小元素代替自己
        remove( t->element, t->right );             //删除右子树用于替代x的元素
    }
    else    //只有一个孩子或没有孩子，就让孩子接替自己
    {
        BinaryNode<Comparable> * oldNode = t;   //先保存待删除节点的地址
        t = ( t->left != nullptr )? t->left : t->right; //哪边有孩子就让哪边接替
        delete oldNode;     //删除旧节点的地址
    }
}

// ==================== ⚙️ 内部辅助：清空、输出与复制 ====================

template <typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode<Comparable> * & t)
{
    //递归地清除
    if ( t != nullptr )
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}


template <typename Comparable>
void BinarySearchTree<Comparable>::printTree(BinaryNode<Comparable> * t) const
{
    if ( t == nullptr )
        return;

    // 中序遍历：左子树、当前节点、右子树。
    printTree(t->left);
    std::cout << t->element << " ";
    printTree(t->right);
}

template <typename Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::clone(BinaryNode<Comparable> * t) const
{
    //递归地赋值
    if ( t == nullptr )
        return nullptr;

    else 
        return new BinaryNode<Comparable> { t->element, clone(t->left), clone(t->right) };
}
#endif
