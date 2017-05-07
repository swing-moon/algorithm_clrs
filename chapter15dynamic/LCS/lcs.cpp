#include <iostream>
#include <cstdlib>
#include <locale>
#include "LCS_len.h"

int main()
{
    setlocale(LC_ALL,"chs");
    char x[N+1]={'\0','1','0','0','1','0','1','0','1'};
    char y[M+1]={'\0','0','1','0','1','1','0','1','1','0'};

    LCS_length(x,y);
    Print_lcs(x,N,M);
    std::cout<<std::endl;

    std::cout<<"Gene Distance:"<<std::endl;

    for(int i=0;i<=N;i++)
    {
        for(int j=0;j<=M;j++)
        {
            std::wcout<<b[i][j]<<"\t";
        }
        std::cout<<std::endl;
        for(int j=0;j<=M;j++)
        {
            std::cout<<c[i][j]<<"\t";
        }
        std::cout<<std::endl;
    }
    system("pause");
    return 0;
}