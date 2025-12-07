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
    //indicates distance from source vertex
    int distance;
    //S is the set of vertices MST comprises upto the point
    //S' is the set of vertices which are yet to enter MST
    bool indicator;//true represents vertex present in S
    //false represent vertex present in S'
}preceedor;

typedef struct superior{
    adj* firstnode;
    adj* lastnode;
}superior;

typedef struct heap{
    //this structure is created to create a heap of edges
    int ver1;
    int ver2;
    int distance;
}heap;

//x is the vertex which was already present in or went to 
// S(set of vertices whose distance was determined)
//insert function for heap based on weight as priority
void insert(int M,heap H[M],int last,adj* p,int x,int distance){
    if(last>=M)return;
    H[last].ver1=x;
    H[last].ver2=p->nodeval;
    H[last].distance=distance;
    int c=((last+1)/2)-1;
    if(c==-1)return;
    while(H[c].distance>H[last].distance){
        int ver1=H[last].ver1;
        int ver2=H[last].ver2;
        int dist=H[last].distance;
        H[last].ver1=H[c].ver1;
        H[last].ver2=H[c].ver2;
        H[last].distance=H[c].distance;
        H[c].ver1=ver1;
        H[c].ver2=ver2;
        H[c].distance=dist;
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
    H[0].distance=H[last-1].distance;
    int c1=1,c2=2,c0=0;
    while(true){
        if(c1>=last-1 && c2>=last-1){
            break;
        }
        else if(c2>=last-1){
            if(H[c0].distance<=H[c1].distance)break;
            else{
                int ver1=H[c0].ver1;
                int ver2=H[c0].ver2;
                int distance=H[c0].distance;
                H[c0].ver1=H[c1].ver1;
                H[c0].ver2=H[c1].ver2;
                H[c0].distance=H[c1].distance;
                H[c1].ver1=ver1;
                H[c1].ver2=ver2;
                H[c1].distance=distance;
                break;
            }
        }
        else{
            if(H[c1].distance<H[c2].distance){
                if(H[c0].distance<=H[c1].distance)break;
                else
                {
                    int ver1=H[c0].ver1;
                int ver2=H[c0].ver2;
                int dist=H[c0].distance;
                H[c0].ver1=H[c1].ver1;
                H[c0].ver2=H[c1].ver2;
                H[c0].distance=H[c1].distance;
                H[c1].ver1=ver1;
                H[c1].ver2=ver2;
                H[c1].distance=dist;
                c0=c1;
                c1=2*(c1+1)-1;
                c2=c1+1;
                }
            }
            else{
                if(H[c0].distance<=H[c2].distance)break;
                else
                {
                    int ver1=H[c0].ver1;
                int ver2=H[c0].ver2;
                int dis=H[c0].distance;
                H[c0].ver1=H[c2].ver1;
                H[c0].ver2=H[c2].ver2;
                H[c0].distance=H[c2].distance;
                H[c2].ver1=ver1;
                H[c2].ver2=ver2;
                H[c2].distance=dis;
                c0=c2;
                c1=2*(c2+1)-1;
                c2=c1+1;
                }
            }
        }
    }
}

void print(preceedor SSD[],int i){
    int pre=SSD[i].preceedor;
    if(pre==-1)return;
    print(SSD,pre);
    printf("%d ",pre+1);
}

int main(){
    int N;
    scanf("%d",&N);
    int M;
    scanf("%d",&M);
    superior* adj_list[N];
    //adj_list here stores vertices 
    // to which particular vertex points to by some edge
    //the edge doesn't gets stored in reverse direction
    //as it is not undirected but directed graph
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
        if(adj_list[a-1]->firstnode==NULL){
            adj_list[a-1]->firstnode=r;
            adj_list[a-1]->lastnode=r;
        }
        else{
            adj_list[a-1]->lastnode->nextnode=r;
            adj_list[a-1]->lastnode=r;
        }
           }
//indicates source vertex 
int S;
scanf("%d",&S);
//SSD represents shortest source distance (of the particular vertex)
//source vertex has no preceedor(-1(which is invalid))
//  which is initial point in SSD
    preceedor SSD[N];
    //there will be wastage of heap,as all edges do not enter it
    heap H[M];
    int lastindex_heap=0;
    int ref=0;
    //ref indicates whether all vertices entered into set S or not
    //as soon as ref reaches N-1,loop breaks
    //initialization of source vertex
    SSD[S-1].preceedor=-1;
    SSD[S-1].indicator=true;
    SSD[S-1].distance=0;
    //FIRST vertex to enter SSD is integer S
    adj* p=adj_list[0]->firstnode;
    while(p!=NULL){
        insert(M,H,lastindex_heap,p,0,p->weight);
        lastindex_heap=lastindex_heap+1;
        p=p->nextnode;
    }
for(int i=1;i<N;i++){
SSD[i].indicator=false;
}
    for(int i=0;i<M;i++){
        int ver1=H[0].ver1;
        int ver2=H[0].ver2;
        int distance=H[0].distance;
        if(SSD[ver1].indicator==true && SSD[ver2].indicator==true){
            delete(M,H,lastindex_heap);
            lastindex_heap=lastindex_heap-1;
            continue;
        }
        else{
            ref=ref+1;
            delete(M,H,lastindex_heap);
            lastindex_heap=lastindex_heap-1;
            if(SSD[ver1].indicator==false){
                SSD[ver1].indicator=true;
                SSD[ver1].preceedor=ver2;
                SSD[ver1].distance=distance;
                adj* p=adj_list[ver1]->firstnode;
                while(p!=NULL){
                    if(SSD[p->nodeval].indicator==false){
                        insert(M,H,lastindex_heap,p,ver1,distance+p->weight);
                        lastindex_heap=lastindex_heap+1;
                    }
                    p=p->nextnode;
                }
            }
            else{
                SSD[ver2].indicator=true;
                SSD[ver2].preceedor=ver1;
                SSD[ver2].distance=distance;
                adj* p=adj_list[ver2]->firstnode;
                while(p!=NULL){
                    if(SSD[p->nodeval].indicator==false){
                        insert(M,H,lastindex_heap,p,ver2,distance+p->weight);
                        lastindex_heap=lastindex_heap+1;
                    }
                    p=p->nextnode;
                }
            }
        }
        if(ref==N-1)break;
    }
    
    for(int i=0;i<N;i++){
        printf("Vertex %d: Length = %d, Path = ",i+1,SSD[i].distance);
        print(SSD,i);
        printf("%d\n",i+1);
    }
    return 0;
}
