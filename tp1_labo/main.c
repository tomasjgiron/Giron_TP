#include <stdio.h>
#include <stdlib.h>
#include "tp1.h"

int main()
{
    char seguir='s';
    int opcion=0;
    int A;
    int B;

    while(seguir=='s')
    {
        printf("1- Ingresar 1er operando (A=x)\n");
        printf("2- Ingresar 2do operando (B=y)\n");
        printf("3- Calcular la suma (A+B)\n");
        printf("4- Calcular la resta (A-B)\n");
        printf("5- Calcular la division (A/B)\n");
        printf("6- Calcular la multiplicacion (A*B)\n");
        printf("7- Calcular el factorial (A!)\n");
        printf("8- Calcular todas las operaciones\n");
        printf("9- Salir\n");

        scanf("%d",&opcion);

        switch(opcion)
        {
            case 1:
                utn_getInt(&A,"Ingrese primer operando: ","Error");
                break;
            case 2:
                utn_getInt(&B,"Ingrese segundo operando: ","Error");
                break;
            case 3:
                utn_sum(A,B,"La suma es: ");
                break;
            case 4:
                utn_substraction(A,B,"La resta es: ");
                break;
            case 5:
                utn_division(A,B,"La división es: ","No se permite dividir por 0");
                break;
            case 6:
                utn_multiply(A,B,"La multiplicación es: ");
                break;
            case 7:
                utn_factorial(A);
                printf("El factorial de %d es: %d\n",A ,utn_factorial(A));
                break;
            case 8:
                utn_calculateAll(A,B);
                printf("El factorial de %d es: %d\n",A ,utn_factorial(A));
                break;
            case 9:
                seguir = 'n';
                break;
        }

    }
    return 0;
}
