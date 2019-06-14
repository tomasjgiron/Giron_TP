#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#include "arraynuevo.h"


Employee* employee_new()
{
    return (Employee*) malloc(sizeof(Employee));
}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldo)
{

    Employee* emp = employee_new();
    if(emp!=NULL)
    {
        employee_setId(emp,idStr);
        employee_setNombre(emp,nombreStr);
        employee_setHorasTrabajadas(emp,horasTrabajadasStr);
        employee_setSueldo(emp,sueldo);
    }
    return emp;
}

int employee_delete(Employee* this)
{
    int retorno = -1;
    if(this != NULL)
    {
        free(this);
        retorno = 0;
    }
    return retorno;
}

int employee_setId(Employee* this, char* value)
{
    int auxID;
    int retorno = -1;

    if(this != NULL && value != NULL && isNumberInt(value))
    {
        auxID = atoi(value);
        if(auxID >= 0)
        {
            this->id = auxID;
            retorno = 0;
        }
    }
    return retorno;
}


int employee_setSueldo(Employee* this,char* value)
{
    int auxSueldo;
    int retorno = -1;
    if(this != NULL && value != NULL && isNumberInt(value))
    {
        auxSueldo = atoi(value);
        if(auxSueldo >= 0)
        {
            this->sueldo = auxSueldo;
            retorno = 0;
        }
    }
    return retorno;
}

int employee_setNombre(Employee* this, char* value)
{
    int retorno = -1;
    if(this != NULL && value != NULL && isLetter(value))
    {
        if(strlen(value) > 0)
        {
            strncpy(this->nombre,value,sizeof(this->nombre));
            retorno = 0;
        }
    }
    return retorno;
}


int employee_setHorasTrabajadas(Employee* this,char* value)
{
    int auxHoras;
    int retorno = -1;
    if(this != NULL && value != NULL && isNumberInt(value))
    {
        auxHoras = atoi(value);
        if(auxHoras >= 0)
        {
            this->horasTrabajadas = auxHoras;
            retorno = 0;
        }
    }
    return retorno;
}


int employee_getNombre(Employee* this, char* value)
{
    int retorno = -1;
    if(this != NULL && value != NULL)
    {
        strncpy(value,this->nombre,sizeof(this->nombre));
        retorno = 0;
    }
    return retorno;
}

int employee_getSueldo(Employee* this, int* value)
{
    int retorno = -1;
    if(this != NULL && value != NULL)
    {
        *value = this->sueldo;
        retorno = 0;
    }
    return retorno;
}

int employee_getHorasTrabajadas(Employee* this, int* value)
{
    int retorno = -1;
    if(this != NULL && value != NULL)
    {
        *value = this->horasTrabajadas;
        retorno = 0;
    }
    return retorno;
}

int employee_getId(Employee* this, int* value)
{
    int retorno = -1;
    if(this != NULL && value != NULL)
    {
        *value = this->id;
        retorno = 0;
    }
    return retorno;
}


int employee_initArray(Employee* arrayEmpleado[],int lenEmpleado)
{
    int i;
    int retorno = -1;
    if(arrayEmpleado != NULL && lenEmpleado > 0)
    {
        for(i=0; i<lenEmpleado; i++)
        {
            arrayEmpleado[i] = NULL;
        }
        retorno = 0;

    }
    return retorno;
}

int employee_findFree(Employee* arrayEmployee[], int lenEmployee)
{
    int i;
    int ret = -1;
    if(arrayEmployee != NULL && lenEmployee > 0)
    {
        for(i=0; i<lenEmployee; i++)
        {
            if(arrayEmployee[i] == NULL)
            {
                ret = i;
                printf("\n----Se encontro lugar libre----\n");
                break;
            }
        }
    }
    return ret;
}

int employee_sortByName(void* pFirstEmployee,void* pSecondEmployee)
{
    int retorno;
    Employee* pEmployeeA;
    Employee* pEmployeeB;

    pEmployeeA = (Employee*) pFirstEmployee;
    pEmployeeB = (Employee*) pSecondEmployee;

    if(strcmp(pEmployeeA->nombre,pEmployeeB->nombre) > 0)
    {
        retorno = 1;///mayor el primero
    }
    else if(strcmp(pEmployeeA->nombre,pEmployeeB->nombre) < 0)
    {
        retorno = -1;///menor el primero
    }
    else
    {
        retorno = 0;///ambos iguales
    }
    return retorno;
}
