#include <iostream>
#include <string>
#include <locale>

#define M 11
#define N 11

wchar_t b[N+1][M+1]={'S'};  //表示起点start
int c[N+1][M+1]={0};
wchar_t northwest=L'\\', up=L'|', leftway=L'-';

void LCS_length(int *x,int *y)
{
    for(int i1=0;i1<=N;i1++)
      b[i1][0]='S';
    for(int j1=0;j1<=M;j1++)
      b[0][j1]='S';

    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(x[i]==y[j])
            {
                c[i][j]=c[i-1][j-1]+1;
                b[i][j]=northwest;     //Northwest往左上
            }
            else
            {
                if(c[i-1][j]>=c[i][j-1])
                //c[i-1][j-1] 过渡到 c[i][j]，需要将c[i-1][j]和c[i][j-1]比较大小
                //取较大的那一个值
                {
                    c[i][j]=c[i-1][j];
                    b[i][j]=up;  //Up往上
                }
                else
                {
                    c[i][j]=c[i][j-1];
                    b[i][j]=leftway;  //Left往左
                }
            }
        }
    }
}

void Print_lcs(int *x,int i,int j)
{
    if(i==0||j==0)
      return;
    if(b[i][j]==northwest)
    {
        Print_lcs(x,i-1,j-1);
        std::cout<<x[i]<<" ";     //当然，按y[j]输出也没有问题，因为是公共序列嘛！
    }
    else
    {
        if(b[i][j]==up)
          Print_lcs(x,i-1,j);
        else
          Print_lcs(x,i,j-1);
    }
}