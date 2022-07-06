#include "stack.h"
//top指针指向栈顶元素！！！！！
/**
 * 初始化一个栈
 * @param S
 */
void InitStack(Stack *s)
{
    s->top = -1;
}

/**
 * 返回栈已使用长度
 * @param S 操作栈
 * @return 返回栈的长度
 */
int StackLength(Stack S)
{
    return S.top + 1;
}

/**
 * 获取栈的一个数组拷贝，顺序为从栈底到栈顶
 * @param S 操作栈
 * @param seq 栈中元素的一个拷贝
 */
void StackToArray(Stack S, DataType *seq)
{
    int i = 0;
    for (; i <= S.top; i++)
    {
        seq[i] = S.data[i];
    }
}

/**
 * 判断栈是否空，为空返回1，否则返回0
 * @param S
 * @return
 */
int StackEmpty(Stack S)
{
    if( S.top == -1 )
        return 1 ;
    else
        return 0 ;
}

/**
 * 向栈插入一个元素
 * @param S 操作栈
 * @param e 操作数
 * @return 成功返回1，否则返回0
 */
int Push(Stack *s, DataType e)
{
    //栈满
    if( s->top == MaxSize - 1 )
        return 0 ;
    ++(s->top) ;
    s->data[s->top] = e ;//先++因为top指针指向栈顶元素
    return 1 ;
}

/**
 * 从栈中弹出一个元素
 * @param S 操作栈
 * @param e 接受栈弹出的值
 * @return 成功返回1，否则返回0
 */
int Pop(Stack *S, DataType *e)
{
    //栈空
    if( S->top == -1 )
        return 0 ;
    *e = S->data[S->top] ;//加*！
    --(S->top) ;
    return 1 ;
}

/**
 * 获取栈顶元素，不删除该元素
 * @param S 操作栈
 * @param e 接受栈顶元素
 * @return 成功返回1，否则返回0
 */
int GetTop(Stack S, DataType *e)
{
    //栈空
    if( StackEmpty( S ) )
        return 0 ;
    else
    {
        e = S.data[S.top] ;
        return 1 ;
    }
}

