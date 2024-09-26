#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

Table InitialTable(Graph G){
    Table T;
    T = (struct TableEntry**)malloc(sizeof(struct TableEntry*) * (G->nv+1));
    for(int i = 1; i <= G->nv; i++){
        T[i] = (struct TableEntry*)malloc(sizeof(struct TableEntry));
        if(T[i] == NULL){
            printf("Out of space!\n");
            exit(1);
        }
        T[i]->FirstAdjV = G->List[i].FirstAdjV;
        T[i]->Dist = -1;                        // -1 for infinity
        T[i]->Path = -1;                        // -1 for no path
        T[i]->Known = 0;                        // 0 for unknown, 1 for known
    }
    return T;
}

void CleanTable(Graph G, Table T){
    for(int i = 1; i <= G->nv; i++){
        free(T[i]);
        T[i] = NULL;
    }
    free(T);
    return;
}

void PrintPath(Table T, int vertex, int start){            // print path from the given vertex to the target
    printf("vertex %d: Dist = %d, Path = %d", vertex, T[vertex]->Dist, start);
    printpa(T, vertex);
    printf("\n");
}

void printpa(Table T, int vertex){              // sub fuction called by PrintPath, recursively print
    if(T[vertex]->Dist == 0){
        return;
    }else if(T[vertex]->Path == -1){
        printf("No Path!");
        return;
    }else{
        printpa(T, T[vertex]->Path);
        printf(" -> ");
        printf("%d", vertex);
    }
}


Table dijkstra_pair(Table T, int start){

    PairHeap Heap = NULL;                          // Heap
    PairNode Min;                           // stores the vertex with minimal dist
    PairNode VPointer[MAXNODE];             // points to the position of the vertex in heap
    T[start]->Dist = 0;
    AdjV pointer = NULL;
    int new_dist = 0;
    int min_dist = 0;
    int min_v = 0;
    VPointer[start] = InitialPairHeap(0, start);    // insert the start node    
    Heap = PairInsert(Heap, VPointer[start]);
    while(!IsPairEmpty(Heap)){
        Min = Heap;                         // Heap is also the minimal node of the heap
        min_dist = Min->value;              // record info of the minimal vertex
        min_v = Min->vertex;
        // printf("%d %d\n", min_dist, min_v);
        Heap = PairDeleteMin(Heap);         // remove the minimal
        T[min_v]->Known = 1;
        pointer = T[min_v]->FirstAdjV;
        while(pointer)
        {
            
            if(!T[pointer->vertex]->Known){             // if the minimal dist hasn't been found
                
                new_dist = pointer->dist + min_dist;
        
                if(T[pointer->vertex]->Dist == -1){     // if the vertex isn't in heap

                    VPointer[pointer->vertex] = InitialPairHeap(new_dist, pointer->vertex);
                    Heap = PairInsert(Heap, VPointer[pointer->vertex]);     // insert to heap
                    T[pointer->vertex]->Dist = new_dist;
                    T[pointer->vertex]->Path = min_v;                 // update dist and path
                    
                }else if(T[pointer->vertex]->Dist > new_dist){    // if dist of new path is less

                    Heap = PairDecrease(Heap, VPointer[pointer->vertex], new_dist);
                    T[pointer->vertex]->Dist = new_dist;
                    T[pointer->vertex]->Path = min_v;

                }
                
            }
            pointer = pointer->next;
            
        }
    }
    return T;
}

Table dijkstra_bin(Table T, int start){

    BinNode Heap = NULL;                          // Heap
    BinNode Min;                           // stores the vertex with minimal dist
    BinNode VPointer[MAXNODE];             // points to the position of the vertex in heap
    T[start]->Dist = 0;

    AdjV pointer = NULL;
    int new_dist = 0;
    int min_dist = 0;
    int min_v = 0;

    VPointer[start] = newBinNode(0, start);    // insert the start node    
    Heap = BinInsert(Heap, VPointer[start]);

    while(!IsBinEmpty(Heap)){
        BinNode* Mmin = BinGetMin2(Heap);    // get the minimal vertex
        Min = Mmin[1];
        min_dist = Min->value;              // record info of the minimal vertex
        min_v = Min->vertex;

        // printf("%d %d\n", min_dist, min_v);
        Heap = BinDeleteMin(Heap);         // remove the minimal
        T[min_v]->Known = 1;
        pointer = T[min_v]->FirstAdjV;
        while(pointer)
        {
            
            if(!T[pointer->vertex]->Known){             // if the minimal dist hasn't been found
                
                new_dist = pointer->dist + min_dist;
        
                if(T[pointer->vertex]->Dist == -1){     // if the vertex isn't in heap

                    VPointer[pointer->vertex] = newBinNode(new_dist, pointer->vertex);
                    Heap = BinInsert(Heap, VPointer[pointer->vertex]);     // insert to heap
                    
                    T[pointer->vertex]->Dist = new_dist;
                    T[pointer->vertex]->Path = min_v;                 // update dist and path
                    
                }else if(T[pointer->vertex]->Dist > new_dist){    // if dist of new path is less

                    BinDecrease(VPointer[pointer->vertex], new_dist,VPointer);
                    T[pointer->vertex]->Dist = new_dist;
                    T[pointer->vertex]->Path = min_v;

                }
                
            }
            pointer = pointer->next;
            
        }
    }
    return T;
}

Table dijkstra_fib(Table T, int start){

    FibHeap fibheap=InitialHeap();
    FibNode Min;
    FibNode VPointer[MAXNODE];
    T[start]->Dist = 0;

    AdjV pointer = NULL;
    int new_dist = 0;
    int min_dist = 0;
    int min_v = 0;
    VPointer[start] =InitialFibNode(0, start);    // insert the start node    
    FibInsertNode(fibheap, VPointer[start]);

    while(fibheap->min){
        Min = fibheap->min;

        min_dist = Min->value;              // record info of the minimal vertex
        min_v = Min->vertex;

        FibDeleteMin(fibheap);         // remove the minimal
        T[min_v]->Known = 1;
        pointer = T[min_v]->FirstAdjV;
        while(pointer)
        {
            
            if(!T[pointer->vertex]->Known){             // if the minimal dist hasn't been found
                
                new_dist = pointer->dist + min_dist;
        
                if(T[pointer->vertex]->Dist == -1){     // if the vertex isn't in heap

                    VPointer[pointer->vertex] = InitialFibNode(new_dist, pointer->vertex);
                    FibInsertNode(fibheap, VPointer[pointer->vertex]);     // insert to heap
                    
                    T[pointer->vertex]->Dist = new_dist;
                    T[pointer->vertex]->Path = min_v;                 // update dist and path
                    
                }else if(T[pointer->vertex]->Dist > new_dist){    // if dist of new path is less

                    FibDecrease(fibheap,VPointer[pointer->vertex], new_dist);
                    T[pointer->vertex]->Dist = new_dist;
                    T[pointer->vertex]->Path = min_v;

                }
                
            }
            pointer = pointer->next;
            
        }
    }
    return T;
}

Table dijkstra_bf(Table T, int start, Graph G){
    int Min;                                    // stores interim min vertex
    T[start]->Dist = 0;
    T[start]->Known = 1;
    AdjV pointer = NULL;
    int new_dist = 0;
    int min_dist = 0;
    int min_v = 0;

    pointer = T[start]->FirstAdjV;
    while(pointer){                             // initialization
        T[pointer->vertex]->Dist = pointer->dist;
        T[pointer->vertex]->Path = start;
        pointer = pointer->next;
    }
    int n = 0;
    while(1){
        Min = 0;
        min_dist = 0;
        for(int i = 1; i <= G->nv; i++){      // find vertex with minimal dist to Known Set
            if(!T[i]->Known && T[i]->Dist!=-1){
                if(min_dist == 0 ||T[i]->Dist < min_dist){
                    Min = i;
                    min_dist = T[i]->Dist;
                }
            }
        }
        
        if(!Min){               // all vertice are known
            break;
        }

        min_v = Min;
        T[min_v]->Known = 1;
        pointer = T[min_v]->FirstAdjV;
        while(pointer)
        {
            
            if(!T[pointer->vertex]->Known){             // if the minimal dist hasn't been found
                
                new_dist = pointer->dist + min_dist;
        
                if(T[pointer->vertex]->Dist == -1 || T[pointer->vertex]->Dist > new_dist){                  
                    T[pointer->vertex]->Dist = new_dist;
                    T[pointer->vertex]->Path = min_v;                 // update dist and path
                    
                }  
            }
            pointer = pointer->next;
        }
        n++;
    }
    return T;
}

Table dijkstra_min(Table T, int start, Graph G){

    minHeap Mheap=MinInitialHeap(G->nv+1);
    MNode Min;
    MNode VPointer[G->nv+1];
    T[start]->Dist = 0;

    AdjV pointer = NULL;
    int new_dist = 0;
    int min_dist = 0;
    int min_v = 0;
    VPointer[start] =InitialMinNode(Mheap,0,start);
    MinInsertNode(Mheap,VPointer[start]);    // insert the start node    

    while(Mheap->currentsize){
        //FibNode* min_nodes = &(fibheap->min);    // get the minimal node
        Min = Mheap->h[1];

        min_dist = Min->value;              // record info of the minimal vertex
        min_v = Min->vertex;

        // printf("%d %d\n", min_dist, min_v);
        MinDeleteMin(Mheap);         // remove the minimal
        T[min_v]->Known = 1;
        pointer = T[min_v]->FirstAdjV;
        while(pointer)
        {
            
            if(!T[pointer->vertex]->Known){             // if the minimal dist hasn't been found
                
                new_dist = pointer->dist + min_dist;
        
                if(T[pointer->vertex]->Dist == -1){     // if the vertex isn't in heap

                    VPointer[pointer->vertex] = InitialMinNode(Mheap, new_dist,pointer->vertex);
                    MinInsertNode(Mheap,VPointer[pointer->vertex]);    // insert the start node 
                    T[pointer->vertex]->Dist = new_dist;
                    T[pointer->vertex]->Path = min_v;                 // update dist and path
                    
                }else if(T[pointer->vertex]->Dist > new_dist){    // if dist of new path is less

                    MinDecrease(Mheap,VPointer[pointer->vertex], new_dist);
                    T[pointer->vertex]->Dist = new_dist;
                    T[pointer->vertex]->Path = min_v;

                }
                
            }
            pointer = pointer->next;
            
        }
    }
    return T;
}