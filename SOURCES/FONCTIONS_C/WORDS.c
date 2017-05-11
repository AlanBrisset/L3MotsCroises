#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zmq.h>
#include <unistd.h>

#include "fonctions.h"



int WORDS(void *requester){

        char buffer[10]; 

/* ENVOYER DU RIEN */
        zmq_send(requester, "ENVOIAEZRT", 30, 0);

zmq_send(requester, "ENVOIAEZRT", 30, 0);



/* RECEPTION DE LA GRILLE */

        printf("\n\n----------------- RECEPTION DES MOTS A TROUVER ------------------\n\n");
        
        char buff[60];

        zmq_recv(requester, buff, 60, 0); 
        printf("zzzz");
	char *parametres[100];
	int i=0;

	parametres[i] = strtok(buff," ");

	while(parametres[i]!=NULL)
	{
	   parametres[++i] = strtok(NULL," ");
	} 



/* Affichage des mots à trouver pour le client */ 
        
	int j = sizeof(parametres);

        for (i=0; i<j; i++)
        {
        printf(parametres[i]);
	printf("     ");

        }
    

        printf("\n\n--------------------\n\n");
        
        return 1;


}


