#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//stores information of node's distance from source
typedef struct node{
    int distance;//distance from source
    bool color;//represents whether node distance decided or not
    int preceedor;//represents node preceeding to it in tree as source s
}node;

//adjacent list of vertices
typedef struct adj{
    int nodeval;
    struct adj* nextnode;
}adj;

//points to first,last nodes of adjacent list
//points to last node
//in order to reduce time for traversing to last node every time for inserting into list
typedef struct superior{
    adj* firstnode;
    adj* lastnode;
}superior;

//stores queue's first and last indices
typedef struct queue{
    int firstindex;
    int lastindex;
}queue;

//function calls itself recursively to print ancestors
//it prints vertices involved in the path from source to given vertex
void printpath(int n,node arr[n],int i){
    if(arr[i].preceedor==-1){
        printf("%d ",i+1);
        return;
    }
    printpath(n,arr,arr[i].preceedor);
    printf("%d ",i+1);
}

int main(){
    int N;
    scanf("%d",&N);
    int M;
    scanf("%d",&M);
    superior* adj_list[N];
    for(int i=0;i<N;i++){
        adj_list[i]=malloc(sizeof(superior));
        adj_list[i]->firstnode=NULL;
        adj_list[i]->lastnode=NULL;
    }
    //on observing edges,insertions into adjacent lists are done
    for(int i=0;i<M;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        adj* r=malloc(sizeof(adj));
        r->nodeval=b-1;
        r->nextnode=NULL;
        adj* p=malloc(sizeof(adj));
            p->nodeval=a-1;
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
    int S;
    scanf("%d",&S);
    node arr[N];
    //initializing distance information of all vertices to unknown
    for(int i=0;i<N;i++){
        arr[i].distance=-1;
        arr[i].color=true;
        arr[i].preceedor=-1;
    }
    //initialize source distance to '0'
    arr[S-1].distance=0;
    arr[S-1].color=false; //false represents black
    // true represents white(distance not decided)
    arr[S-1].preceedor=-1;
    //creating main array for queue
    int q[N];
    //instantiating queue struct to store metadata for queue
    queue metadata;
    //initializing queue
    q[0]=S-1;
    metadata.firstindex=0;
    metadata.lastindex=1;
    //this loop assignes shortest distance for all vertices
    //this loop terminates when all adjacent lists are over 
    while(metadata.firstindex!=metadata.lastindex){
        int c=q[metadata.firstindex];
        adj* p=adj_list[c]->firstnode;
            while(p!=NULL){
            if(arr[p->nodeval].color==false){
                p=p->nextnode;
            }
            else{
                arr[p->nodeval].distance=arr[c].distance+1;
                arr[p->nodeval].color=false;
                arr[p->nodeval].preceedor=c;
                q[metadata.lastindex]=p->nodeval;
                metadata.lastindex=metadata.lastindex+1;
                p=p->nextnode;
            }
        }
        metadata.firstindex=metadata.firstindex+1;
    }
    //prints shortest distance and path info of all vertices
    for(int i=0;i<N;i++){
        printf("Vertex %d: Length = %d, Path = ",i+1,arr[i].distance);
        printpath(N,arr,i);
        printf("\n");
    }
    for(int i=0;i<N;i++){
        free(adj_list[i]);
    }
    return 0;
}