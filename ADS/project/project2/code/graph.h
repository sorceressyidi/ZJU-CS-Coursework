#ifndef __GRAPH_H__
#define __GRAPH_H__

#define MAXNODE 500000

typedef struct AdjVNode* AdjV;
struct AdjVNode{                    // marks which vertex it is and points to next
    int vertex;
    int dist;
    AdjV next;
};

typedef struct VNode{               // points to the adjacent vertex of the given vertex
    AdjV FirstAdjV;
} *AdjList ;                // AdjList[i] means the adjacent list for the ith vertex

typedef struct GRAPH_NODE* Graph;
struct GRAPH_NODE{
    int nv;                         // number of vertice
    int ne;                         // number of edges
    AdjList List;                   // Adjacent list
};

Graph ReadGraph(char* file_name);
void PrintGraph(Graph G);
void CleanGraph(Graph G);

#endif



