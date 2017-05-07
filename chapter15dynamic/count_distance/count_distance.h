#include <iostream>
using namespace std;
#define infinity 0x7fffffff
enum {COPY,REPLACE,DELETE,INSERT,TWIDDLE,KILL,TYPE_NUM};
struct TABLE
{
    int **cnt,**res;
    TABLE(int m,int n)  //res[m][n] 分别表示图中x_max和y_max
    {
        cnt=new int *[m+1];
        for(int i=0;i<=m;i++)
            cnt[i]=new int [n+1];
        res=new int *[m+1];
        for(int i=0;i<=m;i++)
            res[i]=new int [n+1];
    }
};
void PRINT_SOLUTION(TABLE dis,int i,int j);
TABLE count_distance(char x[],char y[],int m,int n)
{
    TABLE dis(m,n);
    int cost[TYPE_NUM]={-1,1,2,2,-2,1};
    //初始化
    dis.cnt[0][0]=0;
    for(int i=0;i<=m;i++)
    {
        dis.cnt[i][0]=i*cost[DELETE];  //这里不操作y，等于把x中的元素全部删除
        //删除的代价就是 第几个元素×cost
        dis.res[i][0]=DELETE;
    }
    for(int j=0;j<=n;j++)
    {
        //这里相当于x中没有元素，y[]的值等于插入每一个新的元素
        dis.cnt[0][j]=j*cost[INSERT];
        dis.res[0][j]=INSERT;
    }
    //计算最优代价
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            dis.cnt[i][j]=0x7fffffff;
            if(x[i]==y[j] && dis.cnt[i-1][j-1]+cost[COPY]<dis.cnt[i][j])
            {
                dis.cnt[i][j]=dis.cnt[i-1][j-1]+cost[COPY];
                dis.res[i][j]=COPY;
            }
            if(x[i]!=y[j] && dis.cnt[i-1][j-1]+cost[REPLACE]<dis.cnt[i][j])
            {
                dis.cnt[i][j]=dis.cnt[i-1][j-1]+cost[REPLACE];
                dis.res[i][j]=REPLACE;
            }
            if(i>=2&&j>=2&& x[i]==y[j-1] && x[i-1]==y[j] && dis.cnt[i-2][j-2]+cost[TWIDDLE]<dis.cnt[i][j])
            {
                dis.cnt[i][j]=dis.cnt[i-2][j-2]+cost[TWIDDLE];
                dis.res[i][j]=TWIDDLE;
            }
            if(dis.cnt[i-1][j]+cost[DELETE]<dis.cnt[i][j])
            {
                dis.cnt[i][j]=dis.cnt[i-1][j]+cost[DELETE];
                dis.res[i][j]=DELETE;
            }
            if(dis.res[i][j-1]+cost[INSERT]<dis.cnt[i][j])
            {
                dis.cnt[i][j]=dis.cnt[i][j-1]+cost[INSERT];
                dis.res[i][j]=INSERT;
            }
        }
    }
    //此时序列y[n]的值已经完成，这个时候截取从0<=i<=m-1中最小的kill值
    //把m以后的值全部截取掉
    for(int i=0;i<=m-1;i++)
    {
        if(dis.cnt[i][n]+cost[KILL]<dis.cnt[m][n])  //相当于调整res[m][n]的值
        //判断从哪里开始截断？
        {
            dis.cnt[m][n]=dis.cnt[i][n]+cost[KILL];
            dis.res[m][n]=i;
            //从i开始截断，distance.solution[][]提供回溯的点，回溯到哪个点？
        }
    }
    cout<<"distance[m][n]="<<dis.cnt[m][n]<<" "<<endl;
    //输出：
    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=n;j++)
            cout<<dis.cnt[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=n;j++)
            PRINT_SOLUTION(dis,i,j);
        cout<<endl;
    }
    cout<<endl;
    return dis;
}
void PRINT_sequence(TABLE dis,int i,int j)
{
    int I,J;
    if(i==0 && j==0)
        return;
    if(dis.res[i][j]==COPY || dis.res[i][j]==REPLACE)
    {
        I=i-1;
        J=j-1;
    }
    else if(dis.res[i][j]==TWIDDLE)
    {
        I=i-2;
        J=j-2;
    }
    else if(dis.res[i][j]==DELETE)
    {
        I=i-1;
        J=j;
    }
    else if(dis.res[i][j]==INSERT)
    {
        I=i;
        J=j-1;
    }
    else
    {
        I=dis.res[i][j];
        J=j;
        dis.res[i][j]=KILL;
    }
    PRINT_sequence(dis,I,J);
    PRINT_SOLUTION(dis,i,j);
}
void PRINT_SOLUTION(TABLE dis,int i,int j)
{
    if(dis.res[i][j]==COPY)
        cout<<"COPY"<<" ";
    else if(dis.res[i][j]==REPLACE)
        cout<<"REPLACE"<<" ";
    else if(dis.res[i][j]==INSERT)
        cout<<"INSERT"<<" ";
    else if(dis.res[i][j]==TWIDDLE)
        cout<<"TWIDDLE"<<" ";
    else
        cout<<"KILL"<<" ";
}