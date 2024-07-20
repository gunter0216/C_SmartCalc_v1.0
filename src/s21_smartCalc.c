#include "s21_smartCalc.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Stack stackInit(double number, int type) {
    Stack stack;
    stack.number = number;
    stack.type = type;
    return stack;
}

/**
 *  1 cos sin
 *  2 ++ --
 *  3 ^
 *  4 * mod /
 *  5 + -
 *  6 number
 *  7 (
 *  8 )
 */
int definePriority(int x) {
    int temp = 0;
    if (x == ecos || x == esin || x == eatan || x == etan ||
            x == eacos || x == easin || x == esqrt || x == eln ||
            x == elog)
        temp = 1;
    else if (x == euminus || x == euplus)
        temp = 2;
    else if (x == epow)
        temp = 3;
    else if (x == emul || x == ediv || x == emod)
        temp = 4;
    else if (x == eplus || x == eminus)
        temp = 5;
    else if (x == enumber)
        temp = 6;
    else if (x == estart)
        temp = 7;
    else if (x == eend)
        temp = 8;
    return temp;
}

int isTrigonometry(char *str) {
    int temp = 0;
    int type[] = {
        emod,
        ecos,
        esin,
        etan,
        eacos,
        easin,
        eatan,
        esqrt,
        eln,
        elog
    };
    char strings[][6] = {
        "mod",
        "cos",
        "sin",
        "tan",
        "acos",
        "asin",
        "atan",
        "sqrt",
        "ln",
        "log",
    };
    for (int i = 0; i < 10; i++) {
        if (strcmp(str, strings[i]) == 0) {
            temp = type[i];
        }
    }
    return temp;
}

int isNumber(char x) {
    int temp = 0;
    if (x >= '0' && x <= '9' || x == '.' || x == ',' || x == 'x')
        temp = 1;
    return temp;
}

int isSpecialSymbol(char x) {
    char symbols[] = "+-*/^()";
    int temp = 0;
    for (int j = 0; j < 7; j++) {
        if (symbols[j] == x) {
            if (symbols[j] == '+')
                temp = eplus;
            else if (symbols[j] == '-')
                temp = eminus;
            else if (symbols[j] == '*')
                temp = emul;
            else if (symbols[j] == '/')
                temp = ediv;
            else if (symbols[j] == '^')
                temp = epow;
            else if (symbols[j] == '(')
                temp = estart;
            else if (symbols[j] == ')')
                temp = eend;
        }
    }
    return temp;
}

// 1 symbols 2 number 3 str
int defineCategory(char x) {
    char symbols[] = "+-*/^()";
    int temp = 0;
    for (int j = 0; j < 8; j++)
        if (x == symbols[j])
            temp = 1;
    if (x >= '0' && x <= '9' || x == '.' || x == ',' || x == 'x')
        temp = 2;
    else if (x >= 'a' && x <= 'z')
        temp = 3;

    return temp;
}

double smartCalc(char *str, int mode_graph, double x) {
    int length = 0;
    int error = 0;
    double result = 0;
    Stack *stack = trimString(str, &length, mode_graph, x);
    int newLength = 0;
    int temp = 0;
    for (int i = 0; i < length; i++) {
        if (stack[i].type == estart)
            temp++;
        else if (stack[i].type == eend)
            temp--;
        if (temp < 0)
            error = 1;
    }
    if (!error) {
        Stack *newStack = polNotation(stack, length, &newLength);
        result = calc(newStack, newLength);
        free(newStack);
    } else {
        result = 0.0/0.0;
    }
    free(stack);
    return result;
}

double calc(Stack *stack, int length) {
    Stack *curStack = (Stack*)malloc(length * sizeof(Stack));
    int curLength = 0;
    int error = 0;
    for (int i = 0; i < length && error == 0; i++) {
        if (stack[i].type == enumber) {
            curStack[curLength++] = stack[i];
        } else {
            if (stack[i].type == eplus) {
                if (curLength - 2 < 0 || curStack[curLength - 2].type != enumber || curStack[curLength - 1].type != enumber)
                    error = 1;
                else
                    curStack[curLength - 2].number = curStack[curLength - 2].number + curStack[curLength - 1].number;
                curLength--;
            } else if (stack[i].type == eminus) {
                if (curLength - 2 < 0 || curStack[curLength - 2].type != enumber || curStack[curLength - 1].type != enumber)
                    error = 1;
                else
                    curStack[curLength - 2].number = curStack[curLength - 2].number - curStack[curLength - 1].number;
                curLength--;
            } else if (stack[i].type == euplus) {
                if (curLength - 1 < 0 || curStack[curLength - 1].type != enumber)
                    error = 1;
                else
                    curStack[curLength - 1].number = curStack[curLength - 1].number;
            } else if (stack[i].type == euminus) {
                if (curLength - 1 < 0 || curStack[curLength - 1].type != enumber)
                    error = 1;
                else
                    curStack[curLength - 1].number = -curStack[curLength - 1].number;
            } else if (stack[i].type == emul) {
                if (curLength - 2 < 0 || curStack[curLength - 2].type != enumber || curStack[curLength - 1].type != enumber)
                    error = 1;
                else
                    curStack[curLength - 2].number = curStack[curLength - 2].number * curStack[curLength - 1].number;
                curLength--;
            } else if (stack[i].type == ediv) {
                if (curLength - 2 < 0 || curStack[curLength - 2].type != enumber || curStack[curLength - 1].type != enumber)
                    error = 1;
                else
                    curStack[curLength - 2].number = curStack[curLength - 2].number / curStack[curLength - 1].number;
                curLength--;
            } else if (stack[i].type == epow) {
                if (curLength - 2 < 0 || curStack[curLength - 2].type != enumber || curStack[curLength - 1].type != enumber)
                    error = 1;
                else
                    curStack[curLength - 2].number = pow(curStack[curLength - 2].number, curStack[curLength - 1].number);
                curLength--;
            } else if (stack[i].type == emod) {
                if (curLength - 2 < 0 || curStack[curLength - 2].type != enumber || curStack[curLength - 1].type != enumber)
                    error = 1;
                else
                    curStack[curLength - 2].number = fmod(curStack[curLength - 2].number, curStack[curLength - 1].number);
                curLength--;
            } else if (stack[i].type == esin) {
                if (curLength - 1 < 0 || curStack[curLength - 1].type != enumber)
                    error = 1;
                else
                    curStack[curLength - 1].number = sin(curStack[curLength - 1].number * M_PI / 180);
            } else if (stack[i].type == ecos) {
                if (curLength - 1 < 0 || curStack[curLength - 1].type != enumber)
                    error = 1;
                else
                    curStack[curLength - 1].number = cos(curStack[curLength - 1].number * M_PI / 180);
            } else if (stack[i].type == eacos) {
                if (curLength - 1 < 0 || curStack[curLength - 1].type != enumber || 
                    curStack[curLength - 1].number < -1 || curStack[curLength - 1].number > 1)
                    error = 1;
                else
                    curStack[curLength - 1].number = acos(curStack[curLength - 1].number) * 180 / M_PI;
            } else if (stack[i].type == easin) {
                if (curLength - 1 < 0 || curStack[curLength - 1].type != enumber || 
                    curStack[curLength - 1].number < -1 || curStack[curLength - 1].number > 1)
                    error = 1;
                else
                    curStack[curLength - 1].number = asin(curStack[curLength - 1].number) * 180 / M_PI;
            } else if (stack[i].type == etan) {
                if (curLength - 1 < 0 || curStack[curLength - 1].type != enumber || 
                    fabs(cos(curStack[curLength - 1].number * M_PI / 180)) < 1e-7)
                    error = 1;
                else
                    curStack[curLength - 1].number = tan(curStack[curLength - 1].number * M_PI / 180);
            } else if (stack[i].type == eatan) {
                if (curLength - 1 < 0 || curStack[curLength - 1].type != enumber)
                    error = 1;
                else
                    curStack[curLength - 1].number = atan(curStack[curLength - 1].number) / M_PI * 180;
            } else if (stack[i].type == esqrt) {
                if (curLength - 1 < 0 || curStack[curLength - 1].type != enumber || 
                    curStack[curLength - 1].number < 0)
                    error = 1;
                else
                    curStack[curLength - 1].number = sqrt(curStack[curLength - 1].number);
            } else if (stack[i].type == eln) {
                if (curLength - 1 < 0 || curStack[curLength - 1].type != enumber || 
                    curStack[curLength - 1].number <= 0)
                    error = 1;
                else
                    curStack[curLength - 1].number = log(curStack[curLength - 1].number);
            } else if (stack[i].type == elog) {
                if (curLength - 1 < 0 || curStack[curLength - 1].type != enumber || 
                    curStack[curLength - 1].number <= 0)
                    error = 1;
                else
                    curStack[curLength - 1].number = log10(curStack[curLength - 1].number);
            }
        }
    }
    double result = 0;
    if (error == 0) 
        result = curStack[0].number;
    else
        result = 0.0/0.0;
    free(curStack);
    return result;
}

Stack* trimString(char *str, int *_size, int mode_graph, double x) {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    int length = 0;
    char string[256];
    int size = 0;
    int category = 0;
    for (int i = 0; str[i] != '\0' && str[i] != '\n'; i++) {
        if (size > 0) {
            int cat = defineCategory(str[i]);
            if (cat != category || (cat == category && cat == 1)) {
                string[size] = '\0';
                Stack tempStack = add(stack, &length, string, mode_graph, x);
                if (tempStack.type != eerror) {
                    stack = (Stack*)realloc(stack, (length + 1) * sizeof(Stack));
                    length++;
                    stack[length - 1] = tempStack;
                }
                string[0] = str[i];
                size = 1;
                category = cat;
            } else {
                string[size++] = str[i];
            }
        } else {
            int x = isSpecialSymbol(str[i]);
            if (x > 0) {
                string[size++] = str[i];
                string[size] = '\0';
                Stack tempStack = add(stack, &length, string, mode_graph, x);
                if (tempStack.type != eerror) {
                    stack = (Stack*)realloc(stack, (length + 1) * sizeof(Stack));
                    length++;
                    stack[length - 1] = tempStack;
                }
                size--;
            } else {
                string[size++] = str[i];
                category = defineCategory(str[i]);
            }
        }
    }
    string[size] = '\0';
    if (size > 0) {
        Stack tempStack;
        tempStack = add(stack, &length, string, mode_graph, x);
        if (tempStack.type != eerror) {
            stack = (Stack*)realloc(stack, (length + 1) * sizeof(Stack));
            length++;
            stack[length - 1] = tempStack;
        }
    }
    *_size = length;
    return stack;
}

Stack* polNotation(Stack *stack, int length, int *newLength) {
    Stack *string = (Stack*)malloc(length * sizeof(Stack));
    int lengthString = 0;
    Stack *curStack = (Stack*)malloc(length * sizeof(Stack));
    int lengthStack = 0;
    for (int i = 0; i < length; i++) {
        int priority = definePriority(stack[i].type);
        if (priority == 6) {
            string[lengthString++] = stack[i];
        } else if (priority == 7) {
            curStack[lengthStack++] = stack[i];
        } else if (priority == 8) {
            for (int j = lengthStack - 1; j >= 0 && definePriority(curStack[j].type) != 7; j--) {
                string[lengthString++] = curStack[j];
                lengthStack--;
            }
            lengthStack--;
        } else {
            for (int j = lengthStack - 1; j >= 0 && definePriority(curStack[j].type) <= priority; j--) {
                string[lengthString++] = curStack[j];
                lengthStack--;
            }
            curStack[lengthStack++] = stack[i];
        }
    }
    for (int j = lengthStack - 1; j >= 0; j--) {
        string[lengthString++] = curStack[j];
        lengthStack--;
    }
    free(curStack);
    *newLength = lengthString;
    return string;
}

Stack add(Stack *stackArr, int *length, char *str, int mode_graph, double x) {
    Stack stack = stackInit(0, eerror);
    if (isNumber(str[0])) {
        if (str[0] == 'x') {
            stack = stackInit(x, 0);
        } else {
            for (int i = 0; str[i] != '\0'; i++) {
#ifdef WIN32
            if (str[i] == '.')
                str[i] = ',';
            }
#else
            if (str[i] == ',')
                str[i] = '.';
            }
#endif
            stack = stackInit(atof(str), 0);
        }
    } else {
        int x1 = isTrigonometry(str);
        int x2 = isSpecialSymbol(str[0]);
        if (x2 > 0) {
            if ((x2 == eminus || x2 == eplus) && (*length == 0 || stackArr[*length - 1].type == eplus ||
                stackArr[*length - 1].type == eminus || stackArr[*length - 1].type == emul ||
                stackArr[*length - 1].type == ediv || stackArr[*length - 1].type == emod ||
                stackArr[*length - 1].type == estart || stackArr[*length - 1].type == epow ||
                stackArr[*length - 1].type == eerror)) {
                if (x2 == eminus)
                    x2 = euminus;
                if (x2 == eplus)
                    x2 = euplus;
            }
            stack = stackInit(0, x2);
        } else if (x1 > 0) {
            stack = stackInit(0, x1);
        }
    }
    return stack;
}

void print(Stack *stackArr, int length) {
    char str[][10] = {
        "number",
        "(",
        ")",
        "+",
        "-",
        "*",
        "/",
        "mod",
        "^",
        "++",
        "--",
        "cos",
        "sin",
        "tan",
        "acos",
        "asin",
        "atan",
        "sqrt",
        "ln",
        "log",
    };
    for (int i = 0; i < length; i++) {
        if (stackArr[i].type == 0)
            printf("%lf ", stackArr[i].number);
        else
            printf("%s ", str[stackArr[i].type]);
    }
    printf("\n");
}