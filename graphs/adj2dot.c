#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//declaring all the necessay functions
typedef struct _GRAPHS_ {
	int vc;
	int **a;
	char graphName[30];
} graphs;




int readGraph (char filename[] , struct graphs* graph );
void printGraph (struct graphs* graph);
void makeGraph (struct graphs* graph , FILE *file);


int main (){
	char filename[100];
	printf("Enter the name of the file \n");
	scanf("%s",filename);
	graphs graph1;
	int check = readGraph (filename , &graph1);
	if (check == 0)
		return 0;
	strcpy (graph1.graphName , "Graph01");
	FILE *file;

	makeGraph ( &graph1  , file);

	return 0;
}

int readGraph (char filename[] , struct graphs* graph)	{
	FILE * file1;
	file1 = fopen (filename , "r");
	if (file1 == 0)	{
		printf("error in opening the file\n");
		return 0;
	}

	char temp[1000];
	int success;
	success = fscanf(file1 , "%s" , temp);
	success = fscanf (file1 , "%s" , temp);
	success = fscanf(file1 , "%d" , &graph -> vc);
	int n = graph -> vc;
	graph ->a = (int **)malloc (n * sizeof (int *));
	for (int i = 0 ; i < n ; i++)	{
		graph ->a[i] = (int *)malloc(n * sizeof(int));
	}
	int counter = 0;
	do	{
		success = fscanf(file1 , "%s" , temp);

		if (success == -1)
			break;
		for (int i =0 ; i < n ; i++){
			graph -> a[counter][i] = temp[i] - '0';

		}
		counter++;
	}while (success != -1);
	fclose(file1);
	return 1;
}

void printGraph (struct graphs *graph){
	printf("The graph name is %s\n" , graph->graphName);
	printf("The number of vertices are %d\n" , graph -> vc);
	int n = graph -> vc;

	printf("The matrix is \n");
	for (int i =0 ; i < n ; i++)
	{
		for (int j =0 ; j< n ; j++)
		{
			printf("%d ",graph->a[i][j]);
		}
		printf("\n");
	}
}

void makeGraph ( struct graphs* graph , FILE *file)
{
	//for the output file
	char output[100];
	printf("Enter the name of the output file\n");
	scanf("%s",output);

	file = fopen (output , "w");
	fprintf(file , "graph one\n" );
	fprintf(file , "{\n");

	int n = graph->vc;
	for (int i =0 ; i < n ; i++)
	{
		for (int j =i ; j< n ; j++)
		{
			if (graph->a[i][j] == 1)
			{
				fprintf(file , "%d -- %d;\n" , i , j);
			}
		}
	}
	fprintf(file , "}\n");
}
