#include<iostream>
#include<vector>
#include<set>      // 小题 b：需要有序集合 std::set 来"在线找前驱"
#include<climits>  // 小题 b：用 INT_MAX 作初始值（总会被更小的正值替换）
#include<algorithm>// 小题 c：用到 std::max / std::min
using namespace std;

//找出最小子序列和

int minSubSum(const vector <int> & v)
{
    int thisSum = 0;
    int minSum = 0;
    for ( size_t i = 0; i < v.size(); i++ )
    {
        thisSum += v[i];
        if ( thisSum > 0 )
            thisSum = 0;
        else if ( thisSum < minSum )
            minSum = thisSum;
    }
    return minSum;
}

//找出最小正子序列和
int minPositiveSubSum(const vector <int> & v)
{
    int best = INT_MAX;     //确保best第一次会被更新
    set <int> seen;         //储存所有前缀和（前缀和做差即为子序列和），set的查找时间复杂度为O(logN)有优势
    seen.insert(0);         //关键：P[0] = 0，否则若目标字段从0开始会被漏掉

    int prefix = 0;
    for ( size_t i = 0; i < v.size(); i++ )
    {
        prefix += v[i];
        seen.insert(prefix);
        auto it = seen.find(prefix);     
        if (it != seen.begin())
        {
            it--;           //小于prefix中最大的元素
            int positive = prefix - *it;
            if (positive < best)
                best = positive;
        }      
    }
    return best;
}

//找出最大子序列积
int maxSubProduct(const vector <int> & v)
{
    int curMax = 1;
    int curMin = 1;
    int best = INT_MIN;

    for ( size_t i = 0; i < v. size(); i++ )
    {
        int oldMax = curMax;
        int oldMin = curMin;

        //若前面有0，则最大或最小就是v[i]
        //若v[i] < 0，则最大和最小会反转
        curMax = max( { v[i], oldMax * v[i], oldMin * v[i]} );
        curMin = min( { v[i], oldMax * v[i], oldMin * v[i]} );

        if ( best < curMax )
            best = curMax;
    }

    return best;
}

int main()
{
    vector <int> v = {-4, 3, -6, 7, 13, -5, 9};
    cout<<"最小子序列和="<<minSubSum(v)<<endl;
    cout<<"最小正子序列和="<<minPositiveSubSum(v)<<endl;
    cout<<"最大子序列积="<<maxSubProduct(v)<<endl;
}