#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct Node
{
    long long int coeff;
    long long int exp;
    struct Node* next;
    struct Node* prev;
};

void addNode(struct Node* sentinel, struct Node* x, long long int coeff, long long int exp)
{
    struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
    temp->coeff=coeff;
    temp->exp=exp;
    temp->next=sentinel;
    temp->prev=x;
    sentinel->prev=temp;
    x->next=temp;
}

struct Node* add(struct Node* p, struct Node* p1, struct Node* q, struct Node* q1, struct Node* r, struct Node* r1)
{
    while(p1!=p&&q1!=q)
    {
        if(p1->exp<q1->exp)
        {
            if(p1->coeff!=0)
            {
                addNode(r,r1,p1->coeff,p1->exp);
                r1=r1->next;
            }
            p1=p1->next;
        }
        else if(p1->exp>q1->exp)
        {
            if(q1->coeff!=0)
            {
                addNode(r,r1,q1->coeff,q1->exp);
                r1=r1->next;
            }
            q1=q1->next;
        }
        else if(p1->exp==q1->exp)
        {
            if(p1->coeff+q1->coeff!=0)
            {
                addNode(r,r1,q1->coeff+p1->coeff,p1->exp);
                r1=r1->next;
            }
            p1=p1->next;
            q1=q1->next;
        }
    }
    while(p1!=p)
    {
        if(p1->coeff!=0)
        {
            addNode(r,r1,p1->coeff,p1->exp);
            r1=r1->next;
        }
        p1=p1->next;
    }
    while(q1!=q)
    {
        if(q1->coeff!=0)
        {
            addNode(r,r1,q1->coeff,q1->exp);
            r1=r1->next;
        }
        q1=q1->next;
    }
    r1=((r1->next)->next);
    return r1;
}

int main()
{
    long long int n,m,coeff,exp;
    scanf("%lld%lld",&n,&m);
    struct Node* p=(struct Node*)malloc(sizeof(struct Node));
    p->next=p;
    p->prev=p;
    struct Node* q=(struct Node*)malloc(sizeof(struct Node));
    q->next=q;
    q->prev=q;
    struct Node* p1=p;
    struct Node* q1=q;
    for(long long int i=0;i<n;i++)
    {
        scanf("%lld%lld",&coeff,&exp);
        addNode(p,p1,coeff,exp);
        p1=(p1->next);
    }
    p1=(p1->next)->next;
    for(long long int i=0;i<m;i++)
    {
        scanf("%lld%lld",&coeff,&exp);
        addNode(q,q1,coeff,exp);
        q1=(q1->next);
    }
    q1=((q1->next)->next);
    struct Node* r=(struct Node*)malloc(sizeof(struct Node));
    r->prev=r;
    r->next=r;
    struct Node* r1=r;
    r1=add(p,p1,q,q1,r,r1);
    int x=0;
    while(r!=r1)
    {
        if(r1->coeff!=0)
        {
            printf("%lld %lld ",r1->coeff,r1->exp);
            x=1;
        }
        r1=r1->next;
    }
    if(x==0)
    {
        printf("0 0");
    }
    return 0;
}