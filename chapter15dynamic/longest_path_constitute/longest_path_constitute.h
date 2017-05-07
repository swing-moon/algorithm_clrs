#include "Graphic_longest_path.h"
#include <iostream>
#include <vector>

#define INFINITY 0x7fffffff

int max(int a,int b)
{
    return a>b?a:b;
}

int Find_longest_path(int **weight,int numVertexes,int k,int t,vector<int> &r,int *solution)  //寻找k到t的最短路径
{
    
    if(r[k]>=0)
        return r[k];
    if(k==t)
    {
        int q=0;
        r[k]=q;
        solution[k]=t;
        return q;
    }
    else
    {
        int q=weight[k][t];
        if(weight[k][t])
            solution[k]=t;
        for(int i=k+1;i<=t && weight[k][i];i++)
        {
            int tmp=max(q,weight[k][i]+Find_longest_path(weight,numVertexes,i,t,r,solution));
            if(tmp>q)
            {
                q=tmp;
                solution[k]=i;
            }
        }
        r[k]=q;
        return q;
    }

}

int dynamic_longest_path(int **weight,int numVertexes,int k,int t,int *solution)
{
    vector<int> r;
    r.resize(numVertexes);

    for(int i=0;i<numVertexes;i++)
    {
        r[i]=-INFINITY;
    }
    //完成初始化
    return Find_longest_path(weight,numVertexes,k,t,r,solution);
}

void print_solution(int *solution,int k,int t)
{
    if(solution[k]==-1)
       cout<<"The path is not exist! "<<endl;
    else
    {
        cout<<"The result is : "<<endl;
        cout<<" "<<k<<" --> ";
        while(k!=t)
        {
            cout<<solution[k];
            if(solution[k]!=t)
            {
                cout<<" --> ";
            }
            k=solution[k];
        }
        cout<<endl;
    }
}