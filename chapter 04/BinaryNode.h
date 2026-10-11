#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#include <utility> // std::move

// 二叉查找树和表达式树共用的节点模板。
template<typename Object>
struct BinaryNode
{
    Object element;
    BinaryNode * left;
    BinaryNode * right;

    // ==================== 🔵 节点构造 ====================
    //注意：这里lt和rt已经指向新的内存了
    BinaryNode(const Object & theElement, BinaryNode * lt, BinaryNode * rt) :
    element{theElement} , left{lt} , right{rt}
    {}

    BinaryNode(Object && theElement, BinaryNode * lt, BinaryNode * rt) :
    element{std::move(theElement)} , left{lt} , right{rt}
    {}
};

#endif
