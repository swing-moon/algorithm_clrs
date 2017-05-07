#include "CSTree.h"


int max(int a,int b)
{
    return a>b?a:b;
}

int confirm(CSTree &T,int flag)
{
    int result;
    if(T->status!=-1)
        return T->status;
    if(flag==1)
    {
        result=T->data;
        for(CSTree p=T->firstChild;p!=NULL;p=p->nextsibling)
        {
            result+=confirm(p,0);
        }
        T->status=result;
        return result;
    }
    else
    {
        result=0;
        int maxnum;
        for(CSTree p=T->firstChild;p;p=p->nextsibling)
        {
            maxnum=confirm(p,0);
            refresh_tree(p);    //注意在求max的时候，洗刷status的值
            maxnum=max(maxnum,confirm(p,1));
            result+=maxnum;
        }
        T->status=result;
        return result;
    }
}

int main()
{
    CSTree T;
    CreateTree(T);

    cout<<"Level order Traverse: "<<endl;
    LevelOrderTraverse(T);
    cout<<endl;
    recurse_Traverse(T);
    cout<<endl;

    int result=confirm(T,1);
    cout<<result<<endl;
    refresh_tree(T);
    cout<<endl;
    result=max(result,confirm(T,0));
    cout<<result;
    cout<<endl;

    cout<<"recurse mathod:"<<endl;

    CSTree Recur_T;
    int root_data;
    Recur_T=new CSNode;
    Recur_T->status=-1;
    cout<<"Input the data of root : "<<endl;
    cin>>root_data;
    Recur_T->data=root_data;

    recurse_createtree(Recur_T);
    cout<<"Level order Traverse: "<<endl;
    LevelOrderTraverse(Recur_T);
    cout<<endl;
    depth_traverse(Recur_T);
    cout<<endl;
}