#include "company_party_array.h"
#include <string.h>

using namespace std;

int main()
{

    //Initialize:对数组的值进行初始化
    for(int i=0;i<MAXNUM;i++)
    {
        for(int j=0;j<2;j++)
            solution[i][j]=-1;
    }
    cout<<"Input the number of members who join the party: "<<endl;
    cin>>how_many_member;

    cout<<"Input the like value of members: "<<endl;
    for(int i=0;i<how_many_member;i++)
        cin>>likevalue[i];
    

    
    for(int i=0;i<how_many_member;i++)
    {
        cout<<"Input member id and how many branch it has: "<<endl;
        cin>>id>>how_many_branch; //输入每个人的编号和下属的个数
        cout<<"branch id: "<<endl;
        for(int j=0;j<how_many_branch;j++)
        {
            cin>>branch_id;  //输入下属员工的id
            party_graph[id][branch_id]=true;
        }
    }
    //初始化完成
    int root=0;
    int result=confirm(root,0);
    memset(solution,-1,sizeof(solution));
    //注意使用这种方法，对数组中的值进行赋值

    result=max(result,confirm(root,1));
    cout<<result<<endl;
    return 0;
}
