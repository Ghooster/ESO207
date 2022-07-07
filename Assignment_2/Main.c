#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
//included needed libraries

struct Node
{
    int nOfNodes;               //0 for a NIL tree, 1 for a leaf, and 2 and 3 for having 2 and 3 children nodes, respectively.
    struct Node* firstNode;     //first child node, can be NULL
    struct Node* secondNode;    //second child node, can be NULL
    struct Node* thirdNode;     //third child node, can be NULL
    struct Node* parentNode;    //points towards the parent of the node, NULL for the root node
    int minSecond;              //minimum value in it's second child node if it exists
    int minThird;               //minimum value in it's third chil node if it exists
    int value;                  //value stored if it's a leaf node
};

//Function to make a singleton node, it's value being the passed value 'v'
struct Node* MakeSingleton(int v)
{
    struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
    temp->nOfNodes=1;
    temp->value=v;
    temp->parentNode=NULL;
    temp->firstNode=NULL;
    temp->secondNode=NULL;
    temp->thirdNode=NULL;
    return temp;
}

//Function to find the height of a given node in a 2-3 tree given its pointer.
int NodeHeight(struct Node* temp)
{
    int h=0;
    while(temp->nOfNodes>1)
    {
        temp=temp->firstNode;
        h++;
    }
    return(h);
}

struct Node* create2Node(int minSecond,struct Node* a,struct Node* b)
{
    //Note that we are not assigning the parent node property to the new node here and it needs to be managed by the calling function
    struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
    temp->nOfNodes=2;
    temp->firstNode=a;
    temp->secondNode=b;
    temp->thirdNode=NULL;
    temp->minSecond=minSecond;
    a->parentNode=temp;
    b->parentNode=temp;
    return temp;
}

struct Node* create3Node(int minSecond, int minThird, struct Node* a, struct Node* b, struct Node* c)
{
    //Again we are not assigning the parent node property to the new node here and it needs to be managed by the calling function
    struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
    temp->nOfNodes=3;
    temp->firstNode=a;
    temp->secondNode=b;
    temp->thirdNode=c;
    temp->minSecond=minSecond;
    temp->minThird=minThird;
    a->parentNode=temp;
    b->parentNode=temp;
    c->parentNode=temp;
    return temp;
}

//Returns the minimum element present in the tree rooted at node temp.
int NodeMinimum(struct Node* temp)
{
    while(temp->nOfNodes>1)
    {
        temp=temp->firstNode;//We traverse down the leftmost path until we hit the leaf node
    }
    return(temp->value);
}

//Function to merge two trees at the same height such that the parent of the second tree is NULL and is called by Merge()
struct Node* Merge1(struct Node* a, struct Node* b, int minb)
{
    if(a->parentNode==NULL)//Degenerate case, will probably not occur, left as a precaution
    {
        struct Node* a1=create2Node(minb,a,b);
        a1->parentNode=NULL;
        return a1;
    }
    else if(a->parentNode->nOfNodes==2)//Since two nodes, b can be made the right adjacent sibling of a
    {
        struct Node* t=a->parentNode;//Making a copy of a's parent before it gets updated
        struct Node* a1=create3Node(NodeMinimum(a),minb,a->parentNode->firstNode,a,b);
        //V.IMP Note that even though we are calling NodeMinimun(a), it is a returning function and thus will be executed at most once when called from Merge()
        a1->parentNode=t->parentNode;
        if(t->parentNode!=NULL)//Condition to update a1's parent's child
        {
        if(t->parentNode->nOfNodes==1)
            t->parentNode->firstNode=a1;
        else if(t->parentNode->nOfNodes==2)
            t->parentNode->secondNode=a1;
        else if(t->parentNode->nOfNodes==3)
            t->parentNode->thirdNode=a1;
        }
        return a1;
    }
    else if(a->parentNode->nOfNodes==3)//We will need to split and recursively call Merge1() again on the two new nodes
    {
        struct Node* t=a->parentNode;//Making a copy of a's parent before it gets updated
        struct Node* a1=create2Node(a->parentNode->minSecond,a->parentNode->firstNode,a->parentNode->secondNode);
        a1->parentNode=t->parentNode;
        if(t->parentNode!=NULL)//Condition to update a1's parent's child
        {
            if(t->parentNode->nOfNodes==1)
                t->firstNode=a1;
            else if(t->parentNode->nOfNodes==2)
                t->secondNode=a1;
            else if(t->parentNode->nOfNodes==3)
                t->parentNode->thirdNode=a1;
        }
        struct Node* b1=create2Node(minb,a,b);
        b1->parentNode=NULL;
        return Merge1(a1,b1,t->minThird);
    }
}

//Function to merge two trees at the same height such that the parent of the first tree is NULL and is called by Merge()
struct Node* Merge2(struct Node* a,struct Node* b,int minb)
{
    if(b->parentNode==NULL)//Degenerate case, will probably not occur, left as a precaution
    {
        struct Node* b1=create2Node(minb,a,b);
        b1->parentNode=NULL;
        return b1;
    }
    else if(b->parentNode->nOfNodes==2)//Since two nodes, a can be made a left adjacent sibling of b
    {
        struct Node* temp=b->parentNode;//Making a copy of b's parent before it gets updated
        struct Node* b1=create3Node(minb,b->minSecond,a,b,b->parentNode->secondNode);
        b1->parentNode=temp->parentNode;
        if(temp->parentNode!=NULL)//Condition to update b1's parent's child
        {
            temp->parentNode->firstNode=b1;
        }
        return b1;
    }
    else if(b->parentNode->nOfNodes==3)//We will need to split and recursively call Merge2() again on the two new nodes
    {
        struct Node* temp=b->parentNode;//Making a copy of b's parent before it gets updated
        struct Node* a1=create2Node(minb,a,b);
        a1->parentNode=NULL;
        struct Node* b1=create2Node(temp->minThird,temp->secondNode,temp->thirdNode);
        b1->parentNode=temp->parentNode;
        if(temp->parentNode!=NULL)//Condition to update b1's parent's child
        {
            temp->parentNode->firstNode=b1;
        }
        return Merge2(a1,b1,temp->minSecond);
    }
}

//Merges the trees a and b assuming that all elements in tree a are less than those in tree b.
struct Node* Merge(struct Node* a, struct Node* b)
{
    int ha=NodeHeight(a);
    int hb=NodeHeight(b);
    if(a->nOfNodes==0)//Testing for degenerate case of a when subtree rooted at it has no elements
        return b;
    if(b->nOfNodes==0)//Same for b as for a
        return a;
    int minb;
    minb=NodeMinimum(b); //Extracts the minimum value of the tree rooted at b as it is required further down the line
    if(ha==hb)
    {
        struct Node* c=create2Node(minb,a,b);
        c->parentNode=NULL;
        return c;
    }
    else if(ha>hb)
    {
        for(int i=1;i<=ha-hb;i++)//loop to traverse to the rightmost node of a at height hb
        {
            if(a->nOfNodes==3)
                a=a->thirdNode;
            else if(a->nOfNodes==2)
                a=a->secondNode;
            else if(a->nOfNodes==1)
                a=a->firstNode;
        }
        a=Merge1(a,b,minb);//Calling the Merge1 subroutine which will merge a and b now that we have the pointer to the required node in a
        while(a->parentNode!=NULL)//Loop to traverse to the root node of the merged trees
        {
            a=a->parentNode;
        }
        return a;
    }
    else if(ha<hb)
    {
        for(int i=1;i<=hb-ha;i++)//loop o traverse to the rightmost node of b at height ha
        {
            b=b->firstNode;
        }
        b=Merge2(a,b,minb);//Calling the Merge2 subroutine which will merge a and b now that we have the pointer to the required node in b
        while(b->parentNode!=NULL)//Loop to traverse to the root node of the merged trees
        {
            b=b->parentNode;
        }
        return b;
    }
}

//Traverses the tree recursively and prints its leaves from left to right
void Extract(struct Node* t)
{
    if(t->nOfNodes==0)
        return;
    if(t->nOfNodes==1)
    {
        printf("%d ",t->value);
        return;
    }
    if(t->nOfNodes==2)
    {
        Extract(t->firstNode);
        Extract(t->secondNode);
        return;
    }
    if(t->nOfNodes==3)
    {
        Extract(t->firstNode);
        Extract(t->secondNode);
        Extract(t->thirdNode);
        return;
    }
}

//Test program to generate fairly random trees covering all cases I could think of by running it multiple times and merges them
/*
int main()
{
    srand(time(NULL));
    int test1=rand()%1000;
    int test2=test1;
    struct Node* T=MakeSingleton(test1);
    for(int i=1;i<=1000;i++)
    {
        int x=rand()%1000;
        if(x<test1)
        {
            T=Merge(MakeSingleton(x),T);
            test1=x;
        }
        else if(x>test2)
        {
            T=Merge(T,MakeSingleton(x));
            test2=x;
        }
        Extract(T);
        printf("\n");
    }
    test1=rand()%1000+1000;
    test2=test1;
    struct Node* U = MakeSingleton(test1);
    for(int i=1;i<=1000;i++)
    {
        int x=rand()%1000+1000;
        if(x<test1)
        {
            U=Merge(MakeSingleton(x),U);
            test1=x;
        }
        else if(x>test2)
        {
            U=Merge(U,MakeSingleton(x));
            test2=x;
        }
        Extract(U);
        printf("\n");
    }
    struct Node* V=Merge(T,U);
    Extract(V);
    return 0;
}*/

struct Node* makeTreeRight(int i,int j)
{
    struct Node* T = MakeSingleton(i*i);
    for (int l = i+1; l<= j; l++)
    {
        struct Node* T= Merge(T,MakeSingleton(l*l));
    }
    return T;
}

struct Node* makeTreeLeft(int i,int j){
    struct Node* T = MakeSingleton(j*j);
    for (int u = j-1; u>=i; u--)
    {
        struct Node* T= Merge(MakeSingleton(u*u),T);
    }
    return T;
    }

struct Node* makeTree(int i,int j){
    int k = (i+j)/2;
    struct Node* T1 = makeTreeRight(i,k);
    struct Node* T2 = makeTreeLeft(k+1,j);
    struct Node* T = Merge(T1,T2);
    return T;
}

//Test program as required by the assignment question, uuncomment and comment the other main to run
int main()
{
    /*
   struct Node* T=MakeSingleton(1);
   for(int i=2;i<=500;i++)
       T=Merge(T,MakeSingleton(i));
    struct Node* U = MakeSingleton(777);
    for(int i=778;i<=1000;i++)
        U=Merge(U,MakeSingleton(i));
     struct Node* V=Merge(T,U);
     Extract(V);*/

     int i = 11, j = 23, k = 40, l = 100;
    struct Node* T1 = makeTree(i,j);
    struct Node* T2 = makeTree(j+1,k);
    struct Node* T3 = makeTree(k+1,l);
    struct Node* U = Merge(T1,Merge(T2,T3));
    struct Node* V = Merge(Merge(T1,T2),T3);
    Extract(U);
    Extract(V);
     return 0;
 }