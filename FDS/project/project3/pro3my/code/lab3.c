#include<stdio.h>
#include<stdlib.h>
#include <limits.h>

// Struct definition: Adjacent node
struct nei {
    int distance;  // Weight of the edge
    int index;      // Index of the target vertex
};
// Struct definition: Vertex of the graph
struct ver {
    int distance;     // Shortest path length from the source to this node
    struct nei *list;  // Adjacency list, storing information about adjacent vertices
    int neinum;        // Number of vertices adjacent to this node
    int known;         // Whether this node has been processed
};
// Function definition: Find the minimum distance among unknown nodes
int findshortest(struct ver* Graph, int vertice) {
    int min = INT_MAX;
    for(int i = 0; i < vertice; i++) {
        // Unprocessed node with a smaller distance
        if(Graph[i].distance >= 0 && Graph[i].distance <= min && (!Graph[i].known)) {
            min = Graph[i].distance;
        }
    }
    return min; // return the minimum distance
}
// Function definition: Dijkstra's algorithm to find the shortest path
void Dijkstra(struct ver* Graph, int vertice, int *a) {
    int source = a[0];               // Set the source vertex of the shortest path problem to be first element of the input sequence.
    Graph[source - 1].distance = 0;  // Set the distance from the source node to itself as 0

    // Traverse all nodes
    for(int i = 0; i < vertice; i++) {
        int min = findshortest(Graph, vertice); //find the shortest distance at the current state between the source vertex and the unknown vertices.
        int vertex = a[i] - 1;

        // If the distance of the current node is invalid or greater than the minimum distance, output No and return
        if(Graph[vertex].distance < 0 || Graph[vertex].distance > min) {
            printf("No\n");
            return;
        }

        Graph[vertex].known = 1;  // Mark the current node as processed
        int cnt = Graph[vertex].neinum; // get the count of the neighbours of the processing vertex

        // Update the distance of adjacent nodes
        for(int j = 0; j < cnt; j++) {
            int neighbour = Graph[vertex].list[j].index; 
            int distance = Graph[vertex].list[j].distance;

            if(!Graph[neighbour].known) {
                // If the distance from the current node to the adjacent node is smaller, update the distance
                if(Graph[vertex].distance + distance < Graph[neighbour].distance || Graph[neighbour].distance < 0) {
                    Graph[neighbour].distance = Graph[vertex].distance + distance;
                }
            }
        }
    }

    printf("Yes\n"); // No violations OUTPUT Yes
    return;
}
int main() {
    int vertice, edge;
    scanf("%d %d", &vertice, &edge); // get the number of vertices and edges in the weighted undirected graph

    // Initialization of the array of graph vertices
    struct ver Graph[vertice];
    for(int i = 0; i < vertice; i++) {
        Graph[i].neinum = 0;        //initialize the number of neighbours to be zero
        Graph[i].list = (struct nei*)malloc(vertice * sizeof(struct nei));
    }
    // Input information about edges and build the adjacency list
    for(int i = 0; i < edge; i++) {
        int from, to, distance;
        scanf("%d %d %d", &from, &to, &distance); //get the information of an edge
        // initialize edge <from,to>
        int index = Graph[from - 1].neinum;
        Graph[from - 1].neinum++;
        Graph[from - 1].list[index].distance = distance;
        Graph[from - 1].list[index].index = to - 1;
        //initialize edge <to,from>
        index = Graph[to - 1].neinum;
        Graph[to - 1].neinum++;
        Graph[to - 1].list[index].distance = distance;
        Graph[to - 1].list[index].index = from - 1;
    }
    int cnt;
    scanf("%d", &cnt);
    // Process multiple queries
    while(cnt--) {
        int a[vertice];
        for(int i = 0; i < vertice; i++) {
            scanf("%d", &a[i]);
        }

        // Initialize the distances and processing status of the vertices
        for(int i = 0; i < vertice; i++) {
            Graph[i].distance = -1;
            Graph[i].known = 0;
        }
        // Call Dijkstra's algorithm
        Dijkstra(Graph, vertice, a);
    }
    // Free allocated memory
    for(int i = 0; i < vertice; i++) {
        free(Graph[i].list);
    }
    return 0;
}
