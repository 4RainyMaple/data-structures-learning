#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm> // std::max
#include <iostream>
#include <stdexcept>
#include <utility>   // std::move、std::swap

template <typename Comparable>
class AvlTree
{
private:
    // ==================== 🌳 节点与属性 ====================
    struct AvlNode
    {
        Comparable element;
        AvlNode * left;
        AvlNode * right;
        int height; // 保存该节点的高度；叶子为 0，空树由 height() 返回 -1。

        AvlNode(const Comparable & ele, AvlNode * lt, AvlNode * rt, int h = 0);

        AvlNode(Comparable && ele, AvlNode * lt, AvlNode * rt, int h = 0);
    };

    AvlNode * root = nullptr;

public:
    // ==================== 🔵 构造与析构 ====================
    AvlTree();

    AvlTree(const AvlTree & rhs);

    AvlTree(AvlTree && rhs);

    ~AvlTree();

    // ==================== 🟢 赋值操作 ====================
    AvlTree & operator=(const AvlTree & rhs);

    AvlTree & operator=(AvlTree && rhs);

    // ==================== 🟠 判空与清空 ====================
    bool isEmpty() const;

    void makeEmpty();

    // ==================== 🟣 元素查询 ====================
    const Comparable & findMin() const;

    const Comparable & findMax() const;

    bool contains(const Comparable & x) const;

    // ==================== 🔴 增删元素 ====================
    void insert(const Comparable & x);

    void insert(Comparable && x);

    void remove(const Comparable & x);

    // ==================== 📄 遍历输出 ====================
    void printTree() const;

private:
    // ==================== 📏 高度与平衡 ====================
    int height(AvlNode * t) const;

    void balance(AvlNode * & t);

    // ==================== 🔄 单旋转与双旋转 ====================
    // 单右旋：左孩子上升，更新高度和子树根。
    void rotateWithLeftChild(AvlNode * & k2);

    // 单左旋：右孩子上升，更新高度和子树根。
    void rotateWithRightChild(AvlNode * & k2);

    // 左—右型：先对左子树左旋，再对当前根右旋。
    void doubleWithLeftChild(AvlNode * & k3);

    // 右—左型：先对右子树右旋，再对当前根左旋。
    void doubleWithRightChild(AvlNode * & k3);

    // ==================== ⚙️ 内部辅助：查询 ====================
    AvlNode * findMin(AvlNode * t) const;

    AvlNode * findMax(AvlNode * t) const;

    bool contains(const Comparable & x, AvlNode * t) const;

    // ==================== ⚙️ 内部辅助：增删 ====================
    void insert(const Comparable & x, AvlNode * & t);

    void insert(Comparable && x, AvlNode * & t);

    void remove(const Comparable & x, AvlNode * & t);

    // ==================== ⚙️ 内部辅助：清空、输出与复制 ====================
    void makeEmpty(AvlNode * & t);

    void printTree(AvlNode * t) const;

    AvlNode * clone(AvlNode * t) const;

};

// 类模板的定义需要对使用者可见。
#include "AvlTree.cpp"

#endif
