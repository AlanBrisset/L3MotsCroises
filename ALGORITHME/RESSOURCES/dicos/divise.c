#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zmq.h>
#include <unistd.h>

void main(int longueur){


	int taille = longueur;
	taille++;
	char mot_bis[longueur];
 	FILE* fichier = NULL;
	FILE* fichier2 = NULL;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;

	  
	fichier = fopen ("dico.txt", "r");
	fichier2 = fopen("dico25.txt", "a");


	if(fichier==NULL)
	printf ("Impossible d'ouvrir le fichier USERS.txt\n");

	else

	{

 	while ((read = getline(&line, &len, fichier)) != -1) {

	if (strlen(line) == 26 && fichier2 != NULL){

	printf("%s\n",line);
	fprintf (fichier2,"\n%s",line);
    	}
	}


 fclose(fichier);
 fclose(fichier2);

	}



}




