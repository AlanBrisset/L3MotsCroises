#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zmq.h>
#include <unistd.h>

#include "fonctions.h"


int FOUND(void *responder, char choix[]){


	printf ("\n");
	char *fonction= choix;
	char *parametres[100];
	int i=0;

	fonction += 6;

 /* Divise la chaine en plusieurs variables dans un tableau de chaine de caractere */

	char *mot = strdup (fonction); /* Recupération de la variable WORDS */
	
	printf("\n----------------- REPONSE RECUE PAR LE CLIENT ------------------\n\n");

        printf("Le mot à verifier pour le client est : ");
        printf (mot); /* Affichage du mot+ coordonnées du joueur */
        printf ("\n");
        sleep (1);    

	/* AJOUT DE L'ALGORITHME (variable buffer contient nom utilisateur )*/

	/* Verifie si le joueur n'est pas déjà connecté */
	int longueur = strlen(mot);
	int existe = 0;
	char mot_bis[longueur];
 	FILE* fichier = NULL;
        char * line = NULL;

        size_t len = 0;


        ssize_t read;

	  
	fichier = fopen ("./RESSOURCES/WORDS.txt", "r");
	if(fichier==NULL)
	printf ("Impossible d'ouvrir le fichier WORDS.txt\n");

	else

	{
	

 	while ((read = getline(&line, &len, fichier)) != -1) {

	if (!strcmp(line,mot)){
        existe=1;

        printf("MOT VALIDE\n\n");
        printf("\n-----------------------------------\n\n");

        zmq_send (responder, "BRAVO ! MOT VALIDE", 60, 0);  /*Envoi du message de confirmation*/

        return 0;
    	}
	}

	}


/* Sinon */

  	if(!existe){

        printf("MOT NON-VALIDE\n\n");
        printf("\n-----------------------------------\n\n");


        zmq_send (responder, "MOT NON VALIDE, REESSAYEZ", 40, 0);  /*Envoi du message de confirmation*/


       return 1;
       }

       fclose(fichier);

}
