#include <iostream>
using namespace std;

#define M 6
#define N 7

int Max(int a,int b)
{
    return a>b?a:b;
}

//数组初始化为0的方法：
//只要定义第一个元素为0，后面就劝为0了
//int c[N+1][M+1]={0}

int lcs_length(char *x,char *y,int c[][M+1],int i,int j)  //这里，i,j指下标，就是第几个数
//在递归的时候，从最后一个数，就是第N，M个数算起
{
    if(i==0||j==0)
      c[i][j]=0;
    else if(c[i][j]>0)
      return c[i][j];
    
    else
    {
        if(x[i]==y[j])
          c[i][j]=lcs_length(x,y,c,i-1,j-1)+1;
        else 
          c[i][j]=Max(lcs_length(x,y,c,i-1,j),lcs_length(x,y,c,i,j-1));

    }
    return c[i][j];
}

int main()
{
    char x[N+1] = {'\0','A','B','C','B','D','A','B'};
    char y[M+1] = {'\0','B','D','C','A','B','A'};
    int c[N+1][M+1]={0};
    cout<<lcs_length(x,y,c,N,M);
    cout<<endl;
}