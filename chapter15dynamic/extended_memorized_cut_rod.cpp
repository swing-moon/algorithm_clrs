#include <iostream>
using namespace std;
#define INFINITY 0x7fffffff

struct rod
{
  int result;
  int solution;
};

int max(int a, int b)
{
  return a>b?a:b;
}

rod *memorized_cut_rod_aux(int p[], int n, rod res[])
{
  int q;
  if(res[n].result>=0)
    return res+n;

  if(n==0)
    q=0;   //规模为0的时候，自然收益为0
  else
  {
    q=-INFINITY;
    for(int i=0;i<n;i++)
    {
      //会犯错误的地方：
      //这里不能够直接写
      //q=max(q,p[i]+(memorized_cut_rod(p,n-1-i,res))->solution)
      //因为还要进行储存切割方案，在子问题规模为i+1的时候，有可能进行切割，也有可能不切割
      int tmp=p[i]+memorized_cut_rod_aux(p,n-1-i,res)->solution;
      //在p[i]处的最优方案是tmp，tmp和q进行比较判断后，推出在i+1处的最优方案

      //这里把n分解成更小的子问题，怎么解决？通过递归解决
      //memorized_cut_rod_aux(p,n-1-i,res)把n-1的子问题转化为n-1-i
      if(q<tmp)
      {
        q=tmp;
        res[n].solution=i+1;
        //我们这里返回的就是问题规模为n时候的切割方案，这里的切割方案是：
        //切割一次or无切割！
        //i<n-1时候，q=tmp表示切割
        //i==n-1的时候，tmp=p[n-1]+memorized_cut_rod(p,0,res)->solution
        //如果此时还满足q<tmp，res[n].solution=n-1+1=n，表示无切割
        //这一步的目的在于保存每一个循环过程中i的最优方案
      }
    }
  }

  res[n].result=q;
  return res+n;
}

rod *memorized_cut_rod(int p[], int n)
{
  rod *res=new rod[n];
  for(int i=0;i<=n;i++)
  {
    res[i].result=-INFINITY;
  }

  return memorized_cut_rod_aux(p,n,res);
}

void PRINT_CUT_ROD_SOLUTION(int p[], int n)
{
  rod *res=memorized_cut_rod(p,n);
  cout<<"max result"<<res->result<<endl;
  cout<<"solution: "<<endl;
  while(n)
  {
    cout<<(*res).solution<<" ";
    n=n-(*res).solution;
    res=res-(*res).solution;
  }
}

//重点：在于区分数组下标和子问题的规模，数组下标为i-1，子问题的规模为i

void main()
{
  const int n=10;
  int p[10]={1,5,8,9,10,17,17,20,24,30};
  PRINT_CUT_ROD_SOLUTION(p,10);
  cout<<endl;
}
