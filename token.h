#define start 0
#define number 1
#define op 2
#define brac 3
#define stop 4
#define error 5
#define bracc 6

typedef struct token {
        int type;
}token;


token gettoken(char *l, int *s, int *e);

