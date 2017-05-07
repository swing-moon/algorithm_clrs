#include <iostream>

#define MAXNUM 20

//使用有向图的邻接矩阵来表示
bool party_graph[MAXNUM][MAXNUM];
int solution[MAXNUM][2];  //用来存储解决方案，solution[i][0]表示不被选中
                          //solution[i][1]表示被选中
int likevalue[MAXNUM];  //表示对party的热衷程度

int how_many_member;

int id;
int how_many_branch,branch_id;

int max(int a,int b)
{
    return a>b?a:b;
}

int confirm(int id,int status)  //递归求解方案
{
    int result;
    if(solution[id][status]!=-1)
        return solution[id][status];
    if(status==0)
    {
        result=0;
        //表示这个id不参加聚会
        for(int i=0;i<how_many_member;i++)   //遍历这个id的边，即邻接链表
        {
            if(party_graph[id][i])
                result+=max(confirm(i,0),confirm(i,1));
        }
        solution[id][status]=result;
        return result;
    }
    else
    {
        result=likevalue[id];
        for(int i=0;i<how_many_member;i++)
        {
            if(party_graph[id][i])
                result+=confirm(i,0);
        }
        solution[id][status]=result;
        return result;
    }
}