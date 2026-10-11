#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

//打印2到n的素数

void printPrime(int n)
{
    vector <bool> v;
    v.resize( n + 1 ); 
    for ( int i = 2; i <= n; i++ )
    {
        v[i] = true;
    }
    
    for ( int j = 2; j <= n; j++ )
    {
        if ( v[j] == false )
            continue;
        cout<<j<<" ";
        //在sqrt(n)终止，因为后面的合数一定有<sqrt(n)的素因子，不必重复删除
        if ( j > sqrt(n) )
            continue;
        int temp = j;

        while ( temp <= n )
        {
            v[temp] = false;
            temp += j;
        }
    }
}

int main()
{
    int n;
    cin >> n;
    printPrime(n);
}