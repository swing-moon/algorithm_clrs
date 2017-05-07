#include <iostream>
#include <cmath>

using namespace std;

#define N 6  //确定有几个点？

struct travelnode
{
    double x;
    double y;
}T[N];

//计算两个点之间的直线距离
double distance(travelnode T[],int i,int j)  //T[]的下标，第几个数？1,2....N
{
    return sqrt((T[i].x-T[j].x)*(T[i].x-T[j].x)+(T[i].y-T[j].y)*(T[i].y-T[j].y));
}

double Bitonic_Eucilid(travelnode T[])
{
    double b[N+1][N+1]={0};

    //初始化b[1][2]，注意初始下标从1开始，1,2.....N
    b[1][2]=distance(T,1,2);
    for(int j=3;j<=N;j++)
    {
        for(int i=1;i<j-1;i++)  //注意1<=i<=j-2
        {
            b[i][j]=b[i][j-1]+distance(T,j-1,j); //巡路系统的初始化，递归求解
            //length((start->j-1)+(start->i)+length(j-1,j))
            //即b[i][j]=b[i][j-1]+distance(T,j-1,j) 这里distance(T,j-1,j)封闭了路径
        }

        //注意：这里递归求解所得到的路径，b[i][j]不一定就是最短的欧几里德旅行商
        //必须用min()维护旅行商信息
        //用min()维护每一条线段[j-1,j]，保证从length(start->j-1)+length(start->k)+length(k,j)均是最小的

        //如图所示：对每一个线段[j-1,j]的两端进行维护，保证最短的Eucilid巡回，即维护b[j-1][j]
        //在维护的过程中b[j-1][j]=min(b[k][j-1]+distance(k,j))，封闭了[k,j]就获取了最佳路径
        //因为j是在最远端，1<=k<=j-1<j，j-1和k一定在回路的不同方向。由递归求解，已知b[k][j-1]
        //最后封闭[k,j]即可年少有你


        //这一步确定了从start->i+start->j的路径，但是巡路并不是封闭的
        //最后确定b[j-1][j]，即确定线段[j-1,j]，完成巡路封闭。
        //这里b[j-1][j]要保证遍历1<=k<j-1中的最小路径，如图中所示
        b[j-1][j]=INFINITY;
        //对每一条线段[j-1,j]两端维护Eucilid巡回路径性质
        for(int k=1;k<j-1;k++)
        {
            double q=b[k][j-1]+distance(T,k,j); //最后封闭的线段长度[j-1,j]是固定的
            //(start->j-1)+(start->k)+length(k,j) 
            //由于1<=k<j-1，k和j-1一定是分居在Eucilid旅行图的线段[j-1,j]的两侧
            if(q<b[j-1][j])
                b[j-1][j]=q;
        }
    }
    b[N][N]=b[N-1][N]+distance(T,N-1,N);
    return b[N][N];
}