#include <stdio.h>
#include <stdlib.h>

typedef struct ile
{
	int number;
	struct ile *next;
} ile;

int append(int pos, int ell, ile **pstrt);//add element in list, -1 for the last possion;
int pop(int pos, ile **pstrt);//delate element in list, -1 for the last possion;
int rm(ile *strt);//free the list;
int printl(ile *strt, char btw[]);//prints the list mit btm betwen elements, -1 for /s;
int len(ile *strt);//counts length of the list;

int main(void)
{
	ile *start = malloc(sizeof(ile));
	(*start).next = NULL;
	(*start).number = 0;
	append(-1, 1, &start);
	append(-1, 2, &start);
	append(-1, 3, &start);
	append(-1, 4, &start);
	append(-1, 5, &start);
	char btwin[] = "\n";
	printl(start, btwin);
	printf("Len: %d;\n", len(start));
	pop(5, &start);
	pop(1, &start);
	pop(0, &start);
	pop(-1, &start);
	printl(start, btwin);
	rm(start);
	return 0;
}

//add element in list, -1 for the last possion;
int append(int pos, int ell, ile **pstrt)
{
	ile *strt = *pstrt;
	ile *act = NULL, *bf = NULL;
	int i;
	for (i = 0; (i <= pos || pos == -1) &&  strt != NULL; i++)
	{
		bf = act;
		act = strt;
		//printf("Number: %d;\n", (*strt).number);
		strt = (*strt).next;
	}
	if (strt == NULL && pos == -1)
	{
		(*act).next = malloc(sizeof(ile));
		(*((*act).next)).next = NULL;
		(*((*act).next)).number = ell;
	}
	else if (pos >= 0)
	{
		ile *ne = malloc(sizeof(ile));
		(*ne).number = ell;
		(*ne).next = act;
		if (pos == 0)
		{
			*pstrt = ne;
		}
		else
		{
			(*bf).next = ne;
		}
	}
	return 0;
}
//prints the list mit btm betwen elements, -1 for /s;
int printl(ile *strt, char btw[])
{
	while (strt != NULL)
	{
		printf("%d%s", (*strt).number, btw);
		strt = (*strt).next;
	}
	return 0;
}

//free the list;
int rm(ile *strt)
{
	ile *next;
	do
	{
		next = (*strt).next;
		free(strt);
		strt = next;
	} while (next != NULL);
	return 0;
}

//counts length of the list;
int len(ile *strt)
{
	int rv = 0;
	while (strt != NULL)
	{
		strt = (*strt).next;
		rv++;
	}
	return rv;
}

//delate element in list, -1 for the last possion;
int pop(int pos, ile **pstrt)
{
	ile* next = *pstrt;
	ile* act = NULL;
	ile* bf = NULL;
	int i;
	for (i = 0; (i <= pos || pos == -1) && next != NULL; i++)
	{
		bf = act;
		act = next;
		next = (*next).next;
	}
	printf("Masseg: 0;\n");
	//if (i-1 != pos || (pos < 0 && pos != -1)) { return 1; }
	if ((i-1 != pos && pos != -1)|| (pos < 0 && pos != -1)) { return 1; }
	printf("Masseg: 1;\n");
	if (pos == -1)
	{
		//printf("In condithion;\n");
		//printf("act.number: %d;\n", (*act).number);
		(*bf).next = NULL;
		free(act);
		return 0;
	}
	else if (pos == 0)
	{
		*pstrt = next;
	}
	else
	{
		(*bf).next = next;
	}
	free(act);
	return 0;
}
