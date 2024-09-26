#include<stdio.h>
int main(){
    int MAX,NUM,K;
    scanf("%d %d %d",&MAX,&NUM,&K);
    int pop_fini[NUM];
    int stk[MAX];
    for(int i=0;i<K;i++){
        int pointer = -1;
        int flag = 1;
        for(int j =0;j<NUM;j++){scanf("%d",&pop_fini[j]);}
        for(int k=0,m=1,q=0;k<NUM;k++){
            if(pointer==MAX-1){flag=0;break;}
            stk[++pointer]=m;
            m++;
            while(stk[pointer]==pop_fini[q]){
                q++;
                pointer--;
                if(pointer == -1){break;}
            }
        }
        if(flag&&pointer==-1){printf("YES\n");}
        else{printf("NO\n");}
    }
}