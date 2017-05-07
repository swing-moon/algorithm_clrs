#include "Eucilid_travel_constitute.h"

int main()
{
    travelnode T[N+1]={0};
    int solution[N+1][N+1]={0};

    cout<<"Input the numbers in order : "<<endl;

    for(int i=1;i<=N;i++)
    {
        cin>>T[i].x>>T[i].y;
    }
    cout<<Bitonic_Eucilid(T,solution)<<endl;

    cout<<"The Eucilid travel is :"<<endl;

    cout<<N<<" ";
    print_eucilid(solution,N-1,N);
    cout<<N-1<<" ";

}