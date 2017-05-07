#include <iostream>
#include <string.h>

#define infinity 0x7fffffff

using namespace std;
int get_lines(int solution[],int j,string number[]);

void print_neatly(int length[],string number[],int n,int Maxnum)
{
    int i,j;

    //保存空格数
    int **space;
    space=new int *[n+1];
    for(int i=0;i<=n;i++)
    {
        space[i]=new int [n+1];
    }


    //保存立方值
    int **cube;
    cube=new int *[n+1];
    for(int i=0;i<=n;i++)
    {
        cube[i]=new int [n+1];
    }

    //用于保存解决方案
    int *solution=new int [n+1];

    //初始化获取space[][]的值
    for(int i=1;i<=n;i++)
    {
        space[i][i]=Maxnum-length[i-1];  //这里space[i][]表示第几个数？length[i-1]对应的是下标
        for(int j=i+1;j<=n;j++)
            space[i][j]=space[i][j-1]-length[j-1]-1;
    }

    //获取cube的值，整齐打印是依据cube的值来确定打印距离
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(space[i][j]<0)
                cube[i][j]=infinity;
            else if(j==n && space[i][j]>=0)
                cube[i][j]=0;
            else
                cube[i][j]=space[i][j]*space[i][j]*space[i][j];
        }
    }

    //动态规划过程，将结果存储在res数组中
    int *res=new int [n+1];
    res[0]=0;

    for(int j=1;j<=n;j++)
    {
        res[j]=infinity;
        for(int i=1;i<=j;i++)
        {
            if(res[i-1]!=infinity && cube[i][j]!=infinity && (res[i-1]+cube[i][j]<res[j]))
            {
                res[j]=res[i-1]+cube[i][j];
                solution[j]=i;    //i为当前行的第一个元素
            }
        }
    }

    get_lines(solution,n,number);

    //释放内存
    delete[] res;

    delete[] solution;

    for(int i=0;i<=n;i++)
        delete[] cube[i];
    delete[] cube;

    for(int i=0;i<=n;i++)
        delete[] space[i];
    delete[] space;
}

int get_lines(int solution[],int j,string number[])  //j为当前行的最后一个元素下标
{
    int k;
    int i=solution[j];

    if(i==1)  //表示第一个元素
        k=1;
    else
        k=get_lines(solution,i-1,number)+1;  //递归
    cout<<"current line number is : "<<k<<" ";

    for(int l=i;l<=j;l++)
        cout<<number[l-1]<<" ";  //当前行的第l个元素，str下标为l-1
    cout<<endl;
    return k;
}