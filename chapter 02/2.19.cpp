#include<iostream>
#include<vector>
using namespace std;

//单一对象
struct result
{
    int maxSum = 0;
    int low = 0;
    int high = 0;
};

result maxSubSum(const vector <int> & v)
{
    result r;
    int thisSum = 0;
    int tempLow = 0;                 // 候选起点：变负时前移，但暂不提交

    for ( size_t i = 0; i < v.size(); i++ )
    {
        thisSum += v[i];

        if ( thisSum > r.maxSum )    // 创新高：才把"候选起点"提交为真正起点，并记终点
        {
            r.maxSum = thisSum;

            //high和low必须同时更新，否则可能造成low > high
            r.low   = tempLow;
            r.high  = i;
        }

        if ( thisSum < 0 )           // 变负：只前移候选起点，不立刻改 low/high
        {
            thisSum = 0;
            tempLow = i + 1;
        }
    }

    return r;
}

int main()
{
    vector <int> v = {3, -4, 2, -1, 3, -4};
    result r = maxSubSum(v);
    
    cout<<"low = "<<r.low<<endl;
    cout<<"high = "<<r.high<<endl;
    cout<<"maxSum = "<<r.maxSum<<endl;
}