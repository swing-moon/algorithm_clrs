#include <iostream>
#include <cmath>
#include <ctime>
#include "stdlib.h"
#include <string>
using namespace std;

#define MAXVEX 100

enum color{WHITE,GRAY,BLACK};
enum which_edge{NONE,TREE,BACK,FORWARD,CROSS};

typedef int status;
typedef string VertexType;
typedef int EdgeType;

typedef struct EdgeNode
{
    int Edgestart;
    int Edgeend;  //邻接点域，储存该顶点对应的下标
    EdgeType weight;  //用于存储权值

    int type;
    struct EdgeNode *next;  //下一个邻接点
}EdgeNode;

typedef struct VertexNode  //顶点表结点
{
    VertexType data;  //顶点域，存储顶点信息

    int color;
    int touch,finish;   //访问开始时间和结束时间
    EdgeNode* FirstEdge;  //边表头指针
    int parent; //指向遍历的父结点
}VertexNode,AdjList[MAXVEX];

typedef struct
{
    AdjList adjList; //图的顶点表
    int numNodes,numEdges;
}GraphAdjList;

void CreateALGraph(GraphAdjList *G)
{
    EdgeNode *e;
    cout<<"Input the number of vertexes and edges: "<<endl;
    cin>>G->numNodes>>G->numEdges;

    //输入顶点表的信息
    for(int i=0;i<G->numNodes;i++)
    {
        cout<<"Input the data (information) of vertexes "<<i+1<<endl;
        cin>>G->adjList[i].data;
        G->adjList[i].FirstEdge=NULL;
        G->adjList[i].parent=-1;

        G->adjList[i].color=WHITE;
        G->adjList[i].touch=G->adjList[i].finish=-1;
    }

    int beg,end;
    for(int k=0;k<G->numEdges;k++)
    {
        cout<<"Input the serial number of edges (Vi,Vj) "<<endl;
        cout<<"Input the vertex of beginning: ";
        cin>>beg;

        cout<<"Input the vertex of endding: ";
        cin>>end;

        e=(EdgeNode *)malloc(sizeof(EdgeNode));
        e->Edgeend=end;
        e->Edgestart=beg;
        e->weight=0;
        e->type=NONE;
        e->next=G->adjList[beg].FirstEdge;
        G->adjList[beg].FirstEdge=e;
    }
}