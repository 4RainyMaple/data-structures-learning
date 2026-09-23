#ifndef AVL_TREE_CPP_INCLUDED
#define AVL_TREE_CPP_INCLUDED

#include "AvlTree.h"

// ==================== 🌳 节点构造 ====================

template <typename Comparable>
AvlTree<Comparable>::AvlNode::AvlNode(const Comparable & ele, AvlNode * lt, AvlNode * rt, int h) :
element{ele} , left{lt} , right{rt} , height{h}
{}

template <typename Comparable>
AvlTree<Comparable>::AvlNode::AvlNode(Comparable && ele, AvlNode * lt, AvlNode * rt, int h):
element{std::move(ele)} , left{lt} , right{rt} , height{h}
{}

// ==================== 🔵 构造与析构 ====================

template <typename Comparable>
AvlTree<Comparable>::AvlTree()
{}

template <typename Comparable>
AvlTree<Comparable>::AvlTree(const AvlTree & rhs)
{
    root = clone(rhs.root);
}

template <typename Comparable>
AvlTree<Comparable>::AvlTree(AvlTree && rhs):
root {rhs.root}
{
    rhs.root = nullptr;
}

template <typename Comparable>
AvlTree<Comparable>::~AvlTree()
{
    makeEmpty();
}

// ==================== 🟢 赋值操作 ====================

template <typename Comparable>
AvlTree<Comparable> & AvlTree<Comparable>::operator=(const AvlTree & rhs)
{
    // TODO：实现拷贝赋值。
}

template <typename Comparable>
AvlTree<Comparable> & AvlTree<Comparable>::operator=(AvlTree && rhs)
{
    // TODO：实现移动赋值。
}

// ==================== 🟠 判空与清空 ====================

template <typename Comparable>
bool AvlTree<Comparable>::isEmpty() const
{
    return root == nullptr;
}

template <typename Comparable>
void AvlTree<Comparable>::makeEmpty()
{
    makeEmpty(root);
}

// ==================== 🟣 元素查询 ====================

template <typename Comparable>
const Comparable & AvlTree<Comparable>::findMin() const
{
    if ( isEmpty() )
        throw std::underflow_error("empty tree");

    return findMin(root)->element;
}

template <typename Comparable>
const Comparable & AvlTree<Comparable>::findMax() const
{
    if ( isEmpty() )
        throw std::underflow_error("empty tree");

    return findMax(root)->element;
}

template <typename Comparable>
bool AvlTree<Comparable>::contains(const Comparable & x) const
{
    if ( isEmpty() )
        return false;

    return contains(x,root);
}

// ==================== 🔴 增删元素 ====================

template <typename Comparable>
void AvlTree<Comparable>::insert(const Comparable & x)
{
    insert( x, root );
}

template <typename Comparable>
void AvlTree<Comparable>::insert(Comparable && x)
{
    insert( std::move(x), root );
}

template <typename Comparable>
void AvlTree<Comparable>::remove(const Comparable & x)
{
    // TODO：调用私有删除函数。
}

// ==================== 📄 遍历输出 ====================

template <typename Comparable>
void AvlTree<Comparable>::printTree() const
{
    printTree(root);
}

// ==================== 📏 高度与平衡 ====================

template <typename Comparable>
int AvlTree<Comparable>::height(AvlNode * t) const
{
    //注意这里对象是节点t
    return t == nullptr ? -1 : t->height;
}

template <typename Comparable>
void AvlTree<Comparable>::balance(AvlNode * & t)
{
    if ( t == nullptr )
        return;

    if ( height(t->left) - height(t->right) > 1 )
    {
        // LL型（含左右孙等高，删除后可能会出现）
        if ( height(t->left->left) - height(t->left->right) >= 0 )
            rotateWithLeftChild(t);
        // LR型
        else
            doubleWithLeftChild(t);
    }
    else if ( height(t->left) - height(t->right) < -1 )
    {
        // RR型（含左右孙等高）
        if ( height(t->right->left) - height(t->right->right) <= 0 )
            rotateWithRightChild(t);
        // RL型
        else
            doubleWithRightChild(t);
    }

    // 更新高度：这是为了防止增删元素后不需要执行旋转导致高度未更新
    t->height = std::max(height(t->left), height(t->right)) + 1;
}

// ==================== 🔄 单旋转与双旋转 ====================

template <typename Comparable>
void AvlTree<Comparable>::rotateWithLeftChild(AvlNode * & k2)
{
    // 调用时保证 k2 和它的左孩子存在。
    // 保存左孩子，它将上升成为这棵子树的新根。
    AvlNode * k1 = k2->left;

    // 将左孩子原来的右子树接到旧根左边，空子树也适用。
    k2->left = k1->right;

    // 旧根下降，成为新根的右孩子。
    k1->right = k2;

    // 先更新旧根，再更新依赖旧根高度的新根。
    k2->height = std::max(height(k2->left), height(k2->right)) + 1;
    k1->height = std::max(height(k1->left), height(k1->right)) + 1;

    // k2 是指针的引用，这会同步更新调用者的子树根指针。
    k2 = k1;
}

template <typename Comparable>
void AvlTree<Comparable>::rotateWithRightChild(AvlNode * & k2)
{
    AvlNode * k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = std::max(height(k2->left),height(k2->right)) + 1;
    k1->height = std::max(height(k1->left),height(k1->right)) + 1;
    k2 = k1;
}

template <typename Comparable>
void AvlTree<Comparable>::doubleWithLeftChild(AvlNode * & k3)
{
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template <typename Comparable>
void AvlTree<Comparable>::doubleWithRightChild(AvlNode * & k3)
{
    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3);
}

// ==================== ⚙️ 内部辅助：查询 ====================

//注意返回值
template <typename Comparable>
typename AvlTree<Comparable>::AvlNode * AvlTree<Comparable>::findMin(AvlNode * t) const
{
    if ( t->left == nullptr )
        return t;
    else 
        return findMin( t->left );
}

template <typename Comparable>
typename AvlTree<Comparable>::AvlNode * AvlTree<Comparable>::findMax(AvlNode * t) const
{
    if ( t->right == nullptr )
        return t;
    else 
        return findMax(t->right);
}

template <typename Comparable>
bool AvlTree<Comparable>::contains(const Comparable & x, AvlNode * t) const
{
    if ( t == nullptr )
        return false;

    if ( x > t->element )
        return contains( x, t->right );
    else if ( x < t->element )
        return contains( x, t->left );
    else
        return true;
}

// ==================== ⚙️ 内部辅助：增删 ====================

template <typename Comparable>
void AvlTree<Comparable>::insert(const Comparable & x, AvlNode * & t)
{
    //节点不存在就先创建一个
    if ( t == nullptr )
        t = new AvlNode { x, nullptr, nullptr };
    else if ( x > t->element )
        insert( x, t->right );
    else if ( x < t->element )
        insert( x, t->left );
    else 
        return;  
        
    balance(t); //进入递归时子树可能会更新，所以每层递归都要平衡
}

template <typename Comparable>
void AvlTree<Comparable>::insert(Comparable && x, AvlNode * & t)
{
    if ( t == nullptr )
        t = new AvlNode { std::move(x), nullptr, nullptr };

    else if ( x > t->element )
        insert( std::move(x), t->right );
    else if ( x < t->element )
        insert( std::move(x), t->left );
    else 
        return;

    balance(t);
}

template <typename Comparable>
void AvlTree<Comparable>::remove(const Comparable & x, AvlNode * & t)
{
    // TODO：图 4.47：删除元素，递归返回时维护平衡。
}

// ==================== ⚙️ 内部辅助：清空、输出与复制 ====================

template <typename Comparable>
void AvlTree<Comparable>::makeEmpty(AvlNode * & t)
{
    if ( t == nullptr )
        return;

    makeEmpty(t->left);
    makeEmpty(t->right);
    //先清空左右子树再清空自己
    delete t;
}

template <typename Comparable>
void AvlTree<Comparable>::printTree(AvlNode * t) const
{
    if ( t == nullptr )
        return;

    printTree(t->left);
    std::cout << t->element <<" ";
    printTree(t->right);
}

template <typename Comparable>
typename AvlTree<Comparable>::AvlNode * AvlTree<Comparable>::clone(AvlNode * t) const
{
    if ( t == nullptr )
        return t;

    return new AvlNode { t->element, clone(t->left), clone(t->right), t->height };
}

#endif
