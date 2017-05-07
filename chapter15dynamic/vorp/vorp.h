#include <ctime>
#include <iostream>
using namespace std;

#define n 10

struct player
{
    int cost;  //雇佣球员的花费，相当于背包问题中物品的容量(体积)
    int vorp;  //球员的价值，相当于背包问题中物品的价值
};

void candidate_vorp(player **candidate,int N,int P,int TOTAL)  //TOTAL表示背包总重量
//player[N][P]  在N个不同位置上，有P个球员供你选择
//表示背包的数据value[position i][package capacity]，即背包的总价值
//who[position i][package capacity]用来储存这个容量的背包，这个位置的放置情况
{
    int **value,**who;
    value=new int *[N+1];
    for(int i=0;i<N+1;i++)
        value[i]=new int[TOTAL];

    who=new int *[N+1];
    for(int i=0;i<N+1;i++)
        who[i]=new int[TOTAL];

    for(int x=0;x<=TOTAL;x+=10)
    //x为此时的total cost，背包总价值
    {
        //初始化value[N][x]，表示在这个容量下背包的放置情况
        value[N][x]=-0x7fffffff;
        who[N][x]=0;
        for(int j=0;j<=P;j++)
        {
            if(candidate[N][j].cost<=x && candidate[N][j].vorp>value[N][x])
            {
                value[N][x]=candidate[N][j].vorp;
                who[N][x]=j;   //表示value[N][x]这个位置，选择的球员编号是第N个位置，第j号球员
            }
        }
    }

    //对剩下的N-1个位置进行放置
    for(int i=N-1;i>=1;i--)
    {
        for(int x=0;x<=TOTAL;x+=10)
        {
            value[i][x]=value[i+1][x];
            who[i][x]=0;

            for(int j=0;j<=P;j++)
            //j=0表示现有球员，不用替换球员，j=P表示替换成P位置的球员
            //candidate[i][j]表示第i个位置第j个球员
            {
                if(x-candidate[i][j].cost>=0 && value[i][x]<candidate[i][j].vorp+value[i+1][x-candidate[i][j].cost])
                //从第i+1个位置到第i个位置的时候，是否放入candidate[i][j]这个候选人?
                //value[i+1][x-candidate[i][j].cost]表示背包的容量减小了，此时i+1 position --> i position
                //加上candidate[i][j].corp值
                {
                    value[i][x]=candidate[i][j].vorp+value[i+1][x-candidate[i][j].cost];
                    who[i][x]=j;  //此时选择的是第j号球员
                }
            }
        }
    }
    cout<<"Max value is : "<<value[1][TOTAL]<<endl;

    int amount=TOTAL;  //用一个变量保存总费用
    for(int i=1;i<=N;i++)
    {
        int k=who[i][amount];  //位置为i，费用不超过amount的球员k
        if(k!=0)
        {
            cout<<"No. "<<i<<" position "<<"No. "<<k<<"candidate->";
            amount=amount-candidate[i][k].cost;  
        }
        //循环结束的时候 amount表示剩下多少钱？花掉多少钱用总价减去amount
    }

    cout<<"The total money spent is "<<TOTAL-amount<<endl;

}

