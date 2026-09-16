#include<iostream>
#include<vector>
using namespace std;

void printLots( const vector <int> & L, const vector <int> & P )
{
    for ( auto itr = P.begin(); itr != P.end(); ++itr )
    {
        cout << L[*itr - 1] <<endl;
    }
}