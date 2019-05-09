#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arraynuevo.h"
#include "ArrayEmployees.h"

static int generateID(void);

int emp_menu(Employee* pEmployees,int len,char* textMenu,char* msgE,int escape,int tries)
{

    int opcion = 0;
    int posLibre;
    int flag = 0;

    if(pEmployees != NULL && len > 0)
    {
        emp_initArray(pEmployees,len);
        while(opcion!=5)
        {
            printf(textMenu);

            getIntInRange(&opcion,"\n Ingrese opcion: ","Informacion invalida\n",
                          1,escape,tries);

            switch(opcion)
            {
                case 1:
                {
                    posLibre = emp_searchFreeSpace(pEmployees,len);
                    if(posLibre >= 0)
                    {
                        printf("\n\t~~~~Se encontro lugar~~~~\t\n");
                        if(emp_addEmployee(pEmployees,len,"Informacion invalida",tries) == 0)
                        {
                            flag = 1;
                            printf("\n\t~~~~Se realizo el alta de manera correcta~~~~\t\n");
                        }
                        else
                        {
                            printf("\n\t~~~~No se realizo el alta~~~~\t\n");
                        }
                    }
                    else
                    {
                        printf("\n\t~~~~No hay lugar libre~~~~\t\n");
                    }
                    break;
                }
                case 2:
                {
                    if(flag == 1)
                    {
                        if(emp_modifyEmployee(pEmployees,len,"Informacion invalida",5,tries) == 0)
                        {
                            printf("\n\t~~~~Se pudo modificar el listado~~~~\t\n");
                        }
                        else
                        {
                            printf("\n\t~~~~No se pudo modificar el listado~~~~\t\n");
                        }
                    }
                    printf("\n~~~~No hay registros para modificar~~~~\n");
                    break;
                }
                case 3:
                {
                    if(flag == 1)
                    {
                        if(emp_removeEmployee(pEmployees,len,"Informacion invalida",tries) == 0)
                        {
                            printf("\n\t~~~~Se pudo dar de baja~~~~");
                        }
                        else
                        {
                            printf("\n\t~~~~No se logro dar de baja~~~~\t\n");
                        }
                    }
                    printf("\n~~~~No hay registros para dar de baja~~~~\n");
                    break;
                }
                case 4:
                    {
                        if(flag == 1)
                        {
                            if(emp_sortEmployeeSurnameSector(pEmployees,len) == 0);
                            {
                                emp_printEmployees(pEmployees,len);
                            }
                            if(emp_printTotalPromAboveSalary(pEmployees,len) == 0)
                            {
                                emp_printTotalPromAboveSalary(pEmployees,len);
                            }

                        }
                        printf("\n~~~~No hay registros para mostrar~~~~\n");
                        break;
                    }
                case 5:
                    {
                        break;
                    }
            }
        }
    }

    return 0;
}

int emp_initArray(Employee* pEmployees, int len)
{
    int i;

    if(pEmployees != NULL && len > 0)
    {
       for(i=0; i<len;i++)
        {
            pEmployees[i].isEmpty = 1;
        }
    }
    return 0;
}

int emp_addEmployee(Employee* pEmployees,int len, char* msgE,int tries)
{
    int auxiliarIDEmployee;
    int posOfID;
    int indexFree;
    char bufferName[51];
    char bufferSurname[51];
    char bufferStrSalary[20];
    char bufferStrSector[20];
    int auxiliarSector;
    float auxiliarSalary;
    int ret = -1;

    if(pEmployees != NULL && len > 0) ///SIEMPRE VALIDAR AL USAR ARRAYS
    {
        auxiliarIDEmployee = emp_getID(pEmployees,len,msgE,tries);
        indexFree = emp_searchFreeSpace(pEmployees,len);
        posOfID = emp_findPosID(pEmployees,len,auxiliarIDEmployee);

        if((auxiliarIDEmployee >= 1) && (posOfID != -1))
        {
            if((getStringLetras(bufferName,"Ingrese nombre: ",msgE,tries) == 0) &&
            (getStringLetras(bufferSurname,"Ingrese apellido: ",msgE,tries) == 0))
            {
                if(getStringNumerosFloat(bufferStrSalary,"Ingrese salario: ",msgE,tries) == 0)
                {
                    auxiliarSalary = atof(bufferStrSalary);
                    if(getStringNumerosInt(bufferStrSector,"Ingrese sector: ",msgE,tries) == 0)
                    {
                        auxiliarSector = atoi(bufferStrSector);
                        strncpy(pEmployees[indexFree].name,bufferName,sizeof(bufferName));
                        strncpy(pEmployees[indexFree].surname,bufferSurname,sizeof(bufferSurname));
                        pEmployees[indexFree].sector = auxiliarSector;
                        pEmployees[indexFree].salary = auxiliarSalary;
                        pEmployees[indexFree].isEmpty = 0;
                        pEmployees[indexFree].idEmployee = generateID();
                        ret = 0;
                    }
                }
            }
        }
    }
    else
    {
        printf("\n~~~~El ID es invalido~~~~\n");
    }

    return ret;
}

int emp_searchFreeSpace(Employee* pEmployees, int len)
{
    int i;
    int ret=-1;

    if(pEmployees != NULL && len > 0)
    {
       for(i=0;i<len;i++)
        {
            if(pEmployees[i].isEmpty==1)
            {
                ret = i;
                break;
            }
        }
    }
    return ret;
}

int emp_findPosID(Employee* pEmployees, int len,int idEmp)
{
    int i;
    int ret=-1;

    if(pEmployees != NULL && len > 0)
    {
      for(i = 0;i < len;i++)
        {
            if(pEmployees[i].idEmployee == idEmp)
            {
                ret = i;
                break;
            }
        }
    }
    return ret;
}

int emp_removeEmployee(Employee* pEmployees, int len,char* msgE,int tries)
{
    int auxiliarID;
    int posID;
    int ret = -1;

    if(pEmployees != NULL && len > 0)
    {
       auxiliarID = emp_getID(pEmployees,len,msgE,tries);
       if(auxiliarID >= 1)
       {
            posID = emp_findPosID(pEmployees,len,auxiliarID);
            if(posID != -1)
            {
                pEmployees[posID].isEmpty = 1;
                ret = 0;
            }
            else
            {
                printf("\n\tID inexistente\t\n");
            }

        }
    }
    return ret;
}

int emp_getID(Employee * pPublicidad, int len, char* msgE, int tries)
{
    char bufferID[20];
    int auxiliarID;
    int ret = -1;

    if(pPublicidad != NULL && len > 0)
    {
        if(getStringNumerosInt(bufferID,"\nIngrese ID: ",msgE,tries) == 0)
        {
            auxiliarID = atoi(bufferID);
            ret = auxiliarID;
        }
    }
    return ret;
}

int emp_printEmployees(Employee* pEmployees,int len)
{
    int i;
    int flag = -1;

    if(pEmployees != NULL && len > 0)
    {
        for(i=0;i<len;i++)
        {
            if(pEmployees[i].isEmpty == 0)
            {
                printf("ID Empleado: %d\nNombre: %s\nApellido: %s\n"
                "Sector: %d\nSalario: %.2f\n--------"
                ,pEmployees[i].idEmployee,pEmployees[i].name,
                pEmployees[i].surname,pEmployees[i].sector,pEmployees[i].salary);
                flag = 0;
            }
        }
    if(flag)
        {
            printf("\n\tNo se encontraron valores\t\n");
        }
    }
    return 0;
}

int emp_sortEmployeeSurnameSector(Employee* pEmployees,int len)
{
    int i;
    int j;
    Employee buffer;

    if(pEmployees != NULL && len > 0)
    {
        for(i=0;i<len-1;i++)
        {
            for(j=i+1;j<len;j++)
            {
                if((pEmployees[i].surname > pEmployees[j].surname) &&(pEmployees[i].sector > pEmployees[j].sector))
                {
                    buffer = pEmployees[i];
                    pEmployees[i] = pEmployees[j];
                    pEmployees[j] = buffer;
                }
            }
        }
    }
    return 0;
}

int emp_printTotalPromAboveSalary(Employee* pEmployees, int len)
{
    int i;
    float acumuladorTotal = 0;
    float prom;
    int contador = 0;
    int auxiliarAboveSalary;

    if(pEmployees != NULL && len > 0)
    {
        for(i=0;i<len;i++)
        {
            if(pEmployees[i].isEmpty == 0)
            {
            acumuladorTotal += pEmployees[i].salary;
            contador += pEmployees[i].salary;
            }
        }
        prom = acumuladorTotal/contador;

        auxiliarAboveSalary = emp_aboveSalary(pEmployees,len,prom);

        printf("El salario total es: %.2f\n",acumuladorTotal);
        printf("El promedio es: %.2f\n",prom);
        printf("La cantidad de empleados con salario por encima del promedio es: %d",auxiliarAboveSalary);
    }
    return 0;
}

int emp_aboveSalary(Employee* pEmployees, int len, float prom)
{
    int contador = 0;
    int i;
    int ret = -1;

    if(pEmployees != NULL && len > 0)
    {

        for(i=0;i<len;i++)
        {
            if(pEmployees[i].salary > prom)
            {
                contador++;
                ret = contador;
            }
        }
    }
    return ret;
}

int emp_modifyEmployee(Employee* pEmployees,int len,char* msgE,int escape,int tries)
{
    char bufferName[51];
    char bufferSurname[51];
    char bufferStrSalary[20];
    char bufferStrSector[20];
    int auxiliarSector;
    float auxiliarSalary;
    int auxiliarID;
    int posID;
    int ret = -1;
    int opcion = 0;


    if(pEmployees != NULL && len > 0)
    {
       auxiliarID = emp_getID(pEmployees,len,msgE,tries);
       if(auxiliarID >= 1)
       {
            posID = emp_findPosID(pEmployees,len,auxiliarID);
            if(posID != -1)
            {
                pEmployees[posID].isEmpty = 1;
                ret = 0;
            }
            else
            {
                printf("\n\tID inexistente\t\n");
            }

        }
        do
        {
            getIntInRange(&opcion,"\n1)Ingrese nuevo nombre\n2)Ingrese nuevo apellido\n3)Ingrese nuevo salario\n"
                          "4)Ingrese nuevo sector\n5)Salir\n\n~~~~~~~~~~~~~~~~~~~~~~\n",msgE,1,escape,tries);
            switch(opcion)
            {
                case 1:
                {
                    if(getStringLetras(bufferName,"\nIngrese nombre: ",msgE,tries) == 0)
                       {
                           strncpy(pEmployees[posID].name,bufferName,sizeof(bufferName));
                           ret = 0;
                       }
                       break;
                }
                case 2:
                {
                   if((getStringLetras(bufferSurname,"\nIngrese apellido: ",msgE,tries) == 0))
                   {
                       strncpy(pEmployees[posID].surname,bufferSurname,sizeof(bufferSurname));
                       ret = 0;
                   }
                   break;
                }
                case 3:
                {
                    if((getStringNumerosFloat(bufferStrSalary,"\nIngrese salario: ",msgE,tries) == 0) && isNumberFloat(bufferStrSalary))
                    {
                        auxiliarSalary = atof(bufferStrSalary);
                        pEmployees[posID].salary = auxiliarSalary;
                    }
                    break;
                }
                case 4:
                {
                    if((getStringNumerosInt(bufferStrSector,"\nIngrese sector: ",msgE,tries) == 0) && isNumberInt(bufferStrSector))
                    {
                        auxiliarSector = atoi(bufferStrSector);
                        pEmployees[posID].sector = auxiliarSector;
                        ret = 0;
                    }
                    break;
                }
                default:
                {
                    ret = -1;
                }
            }
        }while(ret == -1 || opcion != escape);
    }
    return ret;
}

static int generateID(void)
{
    static int idEmp = 0;
    return idEmp++;
}
