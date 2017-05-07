#include <iostream>
#include "optimal_bst.h"

int main()
{
    double p[n+1]={0,0.04,0.06,0.08,0.02,0.10,0.12,0.14};
    double q[n+2]={0.06,0.06,0.06,0.06,0.05,0.05,0.05,0.05};

    e_root Table=Optimal_bst(p,q);
    cout<<"BST result "<<endl;
    Construct_Optimal_BST(Table,1,n);
    cout<<endl;
    cout<<"cost: "<<Table.e[1][n]<<endl;
    return 0;
}