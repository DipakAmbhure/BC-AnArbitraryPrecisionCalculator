/*file to simplify entered string get token value and according
to that do operations as well as decide syntax error*/

#include "number.h"
#include "stack.h"
#include "caller.h"
#include "calculator.h"
#include <stdlib.h>
#include <strings.h>
#include "token.h"

int err;           //err is used in both below functions

//to check the precedence of an operater
int prec(char oper){
    switch(oper){
        case('>'):
        case('<'):
        case('='):
            return 1 ;
        case('+'):
        case('-'):
            return 2 ;
        case('/'):
        case('*'):
        case('%'):
            return 3 ;
        case('^'):
            return 4 ;
        default:
            return -1 ;
    }
}

/* this is base function to call all states based on token  */
int Solve(char *L, No_Stack *NS, stack_int *OP) {
        int s, e;
        char *temp;
        char * opertr;
        token t3;
        int op1;
        NO n, operand1, operand2, result;
        while(1) {
                t3 = gettoken(L, &s, &e);
                if(t3.type == number){
                        //if token gives number it will create a number and push in stack NS
                        n = create_number(L, s, e);
                        push(NS, n);
                }
                else if(t3.type == op){
                        /*if token gives operater if OP stack is empty it will push operator in OP or it
                        will check the precedene of peek operator and new opertor and according to that
                        do operations*/


                        /* If operator is >= or <= it will first push = in stakc then > or < */


                        if(isempty_int(*OP)){
                                if(L[e-1] == '=' && s != e - 1)
                                        push_int(OP, 61);
                                push_int(OP, L[s]);
                        }
                        else if(prec(TopVal(*OP)) > prec(L[s])){
                                operand2 = pop(NS);
                                operand1 = pop(NS);
                                op1 = pop_int(OP);
                                if(TopVal(*OP) == 61){
                                        op1 = op1 + 304;
                                        pop_int(OP);
                                }

                                result=find_ans(&operand1, &operand2, op1);
                                if(result->digit == 143){
                                        err = 2;
                                        break;
                                }
                                else if(result->digit == 987){
                                        err = 5;
                                        break;
                                }
                                else if(result->digit == 578){
                                        err = 7;
                                        break;
                                }
                                push(NS, result);

                                if(L[e - 1] == '=' && s != e-1)
                                        push_int(OP, 61);
                                push_int(OP, L[s]);
                        }
                        else{
                            if(L[e - 1] == '=' && s != e-1)
                                    push_int(OP, 61);
                            push_int(OP, L[s]);
                        }

                }
                else if(t3.type == stop) {

                        /* If token gives stop it will do operation while OP stack will not get empty and push result in NS
                        which will be only one value in NS at end if no error found*/


                        while(!isempty_int(*OP)){
                                if(TopVal(*OP) == '('){
                                err = 1;
                                break;
                                }
                                operand2 = pop(NS);
                                operand1 = pop(NS);
                                op1 = pop_int(OP);
                                if(TopVal(*OP) == 61){
                                        op1 = op1 + 304;
                                        pop_int(OP);
                                }
                                result = find_ans(&operand1, &operand2, op1);
                                if(result->digit == 143){
                                        err = 2;
                                        break;
                                }
                                else if(result->digit == 987){
                                        err = 5;
                                        break;
                                }
                                else if(result->digit == 578){
                                        err = 7;
                                        break;
                                }
                                push(NS, result);
                                }
                    break;
                }
                else if(t3.type == brac){
                    /*if token gives brac it will push '(' in OP*/
                    push_int(OP, 40);
                }
                else if(t3.type == bracc){

                    /* if token gives bracc it will do pop and do operation still '(' not found in stack
                    if not found it will give error */

                    while(TopVal(*OP) != 40) {
                                if(TopVal(*OP) == -1){
                                        err = 1;
                                        break;
                                }
                                operand2=pop(NS);
                                operand1=pop(NS);
                                op1=pop_int(OP);
                                if(TopVal(*OP) == 61){
                                        op1 = op1 + 304;
                                        pop_int(OP);
                                }
                                result=find_ans(&operand1, &operand2, op1);
                                if(result->digit == 143){
                                        err = 2;
                                        break;
                                }
                                else if(result->digit == 987){
                                        err = 5;
                                        break;
                                }
                                else if(result->digit == 578){
                                        err = 7;
                                        break;
                                }
                                push(NS, result);
                    }
                    pop_int(OP);

                }
                if( t3.type == error){
                    /*Error state will get return the function*/
                    err=1;
                    break;
                }
        }
        return 0;
}


int Calculate(char *E){

        /* static declaration of two stack for number and oeprator as NS and OP*/

        static No_Stack NS;
        static stack_int OP;
        init_stack(&NS, 100);
        init_stack_int(&OP, 100);
        Solve(E, &NS, &OP);

        /* if no error found it will print final answer of expression */
        if(err == 0){
                show(pop(&NS));
                return 0;
        }

        /* if there will be error stacks will not be empty for again calculations this will empty two stacks*/

        while(!isempty(NS))
                pop(&NS);
        while(!isempty_int(OP))
                pop_int(&OP);

        /* according to error code print error */
        if(err == 1) printf(" { Syntax Error ! } ");
        else if(err == 2) printf(" { Zero Division Error! } ");
        else if(err == 5) printf(" { Mod for Float is not Suppoeted Yet ! } ");
        else if(err == 7) printf(" { In Power Float Index is not Supported Yet ! }");
        err=0;

        return 0;

}

