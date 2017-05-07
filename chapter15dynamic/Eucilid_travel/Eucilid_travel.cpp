#include "Eucilid_travel.h"

int main()
{
    travelnode T[N+1]={0};
    cout<<"Input the numbers in order : "<<endl;

    for(int i=1;i<=N;i++)
    {
        cin>>T[i].x>>T[i].y;
    }
    cout<<Bitonic_Eucilid(T)<<endl;
}