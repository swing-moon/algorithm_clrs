#include "print_neatly.h"

int main()
{
    int n=10;  //10个单词
    int Maxnum=8;  //一行可以容纳最多8个字符
    string number[n]={"abc","def","gh","polq","cs","opaqe","klfgh","t","asd","th"};
    int length[n]={0};

    for(int i=0;i<n;i++)
    {
        length[i]=number[i].size();
    }
    print_neatly(length,number,n,Maxnum);
    return 0;
}