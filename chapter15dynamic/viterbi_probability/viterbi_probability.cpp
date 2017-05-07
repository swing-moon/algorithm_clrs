#include "viterbi_probability.h"

int main()
{
    GraphAdj G;
    CreateGraph(&G);

    print_graph(&G);

    int start,end;
    cout<<"Input the start of the edge : "<<endl;
    cin>>start;
    cout<<"Input the end of the edge : "<<endl;
    cin>>end;

    double result=DFSTraverse(&G,start,end);
    cout<<endl;
    cout<<path_exist<<endl;
    cout<<result<<endl;
    
    cout<<"The max path is : "<<endl;
    cout<<start<<" ";
    if(path_exist==1)
    {
        int pathID=G.adjlist[start].direction;
        while(pathID!=end)
        {
            cout<<pathID<<" ";
            pathID=G.adjlist[pathID].direction;
        }
        cout<<end;
    }
    
    return 0;
}