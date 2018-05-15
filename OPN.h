#ifndef OPN_h
#define OPN_h


#include <iostream>
#include <cctype>
#include <stdlib.h>
#include <conio.h>
#include <cstdio>
#include <stack>

using namespace std;

int drob(int);
int prior(char);
bool is_op(char);
bool is_digit(char);
void opn(char *, char *);
float Calc(char *);

#endif
