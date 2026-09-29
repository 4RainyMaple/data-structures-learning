#ifndef CHAPTER5_CUCKOO_HASH_TABLE_H
#define CHAPTER5_CUCKOO_HASH_TABLE_H

#include <cstddef>
#include <vector>

template <typename AnyType>
class CuckooHashTable
{
public:
    explicit CuckooHashTable(int size = 101); // 每张表的长度
    void makeEmpty();
    bool contains(const AnyType &x) const;
    bool insert(const AnyType &x);
    bool remove(const AnyType &x);

private:
    struct HashEntry
    {
        AnyType element;
        bool isActive;  //误区：这个状态量不代表懒惰删除，只表示有无元素
        HashEntry(const AnyType &e = AnyType{}, bool active = false);
    };

    std::vector<HashEntry> table1;
    std::vector<HashEntry> table2;
    int currentSize; // 两张表的有效元素总数

    // 两个散列函数各自使用的参数，重建时可重新选择。
    std::size_t seed1;
    std::size_t seed2;
    std::size_t hash1(const AnyType &x) const;
    std::size_t hash2(const AnyType &x) const;

    // 从第一张表开始交替踢出；达到次数上限时返回 false。
    // x 用引用传入，失败时保留最后一个尚未放入表中的元素。
    bool insertHelper(AnyType &x);

    // 用新表长和新散列函数重建，必须同时保留尚未入表的 pending。
    void rehash(int newSize, const AnyType &pending);
    static int nextPrime(int x);
};

#include "CuckooHashTable.cpp"
#endif
