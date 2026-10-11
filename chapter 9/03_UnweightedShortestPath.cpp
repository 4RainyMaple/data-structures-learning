#include <vector>
#include <queue>
#include <iostream>
using namespace std;

// 用 BFS 求 start 到所有顶点的最短路径。
// 返回距离数组 dist，大小为顶点数。
// dist[start]=0，不可达为 -1。
vector<int> unweightedShortestPath(const vector<vector<int>> &graph, int start)
{
    vector<int> dist(graph.size(), -1); //-1表示尚未处理
    queue<int> q;       //队列里面的元素尚未处理邻顶点

    dist[start] = 0;
    q.push(start);

    while ( !q.empty() )
    {
        //把队首拿出来，处理它的邻顶点
        int v = q.front();
        q.pop();
        for ( const auto & w : graph[v] )
            //只处理未处理过的顶点
            if ( dist[w] == -1 )
            {
                dist[w] = dist[v] + 1;
                q.push(w);
            }
    }

    return dist;
}

int main()
{
    vector<vector<int>> graph = {{1, 2}, {0, 3}, {0}, {1}, {}};
    vector<int> dist = unweightedShortestPath(graph, 0);

    for ( int distance : dist )
        cout << distance << " ";
    cout << endl;  // 应输出：0 1 1 2 -1
}
