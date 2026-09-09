#include<iostream>
#include<vector>
using namespace std;

int FindMax(const vector <int> & a, int low, int high)
{
    int max = a[low];
    for ( int i = low; i <= high; i++ )
    {
        if ( max < a[i] )
            max =a[i];
    }
    return max;
}

int FindMin(const vector <int> & a, int low, int high)
{
    int min = a[low];
    for ( int i = low; i <= high; i++ )
    {
        if ( min > a[i] )
            min =a[i];
    }
    return min;
}

int maxInt(const int &a, const int &b, const int &c)
{
    int max = a;
    if ( b > max )
        max = b;
    if ( c > max )
        max = c;
    return max;
}

//a[j] + a[i] max
int func_a(const vector <int> & a)
{
    return 2*FindMax(a, 0, a.size() - 1);
}

//a[j] - a[i] max

//分治O(NlogN)
int func_b_rec(const vector <int> & a, int low, int high)
{
    if ( low == high )
        return a[low];
    
    int mid = ( low + high ) / 2;
    int RightMax = func_b_rec(a, mid + 1, high);
    int LeftMax = func_b_rec(a, low, mid);

    int LeftBroadMax = FindMax(a, mid + 1, high);
    int RightBroadMin = FindMin(a, low, mid);

    return maxInt(LeftMax, RightMax, LeftBroadMax - RightBroadMin);
}

int func_b(const vector <int> & a)
{
    return func_b_rec(a, 0, a.size() - 1);
}

//best solution : O(N)
int best_func_b(const vector <int> & a)
{
    int MinSoFar = a[0];
    int best = 0;           // 当i = j时best == 0,其他情况下best >= 0

    for ( int j = 1; j < a.size(); j++ )
    {
        best = max ( best, a[j] - MinSoFar );
        MinSoFar = min ( a[j], MinSoFar );
    }

    return best;
}