##不带父节点指针的红黑树实现#

该算法提供不带父节点指针的红黑树的实现，实现的思路就是定义一个tree_search函数，让初始指针从树根开始往下遍历，接下来把z->parent替换成tree_search(T,T->root,x->key,par,p_par);
即可。


**主要实现函数**
```bash
#define RED 0
#define BLACK 1
#define INFINITY 345879790

struct RB_node
{
  RB_node *left;  //左孩子
  RB_node *right; //右孩子
  //RB_node *parent; //父节点
  int color;   //结点的颜色
  int key;

  RB_node(RB_node* init,int c_init,int num):left(init),right(init),color(c_init),key(num){}
};
struct RB_tree
{
  RB_tree *root;
  RB_tree *nil;
  RB_tree()
  {
    nil=new RB_node(NULL,BLACK,INFINITY);   //树的哨兵必然为黑色
    root=nil;
  }
};

RB_node *tree_search(RB_tree *T, RB_node *x, int k, RB_node *par, RB_node *p_par)
{
  //人为定义一个tree_search函数，从根节点遍历，寻找x的parent和parent->parent
  while(x!=T->nil && k!=x->key)
  {
    par=x;
    if(k<x->key)
      x=x->left;
    else x=x->right;
    if(k!=x->key)     //如果没有找到待查找的值，此时x=x->child
    {                 //记录下遍历前的x=p_par，遍历后的x=par，返回x，此时用par和p_par表示
      p_par=par;
      par=x;
    }
  }
  return x；
}
/*void RB_insert_fixup(RB_tree *T, RB_node *z)
{
  //相关代码
  RB_node *par=T->nil, *p_par=T->nil;
  tree_search(T,T->root,z->key,par,p_par);
  //将原来的z->parent用par代替，z->parent->parent用p_par代替
}*/

```
