dijkstra.out: dijkstra.o graph.o
	gcc -Wall -O2 dijkstra.o graph.o  -o dijkstra.out -g
dijkstra.o: dijkstra.c graph.c graph.h
	gcc -Wall -O2 -c dijkstra.c -g
graph.o:  graph.h graph.c
	gcc -Wall -O2 -c graph.c -g
clean:
	rm *.o *.out *.dot
