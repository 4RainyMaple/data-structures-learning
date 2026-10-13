#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>
using namespace std;

// 时间 O(n^3)，额外空间 O(n^2)。
vector<vector<int>> floydWarshall(const vector<vector<int>> &weights)
{
    int n = (int)weights.size();
    vector<vector<int>> dist(n,vector<int>(n,INT_MAX));

    //初始化dist
    for ( int i = 0; i < n; i++ )
        for ( int j = 0; j < n; j++ )
            dist[i][j] = weights[i][j];

    for ( int k = 0; k < n; k++ )
        for ( int i = 0; i < n; i++ )
            for  ( int j = 0; j < n; j++ )
            {
                if ( dist[i][k] == INT_MAX || dist[k][j] == INT_MAX )
                    continue;   //不能直接加，因为负值会让一条本来不可达的边相加后误判为可达

                long long throughK = (long long)dist[i][k] + dist[k][j];
                if ( throughK < dist[i][j] && throughK >= INT_MIN )
                    dist[i][j] = (int)throughK;
            }

    return dist;
}

int main()
{
    const int n = 5;
    vector<vector<int>> weights(n, vector<int>(n, INT_MAX));

    for ( int i = 0; i < n; i++ )
        weights[i][i] = 0;

    // 有向边：0->1(4), 0->2(10), 1->2(-2), 2->3(3)。
    // 图中有负边但没有环，因此不存在负权环；顶点 4 孤立。
    weights[0][1] = 4;
    weights[0][2] = 10;
    weights[1][2] = -2;
    weights[2][3] = 3;

    auto printMatrix = [](const vector<vector<int>> &matrix)
    {
        if ( matrix.empty() )
        {
            cout << "(empty)\n";
            return;
        }

        for ( const vector<int> &row : matrix )
        {
            for ( int j = 0; j < (int)row.size(); j++ )
            {
                if ( row[j] == INT_MAX )
                    cout << "INT_MAX";
                else
                    cout << row[j];

                if ( j + 1 < (int)row.size() )
                    cout << '\t';
            }
            cout << '\n';
        }
    };

    cout << "All-pairs shortest distances:\n";
    printMatrix(floydWarshall(weights));
}
