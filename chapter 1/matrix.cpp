// matrix.cpp —— matrix 类模板的函数定义（由 matrix.h 末尾 #include 进来）
// 因为是模板，函数定义必须对使用者可见，所以被头文件包含，
// 而不是像普通类那样单独编译。函数名上方的注释都在 matrix.h 里。

#include <utility>      // std::move

template<typename T>
matrix<T>::matrix(int rows, int cols) : array(rows)
{
    for(auto & thisRow : array)
    {
        thisRow.resize(cols);
    }
}

template<typename T>
matrix<T>::matrix(vector< vector<T> > v) : array{v} {}

template<typename T>
matrix<T>::matrix(vector< vector<T> > &&v) : array{move(v)} {}

template<typename T>
const vector<T>& matrix<T>::operator[](int row) const
{
    return array[row];
}

template<typename T>
vector<T>& matrix<T>::operator[](int row)
{
    return array[row];
}

template<typename T>
int matrix<T>::numrows() const
{
    return array.size();
}

template<typename T>
int matrix<T>::numcols() const
{
    if (numrows() == 0)
        return 0;
    else
        return array[0].size();
}

template<typename T>
void matrix<T>::resize(int rows, int cols)
{
    array.resize(rows);
    for(auto & thisRow : array)
    {
        thisRow.resize(cols);
    }
}
