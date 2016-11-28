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

int main (void)
{
    printf ("Création du joueur pour rejoindre la session ...\n");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:7878");

/* APPELS DES FONCTIONS A AJOUTER DANS L'ORDRE ! */

 	/* FONCTIONS DE JOIN (YOUSSEF) */   
JOIN(requester);

	/*FONCTIONS DE GRID (LEO)


	//FONCTIONS DE WORDS (LEO)


	//FONCTIONS DE FOUND (ALAN)


	//FONCTIONS DE ATTRIBUTION DE SCORE (ALAN) */

    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}

