#include "investment_program.h"

int main()
{
    srand( (unsigned)time(NULL));
    double **r;

    r=new double*[m+1];
    for(int i=0;i<=m;i++)
    {
        r[i]=new double[n+1];
    }

    cout<<"year j, investment i, return: "<<endl;
    for(int i=1;i<=m;i++)  //共有i种投资类型
    {
        for(int j=1;j<=n;j++) //年份从j=1到n，共n年
        {
            r[i][j]=(((rand()%1000+1)/1000.0+1)-1)/10.0;
            cout<<setprecision(3)<<showpoint<<r[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<endl;

    best_investment(r);

    for(int i=0;i<=m;i++)
    {
        delete[] r[i];
    }
    delete[] r;
    return 0;
}