#include "break_string.h"


int main()
{
    //int L[m]={2,8,10};
    int L[m]={11,14,17,20,25};
    int cost[n+1][n+1];
    int cut[n+1][n+1]={0};

    INITIATE(cost);
    //初始化完毕

    int result=break_point(L,cost,1,n,cut);
    print_breaks(L,cut,1,n);

    cout<<endl;
    cout<<"The result is :";
    cout<<result<<endl;
    return 0;

}