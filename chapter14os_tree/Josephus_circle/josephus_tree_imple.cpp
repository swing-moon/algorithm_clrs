#include "Josephus_circle.h"
#include <iostream>
#include "time.h"
#include "os_tree.h"
#include "delete.h"
#include "insert.h"
using namespace std;

int main()
{
  srand((unsigned)time(NULL));
  int m=0,n=0;
  cout<<"输入Josephus排列的m和n值"<<endl;
  cout<<"m=";
  cin>>m;
  cout<<"n=";
  cin>>n;

  int *array_jose=new int [n];
  //对数组进行赋值和初始化
  for(int j=0;j<n;j++)
  {
    array_jose[j]=j+1;
    cout<<array_jose[j]<<" ";
  }
  cout<<endl;

  os_node *nilnode=new os_node [LEN];
  os_tree *T=new os_tree [LENTREE];
  os_node *newroot=new os_node [LEN];


  nilnode->key=-1;
  nilnode->color=BLACK;
  T->nil=nilnode;

  int i=0;
  newroot->key=array_jose[i++];
  RB_insert(T,newroot);
  T->root=newroot;
  while(i!=n)
  {
    os_node *z=new os_node[LEN];
    z->key=array_jose[i];
    RB_insert(T,z);
    i++;
  }

  in_order_traverse(T,T->root);
  cout<<"Josephus排列"<<" ";
  Josephus_imple(T,m,n);
}
