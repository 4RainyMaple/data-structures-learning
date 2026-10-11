#ifndef VECTOR_H
#define VECTOR_H

#include<algorithm>
#include<stdexcept>     //out_of_range
using namespace std;

template<typename Object>
class Vector
{
private:
    int theSize;
    int theCapacity;
    Object * objects;
    static const int SPARE_CAPACITY = 16;   //经验数据

public:
    // ==================== 🧩 迭代器类型 ====================
    typedef Object* iterator;
    typedef const Object* const_iterator;   //提供只读版本

    // ==================== 🔵 构造与析构 ====================
    //默认+有参构造函数，explicit用来防止int隐式转换
    explicit Vector ( int initSize = 0 );

    //拷贝构造函数
    Vector ( const Vector & rhs );

    //移动构造函数（剪切）：先给自己初始化，再把参数清空
    Vector ( Vector && rhs );

    //析构函数
    ~Vector();

    // ==================== 🟢 赋值操作 ====================
    //重载=运算符
    Vector & operator = ( const Vector & rhs );
    Vector & operator = ( Vector && rhs );

    // ==================== 🟠 容量管理 ====================
    bool empty() const;
    int size() const;
    int capacity() const;

    //改变容量
    void reserve(int newCapacity);

    //改变大小
    void resize(int newSize);

    // ==================== 🟣 元素访问 ====================
    //读写操作
    Object & operator [] (int idx);

    //只读操作
    const Object & operator [] (int idx) const;

    //读取最后一个元素
    const Object & back () const;

    // ==================== 🟡 迭代器访问 ====================
    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    // ==================== 🔴 增删元素 ====================
    void push_back(const Object & ele);

    //&&表示右值引用，右值是即将被销毁的值，可以直接拿走其资源，但右值引用的变量本身为左值
    void push_back(Object && ele);   //不加const

    void pop_back();

    //在pos前插入元素，返回指向新插入元素的迭代器
    iterator insert ( iterator pos, const Object & ele );
    iterator insert ( iterator pos, Object && ele );

    //删除pos处的元素，返回指向其后一个元素的迭代器
    iterator erase ( iterator pos );

    //删除[from, to)范围内的元素，返回指向删除区间后一个元素的迭代器
    iterator erase ( iterator from, iterator to );

    // ==================== 🔷 比较操作 ====================
    bool operator == (const Vector & rhs) const;
    bool operator != (const Vector & rhs) const;
};

// Vector 是类模板：成员函数的定义必须对每个使用它的源文件可见，
// 否则链接时会报 undefined reference。所以在这里把实现文件包含进来。
#include "vector.cpp"

#endif
