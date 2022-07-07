#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct Node
{
    int coeff;
    int exp;
    struct Node* next;
    struct Node* prev;
};

void addNode(struct Node* sentinel, struct Node* x, int coeff, int exp)
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
            //if(p1->coeff!=0)
            {
                addNode(r,r1,p1->coeff,p1->exp);
                r1=r1->next;
            }
            p1=p1->next;
        }
        else if(p1->exp>q1->exp)
        {
            //if(q1->coeff!=0)
            {
                addNode(r,r1,q1->coeff,q1->exp);
                r1=r1->next;
            }
            q1=q1->next;
        }
        else if(p1->exp==q1->exp)
        {
            //if(p1->coeff+q1->coeff!=0)
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
        //if(p1->coeff!=0)
        {
            addNode(r,r1,p1->coeff,p1->exp);
            r1=r1->next;
        }
        p1=p1->next;
    }
    while(q1!=q)
    {
        //if(q1->coeff!=0)
        {
            addNode(r,r1,q1->coeff,q1->exp);
            r1=r1->next;
        }
        q1=q1->next;
    }
    r1=((r1->next)->next);
    p1=p1->next;
    q1=q1->next;
    return r1;
}

struct Node* multiply(struct Node* p, struct Node* p1, long long coeff, long long exp, struct Node* s, struct Node* s1)
{
    while(p!=p1)
    {
        addNode(s,s1,(p1->coeff)*coeff,(p1->exp)+(exp));
        s1=s1->next;
        p1=p1->next;
    }
    p1=p1->next;
    s1=(s1->next)->next;
    return s1;
}

struct Node* copy(struct Node* a, struct Node* a1, struct Node* b, struct Node* b1)
{
    while(a!=a1)
    {
        addNode(b,b1,a1->coeff,a1->exp);
        b1=b1->next;
        a1=a1->next;
    }
    a1=a1->next;
    b1=b1->next->next;
    return a1;
}

int main()
{
    int n,m,coeff,exp;
    scanf("%d%d",&n,&m);
    struct Node* p=(struct Node*)malloc(sizeof(struct Node));
    p->next=p;
    p->prev=p;
    struct Node* q=(struct Node*)malloc(sizeof(struct Node));
    q->next=q;
    q->prev=q;
    struct Node* p1=p;
    struct Node* q1=q;
    for(int i=0;i<n;i++)
    {
        scanf("%d%d",&coeff,&exp);
        addNode(p,p1,coeff,exp);
        p1=(p1->next);
    }
    p1=(p1->next)->next;
    for(int i=0;i<m;i++)
    {
        scanf("%d%d",&coeff,&exp);
        addNode(q,q1,coeff,exp);
        q1=(q1->next);
    }
    q1=(q1->next)->next;
    struct Node* s=(struct Node*)malloc(sizeof(struct Node));
    s->next=s;
    s->prev=s;
    struct Node* s1=s;
    struct Node* r=(struct Node*)malloc(sizeof(struct Node));
    r->next=r;
    r->prev=r;
    struct Node* r1=r;
    struct Node* t=(struct Node*)malloc(sizeof(struct Node));
    t->next=t;
    t->prev=t;
    struct Node* t1=t;
    while(q1!=q)
    {
        s1=multiply(p,p1,q1->coeff,q1->exp,s,s1);
        t1=add(s,s1,r,r1,t,t1);
        r1=copy(t,t1,r,r1);
        r=r1->prev;
        q1=q1->next;
        s->next=s;
        s->prev=s;
        s1=s;
        t->next=t;
        t->prev=t;
        t1=t;
    }
    int x=0;
    while(r!=r1)
    {
        if(r1->coeff!=0)
        {
            printf("%d %d ",r1->coeff,r1->exp);
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
