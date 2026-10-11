#include<iostream>
#include<vector>
#include <cstdlib> // 包含 rand() 和 srand()
#include <ctime>   // 包含 time()
#define N 10 
using namespace std;

void algo1(vector <int> & v)
{
    for ( size_t i = 0; i < N; i++ )    //给容器添加N次元素
    {
        while (true)
        {
            int num = rand() % N + 1;       //随机生成1到N之间的整数
            bool flag = true;               //判断能否添加元素
            for ( int j = 0; j < i; j++ )   //与前面的元素查重
            {
                if ( num == v[j] )
                    flag = false;
            }
            if (flag)
            {
                v.push_back(num);
                break;
            }
        }
    }
}

void algo2(vector <int> & v)
{
    vector <bool> used;
    used.resize(N);
    for ( int i = 0; i < N; i++ )
    {
        used[i] = false;
    }

    for (int j = 0; j < N; j++)     //给容器添加N次元素
    {
        while (true)
        {
            int num = rand() % N + 1;
            if ( !used[num] )
            {
                v.push_back(num);
                used[num] = true;
                break;
            }
        }
    }
}

void swap( int & a, int & b )
{
    int temp = a;
    a = b;
    b = temp;
}

void algo3(vector <int> & v)
{
    for ( int i = 0; i < N; i++ )
    {
        v.push_back(i+1);
    }

    for ( int j = 1; j < v.size(); j++ )
    {
        int num = rand() % j;   //随机生成0到j-1之间的整数
        swap ( v[j], v[num] );
    }
}

int main()
{
    srand(time(0));

    vector <int> v;
    //algo1(v);
    //algo2(v);
    algo3(v);

    for (size_t i = 0; i < v.size(); i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}