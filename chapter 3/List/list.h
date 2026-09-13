#ifndef LIST_H
#define LIST_H

#include "node.h"
#include "const_iterator.h"
#include "iterator.h"
#include <utility>

template<typename Object>
class List
{
public:
    using const_iterator = ::const_iterator<Object>;
    using iterator = ::ListIterator<Object>;

private:
    using Node = ::Node<Object>;
    using Exception = ::IteratorOutOfBoundsException;

    int theSize;
    Node * head;
    Node * tail;

    void initial();
    void assertIteratorBelongsToThis ( const const_iterator & itr ) const;

public:
    //迭代器访问接口
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    //构造、复制、移动和析构
    List();
    List ( const List & rhs );
    List ( List && rhs );
    ~List();
    List & operator = ( const List & rhs );
    List & operator = ( List && rhs );

    bool operator == ( const List & rhs ) const;
    bool operator != ( const List & rhs ) const;

    //容量和清空
    int size() const;
    bool empty() const;
    void clear();

    //访问首尾元素
    Object & front();
    const Object & front() const;
    Object & back();
    const Object & back() const;

    //增删元素
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
};

//类模板的实现需要对使用者可见
#include "list.cpp"

#endif
