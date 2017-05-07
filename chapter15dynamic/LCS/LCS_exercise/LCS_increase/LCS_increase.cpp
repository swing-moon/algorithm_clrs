#include "LCS_quicksort.h"
#include "LCS_len.h"
#include <iostream>
#include <locale>
#include <cstdlib>

int main()
{
    setlocale(LC_ALL,"chs");
    srand((unsigned)time(NULL));
    int x[N+1]={0};
    int y[N+1]={0};  //一般，第一个位置放0，第二个位置放1
    //i的循环，从i=1 to N

    for(int i=1;i<=N;i++)
    {
        y[i]=x[i]=rand()%10+1;
        std::cout<<x[i]<<" ";
    }
    std::cout<<std::endl;
    QUICKSORT(y,0,N);
    LCS_length(x,y);
    Print_lcs(x,N,N);
    std::cout<<std::endl;
    std::cout<<"15-8"<<std::endl;

    for(int i=0;i<=N;i++)
    {
        for(int j=0;j<=N;j++)
          std::wcout<<b[i][j]<<"\t";
        
        std::cout<<std::endl;
        for(int j=0;j<=N;j++)
          std::cout<<c[i][j]<<"\t";
        std::cout<<std::endl;
    }
    system("pause");
    return 0;
}