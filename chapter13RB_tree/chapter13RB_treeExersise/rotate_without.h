#include "RB_tree_without.h"

void left_rotate(RB_tree *T,RB_node *x)
{
  RB_node *par=T->nil, *p_par=T->nil;
  RB_node *y=x->right;  //左孩子结点
  x->right=y->left;
  //这一部处理的是加在x，y之间的“内结点”，y->left原先
  //夹在x->left和y->right之间，旋转之后子树的相对顺序不变，最外边的结点是
  //x->left和y->right，注意是围绕x和y进行的旋转，所以子树的相对位置保持不变

  tree_search(T,T->root,x->key,par,p_par);

  /*if(y!=NULL && y->left!=NULL)
    y->left->parent=x;
  //旋转之后需要重新更新parent结点信息

  y->parent=x->parent;  //这个时候y作为子树的根了，y要连到祖先中！*/

  if(par==NULL)
    T->root=y;
  else if(par->left==x)
     par->left=y;
  else
     par->right=y;

   //保证x与祖先结点相连接

   //最后处理x和y的关系
   y->left=x;
}

//右旋，对称的代码
void right_rotate(RB_tree *T,RB_node *x)
{

   RB_node *par=T->nil, *p_par=T->nil;
  //只需要把上述代码的相对位置，right和left互换就可以了
   RB_node *y=x->left;
   x->left=y->right;

  /* if(y!=NULL && y->right!=NULL)
     y->right->parent=x;
   //旋转之后需要重新更新parent结点信息

   y->parent=x->parent;*/

   tree_search(T,T->root,x->key,par,p_par);
   if(par==NULL)
     T->root=y;
   else if(par->left==x)
      par->left=y;
   else
      par->right=y;

    //保证x与祖先结点相连接

    //最后处理x和y的关系
    y->right=x;
}
