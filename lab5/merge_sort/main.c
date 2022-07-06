#include <stdio.h>
#include <stdlib.h>

void merge(int *a, int left, int right, int middle){
    int b[right-left+1], i, j, k;
    for(k = left; k <= right; k++) //b为辅助数组，其元素和a中初始元素相同
        b[k-left] = a[k];
    i = left; //位置指针i初始指向left
    j = middle + 1; //位置指针j初始指向middle+1
    for(k = left; k <= right; k++) //遍历a中下标从left到right的元素，排序a的元素值
    {
        if(i > middle) //如果位置指针i超过middle，则将middle右边部分剩余元素直接赋值到a中
        {
            a[k] = b[j-left];
            j++;
        }
        else if(j > right) //如果位置指针j超过right，则将middle左边部分剩余元素直接赋值到a中
        {
            a[k] = b[i-left];
            i++;
        }
        else if(b[i-left] > b[j-left]) //如果位置指针i所指向的值大于位置指针j所指向的值，则将j所指向的值赋值到a中对应位置
        {
            a[k] = b[j-left];
            j++;
        }
        else //如果位置指针i所指向的值小于位置指针j所指向的值，则将i所指向的值赋值到a中对应位置
        {
            a[k] = b[i-left];
            i++;
        }
    }
}
void mergesort(int *a, int left, int right){
    if(left >= right)
        return ;
    int middle = (left + right) / 2;
    mergesort(a, left, middle);    //左边排序
    mergesort(a, middle+1, right); //右边排序
    merge(a, left, right, middle); //合并排序
}

int main(void)
{
    int a[100], n, i;
    scanf("%d",&n);
    if(n <= 100 && n > 0)
    {
        for(i = 0; i < n; i++)
            scanf("%d",&a[i]);
        mergesort(a, 0, n-1);
        for(i = 0; i < n; i++)
            printf("%d ",a[i]);
    }
    else
        printf("Wrong input! Please input a number between 0 and 100!");
    return 0;
}
