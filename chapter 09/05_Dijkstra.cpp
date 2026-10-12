#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

struct Edge
{
    int to;
    int weight;
};

vector<int> dijkstra(const vector<vector<Edge>> &graph, int start)
{
    int n = (int)graph.size();
    vector<int> dist (n, INT_MAX);
    vector<bool> finalized (n, false);
    dist[start] = 0;

    //每轮确定一个顶点，故 n 轮即可确定所有顶点
    for ( int round = 0; round < n; round++ )
    {
        //找到最近邻顶点
        int v = -1;
        for ( int i = 0; i < n; i++ )
            if ( !finalized[i] && ( v == -1 || dist[i] < dist[v] ) )
                v = i;

        if ( v == -1 || dist[v] == INT_MAX )
            break;

        // v 的距离是所有未确定的顶点中最小的，从别的点绕回来只会更大，故直接确定
        finalized[v] = true;

        for ( const auto & neighbor : graph[v] )
        {
            //跳过已确定最短距离的顶点
            if ( finalized[neighbor.to] )
                continue;
            //防越界，也表示距离太远而不可达
            if ( neighbor.weight + dist[v] >= INT_MAX )
                continue;
            //更新一批顶点的最短距离
            dist[neighbor.to] = min( dist[neighbor.to], dist[v] + neighbor.weight );
        }
    }

    return dist;
}

int main()
{
    // 下标 0~6 对应图中的 v1~v7；每条边为 {终点下标, 权重}。
    vector<vector<Edge>> graph = {
        {{1, 2}, {3, 1}},          // v1 -> v2、v4
        {{3, 3}, {4, 10}},         // v2 -> v4、v5
        {{0, 4}, {5, 5}},          // v3 -> v1、v6
        {{2, 2}, {4, 2}, {5, 8}, {6, 4}}, // v4 -> v3、v5、v6、v7
        {{6, 6}},                 // v5 -> v7
        {},                       // v6 没有出边
        {{5, 1}}                  // v7 -> v6
    };

    vector<int> dist = dijkstra(graph, 0);  // 从 v1 出发。
    for ( int i = 0; i < (int)dist.size(); ++i )
    {
        cout << "v1 -> v" << i + 1 << ": ";
        if ( dist[i] == INT_MAX )
            cout << "INF";
        else
            cout << dist[i];
        cout << endl;
    }
    // 预期距离：0 2 3 1 3 6 5。
}
