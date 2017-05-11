#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zmq.h>
#include <unistd.h>
#include <string.h>

#include "fonctions.h"



int JOIN(void *requester, char choix[]){


/* ---------------------- VERIFICATION DE LA VALIDITE LA FOCNTION ----------------------*/ 
 
	char	*pointeur;
	char	*separateur = { " " };     /* Le séparateur*/
	char 	*buffer;
	char    *Chaine_Entrante = choix;
	int     nb_mot=1;

	buffer =  strdup (Chaine_Entrante);

/* premier appel, */
	pointeur = strtok( buffer, separateur  );
    
	while( pointeur != NULL ) 
	{
/* Cherche les autres separateur */
	pointeur = strtok( NULL, separateur  );
	if ( pointeur != NULL )
	{
	nb_mot++; /* increment du nombre de mot*/

	}
	}


/* ---------------------- SI OK, ENVOI DU BUFFER AU SERVER ----------------------*/ 

	if(nb_mot == 2){

        printf("\n------------ TEST DE CONNEXION AVEC LE SERVEUR -----------\n\n"); /* Affichage du message de confirmation du nombre d'arguments */

        zmq_send(requester, choix, 60, 0); /* Envoi de la fonction au server */


/* ---------------------- REPONSE DU SERVER ----------------------*/ 


        char buffer[60]; /* Création de la variable buffer, qui contiendra le message de confirmation */

        zmq_recv(requester, buffer, 60, 0); /* Réception du message de confirmation */
        printf(buffer); /* Affichage du message de confirmation */

        printf("\n\n--------------------\n\n");


	return 1;
	}


/* ---------------------- SINON, MESSAGE D'ERREUR ----------------------*/ 


	else {

	printf("\nMerci de bien entrer le bon nombre d'arguments pour la fonction JOIN\n\n"); /* Affichage du message d'erreur de nombre d'arguments */
	printf("Du type : JOIN <idnetifiant>"); /* Affichage du message du type attendu de la fonction */
	printf("\n\n--------------------\n\n");
	return 0;

	}

}

