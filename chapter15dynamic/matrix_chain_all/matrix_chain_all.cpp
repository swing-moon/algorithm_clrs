#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <memory>
using namespace std;
#define n 6
#define INFINITY 0x7fffffff

struct Matrix
{
    int rows;  //表示行数
    int columns;  //表示列数
    vector<vector<int> > matrix;
};

struct Matrix_Chain
{
    vector<vector<int> > m;  //表示运算次数
    vector<vector<int> > s;  //划分方式
    Matrix_Chain()
    {
        m.resize(n-1);  //有n-1个括号
        for(int k=0;k<n-1;k++)
        {
            m[k].resize(n-1);    //最后输出的是一个对角阵
                                 //辅助表m[1...n-1, 1...n-1]来保存代价
                                 //s[1...n-1,2...n]记录最优值m[i,j]对应的分割点k
        }
        s.resize(n-1);
        for(int t=0;t<n-1;t++)
        {
            s[t].resize(n-1);
        }
    }
};

Matrix init(Matrix &A,int r,int c)  //对A的矩阵具体值的初始化
{
    A.rows=r;
    A.columns=c;
    A.matrix.resize(A.rows);
    for(int i=0;i<A.rows;i++)
        A.matrix[i].resize(A.columns);

    srand((unsigned)time(0));
    for(int i=0;i<A.rows;i++)
    {
        for(int j=0;j<A.columns;j++)
        {
            A.matrix[i][j]=rand()%n+1;
        }
    }
    return A;
}

void print(Matrix A)
{
    for(int i=0;i<A.rows;i++)
    {
         for(int j=0;j<A.columns;j++)
            cout<<A.matrix[i][j]<<" ";
            cout<<endl;
    }
    cout<<endl;
}

Matrix Matrix_Mutiply(Matrix A,Matrix B)
{
    if(A.columns!=B.rows)
    {
        Matrix D;
        init(D,1,1);
        D.matrix[0][0]=0;
        cerr<<"incompatible dimensions"<<endl;
        return D;
    }
    else
    {
        Matrix C;
        init(C,A.rows,B.columns);
        for(int i=0;i<A.rows;i++)
        {
            for(int j=0;j<B.columns;j++)
            {
                C.matrix[i][j]=0;
                for(int k=0;k<A.columns;k++)
                   C.matrix[i][j]=C.matrix[i][j]+A.matrix[i][k]*B.matrix[k][j];
            }
        }
        return C;
    }
}

Matrix_Chain Matrix_Chain_Order(int p[])  //这里的i j统一表示是：数组中的第几个数？
{                                         //所以，数组下标是T.m[i-1][j-1]
    Matrix_Chain T;
    int len=n-1;    //辅助表m[k,k]来保存代价，其中k=n-1，n为矩阵链长度
    for(int i=0;i<len;i++) //s[k,k]用来保存最优值m[i,j]对应的分割点
    {
        T.m[i][i]=0;
    }
    for(int l=2;l<=len;l++)  //l表示矩阵链长度
    {
        for(int i=1;i<=len-l+1;i++)
        {
            int j=i+l-1;
            T.m[i-1][j-1]=INFINITY;   //用来计算[i,i+1..k] [k+1..,j-1,j]这样划分的运算代价
            for(int k=i;k<j;k++)     //循环中的i表示第几个数，T.m[i]中的i表示数组下标
            //千万注意，这里k从i开始！
            {
                int q=T.m[i-1][k-1]+T.m[k][j-1]+p[i-1]*p[k]*p[j];
                if(q<T.m[i-1][j-1])
                {
                    T.m[i-1][j-1]=q;
                    T.s[i-1][j-1]=k-1;
                }
            }
        }
    }
    return T;
}

//下面这是用错误的贪心算法求解的问题：
Matrix_Chain Matrix_Chain_Order_greedy(int p[])
{
    int N=n-1;
    Matrix_Chain T_greedy;
    for(int i=0;i<N;i++)
      T_greedy.m[i][i]=0;
    for(int l=2;l<=N;l++)
    {
        for(int i=1;i<=N-l+1;i++)
        {
            int j=i+l-1;
            T_greedy.m[i-1][j-1]=INFINITY;
            int q_min=INFINITY;
            for(int k=i;k<=j-1;k++)
            {
                int q=T_greedy.m[i-1][k-1]+T_greedy.m[k][j-1]+p[i-1]*p[k]*p[j];
                if(q_min>p[i-1]*p[k]*p[j])
                {
                    q_min=p[i-1]*p[k]*p[j];
                    T_greedy.m[i-1][j-1]=q;
                    T_greedy.s[i-1][j-1]=k-1;
                }
            }
        }
    }
    return T_greedy;
}


//矩阵链总乘法，相当于二路归并
//在二路归并排序中，递归处理，让区间的长度从l逐渐减小到0
//递归到尾端的时候，是两个数相乘A[i]*A[j] (j==i+1)

//函数参数：矩阵链乘法中，1、传递A[]矩阵的原始数据，2、括号的划分情况，存储在数组T.s[]中
Matrix Matrix_Chain_Multiply(Matrix A[],Matrix_Chain T,int i,int j)
{
    if(j==i)
      return A[i];
    if(j==i+1)
      return Matrix_Mutiply(A[i],A[j]);
    Matrix t1=Matrix_Chain_Multiply(A,T,i,T.s[i][j]);  //矩阵T.s[i][j]表示A[i...j]的划分方式
    Matrix t2=Matrix_Chain_Multiply(A,T,T.s[i][j]+1,j);
    return Matrix_Mutiply(t1,t2);
}

//同理，打印输出矩阵链乘法也是如此：
void Print_Optimal_Parents(Matrix_Chain T,int i,int j)
{
    if(i==j)
      cout<<"A"<<i<<" ";
    else
    {
        cout<<"("<<" ";
        Print_Optimal_Parents(T,i,T.s[i][j]);
        Print_Optimal_Parents(T,T.s[i][j]+1,j);
        cout<<")"<<" ";
    }
}

int main()
{
    Matrix test;
    init(test,4,5);
    print(test);
    cout<<"Program begins: "<<endl;

    int p[n]={5,10,20,25,34,68};
    Matrix_Chain T=Matrix_Chain_Order(p);

    for(int i=0;i<n-1;i++)   //矩阵的dimension，等于矩阵链规模n-1
    {
        for(int j=0;j<n-1;j++)  //原矩阵对应的值A[i....j]=A[0...n-2]
        {
            if(T.m[i][j]<0)
              cout<<"-1"<<"\t";
            else
              cout<<T.m[i][j]<<"\t";
        }
        cout<<endl;
    }

    //贪心算法求解
    cout<<"greedy result:"<<endl;
    Matrix_Chain T_greedy=Matrix_Chain_Order_greedy(p);
    for(int i=0;i<n-1;i++)   //矩阵的dimension，等于矩阵链规模n-1
    {
        for(int j=0;j<n-1;j++)  //原矩阵对应的值A[i....j]=A[0...n-2]
        {
            if(T.m[i][j]<0)
              cout<<"-1"<<"\t";
            else
              cout<<T.m[i][j]<<"\t";
        }
        cout<<endl;
    }


    Print_Optimal_Parents(T,0,n-2);
    cout<<endl;

    cout<<"greedy result:"<<endl;
    Print_Optimal_Parents(T_greedy,0,n-2);
    cout<<endl;

    cout<<"Concret Implement:"<<" "<<endl;

    Matrix A[n];   //这里的A存放的是指向Matrix数组第一个元素的指针
    //A[]的dimension的值,具体一点为p(i-1)*p(i)
    for(int j=1;j<n;j++)
    {
        Matrix t;
        init(t,p[j-1],p[j]);    //A[rows*columns]--->p[j-1]*p[j]
        A[j-1]=t;    //p[]仅仅表示A[]的维度，具体的值用init初始化
        cout<<endl;
        print(A[j-1]);
        cout<<endl;
    }

    Matrix result=Matrix_Chain_Multiply(A,T,0,n-2);
    print(result);

    return 0;
}