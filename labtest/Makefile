labtest.out: labtest.o graph.o
	gcc -Wall -O2 labtest.o graph.o  -o labtest.out -g
labtest.o: labtest.c graph.c graph.h
	gcc -Wall -O2 -c labtest.c -g
graph.o:  graph.h graph.c
	gcc -Wall -O2 -c graph.c -g
clean:
	rm *.o *.out *.dot *.dor
