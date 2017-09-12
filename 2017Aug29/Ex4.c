///////// Ex4.c //////////////////
// Kaushal Kishore              //
// 111601008@smail.iitpkd.ac.in //
//     gcc -std=c11  Ex4.c      //
//////////////////////////////////


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define NAME_LENGTH (2)
#define INITIAL_LINE_LENGTH (2)
#define FAILED (0)
#define SUCCESS (1)

typedef struct _NODE_{
    char data;
    struct _NODE_ *next;
} _NODE_;

typedef struct _STACK_{
    _NODE_ *head;
    _NODE_ *tail;
} _STACK_;

/* returns 1 if the stack is empty */
int stackEmpty(const _STACK_ *stack) {
    return (stack->head == NULL);
}

/* initialize the stack */
void initializeStack(_STACK_ *stack){
    stack->head = NULL;
    stack->tail = NULL;
}

/* push the integer operand on to the stack */
int push(_STACK_ *stack, char data){
    _NODE_ *newNode = (_NODE_ *)malloc(sizeof(_NODE_));
    if(newNode == NULL ) return FAILED;
    newNode->data = data;
    if(stack->head == NULL ) {
        newNode->next = NULL;
        stack->tail = newNode;
    } else {
        newNode->next = stack->head;
    }
    stack->head = newNode;
    return SUCCESS;
}

/* pop the operand out of the stack */
char pop(_STACK_ *stack) {
    _NODE_ *node = stack->head ;
    if(node == NULL) {
        return FAILED;
    } else if (node == stack->tail) {
        stack->head = stack->tail = NULL;
        char data = node->data;
        free(node);
        return data;
    } else {
        stack->head = stack->head->next;
        char data = node->data;
        free(node);
        return data;
    }
}

/* display the stack */
void displayStack(_STACK_ *stack ) {
    _NODE_ *node;
    node =  stack->head;
    printf("STACK: -head-TO-tail-\n");
    while (node != NULL){
        printf("%c ",node->data);
        node = node->next;
    }
    printf("\n");
}

/* destroy the stack */
void destroyStack(_STACK_ *stack){
    _NODE_ *node;
    node  = stack->head;
    while(1){
        if(node == NULL ) {
            break;
        }
        stack->head = stack->head->next;
        free(node);
        node = stack->head;
    }
}

/* returns the stack head */
char stackTop(const _STACK_ *stack){
    if(!stackEmpty(stack))  return stack->head->data;
    else return 0;
}

/* Function to input an Expression*/
char *getExpression(void){
    char *line;
    int size;   /* how much space do I have in the line? */
    int length; /* how many characters have i used ?*/
    int c;
    size = INITIAL_LINE_LENGTH;
    line = malloc(size);
    if(line == 0) {
        /* malloc failed */
        printf("getLine() : failed to allocate memory for the input.");
        return 0;
    }
    length = 0;
    while ((c = getchar()) != EOF && c != '\n') {
        /* code */
        if(c==' ')  continue;
        if(length >= size-1){
            /* need more space */
            size*=2;
            /* make length equal to new size*/
            /* copy contents if necessary */
            line = realloc(line , size);
        }
        line[length++] = c;
    }
    line[length] = '\0';
    return line;
}

int main(){
    double output=0, a=0, b=0, len=0;
    _STACK_ s;
    initializeStack(&s);

    /*initialize operator precedence*/
    char opPrecedence[128];
    for (int i=0;i<128; i++)    opPrecedence[i] =0;
    opPrecedence['+'] = 2;
    opPrecedence['-'] = 2;
    opPrecedence['*'] = 3;
    opPrecedence['/'] = 3;
    opPrecedence['^'] = 4;

    char *Expression = getExpression(); /* input the expression */
    char op,ch;
    len = strlen(Expression);
    char *postfix = (char *)malloc(sizeof(char)*len);
    char *ptr = postfix;
    printf("Your Expression: %s\n", Expression);
    for (size_t i=0; i<len; i++){
        if(isalnum(Expression[i])){
            *ptr++ = Expression[i];
        } else {
            if(stackEmpty(&s) || (stackTop(&s)=='(' && Expression[i]!='(')) {
                push(&s, Expression[i]);
            } else if(Expression[i]=='('){
                push(&s, Expression[i]);
            } else if(Expression[i]==')'){
                while(stackTop(&s)!='(' && !stackEmpty(&s)){
                    *ptr++ = pop(&s);
                }
                if(stackTop(&s)=='(')   pop(&s);
            } else if (!stackEmpty(&s)){
                ch = stackTop(&s);

                if(opPrecedence[Expression[i]] > opPrecedence[ch]){
                    push(&s, Expression[i]);
                } else if(opPrecedence[Expression[i]]==opPrecedence[ch] && ch!='^') {
                    *ptr++ = pop(&s);
                    push(&s, Expression[i]);
                } else if(opPrecedence[Expression[i]] < opPrecedence[ch]){
                    /* pop till the precedence is equal */
                        *ptr++ = pop(&s);
                        i--;
                } else {
                    push(&s, Expression[i]);
                }
            } else {
                push(&s , Expression[i]);
            }
        }
    }
    if(!stackEmpty(&s)){
        while(!stackEmpty(&s)){
            *ptr++ = pop(&s);
        }
    }

    /* Last character will be delimiter string.*/
    *ptr = '\0';
    printf("%s\n", postfix);
    /* freee the allocated memory */
    free(postfix);
    free(Expression);
    destroyStack(&s);

    return 0;
}
