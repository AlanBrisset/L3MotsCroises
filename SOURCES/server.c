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


    /* CREATION DES FLUX DE COMMUNICATION AVEC PORTS 1 & 2 */

    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:1111");
    assert (rc == 0);

    void *context2 = zmq_ctx_new ();
    void *responder2 = zmq_socket (context2, ZMQ_REP);
    rc = zmq_bind (responder2, "tcp://*:2222");
    assert (rc == 0);

    /* Variables de validation d'etats */
    int connexion = 0;
    int grille = 0;
    int mots = 0;
    int valide = 0;
    int quitte = 0;

    /* NETTOYAGE DES FICHIERS .txt DU PROJET */

    FILE* fichier1 = NULL;
    fichier1 = fopen ("./RESSOURCES/USERS.txt", "w");
    FILE* fichier2 = NULL;
    fichier2 = fopen ("./RESSOURCES/GRID.txt", "w");
    FILE* fichier3 = NULL;
    fichier3 = fopen ("./RESSOURCES/WORDS.txt", "w"); 

    while (1) {

    printf ("\n\n------------- EN ATTENTE DE RECEPTION D'UNE COMMANDE -------------\n\n"); 

    char choix[100];
    zmq_recv (responder, choix, 100, 0); /* Réception de la fonction du joueur*/
    char	*pointeur;
    char	*separateur = { " " };     /* Le séparateur*/
    char 	*buffer;
    char    *Chaine_Entrante = choix;

    buffer =  strdup (Chaine_Entrante);


/* DETERMINATON DE LA FONCTION EXECUTEE */

pointeur = strtok( buffer, separateur  );


/* ----------------- APPELS DES FONCTIONS A AJOUTER DANS L'ORDRE ! ------------------- */



/* FONCTIONS DE JOIN (YOUSSEF) */  
    if(!strcmp(pointeur,"JOIN")){ 
    connexion = JOIN(responder,choix);
    }

/*FONCTIONS DE GRID (ALAN) */
    if(connexion){

/*Changement de port avec le client */

    grille = GRID(responder2);
 
    }

/*FONCTIONS DE WORDS (ALAN)*/

    if(grille){
        
/* !!!!!! PROBLEME DE SEGMENTATION FAULT (core dumped) ICI !!!!!!!!*/

    mots = WORDS(responder2); 

    }

/*FONCTIONS DE FOUND (LEO)*/

    else if(!strcmp(pointeur,"FOUND")){

    valide = FOUND(responder,choix);
    }

/*FONCTIONS DE ATTRIBUTION DE SCORE (YOUSSEF) */
    else if(!strcmp(pointeur,"LEAVE")){
        
    quitte = LEAVE(responder,choix);

    }

}

    return 0;
}
