#include<string>
#include<iostream>
using namespace std;


void permute(string & str, int low, int high)
{
    if ( high == low )
    {
        cout<<str<<endl;
        return;
    }

    for ( int i = low; i <= high; i++)
    {
        //注意swap是标准库里面的一个函数

        swap( str[low], str[i] );
        permute(str, low + 1, high);
        swap( str[low], str[i] );
    }
}

void permute(string & str)
{
    permute(str, 0, str.size() - 1);
}

int main()
{
    string str = "abcd";
    permute(str);
}