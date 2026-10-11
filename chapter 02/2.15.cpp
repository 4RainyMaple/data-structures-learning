#include<iostream>
#include<vector>
using namespace std;

//二分查找+循环，复杂度为O(NlogN)
int binarySearch(const vector  <int> & v, const int & key)
{
    int low = 0;
    int high = v.size() - 1;
    while (low <= high)
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

/*设 g(N) = v[N] - N, 则 g(N+1) = v[N+1] - (N+1) >= v[N] + 1 -(N+1) = g(N)
说明g(N)是不减的函数，可用二分查找的方法去查找零点，时间复杂度为O(logN)*/
bool existFixedPoint(const vector <int> & v)
{
    int low = 0;
    int high = v.size() - 1;

    while ( low <= high )
    {
        int center = ( low + high ) / 2;
        if ( v[center] < center )
            low = center + 1;
        else if ( v[center] > center )
            high = center - 1;
        else
            return true;
    }
    return false;
}

int main()
{
    vector <int> v = {0,1,2,3};
    // for (int i = 0; i < v.size(); i++)
    // {
    //     if ( binarySearch(v,i) == -1 )
    //         continue;
    //     cout<<"存在i="<<i<<"使得v[i]=i"<<endl;
    // }
    if (existFixedPoint(v))
        cout<<"true"<<endl;
    else
        cout<<"false"<<endl;
}