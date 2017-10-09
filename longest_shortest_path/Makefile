longest_shortest_path.out: longest_shortest_path.o graph.o
	gcc -Wall -O2 longest_shortest_path.o graph.o  -o longest_shortest_path.out -g
longest_shortest_path.o: longest_shortest_path.c graph.c graph.h
	gcc -Wall -O2 -c longest_shortest_path.c -g
graph.o:  graph.h graph.c
	gcc -Wall -O2 -c graph.c -g
clean:
	rm *.o *.out *.dot
