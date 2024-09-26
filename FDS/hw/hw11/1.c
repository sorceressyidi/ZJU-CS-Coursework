#define MAX_SIZE 1000
int stk[MAX_SIZE];
int top = -1;
int index[MaxVertices];
int low[MaxVertices];
int yes[MaxVertices];
int posi = 0;
void push(int value) {
    if (top < MAX_SIZE - 1) {
        stk[++top] = value;
    } else {
        printf("overflow\n");
    }
}
int pop() {
    if (top >= 0) {
        return stk[top--];
    } else {
        printf("underflow\n");
    }
}
void TarjanDFS(Graph G, int u, void (*visit)(Vertex V)) {
    index[u] = low[u] = ++posi;
    push(u);
    yes[u] = 1;
    PtrToVNode node = G->Array[u];
    while (node != NULL) {
        int v = node->Vert;
        if (index[v] == -1) {
            TarjanDFS(G, v, visit);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];
        } else if (yes[v]) {
            low[u] = (low[u] < index[v]) ? low[u] : index[v];
        }
        node = node->Next;
    }
    if (index[u] == low[u]) {
        while (top != -1) {
            int v = pop();
            yes[v] = 0;
            visit(v);
            if (u == v) break;
        }
        printf("\n");
    }
}
void StronglyConnectedComponents(Graph G, void (*visit)(Vertex V)) {
    memset(index, -1, sizeof(index));
    memset(low, -1, sizeof(low));
    memset(yes, 0, sizeof(yes));
    for (int i = 0; i < G->NumOfVertices; i++) {
        if (index[i] == -1) {
            TarjanDFS(G, i, visit);
        }
    }
}
