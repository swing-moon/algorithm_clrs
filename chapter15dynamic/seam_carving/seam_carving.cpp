#include "seam_carving.h"

int main()
{
    int **d;
    d=new int *[n+1];
    for(int i=0;i<=n;i++)
        d[i]=new int[m+1];
    
    int d_val[n+1][m+1]={{0,0,0,0,0,0},{0,3,2,2,3,3},{0,1,2,1,2,1},{0,3,2,1,3,1},{0,2,1,1,2,2},{0,1,2,2,3,3},{0,2,2,2,1,1}};
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
            d[i][j]=d_val[i][j];
    }

    seam_carving(d);
    
    return 0;
}