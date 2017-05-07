#include <iostream>
using namespace std;

#define n 30
#define m 3
#define LEN sizeof(struct circular_list)
#define LEN_status sizeof(struct circular_list_status)

struct circular_list
{
  int key;  //存储数据
  circular_list *next;
};
struct circular_list_status
{
  int key;
  bool status;  //用来存储该节点的状态，出队没有？
  circular_list_status *next;
  circular_list(int k,circular_list *init):key(k),status(TRUE),next(init){}
};

struct circular_list *tail=NULL;
struct circular_list_status *tail_status=NULL;

circular_list *insert(circular_list *head, int k)
{
  circular_list *z=new circular_list[LEN];
  z->key=k;
  if(head==NULL)
  {
    head=tail=z;
    head->next=tail;  //自循环
  }
  else
  {
    //插入表尾
    tail->next=z;
    z->next=head;
    tail=z;
  }
  return head;
}

circular_list_status *insert_stus(circular_list_status *head,int k)
{
  circular_list_status *z=new circular_list_status[LEN_status];
  z->key=k;
  z->status=TRUE;
  if(head==NULL)
  {
    head=tail=z;
    head->next=tail;  //自循环
  }
  else
  {
    //插入表尾
    tail->next=z;
    z->next=head;
    tail=z;
  }
  return head;
}

circular_list *delete(circular_list *head, circular_list *z)
{
  circular_list *p=head;
  //先是要寻找到z这个结点的位置
  while(p->next!=z)  //要删除的是p->next这个节点
    p=p->next;

  if(head==tail)
    p->next=NULL;
  else
  {
    if(p->next==head)
      head=p->next->next;
    else if(p->next==tail)
      tail=p;
    p->next=p->next->next;
  }

  return p->next;
}

circular_list_status *delete_stus(circular_list_status *head, circular_list_status *z)
{
  circular_list_status *p=head;

  while(p->next!=z)  //要删除的是p->next这个节点
    p=p->next;

  if(head==tail)
    p->next=NULL;
  else
  {
    if(p->next==head)
      head=p->next->next;
    else if(p->next==tail)
      tail=p;
    p->next=p->next->next;
  }

  return p->next;   //返回的值，是更新后的p->next
}

void Josephus_n_m(circular_list_status *head, int n,int m)
{
  struct circular_list_status *p=head;
  //p作为遍历指针
  int count=0;
  while(p && count<=n)
  {
    int i=0;
    while(i!=m-1)
    {
      if(p->status==TRUE)
      {
        p=p->next;
        i++;
      }
      else p=p->next;
    }

    //循环到最后，i报数报M-1
    p->status=false;
    count++;
    p=p->next;
  }
}

void Josephus_link_imple(circular_list *head,int m)
{
  circular_list *p=head;
  while(p)
  {
    int i=0;
    while(i!=m-1)
    {
      p=p->next;
      i++;
    }
    circular_list *z=p;
    cout<<z->key<<" ";
    p=delete(head,z);
  }
}

int main()
{
  int a[n]={0}
  for(int i=0;i<n;i++)
    a[i]=i+1;

  int j=0;
  circular_list *head=NULL;
  while(j!=n)
  {
    head=insert(head,a[j]);
    j++;
  }
  circular_list *p=head;
  do {
    cout<<p->key;
    p=p->next;
    /* code */
  } while(p!=head);
  cout<<endl;
  Josephus_link_imple(head,m);
}
