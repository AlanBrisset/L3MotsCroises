#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zmq.h>
#include <unistd.h>

#include "fonctions.h"



void JOIN(void *requester){

char username[100];
printf("Veuillez saisir votre nom d'utilisateur");
scanf("%s",username);
printf("Vous avez choisi le nom d'utilisateur : %s\n", username);

zmq_send(requester, username , 100, 0);

}





void Hello(){

printf("HELLO ! ");

}
