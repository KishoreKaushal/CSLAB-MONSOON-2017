pathfinder.out:pathfinder.o graph.o
	gcc -Wall -O2 pathfinder.o graph.o  -o pathfinder.out -g
pathfinder.o: pathfinder.c graph.c graph.h
	gcc -Wall -O2 -c pathfinder.c -g
graph.o:  graph.h graph.c
	gcc -Wall -O2 -c graph.c -g
clean:
	rm *.o *.out *.dot
