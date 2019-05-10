#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arraynuevo.h"
#include "ArrayEmployees.h"

static int generateID(void);
/** \brief Proporciona un menú a modo de función main que realiza
* las tareas de alta, baja, modificacion e informes del ABM
* \param lista puntero de Empleado al array de empleados
* \param tamaño del array
* \param textMenu pasa por parámetro todo lo que tendra el texto del menu
* \param msgE mensajes de error de las funciones
* \param escape delimita el numero maximo con el cual saldra de la iteracion y el final del menu
* \param tries reintentos a la hora de volver a cargar algo
* \return retorna 0 diciendo que no hay error
*/
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
                            emp_sortEmployeeSurnameSector(pEmployees,len,1);
                            emp_printEmployees(pEmployees,len);
                            emp_printTotalPromAboveSalary(pEmployees,len);
                        }
                        else
                        {
                            printf("\n~~~~No hay registros para mostrar~~~~\n");
                        }
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
/** \brief Indica que todas las posiciones del array están
* vacías al colocar el isEmpty como 1
* \param lista puntero de Empleado al array de empleados
* \param len del array
* \return retorna 0 diciendo que no hay error
*/
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
/** \brief Realiza la funcion de carga de empleados dentro
* del array
* \param lista puntero de Empleado al array de empleados
* \param tamaño del array
* \param msgE mensajes de error de las funciones
* \param tries reintentos a la hora de volver a cargar algo
* \return retorna 0 diciendo que no hay error o -1 si encuentra un error
*/
int emp_addEmployee(Employee* pEmployees,int len, char* msgE,int tries)
{
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
        indexFree = emp_searchFreeSpace(pEmployees,len);

        if(indexFree >= 0)
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
/** \brief Busca el espacio en el array donde haya espacio (-1)
* \param lista puntero de Empleado al array de empleados
* \param tamaño del array
* \return retorna la posicion o -1 si encuentra un error
*/
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
/** \brief Busca la posicion de un ID comparandolo con otro
* \param lista puntero de Empleado al array de empleados
* \param tamaño del array
* \param idEmp usa para comparar un id con otro
* \return retorna la posicion o -1 si encuentra un error
*/
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
/** \brief Realiza la baja lógica de algún empleado dentro de la nómina
* \param lista puntero de Empleado al array de empleados
* \param tamaño del array
* \param msgE mensajes de errores
* \param tries reintentos de la función
* \return retorna 0 diciendo que no hay error
*/
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
/** \brief Le deja ingresar al usuario un ID
* \param lista puntero de Empleado al array de empleados
* \param tamaño del array
* \param msgE mensajes de errores
* \param tries reintentos de la función
* \return retorna el ID que el usuario ingresa o -1 si hay un error
*/
int emp_getID(Employee * pEmployees, int len, char* msgE, int tries)
{
    char bufferID[20];
    int auxiliarID;
    int ret = -1;

    if(pEmployees != NULL && len > 0)
    {
        if(getStringNumerosInt(bufferID,"\nIngrese ID: ",msgE,tries) == 0)
        {
            auxiliarID = atoi(bufferID);
            ret = auxiliarID;
        }
    }
    return ret;
}
/** \brief Permite imprimir el array completo de Empleado
* \param lista puntero de Empleado al array de empleados
* \param tamaño del array
* \return retorna 0 diciendo que no hay error o -1 si lo hay
*/
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
                printf("\nID Empleado: %d\nNombre: %s\nApellido: %s\n"
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
/** \brief Permite ordenar el array por apellido y, en caso
* de igualdad, los ordena por sector
* \param lista puntero de Empleado al array de empleados
* \param len del array
* \return retorna 0 diciendo que no hay error o -1 si lo hay
*/
int emp_sortEmployeeSurnameSector(Employee* pEmployees,int len,int order)
{
    int i;
    int j;
    Employee buffer;
    int ret = -1;

    if(pEmployees != NULL && len > 0)
    {
        for(i=0;i<len-1;i++)
        {
            for(j=i+1;j<len;j++)
            {
                if(order == 1 && (strcmp(pEmployees[j].surname,pEmployees[i].surname) < 0))
                {
                    buffer = pEmployees[i];
                    pEmployees[i] = pEmployees[j];
                    pEmployees[j] = buffer;
                    ret = 0;
                }
                else if(order == 0 && (strcmp(pEmployees[j].surname,pEmployees[i].surname) > 0))
                {
                    buffer = pEmployees[i];
                    pEmployees[i] = pEmployees[j];
                    pEmployees[j] = buffer;
                    ret = 0;
                }
                else if(strcmp(pEmployees[j].surname,pEmployees[i].surname) == 0)
                {
                    if(pEmployees[i].sector > pEmployees[j].sector)
                    {
                        buffer = pEmployees[i];
                        pEmployees[i] = pEmployees[j];
                        pEmployees[j] = buffer;
                        ret = 0;
                    }
                }
            }
        }
    }
    return ret;
}
/** \brief Imprime el total de los salarios su promedio y
* la cantidad de empleados cuyos salarios superar el promedio
* \param lista puntero de Empleado al array de empleados
* \param tamaño del array
* \return retorna 0 diciendo que no hay error
*/
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
            contador++;
            }
        }
        prom = acumuladorTotal/contador;

        auxiliarAboveSalary = emp_aboveSalary(pEmployees,len,prom);

        printf("\nEl salario total es: %.2f\n",acumuladorTotal);
        printf("El promedio es: %.2f\n",prom);
        printf("La cantidad de empleados con salario por encima del promedio es: %d",auxiliarAboveSalary);
    }
    return 0;
}
/** \brief Funcion auxiliar de la anterior para determinar la cantidad
* de empleados cuyos salarios son mayores al promedio
* \param lista puntero de Empleado al array de empleados
* \param len del array
* \param prom recibe el promedio por parametro
* \return retorna la cantidad de empleados
*/
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
/** \brief Permite modificar la lista de Empleados
* \param lista puntero de Empleado al array de empleados
* \param tamaño del array
* \param msgE mensajes de errores
* \param escape delimita el numero maximo con el cual saldra de la iteracion y el final del menu
* \param tries reintentos de la función
* \return retorna 0 diciendo que no hay error
*/
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
/** \brief Genera un ID de Empleado
* \return retorna el ID generado y lo incrementa cada vez que se usa
*/
static int generateID(void)
{
    static int idEmp = 0;
    return idEmp++;
}
