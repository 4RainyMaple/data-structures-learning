#include <iostream>
#include <vector>
using namespace std;

class Rectangle
{
private:
    double length_ = 0;   // 属性：长
    double width_  = 0;   // 属性：宽

public:
    // 构造函数
    Rectangle(double length, double width)           
    {
        length_ = length;
        width_ = width;
    }

    double getLength() const                        // 返回长
    {
        return length_;
    }
    double getWidth() const                         // 返回宽
    {
        return width_;
    }

    // 便于按"面积/周长"比较的两个函数
    double getArea() const                          // 返回面积
    {
        return length_ * width_;
    }
    double getPerimeter() const                     // 返回周长 
    {
        return 2 * ( length_ + width_ );
    }
};

// 泛型 findMax，用到函数对象 Comparator 比较器
template <typename Object, typename Comparator>
const Object  findMax(const vector<Object> & arr, Comparator isLessThan)
{
    Object max = arr[0];
    for (auto x : arr)
    {
        if (isLessThan(max, x))
        max = x;
    }
    return max;
}

//面积比较器
class AreaCompare
{
public:
    bool operator()(const Rectangle & lhs, const Rectangle & rhs) const
    {
        return lhs.getArea() < rhs.getArea();   
    }
};

//周长比较器
class PerimeterCompare
{
public:
    bool operator()(const Rectangle & lhs, const Rectangle & rhs) const
    {
        return lhs.getPerimeter() < rhs.getPerimeter();   
    }
};

int main()
{
    vector<Rectangle> rects;
    rects.push_back(Rectangle(6, 2));   
    rects.push_back(Rectangle(5, 4));   
    rects.push_back(Rectangle(1, 9));   
    rects.push_back(Rectangle(2, 7));   

    // 打印每个矩形信息
    for (auto r : rects)
    {
        cout << r.getLength() << " x " << r.getWidth()
             << "   面积=" << r.getArea()
             << "   周长=" << r.getPerimeter()
             << endl;
    }

    // 按面积找最大
    const Rectangle & maxArea = findMax(rects, AreaCompare());
    cout << "按面积最大者: 长=" << maxArea.getLength()
         << " 宽=" << maxArea.getWidth()
         << " 面积=" << maxArea.getArea() << endl;

    // 按周长找最大
    const Rectangle & maxPerimeter = findMax(rects, PerimeterCompare());
    cout << "按周长最大者: 长=" << maxPerimeter.getLength()
         << " 宽=" << maxPerimeter.getWidth()
         << " 周长=" << maxPerimeter.getPerimeter() << endl;
}