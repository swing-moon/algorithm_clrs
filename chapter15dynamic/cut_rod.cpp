#include <iostream>
#define INFINITY 0x7fffffff
using namespace std;

int max(int a,int b)
{
  return a>b?a:b;
}

int memorized_cut_rod_aux(int p[],int n,int r)  //n表示问题的规模
{
  //注意，这里p[i]的意义和r[i]的意义不一样
  //p[i]表示对应的数组元素，i表示下标
  //r[i]表示问题的规模为i所对应的解
  //p[i]对应的问题是第i个，其规模为i+1，剩余的问题规模是n-(i+1)
  //从另一个角度，0<=i<=n-1 0<=r<=n-1，所以递归的时候是(p,n-1-i,r)
  int result;
  if(r[n]>=0)
    return r[n];  //表示问题已经被求解完毕了，返回该值

  if(n==0)
    result=0;  //表示没有切割
  else
  {
    result=-INFINITY;
    for(int i=0;i<n;i++)
    {
      result=max(result,p[i]+memorized_cut_rod_aux(p,n-1-i,r));
    }
  }
  //表示规模为n的问题求解完毕
  //实际上，递归过程中r[i+1]=result，返回的是r[i+1]
  r[n]=result;
  return result;

}
int memorized_cut_rod(int p[],int n)
{
  int *r=new int[n];
  for(int i=0;i<n;i++)
  {
    r[i]=-INFINITY;
  }

  return memorized_cut_rod_aux(p,n,r);  //这里(p,n,r)
  //r[]的递归标最多为n-1
}

int BOTTOM_UP_CUT_ROD(int p[],int n)
{
  int *r=new int [n];
  r[0]=0;
  for(int j=0;j<n;j++)
  {
    int result=-INFINITY;
    for(int i=0;i<=j;i++)
    {
      //获取scale=j时候的max值，即最大收益result
      //随着j++，我们获取最大收益的时候要返回r[j+1]的值，这样
      //scale=scale+1时候的最大收益，即r[j+1]，即为上一步求出的
      //result值，即r[j+1]=result
      result=max(result,p[i]+r[j-1]);
    }
    r[j+1]=result;

  }
  return r[n];
  //返回的r[n]这里的n指问题的规模
}

int main()
{
  const int n=10;
  int p[10]={1,5,8,9,10,17,17,20,24,30};
  cout<<memorized_cut_rod(p,9)<<endl;
  cout<<BOTTOM_UP_CUT_ROD(p,9)<<endl;
}
