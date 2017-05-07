#include <iostream>
#include <string>
#include "stdlib.h"

using namespace std;

#define MAXVEX 100

typedef int status;
typedef string VertexType;
typedef double EdgeType;

typedef struct Edge
{
    int e_start;
    int e_end;  //邻接点域
    EdgeType probability;  //用于存储权值，即边的概率

    struct Edge *next;
}Edge;

typedef struct Vertex
{
    VertexType data;
    Edge* head; //边表头指针

    int direction;  //用于指明节点下一步该往哪里走
    double res;  //用于储存最后的结果，初始化为-1
    //direction和res要联动
}Vertex,adjvertex[MAXVEX];

typedef struct
{

    adjvertex adjlist; //图的顶点表
    int numNodes,numEdges;
}GraphAdj;

void CreateGraph(GraphAdj *G)
{
    Edge *e;
    cout<<"Input the number of vertexes and edges: "<<endl;
    cin>>G->numNodes>>G->numEdges;

    //输入顶点表信息
    for(int i=0;i<G->numNodes;i++)
    {
        cout<<"Input the data (information) of vertexes "<<i+1<<endl;
        cin>>G->adjlist[i].data;
        G->adjlist[i].head=NULL;
        G->adjlist[i].direction=-1;
        G->adjlist[i].res=-1;
    }

    int beg,end;
    double prob;
    
    for(int k=0;k<G->numEdges;k++)
    {
        cout<<"Input the serial number of Edges (Vi,Vj) "<<endl;
        cout<<"Input the vertex of beginning: ";
        cin>>beg;

        cout<<"Input the vertex of endding: ";
        cin>>end;

        cout<<"Input the probability of edge: ";
        cin>>prob;

        e=(Edge *)malloc(sizeof(Edge));
        e->e_start=beg;
        e->e_end=end;
        e->probability=prob;

        e->next=G->adjlist[beg].head;
        G->adjlist[beg].head=e;

    }
}