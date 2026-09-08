//输出二进制中1的个数
//若n为偶数，则n/2二进制1的个数相同（右移）
//若n为奇数，则n/2二进制1的个数-1
#include<iostream>
using namespace std;

int func(int n)
{
    //基准情形：0 的二进制中没有 1
    if(n == 0)
        return 0;
    //n为奇数：比 n/2 多一个 1
    if(n % 2 == 1)
        return func(n/2) + 1;
    //n为偶数：和 n/2 相同
    return func(n/2);
}

int main()
{
    int n = 0;
    cin >> n;
    cout<<func(n);
}