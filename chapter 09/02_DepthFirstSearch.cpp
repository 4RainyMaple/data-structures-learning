#include <vector>
#include <iostream>
using namespace std;

// 本文件使用无向图，每条边在邻接表中存两个方向。
// 辅助函数：从尚未访问的 v 开始递归搜索。
// visited 大小等于顶点数；首次访问顶点时将其标记为已访问。
// 只访问未访问过的邻居；按邻接表顺序处理。
void dfsVisit(const vector<vector<int>> &graph, int v,
              vector<bool> &visited)
{
    if ( visited[v] )
        return;
    visited[v] = true;
    for ( const auto & adjacent : graph[v] )
        if ( !visited[adjacent] )
            dfsVisit( graph, adjacent, visited );
}

// 遍历从 start 可到达的顶点。start 必须存在。
// 在这里创建 visited，然后调用 dfsVisit。
void depthFirstSearch(const vector<vector<int>> &graph, int start)
{
    vector<bool> visited(graph.size(), false);
    dfsVisit(graph, start, visited);
}

// 统计整个无向图有多少个连通分量，可以调用 dfsVisit。
// 孤立顶点也算一个分量；空图返回 0。
int countComponents(const vector<vector<int>> &graph)
{
    //先建立一个访问列表
    vector<bool> visited(graph.size(), false);
    int count = 0;

    //开始访问：若访问过则跳过，未访问过则计数+1，再深度优先搜索所有连通的顶点
    for ( int v = 0; v < (int)graph.size(); ++v )
    {
        if ( !visited[v] )
        {
            ++count;  // 找到一个新的连通分量。
            dfsVisit(graph, v, visited);
        }
    }

    return count;
}

int main()
{
    vector<vector<int>> graph;
    graph.push_back({1,2});
    graph.push_back({0,3});
    graph.push_back({0});
    graph.push_back({1});
    graph.push_back({});
    cout << countComponents(graph);
}
