//L[]表示拆分点数组
//cost[][]表示花费

#include <iostream>
#define INFINITY 0x7fffffff
using namespace std;

#define m 5
#define n 30
using namespace std;

//int position[n+1][n+1]={0};

int cost[n+1][n+1]={0};
int exist[n+1][n+1]={0};

int total_cost=INFINITY;
int part=0;
int cut_point=0;

void INITIATE(int cost[][n+1])
{
    for(int i=0;i<=n-1;i++)
    {
        for(int j=i+1;j<=n;j++)
            cost[i][j]=INFINITY;
    }
}

//break_point中，start,end分别表示下标起始坐标，尾坐标
int break_point(int L[],int cost[][n+1],int start,int end,int cut[][n+1])  //start end表示第几个数，而不是数组下标
{
    //使用递归判断的时候要先看看在start和end之间是否存在这样的值
    if(end-start<2)
    {
        cost[start][end]=0;
        return cost[start][end];
    }
    if(cost[start][end]!=INFINITY)
        return cost[start][end];

    for(int i=0;i<m;i++)
    {
        if(L[i]>start && L[i]<end)
        {
            exist[start][end]=1;
            break;
        }
    }

    if(exist[start][end]==0)
    {
        cost[start][end]=0;
        return cost[start][end];
    }
    else
    {
        int total_cost=INFINITY;
        for(int i=0;i<m;i++)
        {
            if(L[i]>start && L[i]<end)
            {
                part=L[i];
                if(break_point(L,cost,start,part,cut)+break_point(L,cost,part+1,end,cut)+(end-start+1)<=total_cost)
                {
                    total_cost=break_point(L,cost,start,part,cut)+break_point(L,cost,part+1,end,cut)+(end-start+1);
                    cut_point=i;
                }
            }
        }
        if(total_cost<=cost[start][end])
        {
            cost[start][end]=total_cost;
            cut[start][end]=cut_point;
        }
    }
    return cost[start][end];
}

void print_breaks(int L[],int cut[][n+1],int start,int end)
{
    if(exist[start][end]==1)
    {
        cout<<L[cut[start][end]]<<" ";

        print_breaks(L,cut,start,L[cut[start][end]]);
        print_breaks(L,cut,L[cut[start][end]]+1,end);
    }
}