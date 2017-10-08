counting_pieces.out:counting_pieces.o graph.o
	gcc -Wall -O2 counting_pieces.o graph.o  -o counting_pieces.out -g
counting_pieces.o: counting_pieces.c graph.c graph.h
	gcc -Wall -O2 -c counting_pieces.c -g
graph.o:  graph.h graph.c
	gcc -Wall -O2 -c graph.c -g
clean:
	rm *.o *.out *.dot
