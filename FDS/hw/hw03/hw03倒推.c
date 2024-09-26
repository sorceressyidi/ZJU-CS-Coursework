#include<stdio.h>
int main(){
    int MAX,NUM,K;
    scanf("%d %d %d",&MAX,&NUM,&K);
    int stk[MAX];
    int num[NUM];  
    for(int i=0;i<K;i++){
        int top = -1;
        int flag = 1;
        int okay_first = 1;
        int max_num = 1;
        for(int k=0;k<NUM;k++){
            scanf("%d",&num[k]);
        }
        
        for(int j = 0;j<NUM;j++){
            if(top==MAX){flag=0;break;}
            if(top==-1&&num[j] == okay_first){
                okay_first++;
                if(num[j]>max_num){max_num=num[j];}
                continue;
            }
            else{
                if(top>=0 && num[j] == stk[top]){
                    if(num[j]>max_num){max_num=num[j];}
                    top--;
                    continue;
                }
                if(top>=0 && num[j]<stk[top]){flag=0;break;}
                else{
                    if((top+num[j]-max_num+1)>=MAX){flag=0;break;}
                    for(int k=0; k<(num[j]-max_num-1);k++){
                        stk[++top]=max_num+1+k;
                    }
                    max_num = num[j];
                }  
            }
        }
        if(flag==1&&top==-1){printf("Yes\n");}
        else{printf("No\n");}
    }
}
