#include <vector>
#include <iostream>
using namespace std;

template <typename Comparable>
void insertionSort(std::vector<Comparable> &a)
{
    int len = (int)a.size();
    //这里不从0开始，因为只有一个元素是有序的
    for ( size_t i = 1; i < len; i++ )
    {
        Comparable temp = a[i];
        int j;
        //只要temp还比较大，就把右边的几个元素右移，停下后把该处位置换为temp
        for ( j = i; j > 0 && temp < a[j-1]; j-- )
            a[j] = a[j-1];
        a[j] = temp;
    }
}

//[left,right]
template <typename Comparable>
void insertionSort(std::vector<Comparable> &a, int left, int right)
{
    for ( int i = left + 1; i <= right; i++ )
    {
        Comparable temp = a[i];
        int j;
        for ( j = i; j > left && temp < a[j-1]; j-- )
            a[j] = a[j-1];
        a[j] = temp;
    }
}

int main()
{
    vector <int> test = { 3, 8, 2, 4, 1, 5, 7 };
    insertionSort( test, 1, 5 );
    for ( const auto & ele : test )
        cout << ele << " ";
    cout << endl;

    insertionSort<int>(test);
    for ( const auto & ele : test )
        cout << ele << " ";
    cout << endl;
}