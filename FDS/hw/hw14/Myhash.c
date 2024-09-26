#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 1100
int queue[MAX];
int front=-1,rear=-1;
int topS[MAX][MAX];
void enqueue(int data){
    //If Full ...rear = (rear + 1) % MAX...
    queue[++rear]=data;
    if(front==-1){front=0;}
}
int dequeue(){
    //if Empty...front = (front + 1) % MAX_SIZE...
    int data=queue[front];
        if (front == rear) {
            front = rear = -1;
        }
        else{front++;}
    return data;
}

void Topology(int n,int *indeg,int *hashed){
    int known[n];
    memset(known,0,sizeof(known));
    for(int i=0;i<n;i++){
        int index = -1,min=9999999;
        for(int j=0;j<n;j++){
            //Choose the smallest element
            if(!known[j]&&indeg[j]==0){
                if(min>hashed[j]){
                    min=hashed[j];
                    index=j;
                }
            }
        }
    if(index==-1){break;}
    known[index]=1;
    enqueue(hashed[index]);
    for(int j=0;j<n;j++){
        if(!known[j]&&topS[j][index]){
            topS[j][index]=0;
            indeg[j]--;
        }
    }
  }
  int flag=0;
  while(front!=-1){
     int val = dequeue();
     if(val==-1){continue;}
     if(flag){printf(" ");}else{flag=1;}
      printf("%d",val);
    }
}

int main(){
    int n;
    memset(topS,0,sizeof(topS));
    scanf("%d",&n);
    int hashed[n];
    for(int i=0;i<n;i++){
        scanf("%d",&hashed[i]);
    }
    int indeg[n];
    memset(indeg,0,sizeof(indeg));
    for(int i=0;i<n;i++){
        int val = hashed[i];
        if(val==-1){continue;}
        int pos = val%n;
        if(pos!=i){
            indeg[i]=(i-pos+n)%n;
            // Build Topologysort Graph
            //Note i-pos+n Because can 'circle' from tail to head
            for(int j=0;j<indeg[i];j++){
                topS[i][(pos+j)%n]=1;
            }
        }
    }
    Topology(n,indeg,hashed);
}