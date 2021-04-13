typedef struct No_Stack{
    NO *a ;
    int top ;
    int size ;
}No_Stack;

typedef struct stack_int{
    int *ops;
    int top ;
    int size ;
}stack_int;


void init_stack(No_Stack *s, int ln);

int isfull(No_Stack s);

int isempty(No_Stack s);

void push(No_Stack *s, NO val);

NO pop(No_Stack *s);

void init_stack_int(stack_int *s, int ln);

int isfull_int(stack_int s);

int isempty_int(stack_int s);

void push_int(stack_int *s,  int opr);

int pop_int(stack_int *s);

int TopVal(stack_int s);


