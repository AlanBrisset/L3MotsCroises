#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include "FONCTIONS_S/fonctions.h"

int main (void)
{

    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:7878");
    assert (rc == 0);

    while (1) {

        /* APPELS DES FONCTIONS A AJOUTER DANS L'ORDRE ! */

 	/* FONCTIONS DE JOIN (YOUSSEF) */   
JOIN(responder);

	/*FONCTIONS DE GRID (LEO)


	//FONCTIONS DE WORDS (LEO)


	//FONCTIONS DE FOUND (ALAN)


	//FONCTIONS DE ATTRIBUTION DE SCORE (ALAN) */
    }

    return 0;
}
