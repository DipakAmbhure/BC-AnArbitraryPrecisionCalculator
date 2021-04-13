/*file to get token*/



#include<strings.h>
#include<ctype.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "token.h"


/* token will give the exact positiion and detect the type which user entered*/
token gettoken(char *l, int *s, int *e){
    static int temp;
    static token t, t1;
    static int curstate  =  start;
    static int i  =  0;
    static int point = 0;
    static int extr = 0;
    char c  =  l[i];
    while(1) {
        c  =  l[i++];
        // if c is space skip it
        if(c == ' '){
            extr++;
            continue;
        }
        *s = temp;
        switch(curstate) {
        case start:
                    if(isdigit(c) || ((c  ==  '+' || c  ==  '-')) && isdigit(l[i])) {
                        curstate  =  number;
                        t.type  =  number;
                        temp = i-1;
                        extr = 0;
                    }
                    else if(c  ==  '\0'){
                        t.type  =  stop;
                        curstate  =  stop;
                        return t;
                    }
                    else if(c  ==  '.'){
                        point = 1;
                        t.type  =  number;
                        curstate = number;
                        temp = i-1;
                        extr = 0;
                    }
                    else if( c  ==  '('){
                                t.type = brac;
                                curstate = brac;
                                temp = i-1;
                                extr = 0;
                            }
                    else {
                        curstate = start;
                        i = 0;
                        point = 0;
                        extr = 0;
                        t.type  =  error;
                        return t;
                    }
                    break;
        case number:
                if(isdigit(c) && !extr){
                    curstate  =  number;
                    t.type  =  number;
                }
                else if(c  ==  '.' && !point && isdigit(l[i])){
                    curstate  =  number;
                    t.type  =  number;
                    point = 1;
                }
                else if(c  ==  '+' || c  ==  '-' || c  ==  '*' || c  ==  '/' || c  ==  '^' || c  ==  '%' || c  ==  '>' || c  ==  '<' ){
                        t1 = t;
                        t.type  =  op ;
                        curstate  =  op;
                        temp = i-1;
                        *e = i-extr-1;
                        extr = 0;
                        return t1;
                }
                else if(c  ==  '\0'){
                    t.type  =  number;
                    *e = i-extr-1;
                    extr = 0;
                    curstate  =  stop;
                    return t;
                }
                else if(c  ==  ')'){
                    t1  =  t;
                    t.type  =  bracc;
                    curstate  =  bracc;
                    *e = i-extr-1;
                    temp = i-1;
                    extr = 0;
                    return t1;

                }
                else{
                        t.type  =  error;
                        curstate = start;
                        i = 0;
                        point = 0;
                        extr = 0;
                        return t;
                }
                break;
        case op:
                  if(c  ==  ' = '  && !extr){
                    t.type  =  op;
                    curstate  =  op;
                  }
                  else if(isdigit(c) || ( (c  ==  '+' || c  ==  '-') && (isdigit(l[i]) || l[i] == '.'))){
                        t1 = t;
                        curstate  =  number;
                        t.type  =  number;
                        point = 0;
                        *e = i-extr-1;
                        temp = i-1;
                        extr = 0;
                        return t1;
                  }
                  else if(c  ==  '.'){
                    t1 = t;
                    curstate  =  number;
                    t.type  =  number;
                    point  =  1;
                    *e = i-extr-1;
                    temp = i-1;
                    extr = 0;
                  return t1;
                  }
                  else if( c  ==  '('){
                                t1 = t;
                                t.type = brac;
                                curstate = brac;
                                temp = i-1;
                                *e = i-extr-1;
                                extr = 0;
                                return t1;
                    }
                  else{
                        t.type  =  error;
                        curstate = start;
                        i = 0;
                        point = 0;
                        extr = 0;
                        return t;
                  }
                  break;
        case brac:
                    if(c == '\0'){
                        t.type = error;
                        curstate = start;
                        i = 0;
                        point = 0;
                        extr = 0;
                        return t;
                    }
                    t1 = t;
                    curstate  =  start;
                    t.type = start;
                    *e = i-extr-1;
                    temp = --i;
                    extr = 0;
                    return t1;
                break;
        case bracc:
                if(isdigit(c)){
                    t1 = t;
                    curstate  =  number;
                    t.type  =  number;
                    temp = i-1;
                    *e = i-extr-1;
                    extr = 0;
                    return t1;
                }
                else if(c  ==  '.' && !point && isdigit(l[i])){
                    t1 = t;
                    curstate  =  number;
                    t.type  =  number;
                    point = 1;
                    temp = i-1;
                    *e = i-extr-1;
                    extr = 0;
                    return t1;
                }
                else if(c  ==  '+' || c  ==  '-' || c  ==  '*' || c  ==  '/' || c  ==  '^' || c  ==  '%' || c  ==  '>' || c  ==  '<' ){
                        t1 = t;
                        t.type  =  op ;
                        curstate  =  op;
                        temp = i-1;
                        *e = i-extr-1;
                        extr = 0;
                        return t1;
                }
                else if(c  ==  '\0'){
                    t1 = t;
                    t.type  =  stop;
                    *e = i-extr-1;
                    curstate  =  stop;
                    extr = 0;
                    return t1;
                    break;
                }
                else if( c  ==  '('){
                                t1 = t;
                                t.type = brac;
                                curstate = brac;
                                *e = i-extr-1;
                                extr = 0;
                                temp = --i;
                                return t1;
                }
                else{
                        t.type = error;
                        curstate = start;
                        i = 0;
                        point = 0;
                        extr = 0;
                        return t;
                }
                break;


        case stop:   t.type   =  stop;
                        curstate = start;
                        i = 0;
                        point = 0;
                        extr = 0;
                     return t;
                     break;
        case error:   t.type  =  error;
                        curstate = start;
                        i = 0;
                        point = 0;
                        extr = 0;
                      return t;
                      break;

        }

    }

}




