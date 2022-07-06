#include <stdio.h>
#include <stdlib.h>
#define N 10000

int a[N]; // 用于存储奶牛产奶量

//Todo
//需要返回中位数奶牛产奶量。
//可以自行添加其他辅助函数,可以修改传参的数量
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
void QuickSort(int *a, int low, int high)
{
    if (low < high)
    {
        int q = Partition(a, low, high);
        QuickSort(a, low, q - 1);
        QuickSort(a, q + 1, high);
    }
}

int solve1(int *a, int n){
    return a[n/2];
}

void test1(){
    int caseNum; //表示测试轮数
    int n, i, case1;
    int ans[N];
    if (freopen("5_1_input_5.in", "r", stdin) == NULL) {
		printf("There is an error in reading file 5_1_input_5.in");
    }
    scanf("%d", &caseNum);
    for (case1 = 0; case1 < caseNum; case1++) {
        printf("==== Case %d ====\n", case1 + 1);
        scanf("%d", &n);
        for (i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        QuickSort(a, 0, n - 1);
        ans[case1] = solve1(a, n);
        printf("ans is:%d\n", ans[case1]);
        printf("\n");
    }
    fclose(stdin);
}

int main() {
    test1();
    return 0;
}
