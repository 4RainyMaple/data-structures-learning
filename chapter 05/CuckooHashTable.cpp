#ifndef CHAPTER5_CUCKOO_HASH_TABLE_CPP
#define CHAPTER5_CUCKOO_HASH_TABLE_CPP

#include "CuckooHashTable.h"
#include <functional>
#include <random>
#include <utility>

template <typename AnyType>
CuckooHashTable<AnyType>::CuckooHashTable(int size):
table1(nextPrime(size)) , table2(nextPrime(size)) , 
currentSize {0} , seed1 {37} , seed2 {101}  {}  //37和101是随便选的

template <typename AnyType>
CuckooHashTable<AnyType>::HashEntry::HashEntry(const AnyType &e, bool active):
element {e} , isActive {active}   {}

template <typename AnyType>
void CuckooHashTable<AnyType>::makeEmpty()
{
    for ( size_t i = 0; i < table1.size(); i++ )
        table1[i].isActive = false;
    for ( size_t j = 0; j < table2.size(); j++ )
        table2[j].isActive = false;
    currentSize = 0;
}

template <typename AnyType>
bool CuckooHashTable<AnyType>::contains(const AnyType &x) const
{
    //记得检查位置元素是否活跃
    const auto & a = table1[hash1(x)];
    const auto & b = table2[hash2(x)];
    return (a.element == x && a.isActive) 
        || (b.element == x && b.isActive);
}

template <typename AnyType>
bool CuckooHashTable<AnyType>::insert(const AnyType &x)
{
    //先查重
    if(contains(x))
        return false;

    AnyType pending = x;    //插入失败后x会被修改，故定义一个新的变量传入
    if (!insertHelper(pending)) //if语句里面的函数是会被执行的
        rehash(2*table1.size(), pending);

    return true;
}

template <typename AnyType>
bool CuckooHashTable<AnyType>::remove(const AnyType &x)
{
    auto & a = table1[hash1(x)];
    if (a.element == x && a.isActive)
    {
        a.isActive = false;
        currentSize--;
        return true;
    }
    auto & b = table2[hash2(x)];
    if (b.element == x && b.isActive)
    {
        b.isActive = false;
        currentSize--;
        return true;
    }
    return false;
}


/*同一程序中，两个函数中调用的std::hash对于同一个x的返回值是相同的，
所以需要两个seed以及不同的运算方式来调节在表中的位置*/
template <typename AnyType>
std::size_t CuckooHashTable<AnyType>::hash1(const AnyType &x) const
{
    //加上偏移量并取余。
    std::size_t value = std::hash<AnyType>{}(x);    //创建一个默认的散列函数对象
    return (value + seed1) % table1.size();
}

template <typename AnyType>
std::size_t CuckooHashTable<AnyType>::hash2(const AnyType &x) const
{
    //使用整数除法再取余
    std::size_t value = std::hash<AnyType>{}(x);
    return (value / seed2) % table2.size();
}

template <typename AnyType>
bool CuckooHashTable<AnyType>::insertHelper(AnyType &x)
{
    const int MAX_KICKS = 100;  //设置搬运次数上限
    bool firstTable = true;     //判断需要去哪张表操作
    for ( int count = 0; count < MAX_KICKS; count++ )
    {
        if (firstTable)
        {
            auto & a = table1[hash1(x)];
            if ( !a.isActive )
            {
                currentSize++;
                a.element = x;
                a.isActive = true;
                return true;
            }
            std::swap(x,a.element);
        }
        else
        {
            auto & b = table2[hash2(x)];
            if ( !b.isActive )
            {
                currentSize++;
                b.element = x;
                b.isActive = true;
                return true;
            }
            std::swap(x,b.element);
        }
        //如果没有返回，则需要继续交换，前往另一张表
        firstTable = !firstTable;
    }
    return false;
}

template <typename AnyType>
void CuckooHashTable<AnyType>::rehash(int newSize, const AnyType &pending)
{
    auto oldTable1 = table1;
    auto oldTable2 = table2;
    makeEmpty();
    table1.resize(nextPrime(newSize));
    table2.resize(nextPrime(newSize));

    //只插入有效元素
    for ( auto & x : oldTable1 )
        if (x.isActive)
            insert(x.element);
    for ( auto & y : oldTable2 )
        if (y.isActive)
            insert(y.element);

    insert(pending);
}

template <typename AnyType>
int CuckooHashTable<AnyType>::nextPrime(int x)
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

#endif
