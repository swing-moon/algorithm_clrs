#include <iostream>
using namespace std;

#define n 7  //为L[]的数组元素的个数

int break_string_array(int L[],int cut[][n+1])
{
    int cost[n+1][n+1]={0};

    for(int len=2;len<=n;len++)
    {
        for(int i=1;i<=n-len+1;i++)  
        {
            int j=i+len-1;
            if(j-i>1)
                cost[i][j]=0x7fffffff;
            for(int part=i+1;part<j;part++)
            {
                int value=cost[i][part]+cost[part][j]+(L[j-1]-L[i-1]);
                //注意，这里cost[start][part]+cost[part+1][end]会发生错误
                if(value<cost[i][j])
                {
                    cost[i][j]=value;
                    cut[i][j]=part;
                }
            }
        }
    }
    return cost[1][n];
}

void print_breaks(int L[],int cut[][n+1],int i,int j)
{
    if(j-i>=2)
    {
        int k=cut[i][j];
        cout<<L[k-1]<<" ";
        print_breaks(L,cut,i,k);
        print_breaks(L,cut,k,j);
    }
}