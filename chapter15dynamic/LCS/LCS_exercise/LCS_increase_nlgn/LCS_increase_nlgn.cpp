#include <iostream>
#include "LIS.h"
using namespace std;

#define N 9

int main()
{
    int array[N]={2,1,6,3,5,4,8,7,9};
    node *result=new node[N+1];

    int cur_len=LIS(array,result,N);
    cout<<cur_len<<endl;

    for(int i=0;i<cur_len;i++)
    {
        cout<<B[i]<<" ";
    }
    cout<<endl;
    cout<<"wrong answer:"<<endl;
    int temp[cur_len]={0};
    int id=cur_len-1;
    for(int i=cur_len-1;i>=0;i--)
    {
        temp[i]=result[id].data;
        id=result[id].prev;
    }
    cout<<temp[0]<<" ";
    for(int i=0;i<cur_len;i++)
    {
        if(i>0 && temp[i]>=temp[i-1])
           cout<<temp[i]<<" ";
    }
    delete[] result;
    return 0;
}