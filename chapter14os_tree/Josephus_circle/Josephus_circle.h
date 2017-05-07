#include "delete.h"
#include "succ_and_other.h"

void Josephus_imple(os_tree *T, int m, int n)
{
  os_node *x=T->root;
  int k=0, i=n;
  int t=1;

  while(T->root!=T->nil && i>0)
  {
    k=(t+m-1)%i;
    //k就是我们需要删除的点，注意到我们对一个点执行删除之后
    //这个点原来的下标是k，删除了之后k+1就自动补到k的位置上
    //这样新的k重新编号的话就是1，相当于原来的t=1
    if(k==0)
      k=i;
    os_node *del=os_select(T,k);
    //这里del表示要删除的结点
    cout<<del->key<<" ";
    //输出节点

    RB_delete(del);

    t=k;
    i--;
  }
}
