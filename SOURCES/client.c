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

/* CREATION DES FLUX DE COMMUNICATION AVEC PORTS 1 & 2 */

    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:1111");

    void *context2 = zmq_ctx_new ();
    void *requester2 = zmq_socket (context2, ZMQ_REQ);
    zmq_connect (requester2, "tcp://localhost:2222");

/* Variables de validation d'etats */
    int connexion = 0;
    int grille = 0;
    int mots = 0;
    int valide = 0;
    int quitte = 0;
    int score = 0;

/* ---------------------- BOUCLE DE CHOIX DU CLIENT ------------------------- */
    
    while(1){

    printf ("\nVeuillez choisir la fonction à executer : JOIN, FOUND ou LEAVE \n");
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



/* ----------- APPELS DES FONCTIONS A AJOUTER DANS L'ORDRE ! ------------ */

/* FONCTIONS DE JOIN (YOUSSEF) */   
    if(!strcmp(pointeur,"JOIN")){
    connexion = JOIN(requester, choix);
    }

/*FONCTIONS DE GRID (LEO - ALAN) */
    if(connexion){


    grille = GRID(requester2); /*Changement de port avec le serveur */

    }

/*FONCTIONS DE WORDS (LEO)*/

    if(grille){

    mots = WORDS(requester2);

    }


/*FONCTIONS DE FOUND (LEO)*/

    else if(!strcmp(pointeur,"FOUND")){

/*Changement de port avec le serveur */

    valide = FOUND(requester, choix);
    
    if(valide){
    
    score = score +2;
    
    }}


/*FONCTIONS DE ATTRIBUTION DE SCORE (YOUSSEF) */
    else if(!strcmp(pointeur,"LEAVE")){
        
    quitte = LEAVE(requester, choix);
    
    printf("VOTRE SCORE EST : %i , A BIENTOT !",score);

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

