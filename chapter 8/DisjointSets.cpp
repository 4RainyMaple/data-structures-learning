#include <vector>
#include <iostream>
using namespace std;

// 初始化：将 s 重置为 n 个互不相交的单元素集合。
// n == 0 时得到空数组；允许对已有的 s 重新初始化。
void initSets(vector<int> &s, int n)
{
    s.assign(n,-1);    
}

// 路径压缩查找：返回根编号，并让本次路径上的非根节点直接指向根。
int findRootCompressed(vector<int> &s, int x)
{
    if ( s[x] < 0 )
        return x;

    s[x] = findRootCompressed(s,s[x]);  //路径压缩，将父节点直接改为根。
    return s[x];
}

// 按大小合并两个根代表的集合。
// 前提：root1、root2 均为根编号。
// 相同根直接结束；小集合挂到大集合下面，并更新新根记录的大小。
void unionRootsBySize(vector<int> &s, int root1, int root2)
{
    if ( root1 == root2 )
        return;
    if ( -s[root1] >= -s[root2] )
    {
        //注意先修改大树根，再修改小数根
        s[root1] += s[root2];
        s[root2] = root1;
    }
    else
    {
        s[root2] += s[root1];
        s[root1] = root2;
    }
}

// 面向任意两个元素 x、y 的合并入口。
// 调用路径压缩查找得到两个根，再调用按大小合并。
// 已在同一集合时，不重复累加大小。
void unionSets(vector<int> &s, int x, int y)
{
    if ( x == y )
        return;
    int root1 = findRootCompressed(s, x);
    int root2 = findRootCompressed(s, y);
    unionRootsBySize(s, root1, root2);
}

// 判断两个有效元素是否属于同一集合。
bool sameSet(vector<int> &s, int x, int y)
{
    return findRootCompressed(s, x) == findRootCompressed(s, y);
}

int main()
{
    vector<int> s;
    initSets(s,6);
    cout << sameSet(s,0,1) << endl;
    unionSets(s,0,1);
    cout << sameSet(s,0,1) <<endl;
    unionSets(s,0,2);
    cout << sameSet(s,1,2) <<endl;
}
