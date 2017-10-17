/*                              */
/*    @kaushal_kishore          */
/* mailTo: kshr4kshl@gmail.com  */
/*         111601008            */

// Header File Containing all function prototype and structure definition
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/*------------------------DATA STRUCTURES--------------------------*/


/*                              */
/*    @kaushal_kishore          */
/* mailTo: kshr4kshl@gmail.com  */
/*                              */

#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#define FAILED 0
#define SUCCESS 1


/* ------------- DATA STRUCTURES ----------------- */

typedef void (*DISPLAY)(void*);         /* DISPLAY: type cast a function to void(*)(void*) */
typedef int (*COMPARE)(void* , void*);  /* COMPARE: type cast a function to int(*)(void*, void*) */

/* ---------- SINGLY LINKED LIST -------------------*/


typedef struct _NODE_{
    void *data;
    struct _NODE_ *next;
} _NODE_;

typedef struct _SINGLY_LINKED_LIST_{
    _NODE_ *head;
    _NODE_ *tail;
    _NODE_ *current;
} _LINKED_LIST_;

void initializeList(_LINKED_LIST_*);                /* Initializes the linked list */
int addHead(_LINKED_LIST_*, void*);                 /* Adds data to the linked lists's head */
int addTail(_LINKED_LIST_*, void*);                 /* Adds data to the linked list's tail */
void removeNode(_LINKED_LIST_*, _NODE_*);               /* Removes a node from the linked list */
_NODE_ *getNode(const _LINKED_LIST_*, COMPARE , void*);   /* Returns a pointer to the node containing a specific data item */
void displayLinkedList(const _LINKED_LIST_*, DISPLAY);    /* Displays the linked list */
int listEmpty(const _LINKED_LIST_*); /*Returns 1 if list is empty */
void freeList(_LINKED_LIST_*); /* Free the allocated linked list from the memory.*/
int searchList(const _LINKED_LIST_ *list, void *data);

/* --------------------- STACK --------------------- */

typedef _LINKED_LIST_  _STACK_ ;

void initializeStack(_STACK_ *) ;               /* Initializes Stack */
void *pop(_STACK_ *);                           /* Pops an element out of the stack from the head */
int push(_STACK_ *, void *);                    /* Pushes an element on the head of the stack */
void displayStack(_STACK_ *, DISPLAY );         /* Displays the whole stack from head to tail */
void destroyStack(_STACK_ *);                   /* Silently destroy the whole stack */
int stackEmpty(const _STACK_ *);                /* returns 1 if stack is empty */

/* ------------------- QUEUE ------------------------ */

typedef _LINKED_LIST_   _QUEUE_ ;

void initializeQueue(_QUEUE_ *);                /* Initializes Queue*/
int enqueue(_QUEUE_ *, void *);                 /* Adds an element in the queue(FIFO) */
void *dequeue(_QUEUE_ *);                       /* Removes an element from the queue at tail position*/
void displayQueue(_QUEUE_ *, DISPLAY  );        /* Displays the whole queue */
void freeQueue(_QUEUE_ *);                   /* Destroy the whole queue */
int queueEmpty(const _QUEUE_ *);                /* returns 1 if the queue is empty. */

/* ---------------- DOUBLY LINKED LIST ------------------ */

typedef struct _DNODE_{
    void *data;
    struct _DNODE_ *next;
    struct _DNODE_ *prev;
} _DNODE_;

typedef struct _DOUBLY_LINKED_LIST_{
    _DNODE_ *head;
    _DNODE_ *tail;
    _DNODE_ *current;
} _DLINKED_LIST_;


void initializeDList(_DLINKED_LIST_*);                /* Initializes the doubly linked list */
int addDHead(_DLINKED_LIST_*, void*);                 /* Adds data to the doubly linked lists's head */
int addDTail(_DLINKED_LIST_*, void*);                 /* Adds data to the doubly linked list's tail */
void removeDNode(_DLINKED_LIST_*, _DNODE_*);               /* Removes a node from the doubly linked list */
_DNODE_ *getDNode(const _DLINKED_LIST_*, COMPARE , void*);   /* Returns a pointer to the node containing a specific data item */
void displayDLinkedList(const _DLINKED_LIST_*, DISPLAY);    /* Displays the doubly linked list */
int DlistEmpty(const _DLINKED_LIST_*);
void freeDList(_DLINKED_LIST_ *); /*Free the allocated doubly linked list from the memory*/


/* ---------------- CIRCULAR LINKED LIST ------------------ */


typedef _NODE_  _CNODE_;

typedef _LINKED_LIST_  _CLINKED_LIST_;

void initializeCList(_CLINKED_LIST_*);                /* Initializes the linked list */
int addCHead(_CLINKED_LIST_*, void*);                 /* Adds data to the linked lists's head */
int addCTail(_CLINKED_LIST_*, void*);                 /* Adds data to the linked list's tail */
int removeCNode(_CLINKED_LIST_*, _CNODE_*);               /* Removes a node from the linked list */
_CNODE_ *getCNode(const _CLINKED_LIST_*, COMPARE , void*);   /* Returns a pointer to the node containing a specific data item */
void displayCLinkedList(const _CLINKED_LIST_*, DISPLAY);    /* Displays the linked list */
void displayIntCLinkedListFromGivenNode(const _CLINKED_LIST_*, DISPLAY, int nodeData);    /* Displays the linked list */
_CNODE_ *getCNodeIntData(const _CLINKED_LIST_ *Clist, int nodeData);
int ClistEmpty(const _CLINKED_LIST_*); /*Returns 1 if list is empty */
void freeCListIntData(_CLINKED_LIST_*); /* Free the allocated linked list from the memory.*/


/* -------------- DOUBLY CIRCULAR LINKED LIST ---------------- */

typedef _DNODE_  _DCNODE_ ;

typedef _DLINKED_LIST_   _DCLINKED_LIST_ ;


void initializeDCList(_DCLINKED_LIST_*);                /* Initializes the circular linked list */
int addDCHead(_DCLINKED_LIST_*, void*);                 /* Adds data to the circular linked lists's head */
int addDCTail(_DCLINKED_LIST_*, void*);                 /* Adds data to the circular linked list's tail */
void removeDCNode(_DCLINKED_LIST_*, _DCNODE_*);               /* Removes a node from the circular linked list */
_DCNODE_ *getDCNode(const _DCLINKED_LIST_*, COMPARE , void*);   /* Returns a pointer to the node containing a specific data item */
void displayDCLinkedList(const _DCLINKED_LIST_*, DISPLAY);    /* Displays the circular linked list */
int DClistEmpty(const _DCLINKED_LIST_*);
void freeDCList(_DCLINKED_LIST_ *); /*Free the allocated circular linked list from the memory*/


#endif // DATASTRUCTURES_H



#ifndef GRAPH_H
#define GRAPH_H

// number of colors available
#define COLOR_NUM (6)

// structure of the graph using adjacency matrix
typedef struct _GNODE_ {
    int nodeNumber;             // vertex/node number
    int adjNum;                 // number of adjacent nodes
    struct _GNODE_ ***adjacent;  // array of pointers to adjacent nodes
} _GNODE_ ;

typedef struct _GRAPH_ {
    int vc;         // number of vertices
    char *name;     // graph name
    int **AM;       // adjacency matrix
    _GNODE_ **node; // array of pointer to each vertices
} _GRAPH_ ;

#define NAME_LENGTH (2)
#define INITIAL_LINE_LENGTH (2)

char *getLine(void);

typedef struct String {
    char *str;
} String;

// deallocating memory allocated for the graph
void freeGraph(_GRAPH_ *graph);
// initialize the Graph
void initializeGraph(_GRAPH_ *graph);
// create graph structure in pointer form
void createGraphFromAM(_GRAPH_ *graph);
// read a text file for the adjacency matrix and creates graph
int readGraphFromTxt(char *filename , _GRAPH_ *graph);
// displays the graph on the screen
void printGraph(_GRAPH_ *graph);
// if current node has adjacent node as goal
int hasGnode(_GNODE_ *current , _GNODE_ *goal);
// Breadth first Traversal and also find shortest path and publish it into a dot file
int * BreadthFirstSearch(_GRAPH_ * graph , _GNODE_ **root , _GNODE_ **goal);
// displays the node number of a given node
static void displayNodeNumber(_GNODE_ **node);
// publish a dot file
void makeDotFile(_GRAPH_ *graph);
// publish the shortest path graph : a modification of the BFS algorithm
void publishShortestPathGraph( _GRAPH_ * graph ,int *shortestPath, int pathLength);
// check whether vertex1 and vertex2 forms an edge in the given path
int checkEdgeInPath(int *shortestPath , int pathLength , int vertex1 , int vertex2);
// utility funciton : prints the 2D int array
void print2Dint( int **arr, size_t rows , size_t cols);
// counts the number of pieces and displays the dot file and push the dot file
int countPiecesAndPublish(_GRAPH_ * graph);
// check whether the node is present in a particular piece of graph
int checkNodeInPiece(int *pieceArr , int nodeNum);
// find the nodes between whom the longest shortest Path exists and return an array containing those two nodes
int * findLongestShortestPath(_GRAPH_ * graph);
// on the basis of given shortest Path this function returns the Path Length
int shortestPathLength(int *Path,  int endnode);
// check whether eulerian circuit exist or not
int existEulerianCircuit(_GRAPH_ *graph);
// finds eulerian circuit and stores it into the circular linked list given as a parameter
int findEulerianCircuit(_GRAPH_ *graph , _CLINKED_LIST_ * eulerianPath);
// color a planar graph vertex using 6-color or few and publish the graph
int publishOptimalColorPlanarGraph(_GRAPH_ *graph);
// finds a hamiltonian cycle and publish the graph , returns 0 if hamiltonian cycle doesn't exists
int publishHamiltonianCycle(_GRAPH_ *graph, _CLINKED_LIST_ * hamiltonianPath);
void markEdgeLeft(int **edgeLeft, int edgeIdx, int vertex1, int vertex2);
void markEdgeLeftHamiltonian(int **edgeLeft, int edgeIdx, int vertex1, int vertex2);
#endif // GRAPH_H
