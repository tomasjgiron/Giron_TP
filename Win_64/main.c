#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "arraynuevo.h"
#define TRIES 3

int main()
{
    int flagTexto = 0;
    int flagBinario = 0;
    int option = 0;
    LinkedList* listaEmpleados = ll_newLinkedList();
    do
    {
        getIntInRange(&option,"\n1)Cargar los datos de los empleados desde el archivo (texto)\n"
                      "2)Cargar los datos de los empleados desde el archivo (binario)\n"
                      "3)Alta de empleado\n4)Modificacion de empleado\n"
                      "5)Baja de empleado\n6)Listar empleados\n7)Ordenar empleados\n"
                      "8)Guardar los datos de los empleados en el archivo (texto)\n"
                      "9)Guardar los datos de los empleados en el archivo (binario)\n10)Salir\n",
                      "\nERROR\n",1,10,TRIES);
        switch(option)
        {
        case 1:
            if(controller_loadFromText("data.csv",listaEmpleados) == 0)
            {
                printf("\n\t~~El archivo se cargo correctamente (texto)~~\t\n");
                flagTexto = 1;
            }
            else
            {
                printf("\n\t~~No se realizo la carga en el archivo (texto)~~\t\n");
            }
            break;
        case 2:
            if(controller_loadFromBinary("data.bin",listaEmpleados) == 0)
            {
                printf("\n\t~~El archivo se cargo correctamente (Binario)~~\t\n");
                flagBinario = 1;
            }
            else
            {
                printf("\n\t~~No se realizo la carga en el archivo (Binario)~~\t\n");
            }
            break;
        case 3:
            if(flagTexto == 1 || flagBinario == 1)
            {
                if(controller_addEmployee(listaEmpleados) == 0)
                {
                    printf("\n\t~~Se realizo el alta~~\t\n");
                }
                else
                {
                    printf("\n\t~~No se realizo el alta~~\t\n");
                }
            }
            else
            {
                printf("\n--No hay informacion para mostrar--\n");
            }
            break;
        case 4:
            if(flagTexto == 1 || flagBinario == 1)
            {
                if(controller_modifyEmployee(listaEmpleados) == 0)
                {
                    printf("\n\t~~Se realizo la modificacion correctamente~~\t\n");
                }
                else
                {
                    printf("\n\t~~No se realizo la modificacion~~\t\n");
                }
            }
            else
            {
                printf("\n--No hay informacion para mostrar--\n");
            }
            break;
        case 5:
            if(flagTexto == 1 || flagBinario == 1)
            {
                if(controller_removeEmployee(listaEmpleados) == 0)
                {
                    printf("\n\t~~Se realizo la baja correctamente~~\t\n");
                }
                else
                {
                    printf("\n\t~~No se realizo la baja~~\t\n");
                }
            }
            else
            {
                printf("\n--No hay informacion para mostrar--\n");
            }
            break;
        case 6:
            if(flagTexto == 1 || flagBinario == 1)
            {
                controller_listEmployee(listaEmpleados);
            }
            else
            {
                printf("\n--No hay informacion para mostrar--\n");
            }
            break;
        case 7:
            if(flagTexto == 1 || flagBinario == 1)
            {
                if(controller_sortEmployee(listaEmpleados) == 0)
                {
                    printf("\n\t~~Se ordeno correctamente~~\t\n");
                }
                else
                {
                    printf("\n\t~~No se realizo el ordenamiento~~\t\n");
                }
            }
            else
            {
                printf("\n--No hay informacion para mostrar--\n");
            }
            break;
        case 8:
            if(flagTexto == 1)
            {
                if(controller_saveAsText("data.csv",listaEmpleados) == 0)
                {
                    printf("\n\t~~Se guardo correctamente (texto)~~\t\n");
                }
                else
                {
                    printf("\n\t~~No se realizo el guardado (texto)~~\t\n");
                }
            }
            else
            {
                printf("\n--No hay informacion para mostrar--\n");
            }
            break;
        case 9:
            if(flagBinario == 1)
            {
                if(controller_saveAsBinary("data.bin",listaEmpleados) == 0)
                {
                    printf("\n\t~~Se guardo correctamente (binario)~~\t\n");
                }
                else
                {
                    printf("\n\t~~No se realizo el guardado (binario)~~\t\n");
                }
            }
            else
            {
                printf("\n--No hay informacion para mostrar--\n");
            }
            break;
        }
    }
    while(option != 10);

    ll_deleteLinkedList(listaEmpleados);

    return 0;
}
