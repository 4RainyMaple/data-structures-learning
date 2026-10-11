#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <utility>
#include "BinaryNode.h"

template <typename Comparable>
class BinarySearchTree
{
public:
    // ==================== 🔵 构造与析构 ====================
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree & rhs);
    BinarySearchTree(BinarySearchTree && rhs);
    ~BinarySearchTree();

    // ==================== 🟢 赋值操作 ====================
    BinarySearchTree & operator=(const BinarySearchTree & rhs);
    BinarySearchTree & operator=(BinarySearchTree && rhs);

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
    // ==================== 🌳 根指针 ====================

    BinaryNode<Comparable> * root;

    // 以下为内部辅助函数：处理以 t 为根的子树。
    // ==================== ⚙️ 内部辅助：查询 ====================
    BinaryNode<Comparable> * findMin(BinaryNode<Comparable> * t) const;
    BinaryNode<Comparable> * findMax(BinaryNode<Comparable> * t) const;
    bool contains(const Comparable & x, BinaryNode<Comparable> * t) const;

    // ==================== ⚙️ 内部辅助：增删 ====================
    void insert(const Comparable & x, BinaryNode<Comparable> * & t);
    void insert(Comparable && x, BinaryNode<Comparable> * & t);
    void remove(const Comparable & x, BinaryNode<Comparable> * & t);

    // ==================== ⚙️ 内部辅助：清空、输出与复制 ====================
    void makeEmpty(BinaryNode<Comparable> * & t);
    void printTree(BinaryNode<Comparable> * t) const;
    BinaryNode<Comparable> * clone(BinaryNode<Comparable> * t) const;
};

// 类模板的函数定义需要对使用它的文件可见。
// 使用时只需包含本头文件，不必单独编译 BinarySearchTree.cpp。
#include "BinarySearchTree.cpp"

#endif
