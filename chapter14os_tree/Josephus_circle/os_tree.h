#define RED 0
#define BLACK 1
#define NIL -1
#define LEN sizeof(struct os_node)
#define LENTREE sizeof(struct os_tree)

struct os_node
{
  os_node *left;
  os_node *right;
  os_node *parent;
  int key;
  int color;
  int size;  //用于顺序统计量

  os_node(os_node *init,int num)
  :left(init),right(init),parent(init),key(num),color(RED),size(0){}

};

struct os_tree
{
  os_node *root;
  os_node *nil;
  os_tree()
  {
    nil=new os_node(NULL,NIL);
    root=nil;
  }
};
