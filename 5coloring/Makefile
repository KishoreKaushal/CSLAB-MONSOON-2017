5coloring.out: 5coloring.o graph.o
	gcc -Wall -O2 5coloring.o graph.o  -o 5coloring.out -g
5coloring.o: 5coloring.c graph.c graph.h
	gcc -Wall -O2 -c 5coloring.c -g
graph.o:  graph.h graph.c
	gcc -Wall -O2 -c graph.c -g
clean:
	rm *.o *.out *.dot *.dor
