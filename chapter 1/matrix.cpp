//实现一个矩阵类模版
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
    matrix(int rows, int cols) : array(rows)
    {
        for(auto & thisRow : array)
        {
            thisRow.resize(cols);
        }
    }

    //拷贝构造函数
    matrix(vector< vector<T> > v) : array{v} {}

    //移动构造函数（剪切）
    matrix(vector< vector<T> > &&v) : array{move(v)} {}

    //注意：冒号语法正在构造函数中使用

    //只读矩阵：第一个const表示返回值不被修改，第二个const表示对象属性不被修改
    const vector<T>& operator[](int row) const
    {
        return array[row];
    }

    //读写矩阵
    vector<T>& operator[](int row)
    {
        return array[row];
    }

    //返回行数
    int numrows() const
    {
        return array.size();
    }

    //返回列数
    int numcols() const
    {
        if (numrows() == 0)
            return 0;
        else
            return array[0].size();
    }

    //重新指定矩阵规格
    void resize(int rows, int cols)
    {
        array.resize(rows);
        for(auto & thisRow : array)
        {
            thisRow.resize(cols);
        }
    }
};