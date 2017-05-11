#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zmq.h>
#include <unistd.h>
#include <string.h>

#include "fonctions.h"



int GRID(void *requester){

        char buffer[0];
        char buffer12[60]; /* Création de la variable buffer, qui contiendra le message de confirmation */


/* ENVOYER DU RIEN */
        zmq_send(requester, buffer, 0, 0);





/* RECEPTION DE LA GRILLE */

        printf("\n\n----------------- RECEPTION DE LA GRILLE ------------------\n\n\n\n");

        zmq_recv(requester, buffer12, 60, 0); 
	char *parametres[100];
	int i=0;

	parametres[i] = strtok(buffer12," ");

	while(parametres[i]!=NULL)
	{
	   parametres[++i] = strtok(NULL," ");
	} 



/* Division des mots en fonction du nombre de lettre par mots */ 
        const char *str = parametres[3];
        int lig = atoi(parametres[1]);
        int col = atoi(parametres[2]); 
        
        char *str1;
        char str2[25];


   
        char subbuff[10][100];
        int nb=0;
    
        for (i=1; i<=lig; i++)
        {
        memcpy(subbuff[i], &str[nb], col );
        subbuff[i][col] = '\0';
        nb=nb+col;
        
        
        char* str1 = subbuff[i];
        
        int j, cpt;
        cpt=0;
	

        /*printf("       |  "); printf(subbuff[i]); printf("  |       \n");*/
        
        printf(" |         "); 
        
        
        for(j=0; j<=lig; j++, cpt++)
        {
            memcpy(str2, &str1[j], 1);
            printf(str2);
            printf("     ");
        }
        
        
        
        
    printf(" |       \n");
    
	
    
    printf(" |         ");  
    
    int k;
    for(k=1; k<col; k++)
    {
        printf("         ");
    }
    
    printf("     ");
    /*int l;
    for(l=0; l<cpt; l++)
    {
        printf(" ");
    }*/
    
    printf(" |       \n");
    
    


        }
    

        printf("\n\n--------------------\n\n");


}

