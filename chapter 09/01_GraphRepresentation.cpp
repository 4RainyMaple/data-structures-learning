#include <vector>
#include <iostream>
using namespace std;

// 将 graph 重置为 n 个顶点、没有边的邻接表，n 可以为 0。
void initGraph(vector<vector<int>> &graph, int n)
{
    graph.assign(n,{});
}

// 添加有向边 from -> to，只添加一个方向。
void addDirectedEdge(vector<vector<int>> &graph, int from, int to)
{
    graph[from].push_back(to);
}

// 添加无向边 u-v，可以调用上面的 addDirectedEdge 两次。
void addUndirectedEdge(vector<vector<int>> &graph, int u, int v)
{
    addDirectedEdge(graph, u, v);
    addDirectedEdge(graph, v, u);
}

// 转成 n*n 的 0/1 邻接矩阵：有边为 1，没有边为 0，只能标记一个方向。
vector<vector<int>> toAdjacencyMatrix(const vector<vector<int>> &graph)
{
    int n = (int)graph.size();
    vector<vector<int>> adjacentMatrix(n,vector<int>(n,0));
    for ( int i = 0; i < n; i++ )
        for ( const auto & vertex : graph[i] )
            adjacentMatrix[i][vertex] = 1;
    return adjacentMatrix;
}

int main()
{
    vector<vector<int>> graph(4);
    addUndirectedEdge(graph, 0, 1);
    addUndirectedEdge(graph, 0, 2);
    addUndirectedEdge(graph, 1, 3);
    graph = toAdjacencyMatrix(graph);
    for ( const auto & i : graph )
    {
        for ( const auto & j : i )
            cout << j <<" ";
        cout << endl;
    }
}
