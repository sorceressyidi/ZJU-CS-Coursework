#include<stdio.h>
int G[300][300];
int V[300];
int main(){
    for(int i=0;i<300;i++){
        for(int j=0;j<300;j++){
            G[i][j]=0;
        }
    }
    
    int ver,edg;
    scanf("%d %d",&ver,&edg);
    for(int i=0;i<edg;i++){
        int m,n;
        scanf("%d %d",&m,&n);
        G[m][n]=G[n][m]=1;
    }
    int cnt;
    scanf("%d",&cnt);
    while(cnt--){
        int num;
        scanf("%d",&num);
        int hamilton[num];
        for(int i=0;i<num;i++){
            scanf("%d",&hamilton[i]);
            V[hamilton[i]]=0;
        }
        if(num!=(ver+1)){printf("NO\n");continue;}     
        else{
            if(hamilton[0]!=hamilton[ver]){
                printf("NO\n");
                continue;
            }
            else{
                int flag=1;
                for(int i=0;i<ver;i++){
                    int m = hamilton[i];
                    int n = hamilton[i+1];
                    if(G[m][n]!=1||V[hamilton[i]]!=0){printf("NO\n");flag=0;break;}
                    V[hamilton[i]]++;
                }
                if(!flag){continue;}
              }
            }
        printf("YES\n");
        }
    return 0;
}
//需要用Vertice不重复再加constrain判断