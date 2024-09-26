#define MAX_SIZE 1000
int data[MAX_SIZE];
int top = -1;
int index[MaxVertices];
int low[MaxVertices];
int onStack[MaxVertices];
int time = 0;
void InitStack() {
    top = -1;
}
void Push(int value) {
    if (top < MAX_SIZE - 1) {
        data[++top] = value;
    } else {
        printf("Stack overflow\n");
    }
}
int Pop() {
    if (top >= 0) {
        return data[top--];
    } else {
        printf("Stack underflow\n");
        return -1;  // 返回一个特殊值表示栈为空
    }
}
int IsStackEmpty() {
    return top == -1;
}
void TarjanDFS(Graph G, int u, void (*visit)(Vertex V)) {
    index[u] = low[u] = ++time;
    Push(u);
    onStack[u] = 1;
    PtrToVNode adjNode = G->Array[u];
    while (adjNode != NULL) {
        int v = adjNode->Vert;

        if (index[v] == -1) {
            TarjanDFS(G, v, visit);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];
        } else if (onStack[v]) {
            low[u] = (low[u] < index[v]) ? low[u] : index[v];
        }

        adjNode = adjNode->Next;
    }

    if (index[u] == low[u]) {
        while (!IsStackEmpty()) {
            int v = Pop();
            onStack[v] = 0;
            visit(v);
            if (u == v) break;
        }
        printf("\n");
    }
}

void StronglyConnectedComponents(Graph G, void (*visit)(Vertex V)) {
    for (int i = 0; i < G->NumOfVertices; i++) {
        index[i] = -1;
        low[i] = -1;
        onStack[i] = 0;
    }
    for (int i = 0; i < G->NumOfVertices; i++) {
        if (index[i] == -1) {
            TarjanDFS(G, i, visit);
        }
    }

}
