#include<stdio.h>
#include<stdlib.h>

#define MAX 1000

//Todo
//��Ҫ����һ�����飬����Ԫ����ԭʼ����������k����
//ע�ⰴ�մ�С�����˳������
//�����������������������,���Ը���ʵ����Ҫ�޸ĺ�������
void HalfInsertionSort(int *a, int n){
    int left, right;
    int i;
    for(i = 1; i < n; i++) //n��ʾ���ݵĸ���,i��ʾ�������
    {
        //��ʾ��������
        left = 0;
        right = i - 1;
        int temp = a[i]; //��������Ԫ���ݴ�
        while(left <= right)
        {
            int middle = (left + right) / 2;
            if(temp < a[middle])
                right = middle - 1;
            else
                left = middle + 1;
        }
        int j;
        for(j = i - 1; j >= left; j--) //�Ӻ���ǰ˳���滻
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
	int caseNum; //��ʾ��������
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
