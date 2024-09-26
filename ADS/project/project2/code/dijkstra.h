#include "graph.h"
#include "pairheap.h"
#include "binomial.h"
#include "FibHeap.h"
#include "MinHeap.h"

#ifndef __DIJKSTRA_H__
#define __DIJKSTRA_H__

struct TableEntry{
    AdjV FirstAdjV;
    int Known;          // whether or not the least distance is found
    int Dist;           // dist to the target
    int Path;           // the vertex which finds it.
};
typedef struct TableEntry* *Table;      // Table[i] stores the info for path of the i th vertex to the target

Table dijkstra_pair(Table T, int start);         // run dijkastra in pairingheap, store the info in table T
Table dijkstra_bin(Table T, int start);          // run dijkastra in binomialheap, store the info in table T
Table dijkstra_fib(Table T, int start);          // run dijkastra in Fibheap, store the info in table T
Table dijkstra_min(Table T, int start, Graph G);          // run dij with common min heap
Table dijkstra_bf(Table T, int start, Graph G);  // brute force
void PrintPath(Table T, int vertex, int start); // print path to a given vertex
void printpa(Table T, int vertex);              // subfunc called by PrintPath
Table InitialTable(Graph G);            // initialize table
void CleanTable(Graph G, Table T);              // free memory of table
#endif