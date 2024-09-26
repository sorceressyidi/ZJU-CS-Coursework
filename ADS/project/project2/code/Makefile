objects = main.o graph.o dijkstra.o pairheap.o binomial.o FibHeap.o MinHeap.o

main : $(objects)
	gcc -o main $(objects)

main.o : main.c dijkstra.h
	gcc -c main.c

dijkstra.o: dijkstra.c dijkstra.h graph.h binomial.h pairheap.h FibHeap.h
	gcc -c dijkstra.c

MinHeap.o: MinHeap.c MinHeap.h
	gcc -c MinHeap.c

FibHeap.o: FibHeap.c FibHeap.h
	gcc -c FibHeap.c

binomial.o: binomial.c binomial.h
	gcc -c binomial.c

pairheap.o : pairheap.c pairheap.h
	gcc -c pairheap.c

graph.o : graph.c graph.h
	gcc -c graph.c

.PHONY : clean
clean : 
	-rm main $(objects)