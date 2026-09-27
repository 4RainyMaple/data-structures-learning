#ifndef CHAPTER5_QUADRATIC_PROBING_CPP
#define CHAPTER5_QUADRATIC_PROBING_CPP

#include "QuadraticProbing.h"

#include <functional>
#include <utility>

using std::size_t;

template <typename HashedObj>
int HashTable<HashedObj>::nextPrime(int x)  //类外定义不需要写static
{
    auto isPrime = [](int x) -> bool
    {
        if ( x < 2 )
            return false;

        for ( int i = 2; i <= x / i; i++ )
            if ( x % i == 0 )
                return false;

        return true;
    };

    while ( !isPrime(x) )
        x++;

    return x;
}

template <typename HashedObj>
HashTable<HashedObj>::HashTable(int size):
array( nextPrime(size) ) , currentSize {0}
{
    makeEmpty();
}

template <typename HashedObj>
HashTable<HashedObj>::HashEntry::HashEntry(const HashedObj &e, EntryType i):
element {e} , info {i}  {}

template <typename HashedObj>
HashTable<HashedObj>::HashEntry::HashEntry(HashedObj &&e, EntryType i):
element {std::move(e)} , info {i}   {}

template <typename HashedObj>
bool HashTable<HashedObj>::contains(const HashedObj &x) const
{
    return isActive(findPos(x));
}

template <typename HashedObj>
void HashTable<HashedObj>::makeEmpty()
{
    for ( auto & entry : array )
        entry.info = EMPTY;
    currentSize = 0;
}

template <typename HashedObj>
bool HashTable<HashedObj>::insert(const HashedObj &x)
{
    int pos = findPos(x);

    if ( isActive(pos) )
        return false;

    array[pos].element = x;
    array[pos].info = ACTIVE;
    currentSize++;

    //元素个数在数组容量一半以内才能确保插入
    if ( currentSize > array.size() / 2 )
        rehash();
    return true;
}

template <typename HashedObj>
bool HashTable<HashedObj>::insert(HashedObj &&x)
{
    int pos = findPos(x);

    if ( isActive(pos) )
        return false;

    array[pos].element = std::move(x);
    array[pos].info = ACTIVE;
    currentSize++;

    if ( currentSize > array.size() / 2 )
        rehash();
    return true;
}

template <typename HashedObj>
bool HashTable<HashedObj>::remove(const HashedObj &x)
{
    //注意：懒惰删除不能减小currentSize，因为删除元素也会影响探测，
    //即使数组里没有活跃的元素也有可能很拥挤，也有可能需要扩容
    int pos = findPos(x);
    if ( !isActive(pos) )
        return false;

    array[pos].info = DELETED;
    return true;
}

template <typename HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos) const
{
    return array[currentPos].info == ACTIVE;
}

template <typename HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj &x) const
{
    size_t pos = myhash(x);

    int detect = 1;
    //注意遇到空位就要停止，（删除标记不停止）即元素不存在时返回第一个空位
    //从这个条件还能看出，有删除标记的位置只能复用原来的元素
    while ( array[pos].info != EMPTY && array[pos].element != x )
    {
        pos += 2 * detect - 1;  //每次递增1,3,5...
        while ( pos >= array.size() )   //当平方数较大时可能需要多次回绕
            pos -= array.size();            
        detect++;
    }
    return (int)pos;
}

template <typename HashedObj>
void HashTable<HashedObj>::rehash()
{
    std::vector <HashEntry> oldArray = array;

    array.resize( nextPrime( 2*array.size() ));
    makeEmpty();    //不要用clear函数，那会使数组长度变为0

    //重新制表，只保留活跃的元素，形成新的排列
    for ( auto & entry : oldArray )
        if ( entry.info == ACTIVE )
            insert( entry.element );
}

template <typename HashedObj>
size_t HashTable<HashedObj>::myhash(const HashedObj &x) const
{
    std::hash<HashedObj> hf;
    return hf(x) % array.size();
}

#endif
