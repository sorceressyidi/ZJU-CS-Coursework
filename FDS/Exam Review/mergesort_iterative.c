#include <stdio.h>
void CopyArray(int B[],int iBegin,int iEnd,int A[]);
void Merge (int A[],int ileft,int iright,int iend,int B[]);
int min(int a,int b){
    if(a<=b){return a;}
    return b;
}
void BottomupMergeSort(int A[],int B[],int n){
   for(int width=1;width<n;width=width*2){
           for(int i=0;i<n;i=i+2*width){
                Merge(A,i,min(i+width,n),min(i+2*width,n),B);
           }
           CopyArray(B,0,n,A);
    }
}

void Merge (int A[],int ileft,int iright,int iend,int B[]){
     int i=ileft,j=iright;
    for(int k=ileft;k<iend;k++){
         if(i<iright&&(j>=iend||A[i]<=A[j])){
            B[k]=A[i++];
         }
         else{B[k]=A[j++];}
    }
}
int main(void)
{
    int n;
    scanf("%d", &n);
    int a[n];
    int b[n];
    for ( int i=0; i<n; i++ ) {
        scanf("%d", &a[i]);
    }
    BottomupMergeSort(a,b,n);
    for ( int i=0; i<n; i++ ) {
        printf("%d  ", a[i]);
    }
}
void CopyArray(int B[],int begin,int end,int A[]){
    for(int i=begin;i<end;i++){
        A[i]=B[i];
    }
}