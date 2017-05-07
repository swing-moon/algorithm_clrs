#include "os_tree.h"

os_node *tree_maxinum(os_tree *T, os_node *x)
{
  while(x!=T->nil && x->right!=T->nil)
    x=x->right;
  return x;
}


os_node *tree_minimum(os_tree *T,os_node *x)
{
  while (x->left!=T->nil) {
    x=x->left;
  }

  return x;
}


os_node *tree_successor(os_tree *T, os_node *x)
{
  if(x->right!=T->nil)
  {
    return tree_minimum(x->right);
  }
  os_node *y=x->parent;  //后继在根节点处
  while(y!=T->nil && x==y->right)
  {
    x=y;
    y=y->parent;
  }
  return y;
}

os_node *tree_predecessor(os_tree *T, os_node *x)
{
  if(x->left!=T->nil)
  {
    return tree_maxinum(x->left);
  }
  os_node *y=x->parent;
  while(y!=T->nil && x==y->left)
  {
    x=y;
    y=y->parent;
  }
  return y;
}

os_node *Iterative_tree_search(os_tree *T,os_node *x, int k)
{
  while(x!=T->nil && k!=x->key)
  {
    if(k<x->key)
      x=x->left;
    else x=x->right;
  }
  return x;
}

void in_order_traverse(os_tree *T, os_node *p)
{
  if(p!=T->nil)
  {
    in_order_traverse(p->left);
    cout<<p->key<<" "<<p->color<<" "<<p->size<<endl;
    in_order_traverse(p->right);
  }
}
os_node *os_select_rank(os_tree *T, os_node *x, int i)
{
  int r=x->left->size+1;
  if(i==r)
    return x;
  else if(i<r)
     return os_select_rank(T,x->left,i);
  else return os_select_rank(T,x->right,i-r);
}

int Interative_os_rank(os_tree *T,os_node *x)
//确定x这个节点的顺序统计树的rank
{
  int r=x->left->size+1;
  os_node *y=x;     //沿左脊柱上升，r=x->left->size+1
  while(y!=T->root)   //如果是沿着右脊柱上升？y->size=y->left->size+1+sum{y->parent->size}
  {                  //沿左脊柱上升，r保持不变；一旦拐弯到了右脊柱，要关注y->parent->left->size+1
    if(y==y->parent->right)
      r=r+y->parent->left->size+1;

    y=y->parent;
    //不管是左脊柱还是右脊柱，都要沿树上升
  }

  return r;

}
