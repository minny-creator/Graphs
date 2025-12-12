#include <stdio.h>
#include <stdlib.h>

typedef struct adj{
    int nodeval;
    int weight;
    struct adj* nextnode;
}adj;

typedef struct level{
    int node;
    int level;
}level;

typedef struct num{
    int num;
    struct num* next;
}num;

typedef struct preceedor{
    int preceedor;
    int weight;
}preceedor;

typedef struct superior{
    adj* firstnode;
    adj* lastnode;
}superior;

int main(){
    int N,M;
    scanf("%d",&N);
    scanf("%d",&M);
    superior* adj_list[N];
    for(int i=0;i<N;i++){
        adj_list[i]=malloc(sizeof(superior));
        adj_list[i]->firstnode=NULL;
        adj_list[i]->lastnode=NULL;
    }
    for(int i=0;i<M;i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        adj* r=malloc(sizeof(adj));
        r->nodeval=b-1;
        r->weight=c;
        r->nextnode=NULL;
        adj* p=malloc(sizeof(adj));
            p->nodeval=a-1;
            p->weight=c;
            p->nextnode=NULL;
        if(adj_list[a-1]->firstnode==NULL){
            adj_list[a-1]->firstnode=r;
            adj_list[a-1]->lastnode=r;
        }
        else{
            adj_list[a-1]->lastnode->nextnode=r;
            adj_list[a-1]->lastnode=r;
        }
        if(adj_list[b-1]->firstnode==NULL){
            adj_list[b-1]->firstnode=p;
            adj_list[b-1]->lastnode=p;
        }
        else{
            adj_list[b-1]->lastnode->nextnode=p;
            adj_list[b-1]->lastnode=p;
        }
    }
    int ref=0;
    for(int i=0;i<N;i++){
        adj* p=adj_list[i]->firstnode;
        if(p->nextnode==NULL)ref=ref+1;
    }
    level L[ref];
    ref=0;
    preceedor pre[N];
    for(int i=0;i<N;i++){
        pre[i].preceedor=-1;
    }
    adj* p=adj_list[0]->firstnode;
    num* root=malloc(sizeof(num));
    if(p->nextnode!=NULL){root->num=0;pre[0].preceedor=-2;}
    else {root->num=1;pre[1].preceedor=-2;}
    num* last_num=root;
    root->next=NULL;
    while(root!=NULL){
        num* r=root;
        p=adj_list[r->num]->firstnode;
        if(p->nextnode==NULL){
            L[ref].node=r->num;
            ref=ref+1;
            root=root->next;
            free(r);
        }
        else{
            int x=p->nodeval;
            int weight=p->weight;
            while(p!=NULL){
                x=p->nodeval;
                weight=p->weight;
            if(pre[x].preceedor==-1){
                pre[x].preceedor=r->num;
                pre[x].weight=weight;
                num* z=malloc(sizeof(num));
                z->num=x;
                z->next=NULL;
                last_num->next=z;
                last_num=z;
            }
            p=p->nextnode;
        }
        root=root->next;
        free(r);
        }
    }
    for(int i=0;i<ref;i++){
        int x=L[i].node;
        int level=0;
        while(pre[x].preceedor!=-2){
            level=level+1;
            x=pre[x].preceedor;
        }
        L[i].level=level;
    }
    int diameter=0;
    for(int i=0;i<ref;i++){
        for(int j=i+1;j<ref;j++){
            int length=0;
            int x=L[i].node;
            int y=L[j].node;
            int x_level=L[i].level;
            int y_level=L[j].level;
            if(x_level>y_level){
                while(x_level!=y_level){
                    length=length+pre[x].weight;
                    x=pre[x].preceedor;
                    x_level=x_level-1;
                }
                while(x!=y){
                    length=length+pre[x].weight;
                    length=length+pre[y].weight;
                    x=pre[x].preceedor;
                    y=pre[y].preceedor;
                }

            }
            else{
                while(x_level!=y_level){
                    length=length+pre[y].weight;
                    y=pre[y].preceedor;
                    y_level=y_level-1;
                }
                while(x!=y){
                    length=length+pre[x].weight;
                    length=length+pre[y].weight;
                    x=pre[x].preceedor;
                    y=pre[y].preceedor;
                }
            }
            if(length>diameter)diameter=length;
        }
    }
    printf("Diameter of tree=%d\n",diameter);
    free(root);
    for(int i=0;i<N;i++){
        free(adj_list[i]);
    }
    return 0;
}