#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
using namespace std;

// 时间 O(n^3)，空间 O(n^2)。
long long minMatrixChainCost(const vector<int> &c)
{
    //c[0]表示第一个矩阵的行数，其他项表示下标对应矩阵的列数，n 表示矩阵的个数
    int n = c.size() - 1;
    vector<vector<long long>> m(n + 1, vector<long long>(n + 1, 0));

    //显然我们需要先遍历小的区间再遍历大的区间，这样计算大区间时才能调用小区间的结果
    for ( int right = 2; right <= n; right++ )
    {
        for ( int left = right - 1; left >= 1; left-- )
        {
            m[left][right] = numeric_limits<long long>::max() / 4;   // 初始化，最后主对角线以下的区域无效
            for ( int k = left; k < right; k++ )
                m[left][right] = min( m[left][right] , 
                    m[left][k] + m[k+1][right] + (long long)c[left - 1]*c[k]*c[right] );
        }
    }

    return m[1][n];
}

int main()
{
    vector<int> c = { 50, 10, 40, 30, 5 };
    cout << minMatrixChainCost(c);
}
