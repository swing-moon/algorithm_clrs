#include "RB_tree.h"
#include "rotate.h"

//删除调整，这个时候x有两重黑色
void RB_delete_fixup(RB_tree *T, RB_node *x)
{
  RB_node *w=NULL;
  while (x!=T->root && x->color==BLACK)
  {
    if(x==x->parent->left)
    {
      w=x->parent->right;   //w为x的兄弟结点
      if(w->color==RED)
      {
        w->color=BLACK;    //将这种情况划归为下面一种情况
        w->parent->color=RED;
        left_rotate(T,x->parent);
        w=x->parent->right;
      }
      if(w->left->color==BLACK && w->right->color==BLACK)
      {
        W->color=RED;
        x=x->parent;      //x和w的黑色沿树上升，注意到x有双重黑色，所以x的颜色不变
      }                  //变得是w，x->parent的颜色
      else
      {
        if(w->right->color==BLACK)
        {
          w->left->color=BLACK;
          w->color=RED;         //同样，内节点变为外节点
          right_rotate(T,w);
          w=x->parent-?right;
        }
        w->color=x->parent->color;   //这里x->parent的颜色不确定，但是w的颜色是黑色
        //x有双重黑色，通过改变颜色加上旋转，可以将双重黑色表现在图中，这样完成了红黑树的局部平衡
        x->parent->color=BLACK;
        w->right->color=BLACK;
        left_rotate(T,x->parent);
        //红黑树局部平衡了
        x=T->root;
      }
    }

    else
    {
      w=x->parent->left;
      if(w->color==RED)
      {
        w->color=BLACK;
        x->parent->color=RED;
        right_rotate(T,x->parent);
        w=x->parent->left;
      }
    }
    if(w->left->color==BLACK && w->right->color==BLACK)
    {
      w->color=RED;
      x=x->parent;
    }
    else
    {
      if(w->left->color==BLACK)
      {
        w->right->color=BLACK;
        W->color=RED;
        left_rotate(T,w);
        w=x->parent->left;
      }
      w->color=x->parent->color;
      x->parent->color=BLACK;
      w->left->color=BLACK;
      right_rotate(T,x->parent);

      x=T->root;
    }
  }

  x->color=BLACK;
}

void transplant(RB_tree *T, RB_node *u, RB_node *v)
{
  if(u->parent==T->nil)
    T->root=v;
  else if(u==u->parent->left)
    u->parent->left=v;
  else u->parent->right=v;

  if(v!=NULL)
    v->parent=u->parent;
}

RB_node *tree_minimum(RB_tree *T,RB_node *x)
{
  while (x->left!=NULL) {
    x=x->left;
  }

  return x;
}

void RB_delete(RB_tree *T, RB_node *z)
{
  RB_node *y=z, *x;
  int y_original_color=y->color;

  if(z->left==NULL)
  {
    x=z->right;
    transplant(T,z,z->right);
  }
  else if(z->right==NULL)
  {
    x=z->left;
    transplant(T,z,z->left);
  }
  else
  {
    y=tree_minimum(T,z->right);   //这里是查找z的后继，为y，用y来代替z的位置
    y_original_color=y->color;
    x=y->right;

    if(y->parent==z)
    {
      x->parent=y;
    }
    else
    {
      transplant(T,y,y->right);
      y->right=z->right;
      y->right->parent=y;
    }

    transplant(T,z,y);
    y->left=z->left;
    y->left->parent=y;
    y->color=z->color;
  }

  if(y_original_color==BLACK)
     RB_delete_fixup(T,x);   //x为y的孩子结点，y的删除会影响x的相关性质
}
