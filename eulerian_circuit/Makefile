eulerian_circuit.out: eulerian_circuit.o graph.o
	gcc -Wall -O2 eulerian_circuit.o graph.o  -o eulerian_circuit.out -g
eulerian_circuit.o: eulerian_circuit.c graph.c graph.h
	gcc -Wall -O2 -c eulerian_circuit.c -g
graph.o:  graph.h graph.c
	gcc -Wall -O2 -c graph.c -g
clean:
	rm *.o *.out *.dot *.dor
