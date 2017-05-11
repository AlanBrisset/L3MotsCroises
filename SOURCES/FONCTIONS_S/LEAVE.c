#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zmq.h>
#include <unistd.h>

#include "fonctions.h"


int LEAVE(void *responder, char choix[]){
    
    
    
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
        printf("Le nom joueur voulant se déconnecter est : ");
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



	  
	fichier = fopen ("./RESSOURCES/USERS.txt", "r+");
	if(fichier==NULL)
	printf ("Impossible d'ouvrir le fichier USERS.txt\n");

	else

	{
	

 	while ((read = getline(&line, &len, fichier)) != -1) {

	if (!strcmp(line,nomJoueur)){
        existe=1;
        fprintf("", line);
    


    zmq_send (responder, "Joueur déconnecté par le serveur !", 60, 0);  /*Envoi du message de confirmation*/

    	}
	}

        
        fclose(fichier);
        
        

	}





/* Si il n'existe pas, alors on l'ajoute */

  	if(!existe){

       


        zmq_send (responder, "Vous n'êtes pas connecté, connectez vous avec JOIN !", 60, 0);  /*Envoi du message de confirmation*/





return 1;
}
    
    

    
}
