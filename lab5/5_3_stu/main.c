#include <stdio.h>
#include <stdlib.h>


//����ʼʱ������ֹʱ��������򣬲�����������д
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

void sort(int *start, int *end, int *time_period, int *result, int *e, int M){
    //�ֱ�����
    QuickSort(start, 0, M-1);
    QuickSort(end, 0, M-1);
    int combine[2*M];
    int i, j, k, temp, lenth;
    //�ϲ�
    for(i = 0; i < M; i++)
        combine[i] = start[i];
    for(i = M; i < 2*M; i++)
        combine[i] = end[i-M];
    //�鲢����
    mergesort(combine, 0, 2*M-1);

    //ȥ��
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

    //����ǰ׺ֵ
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
            if(time_period[k] == tmp1) //start������Ȩֵ��1
            {
                ava[k]++;
                break;
            }
        }
        for(k = 0; k < lenth; k++)
        {
            if(time_period[k] == tmp2) //end������Ȩֵ��1
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

    //����ÿ��ʱ���ѧ����
    for(i = 0; i < lenth; i++)
    {
        if(i == 0)
            result[i] = ava[i];
        else
            result[i] = ava[i] + result[i-1];
    }
}

//�����������������ʼʱ�����ֹʱ�䣬������������д
void findPeriod(int *start,int *end, int *time_period, int *result, int *e, int M, int N){
    int max[*e];
    int i, j, max_res;
    max_res = result[0];
    //�ҵ�������������ʱ��Σ��洢������max��
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

    //��ӡ���
    for(i = 0; i < j; i++)
    {
        printf("%d %d,",time_period[max[i]],time_period[max[i]]);
    }
    printf("\b \n");
}

int main()
{
   int N, M; //�ֱ�洢ʱ��Ķ�����ѧ���ĸ���
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

   /* �ն�����
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

