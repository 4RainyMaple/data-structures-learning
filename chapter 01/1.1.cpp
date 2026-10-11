#include<iostream>
using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void sort(int array[], int len)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len - i; j++)
        {
            if (array[j] > array[j+1])
            {
                swap(array[j], array[j+1]);
            }
        }
    }
}

void printArray(int array[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout<<array[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    int array[] = {7, 5, 9, 4, 8, 6, 1, 0, 3, 2};
    int len = sizeof(array)/sizeof(array[0]);
    sort(array, len);
    printArray(array, len);
}