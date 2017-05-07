#include <iostream>
using namespace std;

int fibonacci(int array[],int n)
{
  if(n>=0)
    array[0]=0;
  if(n>=1)
    array[1]=1;

  for(int i=2;i<n;i++)
  {
    array[i]=array[i-1]+array[i-2];
  }
  return array[n];
}
