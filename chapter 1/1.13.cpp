#include<vector>
#include<algorithm>
using namespace std;

template<typename Object>
class Collection
{
public:
    //判断该类是否为空
    bool isEmpty()
    {
        return v.size() == 0;
    }

    //清空该类
    void makeEmpty()
    {
        v.clear();
    }

    //插入元素
    void insert(const Object & object)
    {
        v.push_back(object);
    }

    //删除元素
    void remove(const Object & object)
    {
        while(true)
        {
            auto it = find(v.begin(), v.end(), object);
            if (it != v.end() )
                v.erase(it);
            else
                break;
        }
    }

    //查找元素
    bool contains(const Object & object)
    {
        return find(v.begin(), v.end(), object) != v.end();
    }
private:
    vector<Object> v;
};