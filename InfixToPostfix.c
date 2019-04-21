#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100
#define StackInitSize 100 //初始分配量
#define StackIncrement 10 //分配增量

typedef int Status;
typedef char SElemType;

//定义顺序存储栈
typedef struct 
{
    SElemType *base; //栈底指针
    SElemType *top; //栈顶指针
    int stacksize; //当前栈的最大容量
}SqStack;

//--------------基本操作的函数原型----------------------

//初始化栈
Status InitStack(SqStack *S)
{
    S->base = (SElemType * )malloc(sizeof(SqStack)*StackInitSize);
    if (!S->base)exit(0);
    S->top = S->base;
    S->stacksize = StackInitSize;
    return OK;
};

//判断栈是否为空
Status EmptyStack(SqStack *S)
{
    if (S->base == S->top)
    {
        return OK;
    }else
    {
        return ERROR;
    }
}


//获得栈顶元素
Status GetTop(SqStack *S,SElemType *e)
{
    if (S->base == S->top)    return ERROR;
    *e = *(S->top-1);
    return OK;
}

//入栈
Status Push(SqStack *S,SElemType e)
{
    if (S->top-S->base == S->stacksize)
    {
        S->base = (SElemType * )realloc(S->base,sizeof(SqStack)*(S->stacksize+StackIncrement));
        if (!S->base) exit(0);//分配失败

        S->top = S->base + S->stacksize;
        S->stacksize += StackIncrement;
    }
    *S->top++ = e;
    return OK;
}

//出栈
Status Pop(SqStack *S,SElemType *e)
{
    if (S->top == S->base) exit(0);
    *e = *--S->top;
    return OK;
}



//-----------优先级比较-----------------------
int Compare(char a,char b)
{
    switch (a)
    {
    case '+':
    case '-':
        if (b == '+' || b == '-')  return 0;
        if (b == '*' || b == '/')  return -1;
        break;
    case '*':
    case '/':
        if (b == '+' || b == '-')  return 1;
        if (b == '*' || b == '/')  return 0;
    default:
        break;
    }
}





//-----------中缀表达式转后缀表达式-------------
Status InfixToPostfix(char *Infix ,char *Postfix)
{
    SqStack S;//创建一个存储操作符的栈
    int i = 0,j = 0;//作为两字符串的游标
    int s = 0;//用于处理一位以上数,表示位数
    char c,k;//存储栈顶元素和作为出栈元素的临时副本
    if (InitStack(&S) != OK)  return ERROR;
    
    

    while (Infix[i] != '\0')
    {
        while (Infix[i] >= '0' && Infix[i] <= '9')
        {
            Postfix[j++] = Infix[i++];//如果是数字直接输出
            s++;//位数增一
        }
        if (s > 1)//两位及以上数时在数字后加上空格
        {
            Postfix[j++] = ' ';
        }
        while (Infix[i] == '+' || Infix[i] == '-' || Infix[i] == '*' || Infix[i] =='/')//如果是操作符则需判断
        {
            if (EmptyStack(&S))
            {
                Push(&S,Infix[i++]);//栈为空时直接进栈
            }else
            {
                GetTop(&S,&c);
                if (Compare(Infix[i],c) <= 0)//只有当Infix[i]的优先级大于栈顶元素时才能入栈
                {
                    do
                    {
                        Pop(&S,&k);
                        Postfix[j++] = k;
                        if (EmptyStack(&S))
                        {
                            break;
                        }
                        GetTop(&S,&c);
                    } while (Compare(Infix[i],c) <= 0);
                }
                Push(&S,Infix[i++]);
            }
        }
        s = 0;
    }
    while (!EmptyStack(&S))//将栈内剩余元素放入逆波兰式
        {
            Pop(&S,&k);
            Postfix[j++] = k;
        }
        Postfix[j] = '\0';
}



int main()
{
    char Infix[MAXSIZE] = {0};
    char Postfix[MAXSIZE] = {0};

    printf("请输入中序表达式:\n");
    scanf("%s",Infix);

    InfixToPostfix(Infix,Postfix);
    printf("转化为后缀表达式:\n");
    printf("%s",Postfix);
    return 0;
}