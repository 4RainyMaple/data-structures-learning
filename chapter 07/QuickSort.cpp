#include <vector>
#include <iostream>
using namespace std;

template <typename Comparable>
void preparePivot(vector<Comparable> &a, int left, int right)
{
    // 少于3个元素直接返回
    if ( right - left < 2 )
        return;

    int mid = ( left + right ) / 2;
    if ( a[left] > a[mid] )
        std::swap(a[left], a[mid]);
    if ( a[mid] > a[right] )
        std::swap(a[mid], a[right]);
    if ( a[left] > a[mid] )
        std::swap(a[left], a[mid]);

    std::swap(a[left], a[mid]);
}

template <typename Comparable>
void quicksort(vector<Comparable> &a, int left, int right)
{
    //终止条件
    if ( left >= right )
        return;

    preparePivot(a, left, right);
    Comparable temp = a[left];
    //注意一开始 i 就在 left 的位置等待被填坑
    int i = left;
    int j = right;
    while ( i < j )
    {
        //先从右边开始遍历
        while ( i < j && a[j] >= temp )
            j--;
        if ( i < j )
        {
            a[i] = a[j];
            i++;
        }
        //再遍历左边
        while ( i < j && a[i] <= temp )
            i++;
        if ( i < j )
        {
            a[j] = a[i];
            j--;
        }
    }
    a[i] = temp;
    quicksort(a, left, i - 1);
    quicksort(a, i + 1, right);
}

template <typename Comparable>
void quicksort(vector<Comparable> &a)
{
    quicksort(a, 0, (int)a.size() - 1);
}

int main()
{
    vector <int> test = { 3, 8, 2, 4, 1, 5, 7 };

    quicksort<int>(test);
    for ( const auto & ele : test )
        cout << ele << " ";
    cout << endl;
}
