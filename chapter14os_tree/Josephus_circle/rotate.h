#include "os_tree.h"

void left_rotate(os_tree *T,os_node *x)
{
  os_node *y=x->right;  //左孩子结点
  x->right=y->left;
  //这一部处理的是加在x，y之间的“内结点”，y->left原先
  //夹在x->left和y->right之间，旋转之后子树的相对顺序不变，最外边的结点是
  //x->left和y->right，注意是围绕x和y进行的旋转，所以子树的相对位置保持不变

  if(y!=T->nil && y->left!=T->nil)
    y->left->parent=x;
  //旋转之后需要重新更新parent结点信息

  y->parent=x->parent;  //这个时候y作为子树的根了，y要连到祖先中！
  if(x->parent==T->nil)
    T->root=y;
  else if(x->parent->left==x)
     x->parent->left=y;
  else
      x->parent->right=y;

   //保证x与祖先结点相连接

   //最后处理x和y的关系
   y->left=x;
   x->parent=y;

   //顺序统计树新增部分
   y->size=x->size;
   //旋转之后，y代替原来x的位置，而x的位置在树的高处
   //直接将原来x的size值赋值给y就可以了
   x->size=x->left->size+x->right->size+1;
}

//右旋，对称的代码
void right_rotate(os_tree *T,os_node *x)
{

  //只需要把上述代码的相对位置，right和left互换就可以了
   os_node *y=x->left;
   x->left=y->right;

   if(y!=T->nil && y->right!=T->nil)
     y->right->parent=x;
   //旋转之后需要重新更新parent结点信息

   y->parent=x->parent;
   if(x->parent==T->nil)
     T->root=y;
   else if(x->parent->left==x)
      x->parent->left=y;
   else
       x->parent->right=y;

    //保证x与祖先结点相连接

    //最后处理x和y的关系
    y->right=x;
    x->parent=y;

    y->size=x->size;
    x->size=x>left->size+x->right->size;
}
