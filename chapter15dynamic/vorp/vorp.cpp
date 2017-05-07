#include "vorp.h"

int main()
{
    player **candidate;
    int N=10,P=8,TOTAL=300;

    candidate=new player*[N+1];
    for(int i=0;i<=N;i++)
        candidate[i]=new player[P+1];

    for(int i=0;i<=N;i++)
    {
        for(int j=0;j<=P;j++)
        {
            candidate[i][j].cost=10*(j+1);
            candidate[i][j].vorp=rand()%300;
        }
    }

    candidate_vorp(candidate,N,P,TOTAL);

    for(int i=0;i<=N;i++)
    {
        delete []candidate[i];
    }
    delete []candidate;
}