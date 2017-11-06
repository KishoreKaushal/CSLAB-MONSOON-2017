DFS.out: DFS.o graph.o
	gcc -Wall -O2 DFS.o graph.o  -o DFS.out -g
DFS.o: DFS.c graph.c graph.h
	gcc -Wall -O2 -c DFS.c -g
graph.o:  graph.h graph.c
	gcc -Wall -O2 -c graph.c -g
clean:
	rm *.o *.out *.dot
