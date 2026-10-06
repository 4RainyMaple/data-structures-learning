#include<iostream>
#include<vector>
using namespace std;

template<typename Comparable>
void ShellSort( vector <Comparable> & a )
{
    for ( int gap = a.size() / 2; gap > 0; gap /= 2 )
        //前 gap 个元素单看已有序，直接从第 gap + 1 个元素开始
        for ( int i = gap; i < (int)a.size(); i++ )
        {
            Comparable temp = a[i];
            int j;
            for ( j = i; j >= gap /*防越界*/ && temp < a[j-1]; j -= gap )
                a[j] = a[j - gap];
            a[j] = temp;
        }
        //验证这段代码的正确性很容易，只需代入 gap = 1 即可
}

int main()
{
    vector <int> test = { 3, 8, 2, 4, 1, 5, 7 };

    ShellSort<int>(test);
    for ( const auto & ele : test )
        cout << ele << " ";
    cout << endl;
}