#include <iostream>
#define M 6
#define N 7

void lcs_len_withouthelp(char *x, char *y,int c[][M+1])
{
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(x[i]==y[j])
              c[i][j]=c[i-1][j-1]+1;
            
            else
            {
                if(c[i-1][j]>=c[i][j-1])
                  c[i][j]=c[i-1][j];
                else
                  c[i][j]=c[i][j-1];
            }
        }
    }
}

void print_LCS_withouthelp(int c[][M+1],char *x,int i,int j)
{
    if(i==0||j==0)
      return;
    if(c[i][j]==c[i-1][j-1]+1)
    {
        print_LCS_withouthelp(c,x,i-1,j-1);
        std::cout<<x[i]<<" ";
    }
    else
    {
        if(c[i-1][j]>=c[i][j-1])
          print_LCS_withouthelp(c,x,i-1,j);
        else
          print_LCS_withouthelp(c,x,i,j-1);
    }
}