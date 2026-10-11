#include <vector>
#include <iostream>
using namespace std;

// 9.2：graph 是有向图，边 u->v 表示 u 必须排在 v 前面。
// 用入度和队列完成拓扑排序，不修改原图。
// 在函数内部创建 order，成功时返回包含全部顶点的排序结果。
// 有环时返回空数组；空图也返回空数组。
// 合法顺序可能不唯一，不要求得到字典序最小的结果。
vector<int> topologicalSort(const vector<vector<int>> &graph)
{
    int n = (int)graph.size();
    //存放拓扑排序的数组
    vector<int> order;
    order.reserve(n);

    //先计算每个点的入度
    vector<int> indegree(n,0);
    for ( const auto & neighbor : graph )
        for ( const int & v : neighbor )
            ++indegree[v];

    //把入度为0的顶点直接放进order
    for ( int i = 0; i < n; i++ )
        if ( indegree[i] == 0 )
            order.push_back(i);

    //把存入order的顶点的邻顶点的入度减小，入度为0则存入order
    for ( size_t i = 0; i < order.size(); ++i )
        for ( const int & neighbor : graph[order[i]] )
            if ( --indegree[neighbor] == 0 )
                order.push_back(neighbor);

    //若存在环，则必然有一些顶点都无法进入第二步，导致order装不满
    if ( (int)order.size() < n )
        return {};
    return order;
}

int main()
{
    vector<vector<int>> graph = {{1, 2}, {4}, {3}, {4}, {}};
    vector<int> order = topologicalSort(graph);
    if ( order.empty() )
        cout << "NO TopologicalSort";
    for ( const int & v : order )
        cout << v << " ";
}
