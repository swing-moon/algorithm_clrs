#include "longest_path_constitute.h"
#include <iostream>

int main()
{
    cout<<"AdjacentMatrix Graphic: "<<endl;
    bool isDirected, isWeighted;
    int numV;
    cout<<"Create Graphics: "<<endl;
    cout<<"input Vertexes: ";
    cin>>numV;

    cout<<"Is weighted? 0(no), 1(yes) : ";
    cin>>isWeighted;
    cout<<"IS directed? 0(no), 1(yes) : ";
    cin>>isDirected;

    graph graph(numV,isWeighted,isDirected);
    cout<<"This is a ";
    isDirected ? cout<<"Directed " : cout<<"Undirected: ";
    isWeighted ? cout<<"Weighted " <<endl : cout<<"Unweighted "<<endl;
    graph.createGraph();

    cout<<"print AdjacentMatrix: "<<endl;
    graph.printAdjacentMatrix();
    cout<<endl;

    int k,t;
    cout<<"input k, t :"<<endl;
    cin>>k>>t;

    int numVertex=graph.getVerNums();
    int **weight_dynamic=graph.getWeight();
    cout<<"test: ";
    cout<<weight_dynamic[k][t]<<endl;

    //初始化solution：
    int *solution=new int[numVertex+1];
    for(int i=0;i<numVertex;i++)
        solution[i]=-1;

    //返回最优解：
    int result=dynamic_longest_path(weight_dynamic,numVertex,k,t,solution);
    cout<<"The result is :"<<endl;
    cout<<result<<endl;

    //返回solution的解，注意delete[]
    cout<<"The solution is "<<endl;
    print_solution(solution,k,t);

    int beg, end, weight;
    bool flag;
    cout<<"Adjust the weight, no(0), yes(1): "<<endl;
    cin>>flag;
    if(flag)
    {
        if(isWeighted)
        {
            cout<<"Enter edges--begin, end, and weight: "<<endl;
            cin>>beg>>end>>weight;
            graph.setEdgeWeight(beg,end,weight);
        }
        else
        {
            cout<<"Enter edges--begin, end: "<<endl;
            cin>>beg>>end;
            graph.setEdgeWeight(beg,end,1);
        }
        cout<<"Successed!"<<endl;
        cout<<"Print AdjacentMatrix: "<<endl;
        graph.printAdjacentMatrix();
    }
    return 0;

}