#include <stdio.h>
#include <stdlib.h>
#define N 10000

int a[N]; // ���ڴ洢��ţ������

//Todo
//��Ҫ������λ����ţ��������
//�����������������������,�����޸Ĵ��ε�����
int Partition(int *a, int low, int high){
    int x = a[high]; //��������������һ������Ϊ��Ԫ����������������л���
    int i = low - 1; //i�����һ��С����Ԫ�������±�
    int j;
    for(j = low; j < high; j++) //�����±���low��high-1����
    {
        if(a[j] < x) //�����С����Ԫ�Ļ��ͽ�i��ǰŲ��һ��λ�ã����ҽ���j��i���ֱ�ָ�����
        {
            int temp;
            i++;
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    //���������ѭ��֮���±�Ϊ��low��i������i�������;�ΪС��x�����ˣ����ڽ���Ԫ��i+1λ������������н���
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
    int caseNum; //��ʾ��������
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
