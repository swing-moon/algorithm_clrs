#include <iostream>
#include <string>
#include <locale>

using namespace std;

#define N 9                 //输入您要判断的字符串的字符数
wchar_t b[N+1][N+1]={'S'};  //表示起点start
int c[N+1][N+1]={0};
wchar_t northwest=L'\\', up=L'|', leftway=L'-';
void LCS_length(char *x,char *y)
{
    for(int i1=0;i1<N;i1++)
      b[i1][0]='S';
    for(int j1=0;j1<N;j1++)
      b[0][j1]='S';
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(x[i]==y[j])
            {
                c[i+1][j+1]=c[i][j]+1;
                b[i+1][j+1]=northwest;     //Northwest往左上
            }
            else
            {
                if(c[i][j+1]>=c[i+1][j])
                //c[i-1][j-1] 过渡到 c[i][j]，需要将c[i-1][j]和c[i][j-1]比较大小
                //取较大的那一个值
                {
                    c[i+1][j+1]=c[i][j+1];
                    b[i+1][j+1]=up;  //Up往上
                }
                else
                {
                    c[i+1][j+1]=c[i+1][j];
                    b[i+1][j+1]=leftway;  //Left往左
                }
            }
        }
    }
}
void Print_lcs(char *x,int i,int j)
{
    if(i==0||j==0)
      return;
    if(b[i][j]==northwest)
    {
        Print_lcs(x,i-1,j-1);
        cout<<x[i-1]<<" ";     //当然，按y[j]输出也没有问题，因为是公共序列嘛！
    }                          //这里的下标是从i=0开始的，所以输出x[i-1]
    else
    {
        if(b[i][j]==up)
          Print_lcs(x,i-1,j);
        else
          Print_lcs(x,i,j-1);
    }
}

char *strReverse(char *str)
{
    for(int i=0;i<N/2;i++)
    {
        swap(str[i],str[N-1-i]);
    }
    return str;
}