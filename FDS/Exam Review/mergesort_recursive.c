void Mergesort( ElementType A[ ], int N );
void MSort( ElementType A[ ], ElementType TmpArray[ ],int Left,int Right);
void Merge( ElementType A[ ], ElementType TmpArray[ ],int Lpos,int Rpos, int RightEnd);

void Mergesort(ElementType A[],int N){
    ElementType *TmpArray;
    TmpArray=malloc(N*sizeof(ElemenType));
    if(TmpArray!=Null){
        Msort(A,TmpArray,0,N-1);
        free(TmpArray);
    }
    else{FatalError("No space for tmp array!!");}
}
void MSort( ElementType A[ ], ElementType TmpArray[ ],int Left,int Right){
    int center;
    if(Left<Right){
        center=(Left+Right)/2;
        Msort(A,TmpArray,Left,center);
        Msort(A,TmpArray,center+1,Right);
        Merge(A,TmpArray,Left,center+1,Right);
    }
}
void Merge( ElementType A[ ], ElementType TmpArray[ ],int Lpos,int Rpos, int RightEnd){
    int i,LeftEnd,numelements,TmpPos;
    LeftEnd=Rpos-1;
    TmpPos=Lpos;
    numElements=RightEnd-Lpos+1;
    while(Lpos<=LeftEnd&&Rpos<=RightEnd){
        if(A[Lpos]<=A[Rpos]){TmpArray[TmpArray++]=A[Lpos++];}
        else{TmpArray[TmpPos++]=A[Rpos++];}
    }
    while(Lpos<=LeftEnd){TmpArray[TmpPos++]=A[Lpos++];}
    while(Rpos<=RightEnd){TmpArray[TmpPos++]=A[Rpos++];}
    for(int i=0;i<numelements;i++;RightEnd--){
        A[RightEnd]=TmpArray[RightEnd];
    }
}
