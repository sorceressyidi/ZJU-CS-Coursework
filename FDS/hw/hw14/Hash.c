#include <stdio.h>

#define MAXN 1010
#define INF 999999

// 全局数组
int e[MAXN][MAXN];
int a[MAXN];
int indegree[MAXN];
int visit[MAXN];
int n, cnt;

// 全局数组定义队列操作
int queue[MAXN];
int front = -1, rear = -1;

// 入队
void enqueue(int value) {
    if (rear == -1) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % MAXN;
    }
    queue[rear] = value;
}

// 出队
int dequeue() {
    int value = queue[front];
    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % MAXN;
    }
    return value;
}

// 拓扑排序
void topSort() {
    for (int i = 0; i < n; i++) {
        int u = -1, min = INF;
        for (int j = 0; j < n; j++) {
            if (visit[j] == 0 && indegree[j] == 0) {
                if (a[j] < min) {
                    min = a[j];
                    u = j;
                }
            }
        }
        if (u == -1)
            break;

        visit[u] = 1;
        enqueue(a[u]);

        for (int v = 0; v < n; v++) {
            if (visit[v] == 0 && e[u][v]) {
                e[u][v] = 0;
                indegree[v]--;
            }
        }
    }

    int flag = 0;
    while (front != -1) {
        int value = dequeue();
        if (value != -1) {
            if (!flag) {
                printf("%d", value);
                flag = 1;
            } else {
                printf(" %d", value);
            }
        }
    }
}

int main() {
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            e[i][j] = 0;
        }
    }

    scanf("%d", &n);
    cnt = n;

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < n; i++) {
        if (a[i] == -1)
            continue;

        int index = a[i] % n;

        if (index != i) {
            indegree[i] = (i - index + n) % n;

            for (int j = 0; j < indegree[i]; j++) {
                e[(index + j) % n][i] = 1;
            }
        }
    }

    topSort();

    return 0;
}
