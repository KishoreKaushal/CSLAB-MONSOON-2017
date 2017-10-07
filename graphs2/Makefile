# output.out: main.o  graph.o stack.o queue.o
# 	gcc -Wall -O2 main.o linkedList.o stack.o queue.o assist.o -o output.out
#
# main.o: main.c dataStructures.h graph.h graph.c  stack.c queue.c utility.o utility.c
# 	gcc -Wall -O2 -c main.c

task2.out:task2.o graph.o  dataStructures.o utility.o
	gcc -Wall -O2 task2.o graph.o dataStructures.o utility.o -o task2.out -g

task2.o: task2.c graph.c graph.h dataStructures.c utility.c  dataStructures.h
	gcc -Wall -O2 -c task2.c -g

graph.o: dataStructures.h dataStructures.c graph.h graph.c utility.c
	gcc -Wall -O2 -c graph.c -g

stack.o: dataStructures.h stack.c
	gcc -Wall -O2 -c stack.c -g

dataStructures.o: dataStructures.h dataStructures.c
	gcc -Wall -O2 -c dataStructures.c -g

utility.o: utility.c utility.h
	gcc -Wall -O2 -c utility.c -g
clean:
	rm *.o *.out
