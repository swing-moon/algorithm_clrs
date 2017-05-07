#include <iostream>
using namespace std;

int main()
{
  int N;
  int M;
  cin>>N;
  cin>>M;
  int result=0;
  for(int i=2; i<=N;i++)
    result=(result+M)%i;
   //值得注意的是，这里的i表示规模，递推关系
   //表示从i递推到i-1，问题规模数组大小
   //最小就为1，所以i的初值为2
  std::cout << "最后输出的元素是" <<result+1<<endl;
  return 0;
}
