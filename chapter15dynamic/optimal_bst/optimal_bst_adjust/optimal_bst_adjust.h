#include <iostream>
#include <vector>
using namespace std;
#define n 7
#define INFINITY 0x7fffffff

struct e_root
{
    vector<vector<double> > e;
    vector<vector<int> > root;

    e_root()
    {
        e.resize(n+2);
        for(int i=0;i<n+2;i++)
          e[i].resize(n+1);
        
        root.resize(n+1);
        for(int j=0;j<n+1;j++)
          root[j].resize(n+1);
    }
};

e_root Optimal_bst(double p[],double q[])
{
    e_root Table;
    double w[n+2][n+1]={0};  //w[][]用来计算概率值，更多是辅助数组

    for(int i=1;i<=n+1;i++)
    {
        Table.e[i][i-1]=q[i-1];
        w[i][i-1]=q[i-1];
    }

    for(int l=1;l<=n;l++)
    {
        for(int i=1;i<=n-l+1;i++)
        {
            int j=i+l-1;
            Table.e[i][j]=INFINITY;
            w[i][j]=w[i][j-1]+p[j]+q[j];
            /*for(int r=i;r<=j;r++)
            {
                double tmp=Table.e[i][r-1]+Table.e[r+1][j]+w[i][j]; //递归公式
                if(tmp<Table.e[i][j])
                {
                    Table.e[i][j]=tmp;
                    Table.root[i][j]=r;
                }
            }*/
            if(i==j)
            {
                Table.root[i][j]=j;
                Table.e[i][j]=Table.e[i][j-1]+Table.e[j+1][j]+w[i][j];
            }
            else
            {
                for(int r=Table.root[i][j-1];r<=Table.root[i+1][j];r++)
                {
                    double tmp=Table.e[i][r-1]+Table.e[r+1][j]+w[i][j];
                    if(tmp<Table.e[i][j])
                    {
                        Table.e[i][j]=tmp;
                        Table.root[i][j]=r;
                    }
                }
            }
        }
    }
    return Table;
}

//输出BST的值
void Construct_Optimal_BST(e_root Table,int i,int j)
{
    int cur_root=Table.root[i][j];
    if(i==1&&j==n)
      cout<<"k"<<cur_root<<" is root "<<endl;

    if(i==cur_root)
      cout<<"d"<<i-1<<" is k"<<cur_root<<" left child "<<endl;
    else
    {
        cout<<"k"<<Table.root[i][cur_root-1]<<" is "<<"k"<<cur_root<<" left child "<<endl;
        Construct_Optimal_BST(Table,i,cur_root-1);
    }

    if(j==cur_root)
      cout<<"d"<<j<<" is "<<"k"<<cur_root<<" right child "<<endl;
    else
    {
        cout<<"k"<<Table.root[cur_root+1][j]<<" is k"<<cur_root<<" right child "<<endl;
        Construct_Optimal_BST(Table,cur_root+1,j);
    }
}