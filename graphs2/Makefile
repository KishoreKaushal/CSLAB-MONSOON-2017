# output.out: main.o  graph.o stack.o queue.o
# 	gcc -Wall -O2 main.o linkedList.o stack.o queue.o assist.o -o output.out
#
# main.o: main.c dataStructures.h graph.h graph.c  stack.c queue.c utility.o utility.c
# 	gcc -Wall -O2 -c main.c

task2.out:task2.o graph.o queue.o singlyLinkedList.o utility.o 
	gcc -Wall -O2 task2.o graph.o queue.o singlyLinkedList.o utility.o -o task2.out

task2.o: task2.c graph.c queue.c singlyLinkedList.c utility.c graph.h dataStructures.h
	gcc -Wall -O2 -c task2.c

graph.o: dataStructures.h queue.c singlyLinkedList.c graph.h graph.c utility.c
	gcc -Wall -O2 -c graph.c

stack.o: dataStructures.h stack.c
	gcc -Wall -O2 -c stack.c

queue.o: dataStructures.h queue.c
	gcc -Wall -O2 -c queue.c

singlyLinkedList.o: dataStructures.h singlyLinkedList.c
	gcc -Wall -O2 -c singlyLinkedList.c

utility.o: utility.c
	gcc -Wall -O2 -c utility.c
clean:
	rm *.o
