 /*file contain all mathematical operations on two numbers */
#include<stdlib.h >
#include<stdio.h >
#include "number.h"
#include "mathoperations.h"

 /*compare two numbers*/
int lessthan(NO n1, NO n2) {

     /*making digit equal after point*/
    mk_digitequal(&n1, &n2);

    int l1 = 0, l2 = 0;
    NO n3, n4, n5;
    int f1 , f2 ;
    n5 = n1;
    n3 = n1;
    n4 = n2;
    while(n1 && n1->pre)
        n1 = n1->pre;
    while(n2 && n2->pre)
        n2 = n2->pre;

     /*check  + ve or  - ve number*/
    f1 = (n1->digit<0) ? 1 : 0;
    f2 = (n2->digit<0) ? 1 : 0;

     /* if signs of two number are different return*/
    if(f1  ==  1 && f2   ==  0)
        return 1;
    if(f1  ==  0 && f2  ==  1)
        return 0;

     /*if initial digits are zero skip that digit*/
    while(n2!= n4 && n2->digit == 0)
        n2 = n2->next;
    while(n1!= n3 && n1->digit == 0)
        n1 = n1->next;

     /*counting digits*/
    while(n3!= n1){
        l1++;
        n3 = n3->pre;
    }
    while(n4!= n2){
        l2++;
        n4 = n4->pre;
    }

     /*according to digits and sign return */
    if(l2 > l1 )
        return (f1 == 0) ? 1: 0;

    if(l1 > l2)
        return (f1 == 0) ? 0: 1;

     /*if both number negative make both  + ve*/
    if(f1 == 1 && f2 == 1){
        if(n1->digit > n2->digit)
            return 0;
        else if(n1->digit<n2->digit)
            return 1;
        else {
                n1 = n2->next;
                n2 = n2->next;
        }
    }

     /* comparing digit by digit first larger will return*/
    while(n1!= n5){
        if(((n2->digit  >  n1->digit )|| n1->digit == 100) && !(n2->digit == 100))
                return (f1 == 0) ? 1: 0;
        if(((n2->digit < n1->digit) || n2->digit == 100) && !(n1->digit == 100))
                return (f1 == 0) ? 0: 1;
        n1 = n1->next;
        n2 = n2->next;
     }
     if(n2->digit  >  n1->digit)
                return (f1 == 0) ? 1: 0;
     if(n2->digit < n1->digit)
                return (f1 == 0) ? 0: 1;
    return 0 ;

}

 /* substraction */
void sub(NO *n4, NO *n5){
    int borrow = 0 ;
    int sub ;
    NO n3, n6;
    NO n1 = *n4;
    NO n2 = *n5;
    int flag = 0, ch_sign = 0, temp = 0;
    while(n1->pre)
        n1 = n1->pre;
    while(n2->pre)
        n2 = n2->pre;

     /* if both numbers  - ve make both  + ve*/
    if(n1->digit<0 && n2->digit<0){
        flag = 1;
        n1->digit =  - n1->digit;
        n2->digit =  - n2->digit;
    }

     /* if signs of both are different add them according to sign and return*/
    if(n1->digit<0 && n2->digit > 0){
        n1->digit =  - n1->digit;
        add(n4, n5);
        n1 = *n4;
        while(n1->pre)
            n1 = n1->pre;
        n1->digit =  - n1->digit;
        return ;
    }

     if(n1->digit > 0 && n2->digit<0){
        n2->digit =  - n2->digit;
        add(n4, n5);
        n1 = *n5;
        while(n1->pre)
            n1 = n1->pre;
        n1->digit =  - n1->digit;
        return ;
    }

     /*make digits equal after point*/
    mk_digitequal(n4, n5);

    n1 = *n4;
    n2 = *n5;

     /* if first operand is lessthan second change sequence of operation with flag*/
    if(lessthan(n1, n2)){
        init(&n6);
        while(n2){
            adddigit(&n6, n2->digit);
            n2 = n2->pre;
        }
        n2 = *n5;
        n3 = n2;
        n2 = n1;
        n1 = n3;
        ch_sign = 1;
    }

     /*actual substraction
    while have digits for both number from left side substract n2's digit from n1's digit
    if any number have extra digits then do only for that number taking care of borrow
    */
    while(n1 && n2){
        if(n1->digit > 9){
            temp = 1;
           n1->digit = (n1->digit == 100) ? 0 : n1->digit / 10;
           n2->digit = (n2->digit == 100) ? 0 : n2->digit / 10;
        }
        sub = (n1->digit - n2->digit - borrow) ;
        borrow = 0 ;
        if(sub<0){
            sub = sub + 10;
            borrow = 1;
        }
        n1->digit = sub;
        if(flag == 1 && n1->pre == NULL && n2->pre == NULL)
            n1->digit =  - n1->digit;
        if(temp){
             n1->digit = (n1->digit == 0) ? 100 : n1->digit*10;
            n2->digit = (n2->digit == 0) ? 100 : n2->digit*10;
            temp = 0;
        }
        n1 = n1->pre;
        n2 = n2->pre;
    }
    while(n1 && borrow){
        if(n1->digit > 9){
            temp = 1;
            n1->digit = (n1->digit == 100) ? 0 : n1->digit / 10;
        }
        sub = n1->digit - borrow;
        borrow = 0;
        if(sub<0){
            sub = sub + 10;
            borrow = 1;
        }
        n1->digit = sub;
        if(temp){
            n1->digit = (n1->digit == 0) ? 100 : n1->digit*10;
            temp = 0;
        }

    }

     /*if operand1 lessthan operand2 undo the above changes*/
    if(ch_sign == 1){
        destroy_number(*n4);
        *n4 = *n5;
        *n5 = n6;
    }
    if(flag == 1){
        n2 = *n5;
        while(n2->pre)
            n2 = n2->pre;
        n2->digit =  - n2->digit;
    }

     /*using XOR give sign to final number*/
    if((!flag)*ch_sign + flag*(!ch_sign)){
        destroy_zeros(*n4);
        n2 = *n4;
        while(n2->pre)
            n2 = n2->pre;
        n2->digit =  - n2->digit;
    }
    return;
}

 /*Addition*/
void add(NO *n3, NO *n4){
    int carry = 0 ;
    int sum ;
    int flag = 1;
    int temp = 0;

    NO n1 = *n3;
    NO n2 = *n4;
    while(n1->pre)
        n1 = n1->pre;
    while(n2->pre)
        n2 = n2->pre;

    //If both numbers are negative make them positive
    if(n1->digit<0 && n2->digit<0){
        flag = 0;
         n1->digit =  - n1->digit;
         n2->digit =  - n2->digit;
    }

    //if signs are different substraction call
    if((n1->digit<0 && n2->digit > 0) || (n2->digit<0 && n1->digit > 0)){
        n2->digit =  - n2->digit;
        sub(n3, n4);
        n2 = *n4;
        while(n2->pre)
            n2 = n2->pre;
        n2->digit =  - n2->digit;
        return;
    }

    mk_digitequal(n3, n4);
    n1 = *n3;
    n2 = *n4;

    //actual addiditon
    while(n1 && n2){
        if(n1->digit > 9){
            temp = 1;
           n1->digit = (n1->digit == 100) ? 0 : n1->digit / 10;
           n2->digit = (n2->digit == 100) ? 0 : n2->digit / 10;
        }
        sum = (n1->digit + n2->digit + carry);
        carry = sum / 10;
        n1->digit = sum%10;
        if(temp){
             n1->digit = (n1->digit == 0) ? 100 : n1->digit*10;
            n2->digit = (n2->digit == 0) ? 100 : n2->digit*10;
            temp = 0;
        }
        n1 = n1->pre;
        n2 = n2->pre;
    }
    while(carry && n1){
         if(n1->digit > 9){
            temp = 1;
            n1->digit = (n1->digit == 100) ? 0 : n1->digit / 10;
        }
        sum = (n1->digit + carry)%10;
        carry = sum / 10;
        n1->digit = sum;
        if(temp){
            n1->digit = (n1->digit == 0) ? 100 : n1->digit*10;
            temp = 0;
        }
        n1 = n1->pre;
    }
    while(n2){
        if(n2->digit > 9){
            temp = 1;
            n2->digit = (n2->digit == 100) ? 0 : n2->digit / 10;
        }
        sum = (n2->digit + carry)%10;
        carry = sum / 10;
        adddigit(n3, sum);
        if(temp){
            n2->digit = (n2->digit == 0) ? 100 : n2->digit*10;
            temp = 0;
        }
        n2 = n2->pre;

    }
    if(carry)
        adddigit(n3, carry);

    //give sign to final number if negative
    if(flag == 0){
        n2 = *n3;
        n1 = *n4;
        while(n2->pre)
            n2 = n2->pre;
        n2->digit =  - n2->digit;
        while(n1->pre)
            n1 = n1->pre;
        n1->digit =  - n1->digit;
    }
    return;
}


 /*multiplication
is same as we do on notebook
if any sign is  - ve make it  + ve
multiply first number with digits of second number starting from unit place and
add with prevous multiplication by multiplying with 10
*/
NO multiply(NO *n8, NO *n9){
    NO n1, n2, n3, n4, n5;
    int point = 0;
    n1 = *n8;
    n2 = *n9;
    init(&n3);
    adddigit(&n3, 0);
    init(&n5);
    int f1 = 0, f2 = 0;
    int count = 0;
    int mul, carry ;
    while(n1->pre)
        n1 = n1->pre;
    while(n2->pre)
        n2 = n2->pre;
    if(n1->digit<0){
        f1 = 1;
        n1->digit =  - n1->digit;
    }
    if(n2->digit<0){
        f2 = 1;
        n2->digit =  - n2->digit;
    }
    while(n1){
        if(n1->digit > 9){
            while(n1->next){
                point++;
                n1 = n1->next;
            }
            point++;
        }
        n1 = n1->next;
    }
    while(n2){
        if(n2->digit > 9){
            while(n2->next){
                point++;
                n2 = n2->next;
            }
            point++;
        }
        n2 = n2->next;
    }
    n1 = *n8;
    n2 = *n9;
    while(n2){
        if(n2->digit > 9){
            n2->digit = n2->digit / 10;
        }
        if(n2->digit == 10)
            n2->digit = 0;

        init(&n4);
        n5 = n1;
        carry = 0;
        while(n5){
            if(n5->digit > 9)
                n5->digit = n5->digit / 10;
            if(n5->digit == 10)
                n5->digit = 0;
            mul = (n5->digit  * n2->digit  +  carry) ;
            carry = (mul) / 10 ;
            adddigit(&n4, mul%10);
            n5 = n5->pre ;
        }
        if(carry!= 0)
            adddigit(&n4, carry);
        mul_with_val(&n4, count++, 0);
        add(&n3, &n4);
        destroy_number(n4);
        n2 = n2->pre ;
    }
    n1 = n3;
    while(point--){
        if(n1->digit > 0){
            n1->digit = n1->digit*10;
        }
        if(n1->digit == 0)
            n1->digit = 100;
        if(!n1->pre){
            n1->pre = (Number *) malloc(sizeof(Number));
            n1->pre->next = n1;
            n1->pre->digit = 0;
            n1->pre->pre = NULL;

        }
        n1 = n1->pre;
    }
    destroy_zeros(n3);
    if(f1*!f2 + !f1*f2){
        n1 = n3;
        while(n1->pre)
            n1 = n1->pre;
        n1->digit =  - n1->digit;
    }
    if(f2){
        n1 = *n9;
        while(n1->pre)
            n1 = n1->pre;
        n1->digit =  - n1->digit;
    }
    rm_last_zeros(&n3);
    return n3;
}


 /*division
is also same as we do on notebook
in first number take numbers upto where second should divide from right side
for division substract second number from first till it can be sbstract with  + ve result with each substract increment
divison by one starting from zero
if mod is 1 it will calculate only interger division so that reminder of operand 1 will be result of modulo
*/
NO divide(NO *n1, NO *n2, int mod, int mxpnt){
    NO n3, n4, division, inc ;
    int point = 0;
    int f1 = 0, f2 = 0;
    n3 = *n1;
    n4 = *n2;
    while(n3->pre)
        n3 = n3->pre;
    while(n4->pre)
        n4 = n4->pre;
    if(n3->digit<0){
        f1 = 1;
        n3->digit =  - n3->digit;
    }
    if(n4->digit<0){
        f2 = 1;
        n4->digit =  - n4->digit;
    }
    while(n3){
        if(n3->digit > 9){
                if(mod){
                        NO errm;
                        init(&errm);
                        adddigit(&errm, 987);
                        return errm;
                }
                n3->digit = n3->digit / 10;
                if(n3->digit == 10)
                    n3->digit = 0;
            while(n3->next){
                point++;
                n3 = n3->next;
                n3->digit = n3->digit / 10;
                if(n3->digit == 10)
                    n3->digit = 0;
            }
            point++;
        }
        n3 = n3->next;
    }
    while(n4){
        if(n4->digit > 9){
                if(mod){
                        NO errm;
                        init(&errm);
                        adddigit(&errm, 987);
                        return errm;
                }
                n4->digit = n4->digit / 10;
                if(n4->digit == 10)
                    n4->digit = 0;
            while(n4->next){
                point--;
                n4 = n4->next;
                n4->digit = n4->digit / 10;
                if(n4->digit == 10)
                    n4->digit = 0;
            }
            point--;
        }
        n4 = n4->next;
    }
    n3 = *n1;
    init(&inc);
    init(&division);
    adddigit(&inc, 1);
    adddigit(&division, 0);

     /*zero division error*/
    if(!lessthan(division, *n2)){
        NO errr;                //declaration of errror number;
        init(&errr);
        adddigit(&errr, 143);
        return errr;
    }

    while(n3 && n3->pre)
        n3 = n3->pre;

    while(n3 && lessthan(*n1, *n2) && point<mxpnt && !mod){
            mul_with_val(n1, 1, 0);
            point++;
    }

    while(!lessthan(*n1, *n2)){
        n4 = *n2;
        mul_with_val(&division, 1, 0);
        while(n3 && lessthan(n3, *n2)){
            n3 = n3-> next;
            mul_with_val(&division, 1, 0);
        }
        while(!lessthan(n3, *n2)){
            sub(&n3, n2);
            add(&division, &inc);
        }

        while(n3 && lessthan(*n1, *n2) && point<mxpnt && !mod){
            mul_with_val(n1, 1, 0);
            point++;
        }

        if(n3)
            n3 = n3->next;

        if(lessthan(*n1, *n2)){
            while(n3){
                mul_with_val(&division, 1, 0);
                n3 = n3->next;
            }
        }



    }
    n3 = division;
    while(point > 0){
        if(n3->digit > 0){
            n3->digit = n3->digit*10;
        }
        if(n3->digit == 0)
            n3->digit = 100;
        if(!n3->pre){
            n3->pre = (Number *) malloc(sizeof(Number));
            n3->pre->next = n3;
            n3->pre->digit = 0;
            n3->pre->pre = NULL;
        }
        n3 = n3->pre;
        point--;
    }
    if(point<0){

        while(point++){
            mul_with_val(&division, 1, 0);
            n3 = n3->next;
        }
    }

    destroy_zeros(division);
    if(f1*!f2 + !f1*f2){
        n3 = division;
        while(n3->pre)
            n3 = n3->pre;
        n3->digit =  - n3->digit;
    }
    if(f2){
        n3 = *n2;
        while(n3->pre)
            n3 = n3->pre;
        n3->digit =  - n3->digit;
    }
        rm_last_zeros(&division);
    return division;
}


 /*power
find power with interger index
2^10
2*2 power = 2
4*4 power = 4
16*16 power = 8
not 256*256 because power will be 16
starting with
2*2 power = 2
total power  =  8 + 2
therefore
final
256*4

if index is negative same operation as above and will divide to one for final answer
*/
NO power(NO *base, NO *index){
    NO n1;
    NO temp;
    NO temp2;
    NO two;
    NO val;
    NO pow;
    init(&n1);
    init(&two);
    init(&val);
    init(&pow);
    int flag = 0, count = 0;;
    adddigit(&pow, 1);
    adddigit(&val, 2);
    adddigit(&zero, 0);
    adddigit(&one, 1);
    adddigit(&two, 2);
    NO n2 = *base;
    while(n2){
        adddigit(&n1, n2->digit);
        n2 = n2->pre;
    }
    n2 = *index;

//if index is zero
    if(!lessthan(zero, n2) && !lessthan(n2, zero))
        return one;

        while(n2->pre){
                if(n2->digit > 9 || n2->digit< - 9){
                        NO flut ;
                        init(&flut);
                        adddigit(&flut, 578);
                        return flut;
                }
                n2 = n2->pre;
        }
        if(n2->digit > 9 || n2->digit< - 9){
                NO flut ;
                init(&flut);
                adddigit(&flut, 578);
                return flut;
        }

        else if(n2->digit<0 && n2->digit >  - 10){
                n2->digit =  - n2->digit;
                flag = 1;
        }
    n2  =  *index;
    while(lessthan(zero, n2)){
                init(&val);
                adddigit(&val, 1);
                temp2 = multiply(&val, &two);
                while(!lessthan(n2, temp2)){
                            temp = multiply(base, base);
                            destroy_number(*base);
                            init(base);
                            *base = temp;
                            destroy_number(val);
                            init(&val);
                            val = temp2;
                            temp2 = multiply(&val, &two);
                }
                sub(&n2, &val);
                temp = multiply(&pow, base);
                destroy_number(pow);
                init(&pow);
                pow = temp;
                destroy_number(*base);
                init(base);
                temp2 = n1;
                while(temp2){
                        adddigit(base, temp2->digit);
                        temp2 = temp2->pre;
                }

        }
        if(flag){
                //count is used for final number of digits after point in final answer
                NO on1;
                init(&on1);
                adddigit(&on1, 1);
                temp2 = pow;
                while(temp2){
                        count++;
                        temp2 = temp2->pre;
                }
                //show(on1);
                temp = divide(&on1, &pow, 0, count + 5);
                destroy_number(pow);
                destroy_number(one);
                init(&pow);
                pow = temp;
        }


    return pow;
}


