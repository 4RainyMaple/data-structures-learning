#include <vector>
#include <climits>
#include <iostream>
using namespace std;

struct Edge
{
    int to;
    int weight;
};

vector<vector<Edge>> prim(const vector<vector<Edge>> &graph)
{
    //空图直接返回
    if ( graph.empty() )
        return {};

    int n = (int)graph.size();
    vector<vector<Edge>> tree(n);       //最小生成树
    vector<bool> inTree(n, false);      //记录点是否进入树
    vector<int> from(n, -1);            //记录进入树的点的来源（无向图双向的需求）
    vector<int> minEdge(n, INT_MAX);    //记录每个点距离已知点的最近距离
    
    //初始化上述容器
    inTree[0] = true;
    minEdge[0] = 0;
    for ( const auto & edge : graph[0] )
    {
        minEdge[edge.to] = edge.weight;
        from[edge.to] = 0;          //建立双边关系
    }
    
    //开始组建最小生成树
    // 起点 0 已经在树中，只需再循环 n - 1 轮，否则最后一轮回返回空数组。
    for ( int round = 1; round < n; round++ )
    {
        //找到距离已在树中的点最近的点
        int v = -1;
        for ( int i = 0; i < n; i++ )
            if ( ( v == -1 || minEdge[i] < minEdge[v] ) && !inTree[i] )
                v = i;
        
        //将 v 装进树中，不连通的图直接返回空数组
        if ( v == -1 || minEdge[v] == INT_MAX )
            return {};

        inTree[v] = true;
        //记录双向关系
        tree[v].push_back( Edge{from[v],minEdge[v]} );
        tree[from[v]].push_back( Edge{v, minEdge[v]});
        

        //更新 v 邻顶点的最短距离
        for ( const auto & neighbor : graph[v] )
        {
            if ( inTree[neighbor.to] )
                continue;
            //找到更短距离才更新
            if ( neighbor.weight < minEdge[neighbor.to] )
            {
                from[neighbor.to] = v;
                minEdge[neighbor.to] = neighbor.weight;
            }
        }
    }

    return tree;
}

int main()
{
    vector<vector<Edge>> graph = {
        {{1, 2}, {2, 4}, {3, 1}},                  // v1
        {{0, 2}, {3, 3}, {4, 10}},                 // v2
        {{0, 4}, {3, 2}, {5, 5}},                  // v3
        {{0, 1}, {1, 3}, {2, 2}, {4, 7}, {5, 8}, {6, 4}}, // v4
        {{1, 10}, {3, 7}, {6, 6}},                 // v5
        {{2, 5}, {3, 8}, {6, 1}},                  // v6
        {{3, 4}, {4, 6}, {5, 1}}                   // v7
    };

    vector<vector<Edge>> tree = prim(graph);
    for ( int i = 0; i < graph.size(); i++ )
    {
        for ( const auto & edge : tree[i] )
            cout << "v" << i + 1 << " - v" << edge.to + 1 << ":" << edge.weight <<"   ";
        cout << endl;
    }
}
