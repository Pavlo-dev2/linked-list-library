#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ule
{
	unsigned long length;//length of the array
	void *el;//pointer on the array
	char type;//type of the array, i - int, f - float, c - char
	struct ule *next;
} ule;

ule* append(void *value, unsigned long length, char type, ule *pn, unsigned long pos);//add element(array) to possion pos, -1 for add to the end, NULL if list is new
ule* pop(ule *pn, unsigned long pos);//delate element on possion pos, -1 for delate the last element, NULL if list is new
int printl(ule* pn, char btw[], char after[]);//prints all of arrays in the list with string btw bitwin elements and after bitwin arrays.
int copyarr(void *to, void *from, char type, unsigned long length);//copy arrays;

int main(void)
{
	//ule test
	
	//create variabls 
	int one[] = {1, 2, 3};
	char two[] = "two";
	float three = 3.7896;
	int fohr = 4;
	char fife = '5';

	//add then to the list
	printf("append test\n");
	ule *st = append(one, 3, 'i', NULL, 0);
	st = append(two, strlen(two), 'c', st, 0);
	st = append(&three, 1, 'f', st, 1);
	st = append(&fohr, 1, 'i', st, -1);
	st = append(&fife, 1, 'c', st, 3);

	//print the list
	printl(st, ";", "\n");

	//pop test
	printf("pop test\n");
	st = pop(st, 0);
	st = pop(st, 2);
	st = pop(st, 1);
	
	//print the list
	printl(st, "; ", "\n");

	return 0;
}

int printl(ule* pn, char btw[], char after[])
{
	//printf("In printl\n");
	//printf(": %lu\n", pn->length);
	while (pn != NULL)
	{
		unsigned long i, len;
		i = 0;
		len = pn->length;
		//printf("In loop %lu;\n", pn->length);
		switch (pn->type)
		{
			case 'f':
				while (i < len)
				{
					printf("%f%s", ((float*)pn->el)[i], btw);
					i++;
				}
				break;
			case 'c':
				while (i < len)
				{
					printf("%c%s", ((char*)pn->el)[i], btw);
					i++;
				}
				break;
			case 'i':
				while (i < len)
				{
					printf("%i%s", ((int*)pn->el)[i], btw);
					i++;
				}
				break;
		}
		printf("%s", after);
		pn = pn->next;
	}
	return 0;
}

ule* append(void *value, unsigned long length, char type, ule *pn, unsigned long pos)
{
	ule *st = pn;//start of the list
	ule *bf = NULL;//element before the new element
	ule *af = NULL;//element that was after bf, and will be after the new element
	
	//create the new element
	ule *new = malloc(sizeof(ule));
	if (new == NULL)
		return 0;
	new->type = type;
	new->length = length;
	//printf("In append, length: %lu, new->length: %lu\n", length, new->length);
	void *pvalue;
	switch (type)
	{
			case 'f':
				pvalue =  malloc(sizeof(float)*length);
				if (pvalue == NULL) return NULL;
				break;
			case 'c':
				pvalue = malloc(sizeof(char)*length);
				if (pvalue == NULL) return NULL;
				break;
			case 'i':
				pvalue =  malloc(sizeof(int)*length);
				if (pvalue == NULL) return NULL;
				break;
	}
	copyarr(pvalue, value, type, length);
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
		unsigned long ap = 0;//actual position
		ule *ae = pn;//actual element
		while (ap+1 != pos)
		{
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

ule* pop(ule* pn, unsigned long pos)
{
	if (pn == NULL) return NULL;

	ule *st = pn;//start of the list
	ule *bf;//element before the element to delate
	ule *td;//element to delate
	ule *af;//element after the element to delate
	unsigned long apos = 0;//actual possion
	
	//if you hove to delate first element
	if (pos == 0 || pos == -1 && st->next == NULL)
	{
		free(st->el);
		if (st->next != NULL)
		{
			af = st->next;
			free(st);
			return af;
		}
		free(st);
		return NULL;
	}
	else if (pos > 0 || pos == -1)
	{
		//printf("In condition\n");
		//find bf
		for (ule *ae = st; (apos < pos || pos == -1) && ae->next != NULL; apos++)
		{
			bf = ae;
			ae = ae->next;
		}
		if (bf->next->next != NULL)
		{
			af = bf->next->next;
		}
		else
		{
			af = NULL;
		}
		//printf("bf->next == NULL: %d\n", bf->next == NULL);
		free(bf->next->el);
		free(bf->next);
		bf->next = af;
		return st;
	}
	return NULL;
}

int copyarr(void *to, void *from, char type, unsigned long length)
{
	while (length > 0)
	{
		switch (type)
		{
			case 'f':
				((float*)to)[length-1] = ((float*)from)[length-1];
				break;
			case 'c':
				((char*)to)[length-1] = ((char*)from)[length-1];
				break;
			case 'i':
				((int*)to)[length-1] = ((int*)from)[length-1];
				break;
		}
		length--;
	}
	return 0;
}
