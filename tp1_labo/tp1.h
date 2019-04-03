#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

int utn_factorial(int numberA);

int utn_sum(int numberA, int numberB, char* msg);

int utn_substraction(int numberA, int numberB, char* msg);

int utn_multiply(int numberA, int numberB, char* msg);

float utn_division(int numberA, int numberB, char* msg, char* msgError);

int utn_getInt(int *pNum, char* msg, char* msgError);

int utn_getFloat(float *pNum, char* msg, char* msgError);

float utn_calculateAll(int numberA, int numberB);

#endif // FUNCIONES_H_INCLUDED

