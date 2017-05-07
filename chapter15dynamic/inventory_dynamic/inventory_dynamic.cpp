#include "inventory_dynamic.h"


int main()
{
    int result_cost,original_create;
    int d[n+1]={0,10,11,13,14,20,25,29,9,8,7};  //146

    int HR_extra[n+1]={0};
    int result[n+1]={0};

    int create[n+1][n+1]={0};
    //int cost[n+1][n+1]={0};

    original_create=create_material(d,create,0,n);
    init_create(create,d);

    result_cost=min_cost(d,HR_extra,1,n);

    cout<<"The result is :"<<endl;
    cout<<result_cost<<endl;

    cout<<"The create result is :"<<endl;

    for(int i=1;i<=n;i++)
    {
        cout<<m-HR_extra[i]<<" ";
    }
}