#include<algorithm>
#include<stdexcept>     //out_of_range
using namespace std;

template<typename Object>
class Vector
{
private:
    int theSize;
    int theCapacity;
    Object * objects;
    static const int SPARE_CAPACITY = 16;   //经验数据

public:
    //默认+有参构造函数，explicit用来防止int隐式转换
    explicit Vector ( int initSize = 0 ) :
        theSize { initSize },
        theCapacity { initSize + SPARE_CAPACITY }
    {
        objects = new Object [ theCapacity ];
    }

    //拷贝构造函数
    Vector ( const Vector & rhs ) :
    //能用初始化列表就用初始化列表
        theSize { rhs.theSize }, theCapacity { rhs.theCapacity },
        objects { nullptr }    //不要指向传入参数的地址，要重新开辟一块内存
    {
        objects = new Object [ theCapacity ];    
        for ( int i = 0; i < theSize; i++ )
        {
            objects[i] = rhs.objects[i];    //p[i] <=> *(p + i)
        }
    }

    //移动构造函数（剪切）
    Vector ( Vector && rhs ) :
        theSize { rhs.theSize }, theCapacity { rhs.theCapacity },
        objects { rhs.objects }
    {
        //把参数清空
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }

    //重载=运算符
    Vector & operator = ( const Vector & rhs )    
    {
        //不可修改传入参数，故定义新的变量
        if ( this != &rhs )      //自赋值检查
        {
            Vector temp = rhs;
            swap( *this, temp );    //不可以返回temp因为这是局部变量
        }
        //=运算返回值是左值，*this也是左值，返回引用是为了避免深拷贝浪费资源
        return *this;         
    }

    Vector & operator= ( Vector && rhs )
    {
        swap( theSize, rhs.theSize );
        swap( theCapacity, rhs.theCapacity );
        swap( objects, rhs.objects );
        return *this;    
    }

    //析构函数
    ~Vector()
    {
        delete [] objects;    //数组要用 delete []
    }

    //改变容量
    void reserve(int newCapacity)
    {
        if ( newCapacity < theSize )    //新容量不可以比容器大小还要小
            return;

        Object * newPoint = new Object[ newCapacity ];  //申请新内存
        for (int i = 0; i < theSize; i++)
        {
            newPoint [i] = move( objects[i] );          
        }

        theCapacity = newCapacity;
        swap(objects,newPoint);     //交换指针
        delete [] newPoint;         //删除旧地址
    }

    //改变大小
    void resize(int newSize)
    {
        if ( newSize < 0 )              //尺寸不可能为负：直接忽略，保住 0 <= theSize
            return;
        if ( newSize > theCapacity )
            reserve ( 2*newSize );
        theSize = newSize;
    }

    //读写操作
    Object & operator [] (int idx)
    {
        return objects[idx];
    }

    //只读操作
    const Object & operator [] (int idx) const
    {
        return objects[idx];
    }

    bool empty() const
    {
        return size() == 0;
    }

    int size() const
    {
        return theSize;
    }

    int capacity() const
    {
        return theCapacity;
    }

    void push_back(const Object & ele)
    {
        if ( theSize == theCapacity )
            reserve( 2*theCapacity + 1 );   //+1是为了防止清空容器后无法扩容
        objects[theSize++] = ele;
    }

    //&&表示右值引用，右值是即将被销毁的值，可以直接拿走其资源，但右值引用的变量本身为左值
    void push_back(Object && ele)   //不加const
    {
        if ( theSize == theCapacity )
            reserve( 2*theCapacity + 1 );
        //move函数本身不搬运资源，只是将有名字的右值引用转换为右值
        objects[theSize++] = move(ele);    
    }

    void pop_back()
    {
        if ( empty() )      //空容器直接不操作，防止 theSize 变成 -1
            return;
        theSize--;
    }

    const Object & back () const
    {
        if ( empty() )      //引用必须绑定到真实对象，没法"什么都不返回"，只能报错
            throw out_of_range( "back(): empty vector" );
        return objects[theSize - 1];
    }

    typedef Object* iterator;
    typedef const Object* const_iterator;   //提供只读版本

    iterator begin()
    {
        return & objects[0];
    }

    const_iterator begin() const
    {
        return & objects[0];
    }

    iterator end()
    {
        return & objects[ theSize ];    
        //本质上是 &*( objects + theSize ) = objects + theSize，故不是UB
    }

    const_iterator end() const
    {
        return & objects[ theSize ];
    }
};