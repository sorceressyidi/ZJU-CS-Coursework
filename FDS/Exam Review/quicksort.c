void Quicksort(int a[],int n){
    qsort(A,0,n-1);
}
int median3(int a[],int left,int right){
    int center = (left+right)/2;
    if(a[left]>a[center]){Swap(&a[left],&a[center]);}
    if(a[left]>a[right]){Swap(&a[left],&a[right]);}
    if(a[center]>a[right]){swap(&a[center],&a[right]);}
    swap(&a[center],&a[right-1]);
    return A[right-1];
}
void Qsort(int a[],int left,int right){
    int i,j;
    if(left+cutoff <=right){
        pivot=Median3(A,left,right);
        i=left;
        j=right-1;
        while(1){
            while(a[++i]<pivot){}
            while(a[--j]>pivor){}
            if(i<j){swap(&a[i],&a[j]);}
            else{break;}
        }
        swap(&a[i],&a[right-1]);
        Qsort(a,left,i-1);
        Qsort(a,i+1,right);
    }
}