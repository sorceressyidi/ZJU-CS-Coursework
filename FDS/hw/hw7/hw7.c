#include<stdio.h>
#include<stdlib.h>

int types;
typedef struct disjoint *ds;
struct disjoint{
    int n;
    int *parent;
    int *size;
};
ds Create(int n){
    ds DS =(ds)malloc(sizeof(struct disjoint));
    DS->parent =(int*)malloc((n+1)*sizeof(int));
    DS->size = (int*)malloc((n+1)*sizeof(int));
    for (int i=0;i<=n;i++) {
        DS->parent[i] = i;
        DS->size[i] = 1;
    }
    return DS;
}
void Union(int n1,int n2,ds DS);
void Judge(int n1,int n2,ds DS);
int Find(ds DS,int n){
    int p = DS->parent[n];
    if (p==n){return p;}
    DS->parent[n]=Find(DS,DS->parent[n]);
    return DS->parent[n];
}
int main(){
    scanf("%d",&types);
    ds DS = Create(types);
    while(1){
        char a;
        scanf("%c",&a);
        if(a=='S'){break;}
        int n1,n2;
        scanf("%d %d",&n1,&n2);
        if(a=='C'){
            Judge(n1,n2,DS);
        }
        if(a=='I'){
            Union(n1,n2,DS);
        }
    }
    if(types==1){printf("The network is connected.");}
    else{printf("There are %d components.",types);}
    free(DS->parent);
    free(DS->size);
    return 0;
}
void Union(int n1,int n2,ds DS){
    int n1p = Find(DS,n1);
    int n2p = Find(DS,n2);
    if(n1p==n2p){return;}
    else{
        if(DS->size[n1p]<DS->size[n2p]){
            DS->parent[n1p]=n2p;
            DS->size[n2p]+=DS->size[n1p];
        }
        else{
            DS->parent[n2p]=n1p;
            DS->size[n1p]+=DS->size[n2p];
        }
    }
    types--;
}
void Judge(int n1,int n2,ds DS){
    int n1p = Find(DS,n1);
    int n2p = Find(DS,n2);
    if(n1p==n2p){printf("yes\n");}
    else{printf("no\n");}
}