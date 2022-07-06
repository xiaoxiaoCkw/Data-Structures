#include <stdio.h>
#include <stdlib.h>


//对起始时间与终止时间进行排序，参数可自行填写
int Partition(int *a, int low, int high){
    int x = a[high]; //将输入数组的最后一个数作为主元，用它来对数组进行划分
    int i = low - 1; //i是最后一个小于主元的数的下标
    int j;
    for(j = low; j < high; j++) //遍历下标由low到high-1的数
    {
        if(a[j] < x) //如果数小于主元的话就将i向前挪动一个位置，并且交换j和i所分别指向的数
        {
            int temp;
            i++;
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    //经历上面的循环之后下标为从low到i（包括i）的数就均为小于x的数了，现在将主元和i+1位置上面的数进行交换
    a[high] = a[i+1];
    a[i+1] = x;
    return i+1;
}
void QuickSort(int *a, int low, int high){

    if (low < high)
    {
        int q = Partition(a, low, high);
        QuickSort(a, low, q - 1);
        QuickSort(a, q + 1, high);
    }
}

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

void sort(int *start, int *end, int *time_period, int *result, int *e, int M){
    //分别排序
    QuickSort(start, 0, M-1);
    QuickSort(end, 0, M-1);
    int combine[2*M];
    int i, j, k, temp, lenth;
    //合并
    for(i = 0; i < M; i++)
        combine[i] = start[i];
    for(i = M; i < 2*M; i++)
        combine[i] = end[i-M];
    //归并排序
    mergesort(combine, 0, 2*M-1);

    //去重
    time_period[0] = combine[0];
    temp = combine[0];
    j = 1;
    for(i = 1; i < 2*M; i++)
    {
        if(combine[i] == temp)
            continue;
        else
        {
            time_period[j] = combine[i];
            temp = combine[i];
            j++;
        }
    }
    lenth = j;
    *e = lenth;

    //计算前缀值
    int ava[lenth];
    for(i = 0; i < lenth; i++)
        ava[i] = 0;
    for(i = 0; i < M; i++)
    {
        int tmp1, tmp2;
        tmp1 = start[i];
        tmp2 = end[i];
        for(k = 0; k < lenth; k++)
        {
            if(time_period[k] == tmp1) //start中有则权值加1
            {
                ava[k]++;
                break;
            }
        }
        for(k = 0; k < lenth; k++)
        {
            if(time_period[k] == tmp2) //end中有则权值减1
            {
                if(k != lenth - 1)
                {
                    ava[k+1]--;
                    break;
                }
                else
                {
                    ava[k]--;
                    break;
                }
            }
        }
    }

    //计算每个时间段学生数
    for(i = 0; i < lenth; i++)
    {
        if(i == 0)
            result[i] = ava[i];
        else
            result[i] = ava[i] + result[i-1];
    }
}

//计算空闲人数最多的起始时间和终止时间，参数可自行填写
void findPeriod(int *start,int *end, int *time_period, int *result, int *e, int M, int N){
    int max[*e];
    int i, j, max_res;
    max_res = result[0];
    //找到空闲人数最多的时间段，存储在数组max中
    for(i = 1; i < *e; i++)
    {
        if(result[i] > max_res)
            max_res = result[i];
    }
    j = 0;
    for(i = 0; i < *e; i++)
    {
        if(result[i] == max_res)
        {
            max[j] = i;
            j++;
        }
    }

    //打印结果
    for(i = 0; i < j; i++)
    {
        printf("%d %d,",time_period[max[i]],time_period[max[i]]);
    }
    printf("\b \n");
}

int main()
{
   int N, M; //分别存储时间的段数和学生的个数
   int caseNum = 0;
   int start[1002];
   int end[1002];
   int i;

   if (freopen("5_3_input.in", "r", stdin) == NULL) {
		printf("There is an error in reading file 5_3_input.in");
    }

   while(scanf("%d %d",&N,&M)!=EOF){
       caseNum++;
       int time_period[2*M], result[M], start1[1002], end1[1002];
       int e;
       printf("==== Case %d ====\n",caseNum);
       for(i = 0; i < M; i++){
           scanf("%d %d",&start[i],&end[i]);
       }
       for(i = 0; i < M; i++){
           start1[i] = start[i];
           end1[i] = end[i];
       }
       sort(start1, end1, time_period, result, &e, M);
       findPeriod(start, end, time_period, result, &e, M, N);
   }
   fclose(stdin);

   /* 终端输入
   while(scanf("%d %d",&N,&M)!=EOF){
       caseNum++;
       printf("==== Case %d ====\n",caseNum);
       for(int i = 0; i < M;i++){
           scanf("%d %d",&start[i],&end[i]);
       }
       sort(start, end, M);
       findPeriod(start, end, M, N);
   }
   */
}

