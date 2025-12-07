#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct adj{
    int nodeval;
    int weight;
    struct adj* nextnode;
}adj;

typedef struct preceedor{
    int preceedor;
    int weight;
    //S is the set of vertices MST comprises upto the point
    //S' is the set of vertices which are yet to enter MST
    bool indicator;//true represents vertex present in S
    //false represent vertex present in S'
}preceedor;

typedef struct heap{
    //this structure is created to create a heap of edges
    int ver1;
    int ver2;
    int weight;
}heap;

typedef struct superior{
    adj* firstnode;
    adj* lastnode;
}superior;

//insert function for heap based on weight as priority
void insert(int M,heap H[M],int last,adj* p,int x){
    if(last>=M)return;
    H[last].ver1=x;
    H[last].ver2=p->nodeval;
    H[last].weight=p->weight;
    int c=((last+1)/2)-1;
    if(c==-1)return;
    while(H[c].weight>H[last].weight){
        int ver1=H[last].ver1;
        int ver2=H[last].ver2;
        int weight=H[last].weight;
        H[last].ver1=H[c].ver1;
        H[last].ver2=H[c].ver2;
        H[last].weight=H[c].weight;
        H[c].ver1=ver1;
        H[c].ver2=ver2;
        H[c].weight=weight;
        last=c;
        c=((c+1)/2)-1;
        if(c==-1)break;
    }
}

void delete(int M,heap H[M],int last){
    if(last==0)return;
    if(last==1)return;
    H[0].ver1=H[last-1].ver1;
    H[0].ver2=H[last-1].ver2;
    H[0].weight=H[last-1].weight;
    int c1=1,c2=2,c0=0;
    while(true){
        if(c1>=last-1 && c2>=last-1){
            break;
        }
        else if(c2>=last-1){
            if(H[c0].weight<=H[c1].weight)break;
            else{
                int ver1=H[c0].ver1;
                int ver2=H[c0].ver2;
                int weight=H[c0].weight;
                H[c0].ver1=H[c1].ver1;
                H[c0].ver2=H[c1].ver2;
                H[c0].weight=H[c1].weight;
                H[c1].ver1=ver1;
                H[c1].ver2=ver2;
                H[c1].weight=weight;
                break;
            }
        }
        else{
            if(H[c1].weight<H[c2].weight){
                if(H[c0].weight<=H[c1].weight)break;
                else
                {
                    int ver1=H[c0].ver1;
                int ver2=H[c0].ver2;
                int weight=H[c0].weight;
                H[c0].ver1=H[c1].ver1;
                H[c0].ver2=H[c1].ver2;
                H[c0].weight=H[c1].weight;
                H[c1].ver1=ver1;
                H[c1].ver2=ver2;
                H[c1].weight=weight;
                c0=c1;
                c1=2*(c1+1)-1;
                c2=c1+1;
                }
            }
            else{
                if(H[c0].weight<=H[c2].weight)break;
                else
                {
                    int ver1=H[c0].ver1;
                int ver2=H[c0].ver2;
                int weight=H[c0].weight;
                H[c0].ver1=H[c2].ver1;
                H[c0].ver2=H[c2].ver2;
                H[c0].weight=H[c2].weight;
                H[c2].ver1=ver1;
                H[c2].ver2=ver2;
                H[c2].weight=weight;
                c0=c2;
                c1=2*(c2+1)-1;
                c2=c1+1;
                }
            }
        }
    }
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
    //one vertex has no preceedor which is initial point in MST
    preceedor MST[N];
    //there will be wastage of heap,as all edges do not enter it
    heap H[M];
    int lastindex_heap=0;
    int ref=0;
    //ref indicates whether all edges are inserted into MST or not
    //as soon as ref reaches N-1,loop breaks
    //initialization of heap
    MST[0].preceedor=-1;
    MST[0].indicator=true;
    MST[0].weight=0;
    //FIRST vertex to enter MST is '1'
    adj* p=adj_list[0]->firstnode;
    while(p!=NULL){
        insert(M,H,lastindex_heap,p,0);
        lastindex_heap=lastindex_heap+1;
        p=p->nextnode;
    }
for(int i=1;i<N;i++){
MST[i].indicator=false;
}
    for(int i=0;i<M;i++){
        int ver1=H[0].ver1;
        int ver2=H[0].ver2;
        int weight=H[0].weight;
        if(MST[ver1].indicator==true && MST[ver2].indicator==true){
            delete(M,H,lastindex_heap);
            lastindex_heap=lastindex_heap-1;
            continue;
        }
        else{
            ref=ref+1;
            delete(M,H,lastindex_heap);
            lastindex_heap=lastindex_heap-1;
            if(MST[ver1].indicator==false){
                MST[ver1].indicator=true;
                MST[ver1].preceedor=ver2;
                MST[ver1].weight=weight;
                adj* p=adj_list[ver1]->firstnode;
                while(p!=NULL){
                    if(MST[p->nodeval].indicator==false){
                        insert(M,H,lastindex_heap,p,ver1);
                        lastindex_heap=lastindex_heap+1;
                    }
                    p=p->nextnode;
                }
            }
            else{
                MST[ver2].indicator=true;
                MST[ver2].preceedor=ver1;
                MST[ver2].weight=weight;
                adj* p=adj_list[ver2]->firstnode;
                while(p!=NULL){
                    if(MST[p->nodeval].indicator==false){
                        insert(M,H,lastindex_heap,p,ver2);
                        lastindex_heap=lastindex_heap+1;
                    }
                    p=p->nextnode;
                }
            }
        }
        if(ref==N-1)break;
    }
    printf("Edges in MST:\n");
    int total=0;
    for(int i=1;i<N;i++){
        printf("(%d, %d) weight = %d\n",i+1,((MST[i].preceedor)+1),MST[i].weight);
        total=total+MST[i].weight;
    }
    printf("Total Weight = %d\n",total);

}