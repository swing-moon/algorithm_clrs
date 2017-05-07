#include "viterbi_graph.h"

int path_time=0;
int path_exist=0;
int path_print_signal=0;

void print_graph(GraphAdjList *G)
{
    EdgeNode *cur_edge;
    for(int i=0;i<G->numNodes;i++)
    {
        cout<<"The start is "<<G->adjList[i].data<<endl;
        cout<<G->adjList[i].data;
        if(G->adjList[i].FirstEdge)
            cout<<" adjust end is: ";
        for(cur_edge=G->adjList[i].FirstEdge;cur_edge;cur_edge=cur_edge->next)
        {
            cout<<cur_edge->Edgeend<<"  ";
        }
        cout<<endl;
    }
}

void DFS_visit(GraphAdjList *G,int start,int end)
{
    G->adjList[start].color=GRAY;
    path_time++;
    G->adjList[start].touch=path_time;

    for(EdgeNode *cur_e=G->adjList[start].FirstEdge;cur_e;cur_e=cur_e->next)
    {
        if(cur_e->Edgeend==end)
        {
            path_exist=1;
        }
        if(path_exist==1)
            return;
        int cur_end=cur_e->Edgeend;
        if(G->adjList[cur_end].color==WHITE)
        {
            G->adjList->parent=start;
            DFS_visit(G,cur_end,end);
            cur_e->type=TREE;
        }
        else if(G->adjList[cur_end].color==GRAY)
        {
            cur_e->type=BACK;
        }
        else if(G->adjList[cur_end].color==BLACK)
        {
            if(G->adjList[start].touch<G->adjList[end].touch)
                cur_e->type=FORWARD;
            else
                cur_e->type=CROSS;
        }
    }

    //G->adjList[start] has finished
    G->adjList[start].color=BLACK;
    path_time++;
    G->adjList[start].finish=path_time;
}

void DFS(GraphAdjList *G,int start,int end)
{
    for(int u=0;u<G->numNodes;u++)
    {
        G->adjList[u].color=WHITE;
        G->adjList[u].parent=-1;
    }
    path_time=0;
    if(G->adjList[start].color==WHITE)
        DFS_visit(G,start,end);
}

void path_print(GraphAdjList *G,int start,int end)
{
    if(path_exist==1)
    {
        cout<<" "<<start;
        for(EdgeNode *e_ptr=G->adjList[start].FirstEdge;e_ptr;e_ptr=e_ptr->next)
        {
            if(e_ptr->Edgeend==end)
            {
                cout<<" "<<end;
                path_print_signal=1;
                return;
            }
        }
        if(path_print_signal==0)
        {
            for(EdgeNode *e_ptr=G->adjList[start].FirstEdge;e_ptr;e_ptr=e_ptr->next)
            {
                if(e_ptr->type==TREE)
                    path_print(G,e_ptr->Edgeend,end);
            }
        }
    }
    else
    {
        cout<<"The path is not exist"<<endl;
    }
}