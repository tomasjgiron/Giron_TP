#ifndef ARRAYEMPLOYEES_H_INCLUDED
#define ARRAYEMPLOYEES_H_INCLUDED

typedef struct
{
    int idEmployee; /// se va autoincrementando
    char name[51];
    char surname[51];
    float salary;
    int sector;
    int isEmpty; /// lleno=0 ; vacio=1
}Employee;

int emp_menu(Employee* pEmployees,int len,char* textMenu,char* msgE,int escape,int tries);

int emp_initArray(Employee* pEmployees, int len);

int emp_addEmployee(Employee* pEmployees,int len, char* msgE,int tries);

int emp_removeEmployee(Employee* pEmployees, int len,char* msgE,int tries);

int emp_printEmployees(Employee* pEmployees,int len);

int emp_sortEmployeeSurnameSector(Employee* pEmployees,int len,int order);

int emp_printTotalPromAboveSalary(Employee* pEmployees, int len);

int emp_modifyEmployee(Employee* pEmployees,int len,char* msgE,int escape,int tries);


int emp_searchFreeSpace(Employee* pEmployees, int len);

int emp_findPosID(Employee* pEmployees, int len,int idEmp);

int emp_getID(Employee* pEmployees, int len, char* msgE, int tries);

int emp_aboveSalary(Employee* pEmployees, int len, float prom);

#endif // ARRAYEMPLOYEES_H_INCLUDED
