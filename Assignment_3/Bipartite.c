#include <stdio.h>
#include <stdlib.h>
struct node
{
    long long int vertex;
    struct node* next;
};
struct Graph
{
    long long int V;
    struct node** adjLists;
};
struct node* createNode(long long int v)
{
    struct node* temp=malloc(sizeof(struct node));
    temp->vertex=v;
    temp->next=NULL;
    return temp;
}
struct Graph* createGraph(long long int V)
{
    struct Graph* graph=malloc(sizeof(struct Graph));
    graph->V=V;
    graph->adjLists=malloc(V*sizeof(struct node*));
    for (long long int i=0;i<V;i++)
        graph->adjLists[i]=NULL;
    return graph;
}
void createEdge(struct Graph* g,long long int s,long long int d)
{
    struct node* temp=createNode(d);
    temp->next=g->adjLists[s];
    g->adjLists[s]=temp;
    temp=createNode(s);
    temp->next=g->adjLists[d];
    g->adjLists[d]=temp;
}
long long int dfs(struct Graph* g,long long int color[],long long int vertex,long long int c)
{
    color[vertex]=c;
    struct node* temp=g->adjLists[vertex];
    while(temp!=NULL)
    {
        if(color[temp->vertex]==-1)
        {
            if(dfs(g,color,temp->vertex,(c+1)%2)==0)
                return 0;
        }
        else if(color[temp->vertex]==c)
        {
            return 0;
        }
        temp=temp->next;
    }
    return 1;
}
void checkBipartite(struct Graph* g)
{
    //long long int color[100000];
    long long int* color=malloc((g->V)*sizeof(long long int));
    for(long long int i=0;i<(g->V);i++)
        color[i]=-1;
    if(dfs(g,color,0,0))
    {
        printf("YES\n");
        for(long long int i=0;i<g->V;i++)
        {
            printf("%lld\n",(color[i]+1));
        }
    }
    else
        printf("NO");
    return;
}

int main()
{
    long long int V,E,u,v;
    scanf("%lld%lld",&V,&E);
    struct Graph* g=createGraph(V);
    for(long long int i=0;i<E;i++)
    {
        scanf("%lld%lld",&u,&v);
        createEdge(g,u,v);
    }
    checkBipartite(g);
    return 0;
}