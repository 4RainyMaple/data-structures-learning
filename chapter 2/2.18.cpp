#include<iostream>
using namespace std;

class func
{
public:
    double operator()(double x)
    {
        return x*x - 2;
    }
};

double findRoot(func f, double low, double high)
{
    double mid;
    do
    {
        mid = ( low + high ) / 2;    
        
        if ( f(mid) > 0 )
            high = mid;      // f(mid)>0：mid 偏大，根在左边，收缩右界
        else
            low = mid;       // f(mid)<0：mid 偏小，根在右边，收缩左界
    } while ( f(mid) > 1e-5 || f(mid) < -(1e-5) );

    return mid;
}

int main()
{
    func f;
    double low = 1.0;
    double high = 2.0;
    cout<<findRoot(f, low, high)<<endl;
}
