#include <stdlib.h>
#include "number.h"
#include "mathoperations.h"
#include "caller.h"


/* this will decide the operation according to operator and do calculation and return number value of result error included*/

NO find_ans(NO *operand1 , NO *operand2, int opr){
        NO one, zero;
        init(&one);
        adddigit(&one, 1);
        init(&zero);
        adddigit(&zero, 0);
        NO r;
        switch(opr){
                case '+' :
                    add(operand1 ,operand2);
                    return *operand1;
                    break;
                case '-' :
                    sub(operand1, operand2);
                    return *operand1;
                    break;
                case '*' :
                    return multiply(operand1, operand2);
                    break;
                case '/' :
                    return divide(operand1, operand2, 0, 5);
                    break;
                case '%' :
                    r=divide(operand1, operand2, 1, 0);
                    if(r->digit == 143 || r->digit == 987)
                        return r;
                    destroy_number(r);
                    return *operand1;
                    break;
                case '>' :
                    if(lessthan(*operand2, *operand1))
                        return one;
                    else
                        return zero;
                    break;
                case '<' :
                    if(lessthan(*operand1, *operand2))
                        return one;
                    else
                        return zero;
                    break;
                case 366 :
                        if(!lessthan(*operand1, *operand2))
                                return one;
                        else
                                return zero;
                        break;
                case 364 :
                        if(!lessthan(*operand2, *operand1))
                                return one;
                        else
                                return zero;
                        break;
                case '='+304 :
                        if(!lessthan(*operand1, *operand2) && !lessthan(*operand2, *operand1))
                                return one;
                        else
                                return zero;
                case '^' :
                    return power(operand1, operand2);
                    break;
            }
            return zero;
}


