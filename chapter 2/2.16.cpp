#include<iostream>
#include<cstdlib>
using namespace std;

/*
只要有一个偶数，则只需迭代一次规模即可减半
若两个奇数，注意到迭代一次后新的a和b之和为原来的a（奇数），故为一奇一偶
因此至多需要两次迭代即可使得规模减半，故时间复杂度为O(logN)
*/
int gcd( int & a, int & b )
{
    if ( a == b )
        return a;
    else
    {
        if ( a%2 == 0 && b%2 == 0 )
        {
            a = a/2;
            b = b/2;
            return 2*gcd(a, b);
        }
        else if ( a%2 == 0 && b%2 != 0 )
        {
            a = a/2;
            return gcd(a, b);
        }
        else if ( a%2 != 0 && b%2 == 0)
        {
            b = b/2;
            return gcd(a, b);
        }
        else 
        {
            int temp = a;       //a会被修改，记得先搞个临时变量储存
            a = ( a + b ) / 2;
            b = abs(( temp - b ) / 2);
            return gcd(a, b);
        }
    }
}

int main()
{
    int a = 125;
    int b = 150;
    cout<<gcd(a,b)<<endl;
}