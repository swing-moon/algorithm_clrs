#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

#define n 10
#define m 8

void best_investment(double **r)
{
    double increase[n+1][m+1];  //二维数组increase[i][j]表示第i年购买第j种投资
    double f1=0.01,f2=0.04;
    double addition;
    
    for(int i=1;i<=m;i++)
    {
        increase[1][i]=r[i][1]+1.0;
        //第一年为初始状态，最大值就是本年每一种投资的值
    }

    for(int j=2;j<=n;j++)  //表示第j年
    {
        for(int k=1;k<=m;k++) //表示第k种投资
        {
            increase[j][k]=-0x7fffffff;
            //从第一种投资开始检查，看看是否有和k相等类型的投资？
            //类似的问题可以这样解决：两个for循环，然后从第一种投资一次开始检查
            //第二种投资类型，只有几种状态：A B C等等。依次检查，看看addition值属于哪种类型
            for(int check=1;check<=m;check++)
            {
                if(check==k)
                    addition=f1;
                else
                    addition=f2;

                if((increase[j-1][check]-addition)*(1.0+r[k][j])>increase[j][k])
                {
                    //r[k][j]第j年第k种投资
                    increase[j][k]=(increase[j-1][check]-addition)*(1.0+r[k][j]);
                }
            }
        }
    }

    cout<<"year i, investment j, total: "<<endl;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cout<<setprecision(5)<<showpoint<<increase[i][j]<<"\t";
        }
        cout<<endl;
    }

    cout<<"after 10 years, the investment is :"<<endl;
    double total_10=-0x7fffffff;
    for(int k=1;k<=m;k++)  //表示第k种投资
    {
        if(increase[n][k]>total_10)
            total_10=increase[n][k];
    }

    cout<<total_10<<endl;
}