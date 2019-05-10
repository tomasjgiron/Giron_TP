#include <stdio.h>
#include <stdlib.h>
#include "ArrayEmployees.h"
#include "arraynuevo.h"

#define LEN 1000
#define TRIES 3

int main()
{
    Employee employees[LEN];

    printf("\n\t~~~~~~BIENVENIDO A SU ABM~~~~~~\t\n");
    emp_menu(employees,LEN,"\n1)Alta empleado\n2)Modificar empleado\n3)Baja empleado\n4)Informes de empleado\n5)Salir\n","Informacion invalida",5,TRIES);

    return 0;
}
