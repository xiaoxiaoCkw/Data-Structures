#include<stdio.h>
#include<stdlib.h>

#define MAX 1000

//Todo
//需要返回一个数组，数组元素是原始数组里最大的k个数
//注意按照从小到大的顺序排序
//可以自行添加其他辅助函数,可以根据实际需要修改函数参数
void HalfInsertionSort(int *a, int n){
    int left, right;
    int i;
    for(i = 1; i < n; i++) //n表示数据的个数,i表示插入次数
    {
        //表示左右区间
        left = 0;
        right = i - 1;
        int temp = a[i]; //将待插入元素暂存
        while(left <= right)
        {
            int middle = (left + right) / 2;
            if(temp < a[middle])
                right = middle - 1;
            else
                left = middle + 1;
        }
        int j;
        for(j = i - 1; j >= left; j--) //从后向前顺序替换
            a[j+1] = a[j];
        a[left] = temp;
    }
}
int *solve2(int *arr, int *result, int n, int k){
    HalfInsertionSort(arr, n);
    int i, j;
    j = 0;
    for(i = n - k; i < n ; i++)
    {
        result[j] = arr[i];
        j++;
    }
    return result;
}

void test2(){
	int caseNum; //表示测试轮数
	if (freopen("5_2_input_5.in", "r", stdin) == NULL) {
		printf("There is an error in reading file 5_2_input_5.in");
    }
	scanf("%d", &caseNum);
    int case1 = 0;
    for (; case1 < caseNum; case1++) {
		int k, N;
        scanf("%d%d", &k, &N);
        int arr[MAX];
        int i = 0;
        for (; i < N; i++) {
            scanf("%d", &arr[i]);
        }
        int *res;
        int result[k];
		res = solve2(arr, result, N, k);
		printf("==== Case %d ====\nres : ", case1 + 1);
        for (i = 0; i < k; i++) {
            printf("%d ",res[i]);
        }
        printf("\n");
    }
	fclose(stdin);
}


int main(void) {
    test2();
    return 0;
}
