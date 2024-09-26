#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

Graph ReadGraph(char* file_name){
    Graph G;
    FILE *fp = fopen(file_name, "r");
    if(!fp){
        printf("fail to open file!");
        exit(0);
    }
    char buff[255];
    int flag = 0;
    int a, b, c;
    AdjV pointer;
    G = (Graph)malloc(sizeof(struct GRAPH_NODE));
    if(G == NULL){
        printf("Out of Space!\n");
        exit(1);
    }
    fscanf(fp, "%s", &buff);
    while(strcmp(buff, "sp")){             // find p sp
        fscanf(fp, "%s", &buff);
    }
    fscanf(fp, "%d %d", &a, &b);
    G->nv = a;                              // number of vertex
    G->ne = b;                              // number of edge
    if(G->nv >= MAXNODE){
        printf("Too Much Node! MaxNode = %d, CurrentNode = %d\n", MAXNODE, G->nv);
        exit(0);
    }
    G->List = (AdjList)malloc(sizeof(struct VNode) * (G->nv+1));
    for(int i = 0; i <= G->nv; i++){       // initialize adjlist to NULL
        G->List[i].FirstAdjV = NULL;
    }

    while(strcmp(buff, "a")){             // find a
        fscanf(fp, "%s", &buff);
    }
    
    while(!feof(fp)){                    // read edge
        fscanf(fp, "%d %d %d", &a, &b, &c);
        flag = 0;   
        if (G->List[a].FirstAdjV == NULL){
            G->List[a].FirstAdjV = (AdjV) malloc (sizeof(struct AdjVNode));
            if(G->List[a].FirstAdjV == NULL){
                printf("Out of Space!\n");
                exit(1);
            }
            G->List[a].FirstAdjV->vertex = b;
            G->List[a].FirstAdjV->dist = c;
            G->List[a].FirstAdjV->next = NULL;
        }else{
            pointer = G->List[a].FirstAdjV;
            if(pointer->vertex == b){    // if the edge already exists, update the distance
                pointer->dist = c < pointer->dist ? c : pointer->dist;
                flag = 1;
            }
            while(pointer->next){    // if the edge does not exist, add a new edge
                pointer = pointer->next;
                if(pointer->vertex == b){
                    pointer->dist = c < pointer->dist ? c : pointer->dist;
                    flag = 1;
                }
            }
            if(!flag){  // if the edge does not exist, add a new edge
                pointer->next = (AdjV) malloc (sizeof(struct AdjVNode));
                if(pointer->next == NULL){
                    printf("Out of Space!\n");
                    exit(1);
                }
                pointer->next->vertex = b;
                pointer->next->dist = c;
                pointer->next->next = NULL;
                }
            
        }
        fscanf(fp, "%s", &buff);
    }
    fclose(fp);
    return G;
}

void PrintGraph(Graph G){
    int ne = G->ne;     // number of edge
    int nv = G->nv;     // number of vertex
    printf("nv: %d\nne: %d\n", nv, ne);
    AdjV pointer = NULL;
    for(int i = 1; i <= nv; i++){
        pointer = G->List[i].FirstAdjV;
        printf("%d:", i);
        if(pointer){
            while(pointer){
                printf(" %d", pointer->vertex);
                pointer = pointer->next;
            }
        }else{
            printf("NULL");
        }
        printf("\n");
    }
    return;
}

void CleanGraph(Graph G){
    AdjV pointer1 = NULL;
    AdjV pointer2 = NULL;
    
    for(int i = 1; i <= G->nv; i++){
        pointer1 = G->List[i].FirstAdjV;
        while(pointer1){
            pointer2 = pointer1;
            pointer1 = pointer1->next;
            free(pointer2);
        }
    }
    free(G->List);
    free(G);
    return;
}