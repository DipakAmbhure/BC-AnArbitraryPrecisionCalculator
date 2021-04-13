typedef struct Number{
    int digit;
    struct Number *next;
    struct Number *pre;
}Number;

typedef Number *NO;

NO one;
NO zero;

NO create_number(char *P, int s, int e);

int destroy_zeros(NO n);

void show(NO n);

void init(NO *n);


void adddigit(NO *n, int digit);

void mul_with_val(NO *n4, int count, int val);

void mk_digitequal(NO *n3, NO *n4);

void rm_last_zeros(NO *n);

void destroy_number(NO  n);
