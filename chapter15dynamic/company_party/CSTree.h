#include <iostream>
#include <cstdlib>
#include <queue>
#include <string.h>

#define Wrong 'W'

using namespace std;

typedef struct CSNode
{
    int data;
    int status;
    struct CSNode *firstChild;
    struct CSNode *nextsibling;
    struct CSNode *parent;
}CSNode,*CSTree;

int InitTree(CSTree &T)
{
    T=NULL;
    return true;
}

int CreateTree(CSTree &T)
{
    queue<CSTree> helpqueue;
    int buffchild[10]={0};
    int child_num;

    cout<<"Input root of the tree: if empty, enter -1: "<<endl;
    cin>>buffchild[0];

    if(buffchild[0]!=-1)
    {
        T=new CSNode;
        T->status=-1;
        T->data=buffchild[0];
        T->nextsibling=NULL;
        helpqueue.push(T);  //根结点入队，只存储根节点

        while(!helpqueue.empty())
        {
            CSTree temp=helpqueue.front();
            helpqueue.pop();

            cout<<"Input the child number of "<<temp->data<<" if child number is 0, please enter '0'"<<endl;
            cin>>child_num;

            cout<<"Input the child data of "<<temp->data<<" ,if it has no child , enter -1"<<endl;
            for(int i=0;i<child_num;i++)
                cin>>buffchild[i];
            
            if(child_num!=0)
            {
                CSTree child_node=temp->firstChild=new CSNode;
                child_node->status=-1;
                child_node->data=buffchild[0];

                helpqueue.push(child_node);  //第一个孩子入队列

                for(int i=1;i<child_num;i++)
                {
                    child_node->nextsibling=new CSNode;
                    child_node->nextsibling->data=buffchild[i];

                    helpqueue.push(child_node->nextsibling);
                    child_node=child_node->nextsibling; //指向刚刚入队的孩子
                }
                child_node->nextsibling=NULL;
            }
            else
                temp->firstChild=NULL;
        }
    }
    else
        T=NULL;
    return true;
}

void DestroyTree(CSTree &T)
{
    if(T)
    {
        if(T->firstChild)
            DestroyTree(T->firstChild);
        if(T->nextsibling)
            DestroyTree(T->nextsibling);
        free(T);
        T=NULL;
    }
}

void ClearTree(CSTree &T)
{
    DestroyTree(T);
}

bool TreeEmpty(CSTree &T)
{
    if(T)
        return true;
    else
        return false;
}

int TreeDepth(CSTree &T)
{
    if(!T)
        return 0;
    if(!T->firstChild)
        return 1;
    CSTree child_ptr;
    int depth, max=0;

    for(child_ptr=T->firstChild;child_ptr;child_ptr=child_ptr->nextsibling)
    {
        depth=TreeDepth(child_ptr);
        if(depth>max)
            max=depth;
    }
    return max+1;
}

int Root(CSTree &T,int cur_node)
{
    if(T)
        return T->data;
    return 0;
}

CSNode *FindNode(CSTree &T,int cur_node)
{
    queue<CSTree> Q;
    if(T)
    {
        Q.push(T);
        while(!Q.empty())
        {
            CSTree tmp_node=Q.front();
            Q.pop();

            if(tmp_node->data==cur_node)
                return tmp_node;
            if(tmp_node->firstChild)
                Q.push(tmp_node->firstChild);
            if(tmp_node->nextsibling)
                Q.push(tmp_node->nextsibling);
        }
    }
    return NULL;
}

bool Assign(CSTree &T,int cur_node,int value) //进行赋值操作
{
    if(!T)
        return false;
    CSNode *find_cur_node=FindNode(T,cur_node);
    if(!find_cur_node)
        return false;
    find_cur_node->data=value;
    return true;
}

CSNode *parent(CSTree &T,int cur_value)
{
    queue<CSTree> Q;
    if(T)
    {
        if(T->data==cur_value)
            return NULL;
        Q.push(T);
        while(!Q.empty())
        {
            CSTree cur_node=Q.front();
            Q.pop();

            CSTree parent_ptr=cur_node;
            if(cur_node->firstChild)
            {
                if(cur_node->firstChild->data==cur_value)
                    return parent_ptr;
                Q.push(cur_node->firstChild);

                CSTree brotherptr=cur_node->firstChild->nextsibling;
                while(brotherptr)
                {
                    if(brotherptr->data==cur_value)
                        return parent_ptr;
                    Q.push(brotherptr);
                    brotherptr=brotherptr->nextsibling;
                }
            }
        }
    }
    return NULL;
}

int leftchild(CSTree &T,int cur_node)
{
    CSNode *node=FindNode(T,cur_node);
    if(node)
    {
        if(node->firstChild)
            return node->firstChild->data;
    }
    return Wrong;
}

int rightsibling(CSTree &T,int cur_node)
{
    CSNode *node=FindNode(T,cur_node);
    if(node)
    {
        if(node->nextsibling)
            return node->nextsibling->data;
    }
    return Wrong;
}

bool LevelOrderTraverse(CSTree T)
{
    queue<CSTree> Q;

    if(T)
    {
        cout<<T->data<<" ";
        Q.push(T);
        while(!Q.empty())
        {
            CSTree cur_node,child_node;
            cur_node=Q.front();
            Q.pop();

            child_node=cur_node->firstChild;
            while(child_node)
            {
                cout<<child_node->data<<" ";
                Q.push(child_node);
                child_node=child_node->nextsibling;
            }
        }
        return true;
    }
    return false;
}

void recurse_Traverse(CSTree T)
{
    if(T)
    {
        T->status=-1;
        cout<<T->data<<" "<<T->status<<" ";
        recurse_Traverse(T->firstChild);
        recurse_Traverse(T->nextsibling);
    }
}

void refresh_tree(CSTree &T)
{
    if(T)
    {
        T->status=-1;
        refresh_tree(T->firstChild);
        refresh_tree(T->nextsibling);
    }
}

void recurse_createtree(CSTree T)
{
    int child_number;
    cout<<"Input the child number of "<<T->data<<" if it has no child, input 0 "<<endl;
    cin>>child_number;

    if(child_number==0)
    {
        T->firstChild=NULL;
    }
    else
    {
        CSTree child,ptr;
        int child_data;
        child=new CSNode;
        child->status=-1;

        cout<<"Input the data of the child node : "<<endl;
        cin>>child_data;

        child->data=child_data;

        T->firstChild=child;
        ptr=child;

        for(int i=1;i<child_number;i++)
        {
            CSTree brother=new CSNode;
            brother->status=-1;

            int brother_data;

            cout<<"Input the data of the child node: "<<endl;
            cin>>brother_data;
            brother->data=brother_data;

            ptr->nextsibling=brother;
            ptr=ptr->nextsibling;
        }
        ptr->nextsibling=NULL;

        for(CSTree p=T->firstChild;p;p=p->nextsibling)
            recurse_createtree(p);

    }
}


void depth_traverse(CSTree &T)
{
    if(T)
    {
        T->status=-1;
        cout<<T->data<<" "<<T->status<<" ";

        for(CSTree p=T->firstChild;p;p=p->nextsibling)
            depth_traverse(p);
    }
}