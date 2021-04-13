/* file contain all operations on a single number */
#include <stdlib.h>
#include <stdio.h>
#include "number.h"


NO one;
NO zero;

void init(NO *n){
    *n=NULL;
    return ;
}

/* destroying zeros from left side of number */
int destroy_zeros(NO n){
    NO n1;
    int flag=0;
    while(n->pre)
        n=n->pre;
    while(n->next && n->digit==0){
        n->next->pre=NULL;
        n1=n->next;
        free(n);
        n=n1;
        flag=1;
    }
    return flag;
}

/*add digit to left side of number */
void adddigit(NO *n, int digit){
    if(*n==NULL){
        *n=(Number *) malloc(sizeof(Number));
        (*n)->digit=digit ;
        (*n)->next=NULL ;
        (*n)->pre=NULL;
        return ;
    }
    NO n1=(*n) ;
    while(n1->pre!=NULL)
        n1=n1->pre;
    n1->pre=(Number *) malloc(sizeof(Number));
    n1->pre->digit=digit ;
    n1->pre->pre=NULL;
    n1->pre->next=n1;

    return ;

}

/*show number from list*/
void show(NO n){
    int flag=0;
    while(n->pre!=NULL)
        n=n->pre;
    while(n){
        if(n->digit<-9){
            if(n->digit==-100)
                printf("-.0");
            else
                printf("-.%d", -n->digit/10);
            flag=1;
        }
        else if(n->digit > 9){
            if (!flag)
                printf("%c", '.');
            while(n){
                if(n->digit==100)
                    printf("0");
                else
                    printf("%d", n->digit/10);
                n=n->next;
            }
        return ;
        }
        else
            printf("%d", n->digit);
        n=n->next;
    }
    return ;
}

/*to add the entered value at end of number list*/
void mul_with_val(NO *n4, int count, int val){
    for(int i=0; i<count ; i++){
        (*n4)->next=(Number *) malloc(sizeof(Number));
        (*n4)->next->digit=val;
        (*n4)->next->next=NULL;
        (*n4)->next->pre=(*n4);
        (*n4)=(*n4)->next;
    }
    return ;

}

/*making all number of  digits equal after point by adding 100 at end of number*/
void mk_digitequal(NO *n3,  NO *n4){
    int c1=0, c2=0;
    NO n1=*n3,  n2=*n4;
    while(n1 && (n1->digit>9 || n1->digit<-9)){
        c1++;
        n1=n1->pre;
    }
    while(n2 && (n2->digit>9 || n2->digit<-9)){
        c2++;
        n2=n2->pre;
    }
    if(c2>c1)
        mul_with_val(n3, c2-c1, 100);
    else if(c2<c1)
        mul_with_val(n4, c1-c2, 100);
    return;
}

/*removing all zeros afer point and and non-sidnificant*/
void rm_last_zeros(NO *n){
        NO n1;
        n1=*n;
        while(n1->pre && n1->digit==100){
            n1=n1->pre;
            free(n1->next);
            n1->next=NULL;

        }
        *n=n1;
    return ;

}


/*create number
adding each digit in separate node
100 -> 1 0 0
-234 -> -2 3 4
23.45 -> 2 3 40 50
-45. 4 -> -4 5 40
-.05 -> -100 5
*/
NO create_number(char *P, int s, int e){
    NO n, n1;
    int flag=0;
    init(&n);
    int j;
    while(e>s){
        --e;
        if(P[e]=='+' || P[e]=='-')
            break;
        if(P[e]=='.'){
            n1=n;
            while(n1->pre)
                n1=n1->pre;
            while(n1 && n1->digit==0){
                n1->digit=10;
                n1=n1->next;
            }
            n1=n;
            while(n1->pre){
                n1->digit=n1->digit*10;
                n1=n1->pre;
            }
            if(P[e-1]=='-')
                n1->digit=-n1->digit*10;
            else
                n1->digit=n1->digit*10;
            continue;
        }
        j=e-1;
        if(j>=s && P[j]=='-'){
            if(P[e]=='0'){
                    destroy_zeros(n);
                    n1=n;
                    while(n1->pre)
                        n1=n1->pre;
                    n1->digit=-n1->digit;
            }
            else
                adddigit(&n, '0'-P[e]);
        }
        else
            adddigit(&n, P[e]-'0');
    }
    destroy_zeros(n);
    return n;
}

/*destroy number to free number node by node*/
void destroy_number(NO  n){
        NO n1;
        while(n->pre){
                n=n->pre;
                free(n->next);
                n->next=NULL;
        }

        return ;

}
