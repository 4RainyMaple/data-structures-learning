// 习题1.14：设计类模板 OrderedCollection，存储（在一个数组中的）Comparable 对象集合，
//          以及该集合的当前大小。
//          提供 public 函数：isEmpty、makeEmpty、insert、remove、findMin、findMax。
//          findMin / findMax 分别返回集合中最小项 / 最大项的引用。
//
// 实现说明：
//   - 这里用 std::vector 充当"动态数组"，它自带 size，天然满足"在数组中存储"和"当前大小"。
//   - "Comparable" 指元素类型 T 支持比较；本实现统一用 <（不用 >），
//     因此 T 只需提供 operator< 即可，可用 int、double、string 等实例化。

#include <vector>      // std::vector
#include <algorithm>   // std::find
#include <cassert>     // assert（用于空集合防御）
using namespace std;

template<typename T>
class OrderedCollection
{
private:
    vector<T> v;       // 用 vector（动态数组）存储元素，v.size() 即当前大小

public:
    // 判断集合是否为空
    bool isEmpty() const
    {
        return v.empty();          // 等价于 v.size() == 0
    }

    // 清空集合
    void makeEmpty()
    {
        v.clear();
    }

    // 插入一个元素（放到数组末尾）
    void insert(const T & ele)
    {
        v.push_back(ele);
    }

    // 删除所有等于 ele 的元素
    void remove(const T & ele)
    {
        while (true)
        {
            auto it = find(v.begin(), v.end(), ele);   // 找第一个等于 ele 的位置
            if (it != v.end())                          // 找到了
                v.erase(it);                            // 删掉，然后继续找下一个
            else
                break;                                  // 找不到，结束（空集合时直接走到这里，安全）
        }
    }

    // 返回集合中最大元素的引用。
    // 前提：集合非空。空集合上没有元素可返回引用，属于未定义行为，故用 assert 拦截（debug 下）。
    const T & findMax() const
    {
        assert(!isEmpty());

        auto max = v.begin();                           // 先假设第一个元素最大
        for (auto cur = v.begin() + 1; cur != v.end(); ++cur)
        {
            if (*max < *cur)                            // 若当前最大 < 当前元素，则更新
                max = cur;
        }
        return *max;                                    // 返回容器内元素（迭代器所指对象）的引用
    }

    // 返回集合中最小元素的引用。
    // 前提：集合非空。空集合上没有元素可返回引用，属于未定义行为，故用 assert 拦截（debug 下）。
    const T & findMin() const
    {
        assert(!isEmpty());

        auto min = v.begin();                           // 先假设第一个元素最小
        for (auto cur = v.begin() + 1; cur != v.end(); ++cur)
        {
            if (*cur < *min)                            // 若当前元素 < 当前最小，则更新
                min = cur;
        }
        return *min;                                    // 返回容器内元素（迭代器所指对象）的引用
    }
};
