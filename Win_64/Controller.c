#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "Controller.h"
#include "parser.h"
#include "arraynuevo.h"
#define TRIES 3


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path,LinkedList* pArrayListEmployee)
{
    FILE* pFile;
    int retorno = -1;
    if(pArrayListEmployee != NULL)
    {
        pFile = fopen(path,"r");
        if(pFile != NULL)
        {
            parser_EmployeeFromText(pFile,pArrayListEmployee);
            fclose(pFile);
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 */
int controller_loadFromBinary(char* path,LinkedList* pArrayListEmployee)
{
    FILE* pFile;
    int retorno = -1;

    if(pArrayListEmployee != NULL)
    {
        pFile = fopen(path,"rb");
        if(pFile != NULL)
        {
            parser_EmployeeFromBinary(pFile,pArrayListEmployee);
            fclose(pFile);
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int

 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    Employee* newEmployee;
    char bufferId[1500];
    char bufferNombre[1500];
    char bufferHorasTrabajadas[1500];
    char bufferSueldo[1500];
    int retorno = -1;

    if(pArrayListEmployee != NULL)
    {
        if((getStringNumerosInt(bufferId,"Ingrese ID:","Error\n",TRIES) == 0)
                &&(getStringLetras(bufferNombre,"Ingrese Nombre: ","Error",TRIES) == 0)
                &&(getStringNumerosInt(bufferHorasTrabajadas,"Ingrese Horas Trabajadas: ","Error",TRIES) == 0)
                &&(getStringNumerosInt(bufferSueldo,"Ingrese Sueldo: ","Error",TRIES == 0)))
        {
            newEmployee = employee_newParametros(bufferId,bufferNombre,bufferHorasTrabajadas,bufferSueldo);
            if(newEmployee != NULL)
            {
                if(ll_add(pArrayListEmployee,newEmployee) == 0)
                    {
                       retorno = 0;
                    }
            }
        }
    }
    return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_modifyEmployee(LinkedList* pArrayListEmployee)
{
    Employee* pEmployee;
    int retorno = -1;
    int size;
    char bufferId[1500];
    int auxId;
    int idBuscado;
    char bufferNombre [1500];
    char bufferHorasTrabajadas [1500];
    char bufferSueldo [1500];
    int i;
    int option;

    if (pArrayListEmployee != NULL)
    {
        size = ll_len(pArrayListEmployee);
        if(getStringNumerosInt(bufferId,"Ingrese el ID del empleado que desea modificar: ","Error\n",TRIES) == 0)
        {
            auxId = atoi(bufferId);
            for (i=0; i<size; i++)
            {
                pEmployee = ll_get(pArrayListEmployee,i);
                if(auxId == employee_getId(pEmployee,&idBuscado))
                {
                    do
                    {
                        printf("Elija que desea modificar: \n");
                        printf("1- Nombre del empleado\n,2- Horas que trabajo el empleado\n"
                               "3- Sueldo del empleado\n4- Salir\n");
                        getIntInRange(&option,"Ingrese Opcion: ","Error\n",1,4,TRIES);
                        switch (option)
                        {
                        case 1:
                            if(getStringLetras(bufferNombre,"Ingrese Nuevo Nombre: ","Error\n",TRIES) == 0)
                            {
                                employee_setNombre(pEmployee,bufferNombre);
                                retorno=0;
                            }
                            break;
                        case 2:
                            if(getStringNumerosInt(bufferHorasTrabajadas,"Ingrese Horas Trabajadas: ","Error\n",TRIES) == 0)
                            {
                                employee_setHorasTrabajadas(pEmployee,bufferHorasTrabajadas);
                                retorno=0;
                            }
                            break;
                        case 3:
                            if(getStringNumerosInt(bufferSueldo,"Ingrese Nuevo Sueldo: ","Error\n",TRIES) == 0)
                            {
                                employee_setSueldo(pEmployee,bufferSueldo);
                                retorno=0;
                            }
                            break;
                        }
                    }
                    while (option != 4);
                }
            }
        }
    }
    return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    Employee* pEmployee;
    int retorno = -1;
    int size;
    char bufferId[1500];
    int auxId;
    int idBuscado;
    int i;

    if (pArrayListEmployee != NULL)
    {
        size = ll_len(pArrayListEmployee);
        if(getStringNumerosInt(bufferId,"Ingrese el ID del empleado que desea modificar: ","Error\n",TRIES) == 0)
        {
            auxId = atoi(bufferId);
            for (i=0; i<size; i++)
            {
                pEmployee = ll_get(pArrayListEmployee,i);
                if(auxId == employee_getId(pEmployee,&idBuscado))
                {
                    ll_remove(pArrayListEmployee,i);
                    employee_delete(pEmployee);
                    retorno = 0;
                }
            }
        }
    }
    return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_listEmployee(LinkedList* pArrayListEmployee)
{
    Employee* pE;
    int auxId;
    int auxSueldo;
    int auxHoras;
    char auxNombre[1500];
    int size;
    int i;

    if(pArrayListEmployee != NULL)
    {
        size = ll_len(pArrayListEmployee);
        for(i=0; i<size; i++)
        {
            pE = ll_get(pArrayListEmployee,i);
            employee_getId(pE,&auxId);
            employee_getNombre(pE,auxNombre);
            employee_getSueldo(pE,&auxSueldo);
            employee_getHorasTrabajadas(pE,&auxHoras);
            if(pE != NULL)
            {
                printf("%d,%s,%d,%d\n",auxId,
                       auxNombre,
                       auxSueldo,
                       auxHoras);
            }
        }
    }
    return 0;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;

    if(pArrayListEmployee != NULL)
    {
        ll_sort(pArrayListEmployee,employee_sortByName,1);
        retorno = 0;
    }
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path, LinkedList* pArrayListEmployee)
{
    Employee* pE;
    int auxId;
    int auxSueldo;
    int auxHoras;
    char auxNombre[1500];
    int size;
    int i;
    int retorno = 1;

    FILE* fp = fopen(path,"a+");
    if(fp != NULL && pArrayListEmployee != NULL)
    {
        fprintf(fp,"id,nombre,horasTrabajadas,sueldo\n");

        size = ll_len(pArrayListEmployee);

        for(i=0;i<size;i++)
        {
            pE = ll_get(pArrayListEmployee,i);
            employee_getId(pE,&auxId);
            employee_getNombre(pE,auxNombre);
            employee_getSueldo(pE,&auxSueldo);
            employee_getHorasTrabajadas(pE,&auxHoras);
            if(pE != NULL)
            {
                fprintf(fp,"%d,%s,%d,%d\n",auxId,
                                            auxNombre,
                                            auxSueldo,
                                            auxHoras);
            }
        }
        fclose(fp);
        retorno = 0;
    }
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path, LinkedList* pArrayListEmployee)
{
    Employee* pE;
    int size;
    int i;

    FILE* fp=fopen(path,"w+b");
    if(fp!=NULL)
    {
        size=ll_len(pArrayListEmployee);

        for(i=0; i<size; i++)
        {
            pE=ll_get(pArrayListEmployee,i);
            fwrite(pE,sizeof(Employee),1,fp);
        }

        fclose(fp);
        return 0;
    }

    return 1;
}

