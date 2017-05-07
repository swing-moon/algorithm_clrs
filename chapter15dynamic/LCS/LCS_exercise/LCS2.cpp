#include <iostream>
#include "lcs_len2.h"

int main()
{
    char x[N+1]={'\0','A','B','C','B','D','A','B'};
    char y[M+1]={'\0','B','D','C','A','B','A'};
    int c[N+1][M+1]={0};
    lcs_len_withouthelp(x,y,c);
    print_LCS_withouthelp(c,x,N,M);
}