#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
    char StuID[11];
    int Grade;
    struct node *next;
}StudentLinkedListNode;


/* �����ཻ���� */
void createCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, int beforeCross1, int beforeCross2){
    // a��b�������ɽ��ֵ��ͬ
    // beforeCross1Ϊ������a�еĸ������ӵ�beforeCross1 + 1����㿪ʼ�ཻ
    // beforeCross2Ϊ������b�еĸ������ӵ�beforeCross2 + 1����㿪ʼ�ཻ
    // �ཻ�����ǽ�b�е�ǰһ���ָ��a�е��׸��ཻ���
    StudentLinkedListNode *p, *q;
    while(beforeCross1--)a=a->next;
    while(--beforeCross2)b=b->next;
    p = b->next;
    b->next = a;
    //����Ұָ����
    while(p){
        q = p->next;
        free(p);
        p = q;
    }
}

void destroyCrossLink(StudentLinkedListNode* a, StudentLinkedListNode* b, StudentLinkedListNode* crossNode){
    StudentLinkedListNode* p = crossNode->next, *q;
    while(p){
        q = p->next;
        free(p);
        p = q;
    }
    while(a != crossNode){
        q = a->next;
        free(a);
        a = q;
    }
    while(b != crossNode){
        q = b->next;
        free(b);
        b = q;
    }
    free(crossNode);
}

/* ��ӡ�����ڵ� */
void printLinkedListNode(StudentLinkedListNode * node){
    printf("{ID:%s, Grade:%d}", node->StuID, node->Grade);
    if(node->next!=NULL){
        printf("->");
    }else{
        printf("\n");
    }

}

/** ����ñ�ĳɼ���� */
void outputStudentLinkedList(StudentLinkedListNode* head){
    // ���ڵ����ڵ�����ĺ���printLinkedListNode���ṩ
    //����ʵ�ֱ���������߼�
	StudentLinkedListNode *p ;
	p = head ;
	while( p->next!=NULL )
    {
        printLinkedListNode( p ) ;
        p = p->next ;
    }
    printLinkedListNode(p) ;
}


/** �½�һ������node������ */
StudentLinkedListNode* studentLinkedListCreate(char student_id[], int grade) {
    //tips:malloc��ʱ��ǵ�Ϊת��Ϊ�ṹ��ָ��
	StudentLinkedListNode *p = (StudentLinkedListNode *)malloc(sizeof(StudentLinkedListNode)) ;
	strcpy( p->StuID , student_id ) ;
	p->Grade = grade ;
	return p ;
}


/** ���ս������ѧ���ĳɼ����,����������ͷָ�� */
StudentLinkedListNode* studentLinkedListAdd(StudentLinkedListNode* head, StudentLinkedListNode* node) {
    //����ͷ�巨
    StudentLinkedListNode *p = head ;
    //������
    node->next = p ;
    p = node ;
    return p ;
}


/** ��ת���� */
StudentLinkedListNode* reverseLinkedList(StudentLinkedListNode*head){
    StudentLinkedListNode *p , *q ;
    p = NULL ;
    //��pΪ����ĩ��NULL�����Ͻ�ԭ������Ľ��ӵ�pǰ��
    while( head->next!=NULL )
    {
        q = head ;
        head = head->next ;
        q->next = p ;
        p = q ;
    }
    head->next = p ;
    return head ;
}

/** �ҵ��ཻ�ĵ�һ����� */
StudentLinkedListNode* findCrossBeginNode(StudentLinkedListNode* class1, StudentLinkedListNode* class2, int beforeCross1 , int beforeCross2) {
    //class1��class2�ں�һ������ȫ�غϣ������ڴ��ַ��ͬ�������ҳ������ؿ�ʼ�ཻ�ĵ�һ����㡣
    //�벻Ҫ�򵥵�ͨ�����ṹ��ĳ�Ա���жϡ�

    //����һ������dif������������Ԫ�ظ����Ĳ�ֵ����������ָ��*p��*q��pָ��class1��qָ��class2����Ԫ�ظ����϶�
    //�������ָ������dif����㣬������һ��ָ�뿪ʼ�ߣ�������ָ����ȣ�����ָ��ĵ�ַ��ͬʱ�����ҵ����ཻ�ĵ�
    //һ�����
    int dif ;
    StudentLinkedListNode *p , *q ;
    p = class1 ;
    q = class2 ;
    if( beforeCross1 > beforeCross2 )
    {
        dif = beforeCross1 - beforeCross2 ;
        for( int i = 1 ; i <= dif ; i++ )
        {
            p = p->next ;
        }
        while( p != q )
        {
            p = p->next ;
            q = q->next ;
        }
        return p ;
    }
    else
    {
        dif = beforeCross2 - beforeCross1 ;
        for( int j = 1 ; j <= dif ; j++ )
        {
            q = q->next ;
        }
        while( p != q )
        {
            p = p->next ;
            q = q->next ;
        }
        return q ;
    }
}

int main(){
    freopen("./gradeImport.in","r",stdin);

    StudentLinkedListNode *class1=NULL, *class2=NULL;
    int num1, num2, i;
    char student_id[11];
    int grade;
    int beforeCross1, beforeCross2;
    StudentLinkedListNode *node;

    while(~scanf("%d%d", &num1, &num2)){
        class1 = class2 = NULL;
        // �洢���ݵ�����
        for(i = 0;i < num1;i++){
            scanf("%s%d", student_id, &grade);
            node = studentLinkedListCreate(student_id, grade);
            class1 = studentLinkedListAdd(class1, node);
        }
        for(i = 0;i < num2;i++){
            scanf("%s%d", student_id, &grade);
            node = studentLinkedListCreate(student_id, grade);
            class2 = studentLinkedListAdd(class2, node);
        }
        printf("* part1:\nclass1:\n");
        outputStudentLinkedList(class1);
        printf("class2:\n");
        outputStudentLinkedList(class2);

        // ��ת����
        class1 = reverseLinkedList(class1);
        class2 = reverseLinkedList(class2);
        printf("* part2:\nclass1:\n");
        outputStudentLinkedList(class1);
        printf("class2:\n");
        outputStudentLinkedList(class2);

        // �����ཻ����
        scanf("%d%d",&beforeCross1,&beforeCross2);
        createCrossLink(class1, class2, beforeCross1, beforeCross2);

        // ��ӡ�ཻ���
        node = findCrossBeginNode(class1, class2, beforeCross1, beforeCross2);
        printf("* part3:\n");
        printf("{ID:%s, Grade:%d}\n", node->StuID, node->Grade);

        //�����ཻ����
        destroyCrossLink(class1, class2, node);

        printf("\n");
    }
    return 0;
}

