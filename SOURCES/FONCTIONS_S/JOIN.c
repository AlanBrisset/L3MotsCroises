#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zmq.h>
#include <unistd.h>

#include "fonctions.h"


void JOIN(void *responder, char choix[]){

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
        char * line = NULL;
        size_t len = 0;
        ssize_t read;

	  
	fichier = fopen ("./RESSOURCES/USERS.txt", "r");
	if(fichier==NULL)
	printf ("Impossible d'ouvrir le fichier USERS.txt\n");

	else

	{


 	while ((read = getline(&line, &len, fichier)) != -1) {
	printf("%s\n",line);

	if (!strcmp(line,nomJoueur)){
        existe=1;
        zmq_send (responder, "Vous êtes déjà connecté !", 40, 0);  /*Envoi du message de confirmation*/
    	}
	}

	}


/* Si il n'existe pas, alors on l'ajoute */

  	if(!existe){

       fichier = NULL;
        fichier = fopen("./RESSOURCES/USERS.txt", "a");
 
       if (fichier != NULL)
        {

	fprintf (fichier,"\n%s",nomJoueur);

        fclose(fichier);

        } 


        zmq_send (responder, "Nouveau joueur ajouté, Bienvenue !", 30, 0);  /*Envoi du message de confirmation*/
}

}
