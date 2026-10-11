#include<iostream>
#include<cmath>
using namespace std;

bool func(int x)
{
    if (x == 1)
        return false;

    bool flag = true;
    for (int i = 2; i <= sqrt(x); i++ )
    {
        if ( x % i == 0 )
            flag = false;
    }
    return flag;
}

int getDigit(int x)
{
    if ( x == 0 )
        return 1;

    int digit = 0;

    while (true)
    {
        digit++;
        if ( pow(2, digit - 1) <= x && x < pow(2, digit) )
            break;
    }

    return digit;
}

//衡量计算素数的时间复杂度应该看二进制位数（输入规模）

int main()
{
    int x;
    cin >> x;
    bool isPrime = func(x);
    if (isPrime)
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;

    cout<<"digit = "<<getDigit(x)<<endl;
}