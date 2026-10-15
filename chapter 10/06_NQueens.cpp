#include <vector>
#include <iostream>
using namespace std;

// 按行放置，columns[r] 表示第 r 行皇后所在列；行列编号从 0 开始。
// 判断 (row,col) 是否与前 row 行的皇后冲突，只读取 [0,row) 的位置。
bool canPlace(const vector<int> &columns, int row, int col)
{
    // 检查前 row 行是否有冲突
    for ( int i = 0; i < row; i++ )
        if ( columns[i] == col )
            return false;
    
    // 检查对角线是否有冲突
    for ( int j = 0; j < row; j++ )
        if ( j + columns[j] == row + col )
            return false;

    for ( int k = 0; k < row; k++ )
        if ( k - columns[k] == row - col )
            return false;

    return true;
}

// 搜索从第 row 行起的所有摆法；columns.size() 就是 n。
// row==n 时将完整方案加入 solutions。
// 尝试每一列，放置、递归、撤销；退出时恢复 columns 到进入时的状态。
// 尚未放置的位置为 -1；solutions 保存所有找到的方案。
void placeQueens(int row, vector<int> &columns, vector<vector<int>> &solutions)
{
    // 迭代到最后一行了直接加入答案
    if ( row == columns.size() )
    {
        solutions.push_back(columns);
        return;
    }

    for ( int i = 0; i < columns.size(); i++ )
    {
        if ( canPlace(columns, row, i) )
        {
            columns[row] = i;  // 尝试把当前行的皇后放在第 i 列
            placeQueens(row + 1, columns, solutions);
            columns[row] = -1; // 回溯：撤销这次放置，再尝试下一列
        }
    }
}

// 对外入口：每种答案都是一个数组，返回所有数组的集合
vector<vector<int>> solveNQueens(int n)
{
    vector<vector<int>> solutions;
    vector<int> columns(n, -1);     // 保存该行皇后的列编号

    placeQueens(0, columns, solutions);
    return solutions;
}

int main()
{
    vector<vector<int>> solutions = solveNQueens(5);
    for ( const auto & col : solutions )
    {
        for ( int i : col )
            cout << i << " ";
        cout << endl;
    }
}
