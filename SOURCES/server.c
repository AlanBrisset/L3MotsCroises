#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include "FONCTIONS_S/fonctions.h"

#define PORT1 8000;
#define PORT2 8001;

int main (void)
{

    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:7878");
    assert (rc == 0);

    /* Variables de validation d'etats */
    int connexion = 0;
    int grille = 0;

    while (1) {

printf ("\n------------- EN ATTENTE DE RECEPTION D'UNE COMMANDE -------------\n");

    char choix[100];
    zmq_recv (responder, choix, 100, 0); /* Réception de la fonction du joueur*/
    char	*pointeur;
    char	*separateur = { " " };     /* Le séparateur*/
    char 	*buffer;
    char        *Chaine_Entrante = choix;

    buffer =  strdup (Chaine_Entrante);

/* DETERMINATON DE LA FONCTION EXECUTEE */

pointeur = strtok( buffer, separateur  );


 /* APPELS DES FONCTIONS A AJOUTER DANS L'ORDRE ! */

 	/* FONCTIONS DE JOIN (YOUSSEF) */  
if(!strcmp(pointeur,"JOIN")){ 
connexion = JOIN(responder,choix);
}


/*Changement de port avec le client */

	/*FONCTIONS DE GRID (ALAN) */
if(connexion){

grille = GRID(responder,choix);

}

	/*FONCTIONS DE WORDS (LEO)*/

if(grille){


}

	/*FONCTIONS DE FOUND (LEO)*/

else if(!strcmp(pointeur,"FOUND")){

}

	/*FONCTIONS DE ATTRIBUTION DE SCORE (YOUSSEF) */
else if(!strcmp(pointeur,"SCORE")){

}

}

    return 0;
}
