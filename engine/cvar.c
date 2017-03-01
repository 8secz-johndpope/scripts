/*
 * cvar.c - ����� ���������� �� ������������ cvar-�� - ������������ ����������,
 * ������� ����� �������� ������������ � ����� ���� �������� � �������� ������
 * ��������� 
 */
#include <stdio.h>
#include <stdlib.h>
#include "cvar.h"
#include "common.h"

/* "����������" cvar */
cvar_t  *cvar_vars;

/* ������������ ���������� ���������� ���������� */
#define MAX_CVARS 31
/* ������ �������� ��� � ������ */
cvar_t  cvar_indexes[MAX_CVARS];
/* ������� ������ */
int     cvar_numIndexes = 0;



/*
==============================
Cvar_FindVal
����� cvar �� �����
==============================
*/
cvar_t *Cvar_FindVar(char *var_name)
{
    cvar_t  *var;
    for(var = cvar_vars; var; var = var->next)
    {
        if(var_name == var->name)return var;
    };
    return NULL;
};


/*
==============================
Cvar_Set
����������/��������� cvar
==============================
*/
cvar_t  *Cvar_Set(char *var_name, char *value)
{
    cvar_t  *var;

    var = Cvar_FindVar(var_name);
    if(var)
    {
        var->value = value;     //���� ��� ���������� - ������ ������� value
    }
    else
    {
        if(cvar_numIndexes > MAX_CVARS) Comm_Error(1, "MAX_CVARS"); // ����� cvar-��

        var = &cvar_indexes[cvar_numIndexes];  //�������� ����� ������� � �������� ��� ����
        cvar_numIndexes++;
        var->name = var_name;
        var->value = value;
        var->defaultValue = value;             //��������� ��������
        var->next = cvar_vars;
        cvar_vars = var;
    };
    return var;
};


/* ������� ������ */

/*
==============================
Cvar_PrintAll
�������� ��� ����������� ���������� ����������
==============================
*/
void Cvar_PrintAll(void)
{
    cvar_t *var;
    for(var = cvar_vars; var; var = var->next)
    {
        printf("Var: \"%s\" = \"%s\"\n", var->name, var->value);
    };
};
