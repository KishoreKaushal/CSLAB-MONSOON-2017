
#define NAME_LENGTH (2)
#define INITIAL_LINE_LENGTH (2)

char *getLine(void);
void free2d(void **a);
void **malloc2d(size_t numRows , size_t rowSize);
void print2Dint( int **arr, size_t rows , size_t cols);
int *readNumbers(int *count /* RETVAL */);
