
#define RED 0
#define BLACK 1
#define INFINITY 345879790

struct RB_node
{
  RB_node *left;  //左孩子
  RB_node *right; //右孩子
  RB_node *parent; //父节点
  int color;   //结点的颜色
  int key;

  RB_node(RB_node* init,int c_init,int num):
  left(init),right(init),parent(init),color(c_init),key(num){}
};
struct RB_tree
{
  RB_node *root;
  RB_node *nil;
  RB_tree()
  {
    nil=new RB_node(NULL,BLACK,INFINITY);   //树的哨兵必然为黑色
    root=nil;
  }
};
