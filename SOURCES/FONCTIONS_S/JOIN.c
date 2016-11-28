#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zmq.h>
#include <unistd.h>

#include "fonctions.h"



void JOIN(void *responder){

char buffer [10]; /*Création du buffer, qui contiendra le nom du joueur*/
        zmq_recv (responder, buffer, 10, 0); /* Réception du nom du joueur*/
        printf("Le nom du nouveau joueur est : ");
        printf (buffer); /* Affichage du nom du joueur */
        printf ("\n");
        sleep (1);    

	/* AJOUT DE L'ALGORITHME (variable bufer contient nom utilisateur )*/


  
        zmq_send (responder, "Nom correct, Bienvenue !\n CHOISISSEZ LA TAILLE DE LA GRILLE", 25, 0); /* Envoi du message de confirmation */

}
