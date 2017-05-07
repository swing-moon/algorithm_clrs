#include "graph_algorithm.h"

int main()
{
    GraphAdjList G;
    CreateALGraph(&G);

    print_graph(&G);

    int start,end;
    cout<<"Input the start of the edge : "<<endl;
    cin>>start;
    cout<<"Input the end of the edge : "<<endl;
    cin>>end;
    DFS(&G,start,end);
    cout<<endl;
    cout<<path_exist<<endl;

    cout<<G.adjList[start].color<<" "<<G.adjList[start].touch<<" "<<G.adjList[start].finish<<" "<<endl;
    cout<<G.adjList[end].color<<" "<<G.adjList[end].touch<<" "<<G.adjList[end].finish<<" "<<endl;

    cout<<"The path is :"<<endl;
    path_print(&G,start,end);

    return 0;
}