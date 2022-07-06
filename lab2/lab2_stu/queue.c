#include "queue.h"

/** ！！要求使用栈实现队列，因此只能使用stack.h中的函数。不允许直接访问stack的底层实现！！

/**
 * 初始化队列
 * @param Q 操作队列
 */
void InitQueue(Queue *Q)
{
    InitStack(&(Q->stack1));
    InitStack(&(Q->stack2));
}

/**
 * 清空队列 操作队列
 * @param Q
 */
void ClearQueue(Queue *Q)
{
    InitStack(&(Q->stack1));
    InitStack(&(Q->stack2));
}

/**
 *
 * @param Q 操作队列
 * @return 返回队列已使用长度
 */
int QueueLength(Queue Q)
{
    return StackLength(Q.stack1) + StackLength(Q.stack2);
}

/**
 * 判断队列是否为空
 * @param Q 操作队列
 * @return 如果为空返回1，否则返回0
 */
int QueueEmpty(Queue Q)
{
    //stack1和stack2都为空则Q为空
    return ( StackEmpty(Q.stack1) )&&( StackEmpty(Q.stack2) ) ;
}

/**
 * 入队操作，将元素插入队列，需要处理队列满的情况（队列元素数目最多为 MaxSize）
 * @param Q 操作队列
 * @param e 插入的元素
 * @return 如果插入成功返回1，否则返回0
 */
int EnQueue(Queue *Q, DataType e)
{
    /*
        认真思考，从哪个栈Push元素，时间复杂度如何？能否降低
    */
    //从stack1 Push元素
    //队列满
    if( QueueLength(*Q) == MaxSize )
        return 0 ;
    else
    {
        Push(&Q->stack1, e) ;
        return 1 ;
    }
}

/**
 * 出队操作，从队列中取出一个元素
 * @param Q 操作队列
 * @param e 接受出队元素
 * @return 如果成功取出返回1，否则返回0
 */
int DeQueue(Queue *Q, DataType *e)
{
    /*
        认真思考，从哪个栈Pop元素，时间复杂度如何？能否降低
    */
    int *n ;
    //队列空
    if( QueueLength(*Q) == 0 )
        return 0 ;
    //当stack1不为空时
    while( !StackEmpty( Q->stack1 ) )
    {
        Pop(&Q->stack1, &n) ;
        Push(&Q->stack2, n) ;
            /*if( GetTop( Q->stack1 , &n ))//获取stack1栈顶元素，存在n中
            {
                if( !(Push( &(Q->stack2) , n )&&Pop( &(Q->stack1) , &m )) )//移动元素
                    return 0 ;
            }
            //元素获取不成功
            else
                return 0 ;*/
    }
    Pop(&Q->stack2 , e) ;//e为pop出来的元素的存储地址
    return 1 ;
    /*if(StackEmpty(Q->stack1))
        Pop(&Q->stack2,e);
    return 1 ;*/
}

/**
 * 获取队列头（不删除元素）
 * @param Q 操作队列
 * @param e 接受队列头元素
 * @return 如果成功获取返回1，否则返回0
 */
int GetHead(Queue Q, DataType *e)
{
    int *n ;
    //队列空
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
 * 获取队列的一个数组拷贝，顺序为从队列头到队列尾
 * @param Q 操作队列
 * @param seq 栈中元素的一个拷贝
 */
void QueueToArray(Queue Q, DataType *seq)
{
    /*
        取决于你的栈如何设计，元素存在哪个队列里。
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
