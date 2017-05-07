#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <memory>
using namespace std;
#define n 5
#define INFINITY 0x7fffffff


struct Matrix
{
    int rows;  //表示行数
    int columns;  //表示列数
    vector<vector<int> > matrix;
    Matrix(int r,int c)
    {
        rows=r;
        columns=c;
        matrix.resize(rows);
        for(int i=0;i<rows;i++)
          matrix[i].resize(columns);
    }
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

Matrix init(Matrix &A)  //对A的矩阵具体值的初始化
{
    srand((unsigned)time(0));
    for(int i=0;i<A.rows;i++)
    {
        for(int j=0;j<A.columns;j++)
        {
            A.matrix[i][j]=rand()%n;
        }
    }
    return A;
}

Matrix Matrix_Mutiply(Matrix A,Matrix B)
{
    if(A.columns!=B.rows)
    {
        Matrix D(1,1);
        D.matrix[0][0]=0;
        cerr<<"incompatible dimensions"<<endl;
        return D;
    }
    else
    {
        Matrix C(A.rows, B.columns);
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

//矩阵链总乘法，相当于二路归并
//在二路归并排序中，递归处理，让区间的长度从l逐渐减小到0
//递归到尾端的时候，是两个数相乘A[i]*A[j] (j==i+1)

//函数参数：矩阵链乘法中，1、传递A[]矩阵的原始数据，2、括号的划分情况，存储在数组T.s[]中
Matrix Matrix_Chain_Multiply(vector<Matrix> &A,Matrix_Chain T,int i,int j)  //vector在这里表示元素的下标
{
    if(j==1)
      return A.at(i);
    if(j==i+1)
      return Matrix_Mutiply(A.at(i),A.at(j));
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
        cout<<"(";
        Print_Optimal_Parents(T,i,T.s[i][j]);
        Print_Optimal_Parents(T,T.s[i][j]+1,j);
        cout<<")";
    }
}

/*int main()
{
    int p[n]={5,10,3,12,5,50,6};
    Matrix_Chain T=Matrix_Chain_Order(p);
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1;j++)
        {
            if(T.m[i][j]<0)
              cout<<"-1"<<"\t";
            else cout<<T.m[i][j]<<"\t";
        }
        cout<<endl;
    }
}*/

int main()
{
    //int p[n]={5,10,3,12,5,50,6};
    int p[n]={2,3,4,5,6};
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

    //part02:
    Print_Optimal_Parents(T,0,n-2);
    //A[]的dimension的值,具体一点为p(i-1)*p(i)
    /*unique_ptr <Matrix[]> A;//这里用智能指针新建数组，A可以指向一个动态分配的数组，数组元素类型为Matrix */
    /*unique_ptr <Matrix[]> A_unique;
    Matrix *A=A_unique.get();
    for(int j=1;j<n;j++)
    {
        Matrix tmp(p[j-1],p[j]);  //A[rows*columns]--->p[j-1]*p[j]
                                  //仅仅表示p[]仅仅表示A[]的维度，具体的值用init初始化
        A[j-1]=tmp;
        init(A[j-1]);
        cout<<endl;
        print(A[j-1]);
        cout<<endl;
    }

    //进行矩阵链运算：
    Matrix result=Matrix_Chain_Multiply(A,T,0,n-2);
    print(result);*/

    //vector<Matrix> array;
    for(int j=1;j<n;j++)
    {
        Matrix tmp(p[j-1],p[j]);
        init(tmp);
        cout<<endl;
        print(tmp);
        cout<<endl;
        //array.push_back(tmp);
    }
    //Matrix result=Matrix_Chain_Multiply(array,T,0,n-2);
    //print(result);
    system("pause");
    return 0;
}