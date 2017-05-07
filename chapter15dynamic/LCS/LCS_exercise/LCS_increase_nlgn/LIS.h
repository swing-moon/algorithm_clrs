#include <iostream>
#include <vector>
#include <stdlib.h>
#include "bisearch.h"

#define N 9

int B[N];
int len; //用来标注数组B中元素的个数

struct node
{
    int data;
    int prev;  //存放上一个prev的下标
};

int LIS(int *array,node *result,int n)
{
    int len=1;  //B[]数组的长度
    B[0]=array[0];
    int i,pos=0;

    result[0].data=B[0];
    result[0].prev=-1;

    for(int i=1;i<n;i++)  //为什么下标从1开始？
    //[i]要和[i-1]比较，然后执行替换，原来array[0]作为初始值
    {
        if(array[i]>B[len-1])
        {
            B[len]=array[i];
            result[len].data=array[i];
            result[len].prev=len-1;
            len++;
        }
        else
        {
            int pos=bisearch(B,len,array[i]);
            B[pos]=array[i];
            result[pos+1].prev=pos;
        }
    }

    return len;
}
//这里，result提供用于回溯的另一组数值