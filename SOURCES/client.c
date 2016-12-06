/*
 * client.c
 *
 *  Created on: 24 oct. 2016
 *      Author: tc
 */

#include <string.h>
#include <zmq.h>
#include <stdio.h>
#include <unistd.h>

#include "FONCTIONS_C/fonctions.h"

#define PORT1 8000;
#define PORT2 8001;

int main (void)
{
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:7878");

/* ---------------------- BOUCLE DE CHOIX DU CLIENT ------------------------- */
    
while(1){

    printf ("\nVeuillez choisir la fonction à executer : JOIN, GRID, WORD ou FOUND\n");
    char choix[100];

    fgets(choix, sizeof choix, stdin); /* Entrée du nom du joueur */
    char	*pointeur;
    char	*separateur = { " " };     /* Le séparateur*/
    char 	*buffer;
    char    *Chaine_Entrante = choix;
    buffer =  strdup (Chaine_Entrante);

/* DETERMINATON DE LA FONCTION EXECUTEE */

if(strchr(buffer, ' ')!=NULL ){
pointeur = strtok( buffer, separateur  );
}

else {
pointeur = buffer;
}



/* APPELS DES FONCTIONS A AJOUTER DANS L'ORDRE ! */

 	/* FONCTIONS DE JOIN (YOUSSEF) */   
if(!strcmp(pointeur,"JOIN")){
JOIN(requester, choix);


	/*FONCTIONS DE GRID (LEO) */


}

	/*FONCTIONS DE WORDS (LEO)*/

else if(!strcmp(pointeur,"WORDS")){

}

	/*FONCTIONS DE FOUND (ALAN)*/

else if(!strcmp(pointeur,"FOUND")){

}

	/*FONCTIONS DE ATTRIBUTION DE SCORE (ALAN) */
else if(!strcmp(pointeur,"SCORE")){

}

else {

printf(pointeur);
printf("\nLa fonction entrée n'existe pas\n\n");
}

}


    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}

