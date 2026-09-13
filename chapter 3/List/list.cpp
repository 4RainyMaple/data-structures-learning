#ifndef LIST_CPP_INCLUDED
#define LIST_CPP_INCLUDED

#include "list.h"

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
        throw Exception{};
}

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

template<typename Object>
int List<Object>::size() const
{
    return theSize;
}

template<typename Object>
bool List<Object>::empty() const
{
    return size() == 0;
}

template<typename Object>
void List<Object>::clear()
{
    while ( !empty() )
        pop_front();
    //注意要先清除元素再将theSize置为零
    theSize = 0;
}

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

template<typename Object>
typename List<Object>::iterator List<Object>::erase ( iterator pos )
{
    assertIteratorBelongsToThis ( pos );
    //end()指向尾哨兵，不能删除
    if ( pos.current == tail )
        throw Exception{};
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
typename List<Object>::iterator List<Object>::insert ( iterator pos, const Object & ele )
{
    pos.assertIsValid();
    if ( pos.theList != this )
        throw Exception{};
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
        throw Exception{};
    Node * p = pos.current;
    Node * newNode = new Node ( std::move(ele), p->prev, p );
    p->prev->next = newNode;
    p->prev = newNode;
    ++theSize;
    return iterator ( *this, newNode, head, tail );
}

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

#endif
