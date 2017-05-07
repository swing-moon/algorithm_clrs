#include "break_string2.h"

int main()
{
    //int L[n]={0,2,8,10,20};
    int L[n]={0,11,14,17,20,25,30};
    int cut[n+1][n+1]={0};

    int result=break_string_array(L,cut);
    cout<<"result is : "<<endl;
    cout<<result<<endl;

    print_breaks(L,cut,1,n);
}