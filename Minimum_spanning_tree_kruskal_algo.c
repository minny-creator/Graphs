#include <stdio.h>
#include <stdlib.h>

typedef struct edge{
    int ver1;
    int ver2;
    int weight;
}edge;

typedef struct node{
    int key;
    int value;
}node;

int main(){
    int N,M;
    scanf("%d",&N);
    scanf("%d",&M);
    int arr[N];
    edge MST[N-1];
    edge edges[M];
    //intializing various connected components
    for(int i=0;i<N;i++){
        arr[i]=i;
    }
    //storing edges
    for(int i=0;i<M;i++){
        int a,b,w;
        scanf("%d %d %d",&a,&b,&w);
        edges[i].ver1=a;
        edges[i].ver2=b;
        edges[i].weight=w;
    }
    //sorting of edges using BST
    int a,b;
    if(edges[0].weight>edges[1].weight){
        int ver1=edges[0].ver1;
        int ver2=edges[0].ver2;
        int weight=edges[0].weight;
        edges[0].ver1=edges[1].ver1;
        edges[0].ver2=edges[1].ver2;
        edges[0].weight=edges[1].weight;
        edges[1].ver1=ver1;
        edges[1].ver2=ver2;
        edges[1].weight=weight;
    }
    for(int i=2;i<M;i++){
        a=0;
        b=i-1;
        int ref=edges[i].weight;
        if(ref>=edges[b].weight)continue;
        while(b!=a+1){
            if(edges[(a+b)/2].weight>ref){
                b=(a+b)/2;
            }
            else{
                a=(a+b)/2;
            }
        }
        int ver1,ver2,weight;
        if(ref<edges[0].weight){
            ver1=edges[0].ver1;
            ver2=edges[0].ver2;
            weight=edges[0].weight;
            edges[0].ver1=edges[i].ver1;
            edges[0].ver2=edges[i].ver2;
            edges[0].weight=edges[i].weight;
            a=0;
            b=1;
        }
        else{
            ver1=edges[i].ver1;
            ver2=edges[i].ver2;
            weight=edges[i].weight;
        }
        while(b!=(i+1)){
            int vert1=edges[b].ver1;
            int vert2=edges[b].ver2;
            int wei=edges[b].weight;
            edges[b].ver1=ver1;
            edges[b].ver2=ver2;
            edges[b].weight=weight;
            ver1=vert1;
            ver2=vert2;
            weight=wei;
            b=b+1;
        }
    }
    int ref=0;
    for(int i=0;i<M;i++){
        int vert1=edges[i].ver1;
        int vert2=edges[i].ver2;
        int wei=edges[i].weight;
        int p=0,q=0;
        while(vert1-1!=arr[vert1-1]){
            vert1=arr[vert1-1]+1;
            p=p+1;
        }
        while(vert2-1!=arr[vert2-1]){
            vert2=arr[vert2-1]+1;
            q=q+1;
        }
        if(vert1==vert2){
            continue;
        }
        if(p>q){
            arr[vert2-1]=vert1-1;
        }
        else{
            arr[vert1-1]=vert2-1;
        }
        MST[ref]=edges[i];
        ref=ref+1;
        if(ref==N-1)break;
    }
    printf("Edges in MST:\n");
    ref=0;
    for(int i=0;i<(N-1);i++){
        printf("(%d, %d) weight = %d\n",MST[i].ver1,MST[i].ver2,MST[i].weight);
        ref=ref+MST[i].weight;
    }
    printf("Total Weight = %d\n",ref);
}