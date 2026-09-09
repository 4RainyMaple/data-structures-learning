#include<iostream>
using namespace std;


//递归快速求幂
long long pow1(int x, int n)
{
    if (n == 0)
        return 1;
    else if (n % 2 == 0)
        return pow1(x*x, n/2);
    else 
        return pow1(x*x, n/2) * x;
}

//二进制快速求幂
long long pow2(int x, int n)
{
    long long result = 1;
    long long base = x;
    int count = 0;
    while ( n > 0 )
    {
        if ( n % 2 == 1 )
        {
            result *= base;
            count++;
        }
        base *= base;   //base自增是一定要做的
        count++;
        n /= 2;         //n的二进制移位要全部操作完成后才进行，防止影响上述判断
    }
    return result;
}