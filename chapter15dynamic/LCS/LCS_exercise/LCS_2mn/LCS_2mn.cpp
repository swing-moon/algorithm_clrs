#include <iostream>
using namespace std;

#define M 8
#define N 9

//仅有的二维数组：
/*用第0行作为上一行，第1行作为当前行，一次循环后，把旧的第1 
行(当前行)的所有数据转移给新的上一行，而新的当前行用来存储新的当前行数据，这样不断循环，最终 
得到LCS长度*/
void copy(int res[][M+1])
{
    for(int i=0;i<=M;i++)
      res[0][i]=res[1][i];
}

void LCS_length_2mn(char *x,char *y)
{
    int res[2][M+1]={0};
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(x[i]==y[j])
              res[1][j]=res[0][j-1]+1;
            else
            {
                if(res[0][j]>=res[1][j-1])
                  res[1][j]=res[0][j];
                else
                  res[1][j]=res[1][j-1];
            }
        }
        copy(res);
    }
    cout<<"first line: "<<res[0][M]<<endl;
    cout<<"second line: "<<res[1][M]<<endl;
}

int main()    
{    
   //char x[N+1] = {'\0','A','B','C','B','D','A','B'};    
   //char y[M+1] = {'\0','B','D','C','A','B','A'};   
   char x[M+1] = {'\0','1','0','0','1','0','1','0','1'};    
   char y[N+1] = {'\0','0','1','0','1','1','0','1','1','0'};   
   LCS_length_2mn(x,y);
   return 0;    
}   