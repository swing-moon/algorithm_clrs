#include "probability_graph.h"

double answer=1;
double maxpath=0;
int path_exist=0;

int path_print_signal=0;
int has_founded[MAXVEX];

double DFS_compute(GraphAdj *G,int beg,int end);

double max(double a,double b)
{
    return a>b?a:b;
}

double DFSTraverse(GraphAdj *G,int beg,int end)
{
    for(int i=0;i<G->numNodes;i++)
        has_founded[i]=0;

    maxpath=DFS_compute(G,beg,end);
    return maxpath;
}

double DFS_compute(GraphAdj *G,int beg,int end)
{
    if(beg==end)
    {
        answer=1;
        return 1;
    }
    for(Edge *e=G->adjlist[beg].head;e;e=e->next)
    {
        if(has_founded[beg]==1)
        {
            answer=G->adjlist[e->e_start].res;
            return G->adjlist[e->e_start].res;
        }
        if(has_founded[beg]==0)
        {
            if(e->e_end==end)
            {
                path_exist=1;
                answer=e->probability;
                if(answer>G->adjlist[e->e_start].res)
                {
                    G->adjlist[e->e_start].res=answer;
                    G->adjlist[e->e_start].direction=e->e_end;
                }
                return G->adjlist[e->e_start].res;
            }

            answer=e->probability*DFS_compute(G,e->e_end,end);
            //计算从G->adjlist[beg]出发的每一条边，找出最大值
            if(answer>G->adjlist[beg].res)
            {
                G->adjlist[beg].res=answer;
                G->adjlist[beg].direction=e->e_end;
            }
        }        
    }
    //beg开始的answer已经全部计算完了

    has_founded[beg]=1;
    return G->adjlist[beg].res;
}

void print_graph(GraphAdj *G)
{
    Edge *cur_edge;
    for(int i=0;i<G->numNodes;i++)
    {
        cout<<"The start is "<<G->adjlist[i].data<<endl;
        cout<<G->adjlist[i].data;
        if(G->adjlist[i].head)
            cout<<" adjust end is: ";
        for(cur_edge=G->adjlist[i].head;cur_edge;cur_edge=cur_edge->next)
        {
            cout<<cur_edge->e_end<<"  ";
        }
        cout<<endl;
    }
}