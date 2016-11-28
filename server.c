

//  Hello World server

#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

int main (void)
{
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);

    while (1) {
        char buffer [10]; //Création du buffer, qui contiendra le nom du joueur
        zmq_recv (responder, buffer, 10, 0); // Réception du nom du joueur
        printf("Le nom du nouveau joueur est : ");
        printf (buffer); // Affichage du nom du joueur
        printf ("\n");
        sleep (1);      
        zmq_send (responder, "Nom correct, Bienvenue !", 25, 0); // Envoi du message de confirmation
    }
    return 0;
}

