#ifndef LIST_H
#define LIST_H

#include "node.h"
#include "const_iterator.h"
#include "iterator.h"
#include <stdexcept>
#include <utility>

template<typename Object>
class List
{
public:
    // ==================== 🧩 迭代器类型 ====================
    using const_iterator = ::const_iterator<Object>;
    using iterator = ::ListIterator<Object>;

private:
    using Node = ::Node<Object>;
    int theSize;
    Node * head;
    Node * tail;

    // ==================== ⚙️ 内部辅助函数 ====================
    void initial();
    void assertIteratorBelongsToThis ( const const_iterator & itr ) const;

public:
    // ==================== 🔵 构造与析构 ====================
    List();
    List ( const List & rhs );
    List ( List && rhs );
    ~List();

    // ==================== 🟢 赋值操作 ====================
    List & operator = ( const List & rhs );
    List & operator = ( List && rhs );

    // ==================== 🟠 容量和清空 ====================
    bool empty() const;
    int size() const;
    void clear();

    // ==================== 🟣 元素访问 ====================
    Object & front();
    const Object & front() const;
    Object & back();
    const Object & back() const;

    // ==================== 🟡 迭代器访问 ====================
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    // ==================== 🔴 增删元素 ====================
    void push_front ( const Object & rhs );
    void push_front ( Object && rhs );
    void push_back ( const Object & rhs );
    void push_back ( Object && rhs );
    void pop_front();
    void pop_back();
    iterator insert ( iterator pos, const Object & ele );
    iterator insert ( iterator pos, Object && ele );
    iterator erase ( iterator pos );
    iterator erase ( iterator from, iterator to );

    //将lst中的所有元素按原顺序转移到本表的position之前，转移后lst为空
    //position属于本表，可以是end()；lst与本表必须是不同的表
    //要求只调整节点之间的连接，以O(1)时间完成
    //当前迭代器保存所属表的信息，转移后请从本表重新获取指向转移元素的迭代器
    void splice ( iterator position, List & lst );

    // ==================== 🔷 比较操作 ====================
    bool operator == ( const List & rhs ) const;
    bool operator != ( const List & rhs ) const;
};

//类模板的实现需要对使用者可见
#include "list.cpp"

#endif
