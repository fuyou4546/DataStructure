#ifndef _OTHERS_H_
#define _OTHERS_H_

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status, Bool;

typedef struct {
    int x;
    int y;
}Data;

Bool Equal(int, int);

Bool Equal_Data1(Data*, Data*);

#endif