#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zmq.h>
#include <unistd.h>

#include "fonctions.h"


int JOIN(void *responder, char choix[]){

	char *fonction= choix;
	char *parametres[100];
	int i=0;

	parametres[i] = strtok(fonction," ");

	while(parametres[i]!=NULL)
	{
	   parametres[++i] = strtok(NULL," ");
	}

 /* Divise la chaine en plusieurs variables dans un tableau de chaine de caractere */

	char *nomJoueur = strdup (parametres[1]); /* Recupération de la variable NOM */
	
	printf("\n----------------- TENTATIVE DE CONNECTION AVEC CLIENT ------------------\n\n");
        printf("Le nom joueur voulant se connecter est : ");
        printf (nomJoueur); /* Affichage du nom du joueur */
        printf ("\n");
        sleep (1);    

/* AJOUT DE L'ALGORITHME (variable buffer contient nom utilisateur )*/

/* Verifie si le joueur n'est pas déjà connecté */
	int longueur = strlen(nomJoueur);
	int existe = 0;
	char mot_bis[longueur];
 	FILE* fichier = NULL;
FILE* fichierbis = NULL;
FILE* fichierter = NULL;
        char * line = NULL;
	char * line2 = NULL;
	char * line3 = NULL;
        size_t len = 0;
        ssize_t read;
	ssize_t read2;
	ssize_t read3;


	  
	fichier = fopen ("./RESSOURCES/USERS.txt", "r");
	if(fichier==NULL)
	printf ("Impossible d'ouvrir le fichier USERS.txt\n");

	else

	{
	

 	while ((read = getline(&line, &len, fichier)) != -1) {

	if (!strcmp(line,nomJoueur)){
        existe=1;

/*
        printf("\n----------------- AFFICHAGE DES JOUEURS CONNECTES ------------------\n\n");

        while ((read2 = getline(&line2, &len, fichier)) != -1) {

	printf(line2);
	} */

zmq_send (responder, "Vous êtes déjà connecté !", 60, 0);  /*Envoi du message de confirmation*/

    	}
	}

        

        fclose(fichier);

	}





/* Si il n'existe pas, alors on l'ajoute */

  	if(!existe){

        /*fichier = NULL;*/
        fichierbis = fopen("./RESSOURCES/USERS.txt", "a");
 
        if (fichierbis != NULL)
        {
        
	fprintf (fichierbis,"%s\n",nomJoueur);

        } 
else
printf("on ouvre pas ici");


       

/*
        char message[60];
        strcat(message, "Nouveau joueur ajouté, Bienvenue ");
        strcat(message, nomJoueur);
        strcat(message, " !"); */


        zmq_send (responder, "Nouveau joueur ajouté, Bienvenue !", 60, 0);  /*Envoi du message de confirmation*/


fclose(fichierbis);

        }

        fichierter = fopen("./RESSOURCES/USERS.txt", "r");

        printf("\n----------------- AFFICHAGE DES JOUEURS CONNECTES ------------------\n\n");

        while ((read3 = getline(&line3, &len, fichierter)) != -1) {

	printf(line3);

	}

        printf("\n\n--------------------\n\n");

fclose(fichierter);



return 1;
}
