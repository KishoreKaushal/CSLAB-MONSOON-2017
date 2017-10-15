6coloring.out: 6coloring.o graph.o
	gcc -Wall -O2 6coloring.o graph.o  -o 6coloring.out -g
6coloring.o: 6coloring.c graph.c graph.h
	gcc -Wall -O2 -c 6coloring.c -g
graph.o:  graph.h graph.c
	gcc -Wall -O2 -c graph.c -g
clean:
	rm *.o *.out *.dot *.dor
