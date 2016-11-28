

//  Hello World client
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main (void)
{
    printf ("Connecting to hello world server…\n");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:5555");

    char text[10]; // Création de la variable text, qui contiendra le nom du joueur
    
    printf("Veuillez saisir votre nom d'utilisateur\n");
    scanf("%s",text); // Entrée du nom du joueur
    printf("Vous avez choisi le nom d'utilisateur : %s\n", text);


    zmq_send(requester, text, 10, 0); // Envoi du nom du joueur


    char buffer[40]; // Création de la variable buffer, qui contiendra le message de confirmation
    zmq_recv(requester, buffer, 40, 0); // Réception du message de confirmation
    printf(buffer); // Affichage du message de confirmation


    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}

