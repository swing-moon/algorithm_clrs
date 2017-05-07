#include <iostream>

//使用二分查找寻找合适的位置
//要插入的位置，是比该数大的第一个数值
int bisearch(int *b,int len,int w)
{
    int left=0,right=len-1;
    int mid;

    while(left<=right)
    {
        mid=left+(right-mid)/2;
        if(b[mid]>w)
          right=mid-1;
        else if(b[mid]<w)
          left=mid+1;
        else return mid;
    }
    return left;
}

//二分查找最后返回的值，是b[mid+1]
//当然，如果找不到该值，最后返回的是b[0+1]，或者是b[len+1]