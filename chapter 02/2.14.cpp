#include<vector>
#include<iostream>
using namespace std;


//时间复杂度为O(N)的好算法
int Horner(int x, vector <int> a)
{
    int poly = 0;
    for ( int i = a.size() - 1; i >= 0; i-- )
    {
        poly = x * poly + a[i];
    }
    return poly;
}

int main()
{
    vector <int> a = {2, 1, 0, 8, 4};
    int x = 3;
    cout<<Horner(x,a)<<endl;
}