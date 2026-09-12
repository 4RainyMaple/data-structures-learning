//实现一个矩阵类模版
#ifndef MATRIX_H
#define MATRIX_H

#include<vector>
using namespace std;

template<typename T>
class matrix
{
private:
    //定义容器
    vector< vector<T> > array;
public:
    //构造函数
    matrix(int rows, int cols);

    //拷贝构造函数
    matrix(vector< vector<T> > v);

    //移动构造函数（剪切）
    matrix(vector< vector<T> > &&v);

    //注意：冒号语法正在构造函数中使用

    //只读矩阵：第一个const表示返回值不被修改，第二个const表示对象属性不被修改
    const vector<T>& operator[](int row) const;

    //读写矩阵
    vector<T>& operator[](int row);

    //返回行数
    int numrows() const;

    //返回列数
    int numcols() const;

    //重新指定矩阵规格
    void resize(int rows, int cols);
};

// 关键：类模板的函数定义必须对"使用它的文件"可见，否则链接会报 undefined reference。
// 所以这里把实现文件 matrix.cpp 包含进来，任何类型都能直接用。
// 注意：因为 matrix.h 已经包含了 matrix.cpp，编译时只需编译你的主文件，
//       不要单独编译 matrix.cpp。
#include "matrix.cpp"

#endif // MATRIX_H
