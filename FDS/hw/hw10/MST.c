#include<stdio.h>
#include<stdlib.h>
typedef struct {
    int ver1;
    int ver2;
    int distance;
    int istree;
}edge;
int father[600];
int cmpfunc(const void *a, const void *b) {
    return ((edge *)a)->distance - ((edge *)b)->distance;
}
int find(int x) {
    if(father[x]<0){return x;}
    else return father[x] = find(father[x]);
}
int main(){
    int vertex,edges;
    scanf("%d %d",&vertex,&edges);
    edge Graph[edges];
    for(int i=0;i<edges;i++){
        scanf("%d",&Graph[i].ver1);
        scanf("%d",&Graph[i].ver2);
        scanf("%d",&Graph[i].distance);
        Graph[i].istree=0;
    }
    qsort(Graph,edges,sizeof(edge),cmpfunc);
    for(int i=1;i<=vertex;i++){
        father[i]=-1;
    }
    int j=0;
    int cnt = 0;
    int dist =0;
    int flag=1;
    for (int i=0; i<edges;i=j) {
        for (j=i;j<edges&&Graph[j].distance==Graph[i].distance; j++){
            if (find(Graph[j].ver1) != find(Graph[j].ver2)){
                Graph[j].istree = 1;
            }
        }
        for(int k=i;k<j;k++){
            if (find(Graph[k].ver1) != find(Graph[k].ver2)){
                Graph[k].istree=1;
                dist += Graph[k].distance;
                int root1 = find(Graph[k].ver1);
                int root2 = find(Graph[k].ver2);
                if (father[root1] <= father[root2]) {
                    father[root1] += father[root2];
                    father[root2] = root1;
                } else {
                    father[root2] += father[root1];
                    father[root1] = root2;
                }
                cnt++;
            } 
            else if(Graph[k].istree) {
                flag = 0;
            }
        } 
    }
    
    if(cnt==vertex-1){
        printf("%d\n",dist);
        if(flag){
            printf("Yes");
        }
        else{printf("No");}
    }
    else{
        printf("No MST\n");
        printf("%d",vertex-cnt);
}
    return 0;
}

