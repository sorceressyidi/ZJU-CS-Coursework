#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dijkstra.h"


void test(char* filename, int sample);         //filename is the name of the dataset, sample is the number of times you want to run dijkstra. Return value is the average time     
double test_common(Graph G, int target, int print);
double test_pair(Graph G, int target, int print);
double test_bin(Graph G, int target, int print);
double test_fib(Graph G, int target, int print);
double test_bf(Graph G, int target, int print);

int main(){
    int sample = 10;            // how many vertice you want to sample in a graph
    test("50data.gr", sample);  // dataset name, sample number. The printed test time is the average time of all samples
    // test("100data.gr", sample);
    // test("500data.gr", sample);
    // test("1000data.gr", sample);
    // test("5000data.gr", sample);
    // test("10000data.gr", sample);
    // test("50000data.gr", sample);
    // test("100000data.gr", sample);
    // test("150000data.gr", sample);
    // test("200000data.gr", sample);
    // test("250000data.gr", sample);
    // test("USA-road-d.NY.gr", sample);
    // test("USA-road-d.BAY.gr", sample);
    printf("Finish!!!\n");
    return 0;
}



void test(char* filename, int sample){
    Graph G = NULL;
    double time_pair = 0;
    double time_fib = 0;
    double time_bin = 0;
    double time_com = 0;
    double time_bf = 0;
    G = ReadGraph(filename);
    if(sample > G->nv){
        printf("sample is too large!\n");
        exit(0);
    }
    printf("test for graph with %d vertice, %d edges, %d samples: \n", G->nv, G->ne, sample);
    // PrintGraph(G);
    int n = 0;
    int factor = G->nv / sample;
    for(n = 1; n*factor <= G->nv; n++){
        time_pair += test_pair(G, n*factor, 0);
        time_bin += test_bin(G, n*factor, 0);
        time_com += test_common(G, n*factor, 0);
        time_fib += test_fib(G, n*factor, 0);
        // time_bf += test_bf(G, n*factor, 0);
    }
    n--;

    printf("average time: \n");
    printf("PairHeap: %f ms\n", time_pair/n);
    printf("BinHeap: %f ms\n", time_bin/n);
    printf("ComHeap: %f ms\n", time_com/n);
    printf("FibHeap: %f ms\n", time_fib/n);
    // printf("BruteForce: %f ms\n", time_bf/n);
    CleanGraph(G);
    printf("\n");
}

double test_common(Graph G, int target, int print){
    Table T;
    clock_t start, finish;
    double Tot_Time = 0;
    T = InitialTable(G);
    start = clock();            // only count clock during the running of dijkstra
    T = dijkstra_min(T, target, G);
    // for(int i = 1; i < 50; i++){
    //     PrintPath(T, i, target);
    // }
    finish = clock();
    Tot_Time = (double)(finish - start) / CLOCKS_PER_SEC * 1000;
    if(print){
        printf("CommonHeap: %d clock, %f ms\n", (finish - start), Tot_Time);
    }
    
    CleanTable(G, T);
    return Tot_Time;
}

double test_pair(Graph G, int target, int print){
    Table T;
    clock_t start, finish;
    double Tot_Time = 0;
    T = InitialTable(G);
    start = clock();
    T = dijkstra_pair(T, target);
    finish = clock();
    Tot_Time = (double)(finish - start) / CLOCKS_PER_SEC * 1000;
    if(print){
        printf("PairHeap: %d clock, %f ms\n", (finish - start), Tot_Time);
    }
    
    CleanTable(G, T);
    return Tot_Time;
}

double test_fib(Graph G, int target, int print){
    Table T;
    clock_t start, finish;
    double Tot_Time = 0;
    T = InitialTable(G);
    start = clock();
    T = dijkstra_fib(T, target);
    finish = clock();
    Tot_Time = (double)(finish - start) / CLOCKS_PER_SEC * 1000;
    if(print){
        printf("FibHeap: %d clock, %f ms\n", (finish - start), Tot_Time);
    }
    
    CleanTable(G, T);
    return Tot_Time;
}

double test_bf(Graph G, int target, int print){
    Table T;
    clock_t start, finish;
    double Tot_Time = 0;
    T = InitialTable(G);
    start = clock();
    T = dijkstra_bf(T, target, G);
    finish = clock();
    Tot_Time = (double)(finish - start) / CLOCKS_PER_SEC * 1000;
    if(print){
        printf("BruteForce: %d clock, %f ms\n", (finish - start), Tot_Time);
    }
    CleanTable(G, T);
    return Tot_Time;
}

double test_bin(Graph G, int target, int print){
    Table T;
    clock_t start, finish;
    double Tot_Time = 0;
    T = InitialTable(G);
    start = clock();
    T = dijkstra_bin(T, target);
    finish = clock();
    Tot_Time = (double)(finish - start) / CLOCKS_PER_SEC * 1000;
    if(print){
        printf("BinHeap: %d clock, %f ms\n", (finish - start), Tot_Time);
    }
    CleanTable(G, T);
    return Tot_Time;
}