#include <vector>
#include<iostream>
using namespace std;

/*
i 是开始下滤的下标
n 是二叉堆的逻辑大小（忽略交换后的最后一个元素）
*/
template <typename Comparable>
void percDown(std::vector<Comparable> &a, int i, int n)
{
    int child;
    Comparable temp = a[i];

    //给 i 选一个合适的位置填 temp
    while ( 2 * i + 1 < n )
    {
        //找出左右孩子中最大的
        child = 2 * i + 1;
        if ( child != n - 1 && a[child] < a[child + 1] )
            child++;

        //如果父节点小于子节点，就把孩子搬上来，i 沉下去
        if ( temp < a[child] )
        {
            a[i] = a[child];
            i = child;
        }
        else
            break;
    }
    a[i] = temp;
}

//注意：由于传入数组第0号位存有元素，所以在不花费额外开销的前提下做不到逻辑下标与实际下标一致
//左孩子是 2 * i + 1，右孩子是 2 * i + 2
template <typename Comparable>
void heapsort(std::vector<Comparable> &a)
{
    //建堆
    for ( int i = a.size() / 2 - 1; i >= 0; i-- )
        percDown( a, i, (int)a.size() );
    //排序
    for ( int j = a.size() - 1; j > 0; j-- )
    {
        std::swap( a[0], a[j] );    //首位互换
        percDown( a, 0, j );        //将交换后的首元素下滤
    } 
}

int main()
{
    vector <int> test = { 3, 8, 2, 4, 1, 5, 7 };

    heapsort<int>(test);
    for ( const auto & ele : test )
        cout << ele << " ";
    cout << endl;
}