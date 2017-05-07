#include <iostream>
using namespace std;
#define INFINITY 0x7fffffff

struct rod
{
  int result;   //代表最大收益
  int solution;  //代表切割方案
};

rod *EXTENDED_BOTTOM_UP_CUT_ROD(int p[], int n)
{
  rod *res=new rod[n];
  res[0].result=0;  //初始化，钢条规模为0，收益为0
  int q;
  for(int j=0;j<n;j++)
  {
    q=-INFINITY;
    for(int i=0;i<=j;i++)
    {
      if(q<p[i]+res[j-i].result)
      {
        q=p[i]+res[j-i].result;
        res[j+1].solution=i+1;  //保存切割方式
      }        //这里的i表示切割下来的片段，规模有多大？
    }
    //此时已经完成了从1---j的循环
    res[j+1].result=q;
  }
  return res+n;  //注意：这里res表示指向第一个元素的指针
}
//res+n表示指针移动n位，新的指针指向n之后的那个位置
//rod *res=new rod[n] res[i].result  (res+i)->result
//两种用法注意区分

//特别注意：这里res[0].result=0  最后res[j+1].result
//res[j+1].solution，意味这res[]的存储范围如下：
//res[1]，res[2],......,res[n]
//res初始指针位置为res[0]，res末指针的位置为res[n]

void PRINT_CUT_ROD_SOLUTION(int p[], int n)
{
  rod *res=EXTENDED_BOTTOM_UP_CUT_ROD(p,n);
  //注意这里函数的返回值为res+n，即最后一个数组元素的地址
  while(n>0)
  {
    cout<<(*res).solution<<" ";
    n=n-(*res).solution;
    //注意返回的res指的是res[n]的位置
    //返回的是规模为n时候的切割方法,从最大规模往最小规模输出
    //这里从大规模往小规模输出，指针也要调整
    //从规模为n的位置逐渐减小到i，再逐渐减小到1，0
    res=res-(*res).solution;

  }
}

void main()
{
  const int n=10;
  int p[10]={1,5,8,9,10,17,17,20,24,30};
  cout<<(*EXTENDED_BOTTOM_UP_CUT_ROD(p,4)).result<<endl;
  PRINT_CUT_ROD_SOLUTION(p,4);
}
