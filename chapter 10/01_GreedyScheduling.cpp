#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

// 10.1.1：贪心算法求单处理器平均完成时间最小值。
double minAverageCompletionTime(vector<int> durations)
{
    if ( durations.empty() )
        return 0.0;
    
    int n = durations.size();
    size_t sum = 0;
    sort(durations.begin(), durations.end());
    for ( int i = 0; i < n; i++ )
        sum += durations[i] * (n - i);
    double average = (double)sum / n;
    return average;
}

int main()
{
    vector<int> durations = { 15, 8, 3, 10 };
    cout << minAverageCompletionTime(durations);
}
