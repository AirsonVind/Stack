#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100
#define StackInitSize 100 //��ʼ������
#define StackIncrement 10 //��������

typedef int Status;
typedef char SElemType;

//����˳��洢ջ
typedef struct 
{
    SElemType *base; //ջ��ָ��
    SElemType *top; //ջ��ָ��
    int stacksize; //��ǰջ���������
}SqStack;

//--------------���������ĺ���ԭ��----------------------

//��ʼ��ջ
Status InitStack(SqStack *S)
{
    S->base = (SElemType * )malloc(sizeof(SqStack)*StackInitSize);
    if (!S->base)exit(0);
    S->top = S->base;
    S->stacksize = StackInitSize;
    return OK;
};

//�ж�ջ�Ƿ�Ϊ��
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


//���ջ��Ԫ��
Status GetTop(SqStack *S,SElemType *e)
{
    if (S->base == S->top)    return ERROR;
    *e = *(S->top-1);
    return OK;
}

//��ջ
Status Push(SqStack *S,SElemType e)
{
    if (S->top-S->base == S->stacksize)
    {
        S->base = (SElemType * )realloc(S->base,sizeof(SqStack)*(S->stacksize+StackIncrement));
        if (!S->base) exit(0);//����ʧ��

        S->top = S->base + S->stacksize;
        S->stacksize += StackIncrement;
    }
    *S->top++ = e;
    return OK;
}

//��ջ
Status Pop(SqStack *S,SElemType *e)
{
    if (S->top == S->base) exit(0);
    *e = *--S->top;
    return OK;
}



//-----------���ȼ��Ƚ�-----------------------
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





//-----------��׺���ʽת��׺���ʽ-------------
Status InfixToPostfix(char *Infix ,char *Postfix)
{
    SqStack S;//����һ���洢��������ջ
    int i = 0,j = 0;//��Ϊ���ַ������α�
    int s = 0;//���ڴ���һλ������,��ʾλ��
    char c,k;//�洢ջ��Ԫ�غ���Ϊ��ջԪ�ص���ʱ����
    if (InitStack(&S) != OK)  return ERROR;
    
    

    while (Infix[i] != '\0')
    {
        while (Infix[i] >= '0' && Infix[i] <= '9')
        {
            Postfix[j++] = Infix[i++];//���������ֱ�����
            s++;//λ����һ
        }
        if (s > 1)//��λ��������ʱ�����ֺ���Ͽո�
        {
            Postfix[j++] = ' ';
        }
        while (Infix[i] == '+' || Infix[i] == '-' || Infix[i] == '*' || Infix[i] =='/')//����ǲ����������ж�
        {
            if (EmptyStack(&S))
            {
                Push(&S,Infix[i++]);//ջΪ��ʱֱ�ӽ�ջ
            }else
            {
                GetTop(&S,&c);
                if (Compare(Infix[i],c) <= 0)//ֻ�е�Infix[i]�����ȼ�����ջ��Ԫ��ʱ������ջ
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
    while (!EmptyStack(&S))//��ջ��ʣ��Ԫ�ط����沨��ʽ
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

    printf("������������ʽ:\n");
    scanf("%s",Infix);

    InfixToPostfix(Infix,Postfix);
    printf("ת��Ϊ��׺���ʽ:\n");
    printf("%s",Postfix);
    return 0;
}