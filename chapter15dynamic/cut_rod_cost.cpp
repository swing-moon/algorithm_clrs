#include <iostream>
using namespace std;
#define INFINITY -0x7fffffff
#define cost 2

int max(int a, int b)
{
  return a>b?a:b;
}

struct rod_cost
{
  int result;
  int solution;
  bool cut_or_not;
};

rod_cost *EXTENDED_BOTTOM_UP_CUT_ROD(int p[], int n)
{
  rod_cost *res=new rod_cost[n];
  res[0].result=0;
  int q;

  for(int j=0;j<n;j++)
  {
    q=-INFINITY;
    bool cut_or_not=false;
    for(int i=0;i<j;i++)
    {
      if(q<=p[i]+res[j-i].result-cost)
      {
        q=p[i]+res[j-i].result-cost;
        res[j+1].solution=i+1;
        cut_or_not=true;
      }
    }

    //每一次循环，j=0----j=n-1，表示问题的规模从1---n
    //每一个规模，cut_or_not都初始化为false，最后看是否切割？
    //如果发生了切割，在i的循环中，也就是j的子问题中
    //让cut_or_not=true，最后判断是否切割？

    if(j==i)
    {
      if(q<=p[i]+res[j-i].result && cut_or_not==false)
      {
        res[j+1].solution=i+1;
      }
    }

    //求解完毕
    res[j+1].result=q;
  }

  return res+n;
}

void PRINT_CUT_ROD_SOLUTION(int p[], int n)
{
  rod_cost *res=EXTENDED_BOTTOM_UP_CUT_ROD(p,n);
  while(n)
  {
    cout<<(*res).solution<<" "；
    n=n-(*res).solution;
    res=res-(*res).solution;
  }
}

void main()
{
  const int n=10;
  int p[10]={1,5,8,9,10,17,17,20,24,30};
  cout<<(*EXTENDED_BOTTOM_UP_CUT_ROD(p,10)).result<<endl;
  PRINT_CUT_ROD_SOLUTION(p,10);
}
