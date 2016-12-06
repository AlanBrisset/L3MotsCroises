#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zmq.h>
#include <unistd.h>

#include "fonctions.h"


char recupererArguments(char choix[]){

	char *fonction= choix;
	char *array[10];
	int i=0;

	array[i] = strtok(fonction," ");

	while(array[i]!=NULL)
	{
	   array[++i] = strtok(NULL," ");
	}

return array;
}
