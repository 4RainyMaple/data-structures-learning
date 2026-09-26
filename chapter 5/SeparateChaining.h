#ifndef CHAPTER5_SEPARATE_CHAINING_H
#define CHAPTER5_SEPARATE_CHAINING_H

#include <cstddef>
#include <list>
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

private:
    std::vector<std::list<HashedObj>> theLists;
    int currentSize;

    void rehash();
    std::size_t myhash(const HashedObj &x) const;
};

#include "SeparateChaining.cpp"

#endif
