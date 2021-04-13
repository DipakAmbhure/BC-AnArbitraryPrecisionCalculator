#include<stdlib.h>
#include<stdio.h>
#include "number.h"
#include "stack.h"

/*Number stack operations*/


void init_stack(No_Stack *s, int ln){
    s->top = -1;
    s->a = (NO *) malloc(sizeof(NO)*ln);
    s->size = ln;
    return ;
}


int isfull(No_Stack s){
    if(s.top == s.size-1)
        return 1;
    else
        return 0;

}

int isempty(No_Stack s){
    if(s.top == -1)
        return 1 ;
    else
        return 0 ;
}

void push(No_Stack *s,  NO val){
    if(isfull(*s))
        return ;
    else
        s->top++;
        s->a[s->top] = val;
    return;
}

NO pop(No_Stack *s){
    NO val ;
    if (isempty(*s))
        return zero ;
    else{
        val = s->a[s->top];
        s->top-- ;
    }
    return val ;
}


/*operator Stack operations*/



void init_stack_int(stack_int *s, int ln){
    s->top = -1;
    s->ops = (int *) malloc(sizeof(int)*ln);
    s->size = ln;
    return ;
}


int isfull_int(stack_int s){
    if(s.top == s.size-1)
        return 1;
    else
        return 0;

}

int isempty_int(stack_int s){
    if(s.top == -1)
        return 1 ;
    else
        return 0 ;
}

void push_int(stack_int *s, int opr){
    if(isfull_int(*s))
        return ;
    else
        s->top++;
        s->ops[s->top] = opr;
    return;
}

int pop_int(stack_int *s){
    int opr ;
    if (isempty_int(*s))
        return -1 ;
    else{
        opr = s->ops[s->top];
        s->top-- ;
    }
    return opr ;
}

int TopVal(stack_int s){
        int opr ;
        if (isempty_int(s))
                return -1 ;
        else{
                opr = s.ops[s.top];
        }
        return opr ;
}

