#include "queue.h"

/** ����Ҫ��ʹ��ջʵ�ֶ��У����ֻ��ʹ��stack.h�еĺ�����������ֱ�ӷ���stack�ĵײ�ʵ�֣���

/**
 * ��ʼ������
 * @param Q ��������
 */
void InitQueue(Queue *Q)
{
    InitStack(&(Q->stack1));
    InitStack(&(Q->stack2));
}

/**
 * ��ն��� ��������
 * @param Q
 */
void ClearQueue(Queue *Q)
{
    InitStack(&(Q->stack1));
    InitStack(&(Q->stack2));
}

/**
 *
 * @param Q ��������
 * @return ���ض�����ʹ�ó���
 */
int QueueLength(Queue Q)
{
    return StackLength(Q.stack1) + StackLength(Q.stack2);
}

/**
 * �ж϶����Ƿ�Ϊ��
 * @param Q ��������
 * @return ���Ϊ�շ���1�����򷵻�0
 */
int QueueEmpty(Queue Q)
{
    //stack1��stack2��Ϊ����QΪ��
    return ( StackEmpty(Q.stack1) )&&( StackEmpty(Q.stack2) ) ;
}

/**
 * ��Ӳ�������Ԫ�ز�����У���Ҫ��������������������Ԫ����Ŀ���Ϊ MaxSize��
 * @param Q ��������
 * @param e �����Ԫ��
 * @return �������ɹ�����1�����򷵻�0
 */
int EnQueue(Queue *Q, DataType e)
{
    /*
        ����˼�������ĸ�ջPushԪ�أ�ʱ�临�Ӷ���Σ��ܷ񽵵�
    */
    //��stack1 PushԪ��
    //������
    if( QueueLength(*Q) == MaxSize )
        return 0 ;
    else
    {
        Push(&Q->stack1, e) ;
        return 1 ;
    }
}

/**
 * ���Ӳ������Ӷ�����ȡ��һ��Ԫ��
 * @param Q ��������
 * @param e ���ܳ���Ԫ��
 * @return ����ɹ�ȡ������1�����򷵻�0
 */
int DeQueue(Queue *Q, DataType *e)
{
    /*
        ����˼�������ĸ�ջPopԪ�أ�ʱ�临�Ӷ���Σ��ܷ񽵵�
    */
    int *n ;
    //���п�
    if( QueueLength(*Q) == 0 )
        return 0 ;
    //��stack1��Ϊ��ʱ
    while( !StackEmpty( Q->stack1 ) )
    {
        Pop(&Q->stack1, &n) ;
        Push(&Q->stack2, n) ;
            /*if( GetTop( Q->stack1 , &n ))//��ȡstack1ջ��Ԫ�أ�����n��
            {
                if( !(Push( &(Q->stack2) , n )&&Pop( &(Q->stack1) , &m )) )//�ƶ�Ԫ��
                    return 0 ;
            }
            //Ԫ�ػ�ȡ���ɹ�
            else
                return 0 ;*/
    }
    Pop(&Q->stack2 , e) ;//eΪpop������Ԫ�صĴ洢��ַ
    return 1 ;
    /*if(StackEmpty(Q->stack1))
        Pop(&Q->stack2,e);
    return 1 ;*/
}

/**
 * ��ȡ����ͷ����ɾ��Ԫ�أ�
 * @param Q ��������
 * @param e ���ܶ���ͷԪ��
 * @return ����ɹ���ȡ����1�����򷵻�0
 */
int GetHead(Queue Q, DataType *e)
{
    int *n ;
    //���п�
    if( QueueLength(Q) == 0 )
        return 0 ;
    else
        {
            while( Q.stack1.top != -1 )
            {
                Pop(&Q.stack1, &n) ;
                Push(&Q.stack2, n) ;
            }
            Pop(&Q.stack2, e) ;
            return 1 ;
        }
}

/**
 * ��ȡ���е�һ�����鿽����˳��Ϊ�Ӷ���ͷ������β
 * @param Q ��������
 * @param seq ջ��Ԫ�ص�һ������
 */
void QueueToArray(Queue Q, DataType *seq)
{
    /*
        ȡ�������ջ�����ƣ�Ԫ�ش����ĸ������
    */
    int *q , i ;
    i = 0 ;
    while( StackLength( Q.stack1 )!=0 )
    {
        Pop(&Q.stack1, &q) ;
        Push(&Q.stack2, q) ;
    }

    while( StackLength( Q.stack2 )!=0 )
    {
        Pop(&Q.stack2, seq+i) ;
        Push(&Q.stack1, *(seq+i)) ;
        i++ ;
    }
}
