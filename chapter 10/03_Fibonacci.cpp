#include <vector>
#include <iostream>
using namespace std;

// 用表代替递归
// 时间 O(n)，空间 O(n)
long long fib1Rec( int n , vector<long long> & done )
{
    //如果已经计算过就直接返回
    if ( done[n] )
        return done[n];
    if ( n == 0 )
    {
        done[0] = 1;
        return 1;
    }
    if ( n == 1 )
    {
        done[0] = 0;
        done[1] = 1;
        return 1;
    }

    done[n] = fib1Rec( n - 1, done ) + fib1Rec( n - 2 , done );
    return done[n];
}

long long fib1( int n )
{
    vector<long long> done(n + 1 , 0);
    return fib1Rec( n , done );
}

// 线性算法：只保留计算下一项所需的最近两项。
// 时间 O(n)，空间 O(1)。
long long fib2( int n )
{
    if ( n <= 1 )
        return 1;

    long long last = 1;
    long long nextToLast = 1;
    long long ans = 0;
    for ( int i = 2; i <= n; i++ )
    {
        ans = last + nextToLast;
        nextToLast = last;
        last = ans;
    }
    return ans;
}

int main()
{
    cout << "fib1:"; 
    for ( int i = 0; i < 20; i++ )
        cout << " " << fib1(i);
    cout << endl;
    cout << "fib2:"; 
    for ( int i = 0; i < 20; i++ )
        cout << " " << fib2(i);
    cout << endl;
}
