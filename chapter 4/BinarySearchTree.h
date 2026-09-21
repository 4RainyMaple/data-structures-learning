#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <utility>

// 教材印刷页码 108–109，图 4.16。
// Comparable 需要支持 < 比较；本练习不保存重复项。
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
    void printTree(std::ostream & out = std::cout) const;

private:
    // ==================== 🌳 节点结构与根指针 ====================
    // 按教材使用类内部的节点类型，不依赖已有的 BinaryNode.h。
    struct BinaryNode
    {
        Comparable element;
        BinaryNode * left;
        BinaryNode * right;

        // 节点构造：拷贝元素 / 移动元素。
        BinaryNode(const Comparable & theElement, BinaryNode * lt, BinaryNode * rt);
        BinaryNode(Comparable && theElement, BinaryNode * lt, BinaryNode * rt);
    };

    BinaryNode * root;

    // 以下为内部辅助函数：处理以 t 为根的子树。
    // ==================== ⚙️ 内部辅助：查询 ====================
    BinaryNode * findMin(BinaryNode * t) const;
    BinaryNode * findMax(BinaryNode * t) const;
    bool contains(const Comparable & x, BinaryNode * t) const;

    // ==================== ⚙️ 内部辅助：增删 ====================
    void insert(const Comparable & x, BinaryNode * & t);
    void insert(Comparable && x, BinaryNode * & t);
    void remove(const Comparable & x, BinaryNode * & t);

    // ==================== ⚙️ 内部辅助：清空、输出与复制 ====================
    void makeEmpty(BinaryNode * & t);
    void printTree(BinaryNode * t, std::ostream & out) const;
    BinaryNode * clone(BinaryNode * t) const;
};

// 类模板的函数定义需要对使用它的文件可见。
// 使用时只需包含本头文件，不必单独编译 BinarySearchTree.cpp。
#include "BinarySearchTree.cpp"

#endif
