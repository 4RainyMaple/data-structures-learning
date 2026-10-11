#include<vector>
#include<iostream>
using namespace std;

//O(N*N)
int maxSubSum1(const vector<int> & v)
{
    int maxSum = 0;

    for ( size_t i = 0; i < v.size(); i++ )
    {
        int thisSum = 0;

        for ( size_t j = i; j < v.size(); j++ )
        {
            thisSum += v[j];
            if ( thisSum > maxSum )
                maxSum = thisSum;
        }
    }

    return maxSum;
}

//O(NlogN)

int maxInt(const int &a, const int &b, const int &c)
{
    int max = a;
    if ( b > max )
        max = b;
    if ( c > max )
        max = c;
    return max;
}

//Recursion function
int maxSubRec(const vector<int> & v, int left, int right)
{
    //基准情形
    if(left == right)
    {
        if( v[left] > 0 )
            return v[left];
        else
            return 0;
    }

    int center = ( left + right )/2;

    int LeftMaxSum = maxSubRec(v, left, center);
    int RightMaxSum = maxSubRec(v, center + 1, right);
    int LeftBroaderSum = 0;
    int RightBroaderSum = 0;
    int maxLeftBroaderSum = 0;
    int maxRightBroaderSum = 0;

    for ( int i = center; i >= left; i-- )  //这里若用size_t（无符号数），则left为0再减一时会溢出
    {
        LeftBroaderSum += v[i];
        if ( LeftBroaderSum > maxLeftBroaderSum )
            maxLeftBroaderSum = LeftBroaderSum;
    }

    for ( size_t j = center + 1; j <= right; j++ )
    {
        RightBroaderSum += v[j];
        if ( RightBroaderSum > maxRightBroaderSum )
            maxRightBroaderSum = RightBroaderSum;
    }

    return maxInt( LeftMaxSum, RightMaxSum, maxLeftBroaderSum + maxRightBroaderSum );
}

//启动器
int maxSubSum2(const vector<int> & v)
{
    return maxSubRec( v, 0, v.size() - 1 );
}

//O(N)
int maxSubSum3(const vector<int> & v)
{
    int maxSum = 0;
    int thisSum = 0;

    for ( size_t i = 0; i < v.size(); i++ )
    {
        thisSum += v[i];

        if ( thisSum < 0 )
            thisSum = 0;
        else if( thisSum > maxSum )
            maxSum = thisSum;
    }

    return maxSum;
}

int main()
{
    vector <int> v = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout<<maxSubSum1(v)<<endl;
    cout<<maxSubSum2(v)<<endl;
    cout<<maxSubSum3(v)<<endl;
}