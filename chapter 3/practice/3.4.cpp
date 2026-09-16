#include<algorithm>
using namespace std;

template<typename Container>
//3.4：求两个已排序的表的交集
//由于是有序数组，可以有O(|L1|+|L2|)的算法
Container listIntersection ( const Container & L1, const Container & L2 )
{
    Container ret;

    auto itr1 = L1.begin();
    auto itr2 = L2.begin();
    while ( itr1 != L1.end() && itr2 != L2.end() )
    {
        if ( *itr1 == *itr2 )
        {
            ret.push_back(*itr1);
            ++itr1;
            ++itr2;
        }

        //谁小推进谁，这样后面可能遇到更大的相同元素
        else if ( *itr1 > *itr2)
            ++itr2;    

        else
            ++itr1;
    }

    return ret;
}

//3.5：求两个已排序的表的并集
template<typename Container>
Container listUnion ( const Container & L1, const Container & L2 )
{
    Container ret ;
    auto itr1 = L1.begin();
    auto itr2 = L2.begin();
    while ( itr1 != L1.end() && itr2 != L2.end() )
    {
        if ( *itr1 < *itr2 )
        {
            ret.push_back(*itr1);
            ++itr1;
        }
        else if ( *itr1 > *itr2 )
        {
            ret.push_back(*itr2);
            ++itr2;
        }
        else
        {
            ret.push_back(*itr1);
            ++itr1;
            ++itr2;
        }

    }

    if ( itr1 == L1.end() )
    {
        while ( itr2 != L2.end() )
        {
            ret.push_back(*itr2);
            ++itr2;
        }
    }

    if ( itr2 == L2.end() )
    {
        while ( itr1 != L1.end() )
        {
            ret.push_back(*itr1);
            ++itr1;
        }
    }

    return ret;
}
