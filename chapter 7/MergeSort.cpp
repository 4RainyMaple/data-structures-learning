#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

// 合并两个相邻的有序闭区间 [leftPos, rightPos - 1] 与 [rightPos, rightEnd]。
// 前提：0 <= leftPos < rightPos <= rightEnd < a.size()。
// tmpArray 与 a 等长且是不同的数组，合并结果须写回 a 的对应区间。
// 保持相等元素的原始相对顺序，区间外的元素不变。
template <typename Comparable>
void merge(vector<Comparable> &a, vector<Comparable> &tmpArray,
           int leftPos, int rightPos, int rightEnd)
{
    tmpArray.clear();   //这个辅助数组是复用的
    int left = leftPos;
    int right = rightPos;
    while ( left < rightPos && right <= rightEnd )
    {
        if ( a[left] <= a[right] )
            tmpArray.push_back(a[left++]);
        else
            tmpArray.push_back(a[right++]);
    }
    if ( left == rightPos )
        while ( right <= rightEnd )
            tmpArray.push_back(a[right++]);
    else
        while ( left < rightPos )
            tmpArray.push_back(a[left++]);

    for ( int i = leftPos; i <= rightEnd; i++ )
        a[i] = tmpArray[i - leftPos];
}

// 自底向上的归并排序：用循环逐轮合并长度为 1、2、4、8……的有序段。
// 在入口中统一分配辅助数组；处理空数组和单元素数组。
template <typename Comparable>
void mergeSort(std::vector<Comparable> &a)
{
    vector<Comparable> temp;    //使用临时辅助数组，空间复杂度为O(N)
    for ( int i = 1; i < a.size(); i *= 2 )
    {
        for ( int j = 0; j + i < a.size(); j += 2 * i ) //若 i + j == a.size() - 1，则归并时最后一个区间仅一个元素
        {
            temp.resize( 2 * i );
            merge( a, temp, j, j + i, std::min(j + 2 * i - 1, (int)a.size() - 1)/*防越界*/ );
        }
    }
}

int main()
{
    vector <int> test = { 3, 8, 2, 4, 1, 5, 7 };

    mergeSort<int>(test);
    for ( const auto & ele : test )
        cout << ele << " ";
    cout << endl;
}