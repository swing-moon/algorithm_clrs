#include "os_tree.h"
#include "rotate.h"
#include "succ_and_other.h"

//删除调整，这个时候x有两重黑色
void RB_delete_fixup(os_tree *T, os_node *x)
{
  os_node *w=T->nil;
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
        w->color=RED;
        x=x->parent;      //x和w的黑色沿树上升，注意到x有双重黑色，所以x的颜色不变
      }                  //变得是w，x->parent的颜色
      else
      {
        if(w->right->color==BLACK)
        {
          w->left->color=BLACK;
          w->color=RED;         //同样，内节点变为外节点
          right_rotate(T,w);
          w=x->parent->right;
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
        w->color=RED;
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

void transplant(os_tree *T, os_node *u, os_node *v)
{
  if(u->parent==T->nil)
    T->root=v;
  else if(u==u->parent->left)
    u->parent->left=v;
  else u->parent->right=v;

  if(v!=T->nil)
    v->parent=u->parent;
}

void RB_delete(os_tree *T, os_node *z)
{
  os_node *y=z, *x;
  int y_original_color=y->color;
  os_node *par=z->parent;  //par作为被删除节点的双亲

  if(z->left==T->nil)
  {
    //删除一个节点的时候，size会发生变化
    while(par!=T->nil)
    {
      //删除节点后，z的双亲的size值会减小
      par->size--;
      par=par->parent;  //自底向上遍历，所有的节点的size都减小
    }
    x=z->right;
    transplant(T,z,z->right);
  }
  else if(z->right==T->nil)
  {
    while(par!=T->nil)
    {
      //删除节点后，z的双亲的size值会减小
      par->size--;
      par=par->parent;  //自底向上遍历，所有的节点的size都减小
    }
    x=z->left;
    transplant(T,z,z->left);
  }
  else
  {
    y=tree_minimum(T,z->right);   //这里是查找z的后继，为y，用y来代替z的位置
    y_original_color=y->color;
    os_node *par=y->parent;
    //这里用y嫁接到z处，原先y位置往上所有的节点相当于
    //少了一个y结点，所以par往上遍历的过程中所有的size都为size--

    //特别地，当用y来代替z的时候，并不是y->size=z->size
    //因为子树中少了一个y，所以size-1

    //特别注意，实际上，从y结点到z节点之间的节点，少了一个y
    //从z节点往上，少了一个z，由于size结点是不包括当前节点的
    //所以y->size=z->size-1

    /*y->size=z->size-1;
    while(par!=T->nil)
    {
      //删除节点后，z的双亲的size值会减小
      par->size--;
      par=par->parent;  //自底向上遍历，所有的节点的size都减小
    }*/
    //还有一种方法：完成transplant之后自底向上调整！
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

    //这里进行size属性的维护

    while(par!=T->nil)
    {
      //删除节点后，z的双亲的size值会减小
      par->size--;
      par=par->parent;  //自底向上遍历，所有的节点的size都减小
    }

  }

  if(y_original_color==BLACK)
     RB_delete_fixup(T,x);   //x为y的孩子结点，y的删除会影响x的相关性质
}
