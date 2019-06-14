#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
} Employee;

Employee* employee_new();
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldo);
int employee_delete();

int employee_setId(Employee* this, char* value);
int employee_getId(Employee* this,int* value);

int employee_setNombre(Employee* this,char* value);
int employee_getNombre(Employee* this,char* value);

int employee_setHorasTrabajadas(Employee* this,char* value);
int employee_getHorasTrabajadas(Employee* this,int* value);

int employee_setSueldo(Employee* this,char* value);
int employee_getSueldo(Employee* this,int* value);

int employee_sortByName(void* pFirstEmployee,void* pSecondEmployee);

#endif // employee_H_INCLUDED
