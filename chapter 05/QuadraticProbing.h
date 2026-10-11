#ifndef CHAPTER5_QUADRATIC_PROBING_H
#define CHAPTER5_QUADRATIC_PROBING_H

#include <cstddef>
#include <vector>

template <typename HashedObj>
class HashTable
{
public:
    explicit HashTable(int size = 101);

    bool contains(const HashedObj &x) const;

    void makeEmpty();
    bool insert(const HashedObj &x);
    bool insert(HashedObj &&x);
    bool remove(const HashedObj &x);

    //由于元素删除使用懒惰删除，故需要多种状态
    enum EntryType { ACTIVE, EMPTY, DELETED };

private:
    //由于元素具有多种状态，故数组里装的是这个有状态的结构体
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry(const HashedObj &e = HashedObj{}, EntryType i = EMPTY);
        HashEntry(HashedObj &&e, EntryType i = EMPTY);
    };

    std::vector<HashEntry> array;
    int currentSize;

    bool isActive(int currentPos) const;
    int findPos(const HashedObj &x) const;
    void rehash();
    std::size_t myhash(const HashedObj &x) const;

    static int nextPrime(int x);
};

#include "QuadraticProbing.cpp"

#endif
