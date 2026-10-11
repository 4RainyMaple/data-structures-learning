#include<vector>
using namespace std;

template<typename T>
int binarySearch(const vector <T> & v, const T & key)
{
    int low = 0;
    int high = v.size() - 1;
    
    while ( low <= high )
    {
        int center = ( low + high ) / 2;
        if ( v[center] > key )
            high = center - 1;
        else if ( v[center] < key )
            low = center + 1;
        else
            return center;
    }
    return -1;
}