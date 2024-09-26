#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

#define MAX_VERTEX 1100
#define MAX_EDGE 600

typedef struct {
    char name[4];
}vertex;
typedef struct Edge{
    int to;
    int cap;
    int flow;
    struct Edge* next;
}edge;

int my_min(int a, int b) {
    return a < b ? a : b;
}

int vertexnum = 0;
int parent[MAX_VERTEX];
vertex GRAPH[MAX_VERTEX];
edge* EDGE[MAX_EDGE];

int find(const char* name);
void addEdge(int from,int to,int cap);
int Edmonds_Karp(int source, int dest);
int main(){
    vertex start,end;
    int n;
    scanf("%s %s %d",start.name,end.name,&n);
    int index_start = find(start.name);
    int index_end = find(end.name);
    for(int i=0;i<n;i++){
        vertex v1,v2;
        int cap;
        scanf("%s %s %d",v1.name,v2.name,&cap);
        int index1 = find(v1.name);
        int index2 = find(v2.name);
        addEdge(index1,index2,cap);
    }
    int re = Edmonds_Karp(index_start, index_end);
    printf("%d\n", re);
    for(int i=0;i<vertexnum;i++){
        edge* current = EDGE[i];
        while(current){
            edge* tmp = current;
            current = current->next;
            free(tmp);
        }
    }
    return 0;
}
int find(const char* name){
    for(int i=0;i<vertexnum;i++){
        if(strcmp(GRAPH[i].name,name)==0){
            return i;
        }
    }
    if(vertexnum < MAX_VERTEX){
        strcpy(GRAPH[vertexnum].name,name);
        return vertexnum++;
    }
    else{
        fprintf(stderr, "Error: Maximum number of vertices reached.\n");
        exit(EXIT_FAILURE);
    }
}
void addEdge(int from,int to,int cap){
    edge* e=(edge*)malloc(sizeof(edge));
    e->to=to;
    e->cap=cap;
    e->flow = 0;
    e->next = EDGE[from];
    EDGE[from]=e;

    e = (edge*)malloc(sizeof(edge));
    e->to  =from;
    e->cap =0;
    e->flow = 0;
    e->next = EDGE[to];
    EDGE[to] = e;
}

int Edmonds_Karp(int source, int dest){
    int flow = 0;
    while(1){
        memset(parent, -1, sizeof(parent));
        parent[source] = source;
        int queue[MAX_VERTEX];
        int front = 0, rear = 0;
        queue[rear++] = source;
        int foundPath = 0;
        while (front < rear) {
            int current = queue[front++];
            for (edge* e = EDGE[current]; e != NULL; e = e->next) {
                if (parent[e->to] == -1 && e->cap > e->flow) {
                    parent[e->to] = current;
                    queue[rear++] = e->to;
                    if (e->to == dest) {
                        foundPath = 1;
                        break;
                    }
                }
            }
            if (foundPath) {
                break;
            }
        }
        if (!foundPath) {
            break;
        }
        int pathFlow = INT_MAX;
        //First find the previous vertex and find the edge among all the neighbour edges of that vertex for it.
        for (int i = dest; i != source; i = parent[i]) {
            for (edge* e = EDGE[parent[i]]; e != NULL; e = e->next) {
                if (e->to == i) {
                    pathFlow = my_min(pathFlow, e->cap - e->flow);
                    break;
                }
            }
        }

        for (int i = dest; i != source; i = parent[i]) {
            for (edge* e = EDGE[parent[i]]; e != NULL; e = e->next) {
                if (e->to == i) {
                    e->flow += pathFlow;
                    break;
                }
            }

            for (edge* e = EDGE[i]; e != NULL; e = e->next) {
                if (e->to == parent[i]) {
                    e->flow -= pathFlow;
                    break;
                }
            }
        }
        flow += pathFlow;
    }

    return flow;
}
