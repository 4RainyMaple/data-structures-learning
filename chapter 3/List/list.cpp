#ifndef LIST_CPP_INCLUDED
#define LIST_CPP_INCLUDED

#include "list.h"

// ==================== ⚙️ 内部辅助函数 ====================
template<typename Object>
void List<Object>::initial()
{
    theSize = 0;
    //与迭代器相比，链表的首尾节点需要长期存在，故在堆区开辟内存
    head = new Node;
    tail = new Node;
    //连接首尾节点
    head->next = tail;
    tail->prev = head;
}

template<typename Object>
void List<Object>::assertIteratorBelongsToThis ( const const_iterator & itr ) const
{
    itr.assertIsValid();
    if ( itr.theList != this )
        throw std::out_of_range ( "Iterator does not belong to this List" );
}

// ==================== 🔵 构造与析构 ====================
template<typename Object>
List<Object>::List()
{
    //直接调用初始化函数即可
    initial();
}

template<typename Object>
List<Object>::List ( const List & rhs )
{
    initial();
    for ( auto x : rhs )
        push_back ( x );
}

template<typename Object>
List<Object>::List ( List && rhs ) :
theSize {rhs.theSize}, head {rhs.head}, tail {rhs.tail}
{
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

template<typename Object>
List<Object>::~List()
{
    clear();
    delete head;
    delete tail;
}

// ==================== 🟢 赋值操作 ====================
template<typename Object>
List<Object> & List<Object>::operator = ( const List & rhs )
{
    if ( this != &rhs )   //要比较地址而非内容
    {
        List temp = rhs;
        std::swap ( *this, temp );
    }
    return *this;
}

template<typename Object>
List<Object> & List<Object>::operator = ( List && rhs )
{
    std::swap ( theSize, rhs.theSize );
    std::swap ( head, rhs.head );
    std::swap ( tail, rhs.tail );
    return *this;
}

// ==================== 🟠 容量和清空 ====================
template<typename Object>
bool List<Object>::empty() const
{
    return size() == 0;
}

template<typename Object>
int List<Object>::size() const
{
    return theSize;
}

template<typename Object>
void List<Object>::clear()
{
    while ( !empty() )
        pop_front();
    //注意要先清除元素再将theSize置为零
    theSize = 0;
}

// ==================== 🟣 元素访问 ====================
template<typename Object>
Object & List<Object>::front()
{
    return *begin();
}

template<typename Object>
const Object & List<Object>::front() const
{
    return *begin();
}

template<typename Object>
Object & List<Object>::back()
{
    return *(--end());
}

template<typename Object>
const Object & List<Object>::back() const
{
    return *(--end());
}

// ==================== 🟡 迭代器访问 ====================
template<typename Object>
typename List<Object>::iterator List<Object>::begin()
{
    return iterator ( *this, head->next, head, tail );
}

template<typename Object>
typename List<Object>::const_iterator List<Object>::begin() const
{
    return const_iterator ( *this, head->next, head, tail );
}

template<typename Object>
typename List<Object>::iterator List<Object>::end()
{
    return iterator ( *this, tail, head, tail );
}

template<typename Object>
typename List<Object>::const_iterator List<Object>::end() const
{
    return const_iterator ( *this, tail, head, tail );
}

// ==================== 🔴 增删元素 ====================
template<typename Object>
void List<Object>::push_front ( const Object & rhs )
{
    insert ( begin(), rhs );
}

template<typename Object>
void List<Object>::push_front ( Object && rhs )
{
    insert ( begin(), std::move(rhs) );
}

template<typename Object>
void List<Object>::push_back ( const Object & rhs )
{
    insert ( end(), rhs );
}

template<typename Object>
void List<Object>::push_back ( Object && rhs )
{
    insert ( end(), std::move(rhs) );
}

template<typename Object>
void List<Object>::pop_front()
{
    erase ( begin() );
}

template<typename Object>
void List<Object>::pop_back()
{
    erase ( --end() );
}

template<typename Object>
typename List<Object>::iterator List<Object>::insert ( iterator pos, const Object & ele )
{
    pos.assertIsValid();
    if ( pos.theList != this )
        throw std::out_of_range ( "Iterator does not belong to this List" );
    Node * p = pos.current;
    //先创建新节点，让它连接到原来的前一个节点和当前位置
    Node * newNode = new Node ( ele, p->prev, p );
    //让原来的前一个节点指向新节点
    p->prev->next = newNode;
    //让当前位置的前一个节点也指向新节点
    p->prev = newNode;
    //插入后元素个数加一
    ++theSize;
    //返回指向新插入节点的迭代器
    return iterator ( *this, newNode, head, tail );
}

template<typename Object>
typename List<Object>::iterator List<Object>::insert ( iterator pos, Object && ele )
{
    pos.assertIsValid();
    if ( pos.theList != this )
        throw std::out_of_range ( "Iterator does not belong to this List" );
    Node * p = pos.current;
    Node * newNode = new Node ( std::move(ele), p->prev, p );
    p->prev->next = newNode;
    p->prev = newNode;
    ++theSize;
    return iterator ( *this, newNode, head, tail );
}

template<typename Object>
typename List<Object>::iterator List<Object>::erase ( iterator pos )
{
    assertIteratorBelongsToThis ( pos );
    //end()指向尾哨兵，不能删除
    if ( pos.current == tail )
        throw std::out_of_range ( "erase(): cannot erase end iterator" );
    Node * p = pos.current;
    iterator retItr ( *this, p->next, head, tail );
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    --theSize;
    return retItr;
}

template<typename Object>
typename List<Object>::iterator List<Object>::erase ( iterator from, iterator to )
{
    assertIteratorBelongsToThis ( from );
    assertIteratorBelongsToThis ( to );
    for ( iterator itr = from; itr != to; )
        itr = erase ( itr );   //erase本来就有让迭代器前进的效果
    return to;  //右边是开区间，故直接返回to即可
}

template<typename Object>
void List<Object>::splice ( iterator position, List & lst )
{
    //检查position是否有效，并且属于本表
    assertIteratorBelongsToThis ( position );
    //没有元素需要转移，或者两个表是同一个表时，直接返回
    if ( lst.theSize == 0 || this == &lst )
        return;

    //先保存插入位置及其前一个节点，current是节点指针
    Node * p = position.current;
    Node * before = p->prev;    //必须要现在保存这个节点，操作后就拿不到了
    //只转移实际存储元素的节点，不转移lst的首尾哨兵
    Node * first = lst.head->next;
    Node * last = lst.tail->prev;

    //把这一段节点的开头接到before后面，两个方向都要连接
    before->next = first;
    first->prev = before;
    //把这一段节点的末尾接到p前面，中间各节点的连接不变
    last->next = p;
    p->prev = last;

    //保留lst原来的首尾哨兵，让它们互相连接，恢复为空表
    lst.head->next = lst.tail;
    lst.tail->prev = lst.head;
    //先增加本表的元素个数，再将lst的元素个数清零
    theSize += lst.theSize;
    lst.theSize = 0;
}

// ==================== 🔷 比较操作 ====================
template<typename Object>
bool List<Object>::operator == ( const List & rhs ) const
{
    auto itr1 = begin();
    auto itr2 = rhs.begin();
    while ( itr1 != end() && itr2 != rhs.end() )
    {
        if ( *itr1 != *itr2 )
            return false;
        ++itr1;
        ++itr2;
    }
    return itr1 == end() && itr2 == rhs.end();
}

template<typename Object>
bool List<Object>::operator != ( const List & rhs ) const
{
    return !( *this == rhs );
}

#endif
