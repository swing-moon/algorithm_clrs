#include <iostream>
#include <cmath>
using namespace std;

#define m 15
#define n 10
#define c 3


void find_create(int *extra_create,int *create_result,int *d)
{
    for(int i=0;i<=n;i++)
        create_result[i]=extra_create[i]+d[i];
}

int min_val(int a ,int b)
{
    return a<b?a:b;
}


int man_cost(int man_num)
{
    if(man_num<=m)
        return 0;
    else
        return c*(man_num-m);
}

int store_cost(int store_num)
{
    if(store_num>0)
        return (int)log((double)store_num);
    else
        return 0;
}

int create_material(int d[],int create[][n+1],int start,int end)
//start从0开始
{
    if(start==end)
    {
        create[start][end]=0;
    }
    if(end==start+1)
    {
        create[start][end]=d[end];
    }
    if(end>start)
    {
        create[start][end]=create_material(d,create,start,end-1)+d[end];
        //实现结果 d[start+1]+d[start+2]+.....+d[end]
    }
    else
    {
        return 0;
    }
    return create[start][end];
}

void init_create(int create[][n+1],int d[])
{
    for(int i=0;i<n;i++)
        create_material(d,create,i,n);
}

int min_cost(int d[],int HR_extra[],int start,int end)
{
    if(start>=end)
        return 0;

    int cost=0; //最初cost[]值为0，一开始每一个位置所保存的create[]就是当前需求值
    
    for(int i=start;i<=end;i++)
    {

        if(d[i]<=m)
        {
            //此时不需要花费额外的人力成本，所有的create[i]==d[i]均会销售出去
            cost+=0; //不需要花费任何代价，月末就可以出售完毕，没有库存
            HR_extra[i]=m-d[i];
        }
        else
        {
            HR_extra[i]=m-d[i];
            int HR_cost=d[i];  //人力资源成本超出预算，这部分预算可以考虑转换成库存成本
            int HR_cost_copy=d[i]; //副本，用来输出

            int cost_original=man_cost(HR_cost);
            int extra_store=0; //额外付出的库存代价
            //注意判断cost_original和cost_adjust哪个大？哪个小？

            for(int l=start;l<i;l++)  //(l,i)
            {
                int cur_extra=HR_extra[l];
                if(cur_extra>0 && HR_cost!=0)  //这部分人力资源成本可以用来存放库存，转换成库存成本
                {
                    int temp_excess=min_val(cur_extra,HR_cost);
                    //势能守恒来求解
                    HR_cost-=temp_excess;
                    extra_store+=temp_excess;
                }
            }

            int cost_adjust=man_cost(HR_cost)+store_cost(extra_store);

            if(cost_adjust<cost_original)
            {
                cost+=cost_adjust;
                //HR_extra也要调整
                for(int l=start;l<i;l++)
                {
                    if(HR_extra[l]>0 && HR_cost_copy!=0)
                    {
                        int temp_excess_copy=min_val(HR_extra[l],HR_cost_copy);

                        HR_cost_copy-=temp_excess_copy;

                        //保持势能守恒
                        HR_extra[l]-=temp_excess_copy;
                        HR_extra[i]+=temp_excess_copy;
                    }
                }
            }
            else
            {
                cost+=cost_original;
            }
        }
    }
    return cost;
}