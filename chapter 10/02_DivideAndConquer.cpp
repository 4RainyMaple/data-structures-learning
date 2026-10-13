#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

//分治算法求解最大子区间问题（并非最好算法）
long long maxSubSumRec(const vector<int> &a, int left, int right)
{
    if ( left == right )
        return (long long)a[left];
    int mid = ( left + right ) / 2;
    long long leftMax = maxSubSumRec( a, left, mid );
    long long rightMax = maxSubSumRec( a, mid + 1, right );
    long long leftSubMax = INT_MIN;
    long long rightSubMax = INT_MIN;
    long long tempSum = 0;
    for ( int i = mid + 1; i <= right; i++ )
    {
        tempSum += a[i];
        rightSubMax = max( rightSubMax, tempSum );
    }
    tempSum = 0;
    for ( int j = mid; j >= left; j-- )
    {
        tempSum += a[j];
        leftSubMax = max( leftSubMax, tempSum );
    }
    long long temp = max( rightMax, leftMax );
    return max( temp, leftSubMax + rightSubMax );
}

long long maxSubSum(const vector<int> &a)
{
    return maxSubSumRec( a, 0, (int)a.size() - 1);
}

int main()
{
    //这里规定子串不可以为空
    vector<int> a = {-2,-11,-4,-13,-5,-2};
    cout << maxSubSum(a);
}
