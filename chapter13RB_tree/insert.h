#include "RB_tree.h"
#include "rotate.h"

void RB_insert_fixup(RB_tree *T, RB_node *z);

void RB_insert(RB_tree *T, RB_node *z)
{
  RB_node *y=NULL;
  //y作为遍历指针的双亲
  RB_node *x=T->root;
  while(x!=NULL)
  {
    y=x;
    if(z->key<x->key)
      x->x->left;
    else x=x->right;
  }

  z->parent=y;
  //y作为遍历指针x的母结点，x遍历寻找合适的插入位置
  if(y==NULL)
    T->root=z;
  else if(z->key<y->key)
    y->left=z;
  else y->right=z;

  z->left=NULL;
  z->right=NULL;
  z->parent=RED;

  RB_insert_fixup(T,z);   //最后插入的结点是红色的，与此同时进行红黑树性质的调整
}

void RB_insert_fixup(RB_tree *T,RB_node *z)
{
  while(z->parent->color==RED)
  {
    if(z->parent==z->parent->parent->left)
    {
      RB_node *y=z->parent->parent->right;  //设置叔结点
      if(y->color==RED)
      {
        z->parent->color=BLACK;   //父节点的黑色可以下放给两个结点
        y->color=BLACK;
        z->parent->parent->color=RED;
        z=z->parent->parent;   //z沿树上升
      }
      else
      {
        if(z==z->parent->right)   //内结点先旋转成外节点
        {
          z=z->parent;
          left_rotate(T,z);
        }
        z->parent->color=BLACK;    //改变颜色之后，z的兄弟结点和z颜色相同
        z->parent->parent->color=RED;  //红黑树局部恢复平衡
        right_rotate(T,z->parent->parent);  //这个技巧是：改变颜色之后，然后旋转，这样不破坏红黑树性质
      }                                     //与此同时，结点沿树上升

    }
    else
    {
      RB_node *y=z->parent->parent->left;
      if(y->color==RED)
      {
        z->parent->color=BLACK;
        y->color=BLACK;
        z->parent->parent->color=RED;
        z=z->parent->parent;
      }
      else
      {
        if(z==z->parent->left)
        {
          z=z->parent;
          right_rotate(T,z);
        }
        z->parent->color=BLACK;
        z->parent->parent->color=RED;
        left_rotate(T,z->parent->parent);
      }
    }
  }

  T->root->color=BLACK;
}
