#include <iostream>
using namespace std;

#define n 6  //数组行
#define m 5  //数组列
#define INFINITY 0x7fffffff

//总共n行 m列

void print_seam(int **A,int i,int j);  //第i行 第j列

int Additional_Min(int **A,int i,int j)  //第i行 第j列
{
    int temp=0;
    if(j==1)
    {
        temp=A[i-1][j]>A[i-1][j+1]?A[i-1][j+1]:A[i-1][j];
    }
    else if(j==m)
    {
        temp=A[i-1][j]>A[i-1][j-1]?A[i-1][j-1]:A[i-1][j];
    }
    else
    {
        if(A[i-1][j]>A[i-1][j-1])
        {
            temp=A[i-1][j-1];
            if(A[i-1][j-1]>A[i-1][j+1])
                temp=A[i-1][j+1];
        }
        else
        {
            temp=A[i-1][j];
            if(A[i-1][j]>A[i-1][j+1])
                temp=A[i-1][j+1];
        }
    }
    return temp;
}

void seam_carving(int **d)
{
    int **A,i;  //二维数组表示破坏度之和
    A=new int *[n+1];
    for(i=0;i<=n;i++)
        A[i]=new int[m+1];
    
    for(int j=1;j<=m;j++)
        A[1][j]=d[1][j];

    for(i=2;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
            A[i][j]=d[i][j]+Additional_Min(A,i,j);
    }

    //输出最后接缝的位置
    int min_seam=INFINITY;
    int seam_plot=0;
    for(int j=1;j<=m;j++)
    {
        if(A[n][j]<min_seam)
        {
            min_seam=A[n][j];
            seam_plot=j;
        }
    }
    cout<<"MIN break point is "<<min_seam<<endl;
    print_seam(A,n,seam_plot);

    for(int i=0;i<=m;i++)
        delete [] A[i];
    delete[] A; 
}

void print_seam(int **A,int i,int j) //i行 j列，总共n行 m列
{
    int seam_next;
    if(i==0)
        return;
    else
    {
        if(j==m)
            seam_next=A[i][j]>A[i][j-1]?j-1:j;
        else if(j==1)
            seam_next=A[i][j]>A[i][j+1]?j+1:j;
        else
        {
            if(A[i][j]>A[i][j-1])
            {
                seam_next=j-1;
                if(A[i][j-1]>A[i][j+1])
                    seam_next=j+1;
            }
            else
            {
                seam_next=j;
                if(A[i][j]>A[i][j+1])
                    seam_next=j+1;
            }
        }
    }

    print_seam(A,i-1,seam_next);
    cout<<"ROW: "<<i<<" "<<"COLUMN: "<<seam_next<<"->";  
    //输出方式，注意把这一句放在递归下面，从i=1--->i=n从上往下执行输出
    //如果放在递归前面就是从下往上输出
}