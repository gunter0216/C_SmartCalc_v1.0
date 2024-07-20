#ifndef SRC_S21_SMARTCALC_H_
#define SRC_S21_SMARTCALC_H_

enum Type {
    enumber,
    estart,
    eend,
    eplus,
    eminus,
    emul,
    ediv,
    emod,
    epow,
    euplus,
    euminus,
    ecos,
    esin,
    etan,
    eacos,
    easin,
    eatan,
    esqrt,
    eln,
    elog,
    eerror,
} static eType;

typedef struct Stack {
    double number;
    int type;
} Stack;

double smartCalc(char *str, int mode_graph, double x);

int isSpecialSymbol(char x);
int isNumber(char x);
int isTrigonometry(char *str);
Stack stackInit();
Stack add(Stack *stackArr, int *length, char *str, int mode_graph, double x);
void print(Stack *stackArr, int length);
int defineCategory(char x);
int definePriority(int x);
Stack* polNotation(Stack *stack, int length, int *newLength);
Stack* trimString(char *str, int *_size, int mode_graph, double x);
double calc(Stack *stack, int length);

#endif  // SRC_S21_SMARTCALC_H_
