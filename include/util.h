#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include<time.h>
#include "user.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



typedef struct
{
    int dia;
    int mes;
    int ano;

} Data;

time_t stot(char *date);

void ttos(time_t time, char *date);

void meuPrintf(int verbosidade, char *,...);

#endif