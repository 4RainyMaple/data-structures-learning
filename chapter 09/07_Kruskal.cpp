#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

struct Edge
{
    int from;
    int to;
    int weight;
};

// 返回的树用邻接表表示，起点由外层数组下标确定。
struct AdjacentEdge
{
    int to;
    int weight;
};

// 复习第八章：初始化 n 个单元素集合，根位置保存负的集合大小。
void initSets(vector<int> &s, int n)
{
    s.assign(n, -1);
}

// 路径压缩查找，返回 x 所在集合的根。
int findRootCompressed(vector<int> &s, int x)
{
    if ( s[x] < 0 )
        return x;

    s[x] = findRootCompressed(s, s[x]);
    return s[x];
}

// 按集合大小合并。参数均为根，相同根不作操作。
void unionRootsBySize(vector<int> &s, int root1, int root2)
{
    if ( root1 == root2 )
        return;

    // 根中保存负的集合大小，越小（越负）表示集合越大。
    if ( s[root1] <= s[root2] )
    {
        s[root1] += s[root2];
        s[root2] = root1;
    }
    else
    {
        s[root2] += s[root1];
        s[root1] = root2;
    }
}

// 供 sort 使用：按边权从小到大比较；相同权重返回 false 即可。
bool edgeWeightLess(const Edge &a, const Edge &b)
{
    return a.weight < b.weight;
}

vector<vector<AdjacentEdge>> kruskal(int n, vector<Edge> edges)
{
    if ( n <= 0 )
        return {};

    vector<int> vertex;
    initSets(vertex, n);
    vector<vector<AdjacentEdge>> tree(n);
    if ( n == 1 )
        return tree;    //返回{{}}，与空图和不连通的图区分开来

    sort(edges.begin(), edges.end(), edgeWeightLess);
    int selectedEdges = 0;
    for ( auto itr = edges.begin(); itr != edges.end(); itr++ )
    {
        int root1 = findRootCompressed(vertex, itr->from);
        int root2 = findRootCompressed(vertex, itr->to);
        if ( root1 == root2 )
            continue;

        unionRootsBySize( vertex, root1, root2 );
        tree[itr->from].push_back(AdjacentEdge{itr->to, itr->weight});
        tree[itr->to].push_back(AdjacentEdge{itr->from, itr->weight});
        ++selectedEdges;
        if ( selectedEdges == n - 1 )   //够了 n - 1 条边就直接返回
            return tree;
    }

    return {};  // 边用完仍未选够 n-1 条，说明图不连通。
}

int main()
{
    // 每条无向边只记录一次，顶点编号 0~6 对应 v1~v7。
    vector<Edge> edges = {
        {0, 1, 2}, {0, 2, 4}, {0, 3, 1},
        {1, 3, 3}, {1, 4, 10},
        {2, 3, 2}, {2, 5, 5},
        {3, 4, 7}, {3, 5, 8}, {3, 6, 4},
        {4, 6, 6}, {5, 6, 1}
    };

    vector<vector<AdjacentEdge>> tree = kruskal(7, edges);
    for ( int from = 0; from < (int)tree.size(); ++from )
    {
        for ( const auto & edge : tree[from] )
            cout << "v" << from + 1 << " - v" << edge.to + 1
                 << ": " << edge.weight << "   ";
        cout << endl;
    }
}
