#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;

int PARTITION(int A[],int p,int r)
{
    int x=A[r];
    int i=p-1;
    for(int j=p;j<=r-1;j++)
    {
        if(A[j]<=x)
        {
            i++;
            swap(A[i],A[j]);
        }
    }
    swap(A[i+1],A[r]);
    return i+1;
}

void QUICKSORT(int A[],int p,int r)
{
    if(p<r)
    {
        int q=PARTITION(A,p,r);
        QUICKSORT(A,p,q-1);
        QUICKSORT(A,q+1,r);
    }
}
