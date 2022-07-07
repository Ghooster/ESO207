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

void addNode(struct Node* sentinel, struct Node* x,long long int coeff,long long int exp)
{
    struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
    temp->coeff=coeff;
    temp->exp=exp;
    temp->prev=x;
    temp->next=sentinel;
    sentinel->prev=temp;
    x->next=temp;
}

int main()
{
    long long int n,m;
    scanf("%lld%lld",&n,&m);
    struct Node* p=(struct Node*)malloc(sizeof(struct Node));
    p->next=p;
    p->prev=p;
    struct Node* q=(struct Node*)malloc(sizeof(struct Node));
    q->next=q;
    q->prev=q;
    struct Node* curr=p;
    for(long long int i=0;i<n;i++)
    {
        long long int coeff,exp;
        scanf("%lld%lld",&coeff,&exp);
        addNode(p,curr,coeff,exp);
        curr=curr->next;
    }
    curr=q;
    for(long long int i=0;i<m;i++)
    {
        long long int coeff,exp;
        scanf("%lld%lld",&coeff,&exp);
        addNode(q,curr,coeff,exp);
        curr=curr->next;
    }
    struct Node* r=(struct Node*)malloc(sizeof(struct Node));
    r->next=r;
    r->prev=r;
    struct Node* p1=p->next;
    struct Node* q1=q->next;
    struct Node* r1=r;
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
    long long int x=0;
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
        printf("0 0 ");
    }
    return 0;
}