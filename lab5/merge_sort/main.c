#include <stdio.h>
#include <stdlib.h>

void merge(int *a, int left, int right, int middle){
    int b[right-left+1], i, j, k;
    for(k = left; k <= right; k++) //bΪ�������飬��Ԫ�غ�a�г�ʼԪ����ͬ
        b[k-left] = a[k];
    i = left; //λ��ָ��i��ʼָ��left
    j = middle + 1; //λ��ָ��j��ʼָ��middle+1
    for(k = left; k <= right; k++) //����a���±��left��right��Ԫ�أ�����a��Ԫ��ֵ
    {
        if(i > middle) //���λ��ָ��i����middle����middle�ұ߲���ʣ��Ԫ��ֱ�Ӹ�ֵ��a��
        {
            a[k] = b[j-left];
            j++;
        }
        else if(j > right) //���λ��ָ��j����right����middle��߲���ʣ��Ԫ��ֱ�Ӹ�ֵ��a��
        {
            a[k] = b[i-left];
            i++;
        }
        else if(b[i-left] > b[j-left]) //���λ��ָ��i��ָ���ֵ����λ��ָ��j��ָ���ֵ����j��ָ���ֵ��ֵ��a�ж�Ӧλ��
        {
            a[k] = b[j-left];
            j++;
        }
        else //���λ��ָ��i��ָ���ֵС��λ��ָ��j��ָ���ֵ����i��ָ���ֵ��ֵ��a�ж�Ӧλ��
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
    mergesort(a, left, middle);    //�������
    mergesort(a, middle+1, right); //�ұ�����
    merge(a, left, right, middle); //�ϲ�����
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
