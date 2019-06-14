#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"


/** \brief Parsea los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile, LinkedList* pArrayListEmployee)
{
    char bufferId[1500];
    char bufferNombre[1500];
    char bufferHorasTrabajadas[1500];
    char bufferSueldo[1500];
    int cantidadDatos;
    Employee *pEmpleado;
    int retorno = 1;

    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",bufferId,
               bufferNombre,
               bufferHorasTrabajadas,
               bufferSueldo);
        do
        {
            cantidadDatos = fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",bufferId,
                                   bufferNombre,
                                   bufferHorasTrabajadas,
                                   bufferSueldo);
            if(cantidadDatos == 4)
            {
                pEmpleado = employee_newParametros( bufferId,
                                                    bufferNombre,
                                                    bufferHorasTrabajadas,
                                                    bufferSueldo);
                if(pEmpleado != NULL)
                {
                    if(ll_add(pArrayListEmployee,pEmpleado) == 0)
                    {
                        retorno = 0;
                    }
                }
            }
        }
        while(!feof(pFile));
    }
    return retorno;
}

/** \brief Parsea los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile, LinkedList* pArrayListEmployee)
{
    Employee* pe;
    int cantidad;
    int retorno = 1;

    do
    {
        pe = employee_new();
        if(pe != NULL && pFile != NULL && pArrayListEmployee != NULL)
        {
            cantidad = fread(pe,sizeof(Employee),1,pFile);
            if(cantidad == 1)
            {
                if(ll_add(pArrayListEmployee,pe) == 0)
                {
                   retorno = 0;
                }
            }
            else
            {
                employee_delete(pe);
            }
        }
    }
    while(!feof(pFile));
    return retorno;
}
