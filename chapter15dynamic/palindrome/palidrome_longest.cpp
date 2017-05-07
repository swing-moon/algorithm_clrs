#include "palidrome_longest.h"

int main()
{
    char x[N+1]={0};
    char y[N+1]={0};
    char c;
    cout<<"get the string you need to judge: "<<endl;
    int i;
    for(i=1;i<=N;i++)  //默认的字符串是从下标1开始的，这里我们可以让它从0开始
    {
        cin>>c;
        y[i]=x[i]=c;
    }
    x[i]='\0';y[i]='\0';
    cout<<y<<endl;
    cout<<"x="<<y<<endl;
    strReverse(y);   //反转字符串
    cout<<"y="<<y<<endl;
    LCS_length(x,y);
    Print_lcs(x,N,N);
    return 0;
}