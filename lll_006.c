#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ule
{
	void *el;
	char type;//i - int, f - float, s - string, c - char.
	struct ule *next;
} ule;

ule* append(void *value, char type, ule *pn, long pos);//add element to possion pos, -1 for add to the end, NULL if list is new
int printl(ule* pn, char btw[]);//prints all of element in the list with string btw bitwin

int main(void)
{
	//ule test
	
	//create variabls 
	int one = 1;
	char two[] = "two";
	float three = 3.7896;

	//add then to the list
	ule *st = append(&one, 'i', NULL, 0);
	st = append(&two, 's', st, 1);
	st = append(&three, 'f', st, 1);

	//print he list
	printl(st, "\n");
	return 0;
}

int printl(ule* pn, char btw[])
{
	while (pn != NULL)
	{
		switch (pn->type)
		{
			case 'f':
				printf("%f%s", *(float*)pn->el, btw);
				break;
			case 's':
				printf("%s%s", (char*)pn->el, btw);
				break;
			case 'c':
				printf("%c%s", *(char*)pn->el, btw);
				break;
			case 'i':
				printf("%d%s", *(int*)pn->el, btw);
				break;
		}
		//printf("%d%s", *(pn->el), btw);
		pn = pn->next;
	}
	return 0;
}

ule* append(void *value, char type, ule *pn, long pos)
{
	ule *st = pn;//start of the list
	ule *bf = NULL;//element before the new element
	ule *af = NULL;//element that was after bf, and will be after the new element
	
	//create the new elsement
	ule *new = malloc(sizeof(ule));
	if (new == NULL)
		return 0;
	new->type = type;
	void *pvalue;
	switch (type)
	{
			case 'f':
				pvalue =  malloc(sizeof(float));
				*(float*)pvalue = *(float*)value;
				break;
			case 's':
				pvalue =  malloc(strlen((char*)value)+1);
				strcpy((char*)pvalue, (char*)value);
				break;
			case 'c':
				pvalue = malloc(sizeof(char));
				*(char*)pvalue = *(char*)value;
				break;
			case 'i':
				pvalue =  malloc(sizeof(int));
				*(int*)pvalue = *(int*)value;
				break;
	}
	new->el = pvalue;
	new->next = NULL;

	//if you need to create a new list
	if (pn == NULL)
	{
		if (pos != 0)
		{
			return NULL;
		}
		return new;
	}
	
	//if you heve to put the new element on the begining(0 position)
	if (pos == 0)
	{
		af = pn;
		st = new;
		st->next = af;
		return st;
	}
	//if you need to put the element on position 1
	else if (pos == 1)
	{
		bf = pn;
		if (bf->next == NULL)
		{
			bf->next = new;
		}
		else
		{
			af = bf->next;
			bf->next = new;
			bf->next->next = af;
		}
		return st;
	}
	//else if you need to put element on the last position
	else if (pos == -1)
	{
		ule *ae;//actual element
		for (ae = pn; ae->next != NULL; ae = ae->next);
		ae->next = new;
		return st;
	}
	//else if you need to put element after position 1
	else if (pos > 1)
	{
		//find bf
		long ap = 0;//actual position
		ule *ae = pn;//actual element
		while (ap+1 != pos)
		{
			//printf("ap: %ld\n", ap);
			/*if (ae == NULL)
			{
				return NULL;
			}*/	
			//printf("ae.num = %d\nae.next==NULL = %d\n", ae->el, ae->next == NULL);
			ae = ae->next;
			ap++;
			if (ae == NULL)
			{
				return NULL;
			}	
		}
		bf = ae;
		af = ae->next;
		bf->next = new;
		bf->next->next = af;
		return pn;	
	}
	else
	{
		return NULL;
	}
}
