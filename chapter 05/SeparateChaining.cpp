#ifndef CHAPTER5_SEPARATE_CHAINING_CPP
#define CHAPTER5_SEPARATE_CHAINING_CPP

#include "SeparateChaining.h"

#include <algorithm>
#include <functional>
#include <utility>

using std::list;
using std::size_t;
using std::vector;

template <typename HashedObj>
HashTable<HashedObj>::HashTable(int size):
theLists (size) , currentSize{0}
{}

template <typename HashedObj>
bool HashTable<HashedObj>::contains(const HashedObj &x) const
{
    size_t key = myhash(x);
    const auto & l = theLists[key];     //使用常量引用避免拷贝
    auto itr = find( l.begin(), l.end(), x );
    return itr != l.end();
}

template <typename HashedObj>
void HashTable<HashedObj>::makeEmpty()
{
    for ( auto & l : theLists ) //注意引用
    {
        l.clear();
    }
    currentSize = 0;
}

template <typename HashedObj>
bool HashTable<HashedObj>::insert(const HashedObj &x)
{
    if ( contains(x) )
        return false;

    size_t key = myhash(x);
    auto & l = theLists[key];
    l.push_back(x);
    currentSize++;

    //意思是，我们希望平均每个链表只装一个元素，这是时间和空间的权衡
    if ( currentSize > theLists.size() )
        rehash();
    return true;
}

template <typename HashedObj>
bool HashTable<HashedObj>::insert(HashedObj &&x)
{
    if ( contains(x) )
        return false;

    size_t key = myhash(x);
    auto & l = theLists[key];
    l.push_back(std::move(x));
    currentSize++;
    if ( currentSize > theLists.size() )
        rehash();
    return true;
}

template <typename HashedObj>
bool HashTable<HashedObj>::remove(const HashedObj &x)
{
    size_t key = myhash(x);
    auto & l = theLists[key];
    auto itr = find( l.begin(), l.end(), x );
    if ( itr == l.end() )
        return false;

    l.erase(itr);
    currentSize--;
    return true;
}

template <typename HashedObj>
void HashTable<HashedObj>::rehash()
{
    vector <list<HashedObj>> oldLists = theLists;

    auto isPrime = [](int x) -> bool
    {
        if ( x < 2 )
            return false;

        for ( int i = 2; i <= x / i; i++ )
        {
            if ( x % i == 0 )
            return false;
        }
        return true;
    };

    auto nextPrime = [&isPrime](int x) -> int
    {
        while ( true )
        {
            if ( isPrime(x) )
                return x;
            x++;
        }
    };

    //创建两倍大的空表
    theLists.resize( nextPrime( 2*theLists.size() ));
    for ( auto & l : theLists )
        l.clear();

    //复制整个表
    currentSize = 0;    //先将大小置0，因为insert会调节大小
    for ( auto & l : oldLists )
        for ( const auto & x : l )
            insert(x);
}

template <typename HashedObj>
std::size_t HashTable<HashedObj>::myhash(const HashedObj &x) const
{
    std::hash<HashedObj> hf;
    return hf(x) % theLists.size();
}

#endif
