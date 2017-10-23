hamiltonianCycle.out: hamiltonianCycle.o graph.o
	gcc -Wall -O2 hamiltonianCycle.o graph.o  -o hamiltonianCycle.out -g
hamiltonianCycle.o: hamiltonianCycle.c graph.c graph.h
	gcc -Wall -O2 -c hamiltonianCycle.c -g
graph.o:  graph.h graph.c
	gcc -Wall -O2 -c graph.c -g
clean:
	rm *.o *.out *.dot *.dor
