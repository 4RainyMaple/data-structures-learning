#include <iostream>
#include <vector>
#include "matrix.cpp"    //矩阵源文件的路径
using namespace std;

// ============================================================
// 在"行左→右递增、列上→下递增"的 N×N 矩阵中查找 key
// 最坏情形 O(N)。思路：阶梯法（saddleback search）。
//
// 从右上角 (0, N-1) 出发：
//   - m[row][col] > key：这一"列"往下（含当前格）的元素都更大，
//     整列不可能有 key，向左移一列 (col--)；
//   - m[row][col] < key：这一"行"往左（含当前格）的元素都更小，
//     整行不可能有 key，向下移一行 (row++)；
//   - 相等则找到。
// 每一步都排除一行或一列：row 最多 +N 次、col 最多 -N 次，
// 总共 ≤ 2N 步，每步 O(1)，故最坏 O(N)。
// ============================================================
bool searchMatrix(const matrix<int>& m, int key)
{
    int row = 0;
    int col = m.numcols() - 1;              // 从右上角出发

    while (row < m.numrows() && col >= 0)
    {
        if (m[row][col] == key)
            return true;
        else if (m[row][col] > key)
            --col;                          // 当前格太大：排除这一列，向左
        else
            ++row;                          // 当前格太小：排除这一行，向下
    }

    return false;                           // 走完还没找到
}

int main()
{
    // 构造一个 4×4 的"行、列均递增"矩阵
    vector< vector<int> > data = {
        { 1,  4,  7, 11 },
        { 2,  5,  8, 12 },
        { 3,  6,  9, 16 },
        { 10, 13, 14, 17 }
    };
    matrix<int> m(data);

    // 测试：5,11,13,16,3 在矩阵中；20,0 不在
    int keys[] = { 5, 11, 13, 16, 20, 0, 3 };
    for (int key : keys)
        cout << "key = " << key << " -> "
             << (searchMatrix(m, key) ? "找到" : "未找到") << "\n";

    return 0;
}
