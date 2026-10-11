#include<vector>
#include<utility>      //std::move
#include<stdexcept>    //std::out_of_range

//3.33：使用vector作为底层数组，实现循环队列
template<typename Object>
class CircularQueue
{
private:
    //objects.size()表示底层数组中可访问的位置数，theSize表示队列中的有效元素个数
    std::vector<Object> objects;
    int theSize = 0;
    int frontIndex = 0;   //队头元素的位置
    int backIndex = 0;    //下一次入队写入的位置

    // ==================== 🟠 扩容 ====================
    //扩大底层数组，并按出队顺序重新排列有效元素、调整队头和队尾下标
    void reserve ( int newCapacity )
    {
        if ( newCapacity <= (int)objects.size() )
            return;

        //创建newCapacity个可访问的位置；vector的reserve只预留内存，不增加size
        std::vector<Object> newObjects( newCapacity );
        int oldIndex = frontIndex;

        for ( int i = 0; i < theSize; ++i )
        {
            //从旧队头开始，按出队顺序搬到新数组的0、1、2……位置
            newObjects[i] = std::move( objects[oldIndex] );
            ++oldIndex;

            //旧数组中的元素可能分布在数组末尾和开头，要按旧数组的长度回绕
            if ( oldIndex == (int)objects.size() )
                oldIndex = 0;
        }

        //交换后objects持有新数组，局部变量newObjects析构时会释放旧数组
        objects.swap( newObjects );
        frontIndex = 0;
        //扩容后元素连续排列，下一次写入位置紧跟在有效元素后面
        backIndex = theSize;
    }

public:
    // ==================== 🔴 入队和出队 ====================
    //在队尾插入元素；队列满时先扩容，下标到达数组末尾后回到开头
    void enqueue ( const Object & ele )
    {
        if ( theSize == (int)objects.size() )
            reserve( 2*objects.size() + 1 );

        objects[backIndex] = ele;

        //注意：不能用theSize判断数组末尾
        //先递增再回绕，防止递增后访问越界
        ++backIndex;

        if ( backIndex == (int)objects.size() )
            backIndex = 0;

        ++theSize;
    }

    void enqueue ( Object && ele )
    {
        if ( theSize == objects.size() )
            reserve( 2*objects.size() + 1 );

        objects[backIndex] = std::move(ele);

        ++backIndex;

        if ( backIndex == (int)objects.size() )
            backIndex = 0;

        ++theSize;
    }

    //删除队头元素，并让队头下标循环前进
    void dequeue()
    {
        if ( theSize == 0 )
            throw std::out_of_range("dequeue():empty queue");

        ++frontIndex;

        if ( frontIndex == (int)objects.size() )
            frontIndex = 0;
            
        --theSize;
    }

    // ==================== 🟣 访问队头 ====================
    Object & front()
    {
        if ( theSize == 0 )
            throw std::out_of_range("front():empty queue");
        return objects[frontIndex];
    }

    const Object & front() const
    {
        if ( theSize == 0 )
            throw std::out_of_range("front():empty queue");
        return objects[frontIndex];
    }
};