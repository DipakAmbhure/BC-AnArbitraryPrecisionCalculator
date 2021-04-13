#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <limits.h>
#include "number.h"
#include "stack.h"
#include "token.h"
#include "calculator.h"
#include "caller.h"
#include "mathoperations.h"
#include <strings.h>
#include <ctype.h>
#define MAX 500


/*function to take input */
void Call(){
        char E[MAX];
        gets(E);
        Calculate(E);
        printf("\n\n");
        return ;
}

/*main function*/
int main(){
        while(1){
                Call();
        }
        return 0;
}
