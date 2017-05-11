#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <zmq.h>

#include "fonctions.h"

int WORDS(void *responder){


/* RECEVOIR DU RIEN */
    char buffer[30];

    zmq_recv(responder, buffer, 30, 0); /* Réception du message de confirmation */
    
    

    printf("------------------- ENVOI DES MOTS A TROUVER ------------------");


    
    /* Ouverture du fichier GRID.txt
    / Chemin : ../RESSOURCES/GRID.txt
    / Stockage de tous les mots dans une seule variable
    / Un seul String contenant tous les mots bout à bout*/
    
    
    char const* const fileName = "./RESSOURCES/GRID.txt"; /* should check that argc > 1 */
    FILE* file = fopen(fileName, "r"); /* should check the result */
    char line[250];
    
    int idx1, idx2=0;
    char grilleIntermediaire[5][6];
    
    int nbColonnes, nbCaracteres = 0;

    while (fgets(line, sizeof(line), file)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        
        nbColonnes = strlen(line);
        
        
        line[nbColonnes]='\0';
        nbColonnes = nbColonnes-2;
        nbCaracteres = nbCaracteres+nbColonnes+1;
        
        /*printf("%s", line); */
        strcpy(grilleIntermediaire[idx1], line);
        idx1++;
    }
    /* may check feof here to make a difference between eof and io failure -- network
       timeout for instance */

    fclose(file);
    
    int nbLignes = nbCaracteres/(nbColonnes+1);
    
    char *grilleEnLigne = grilleIntermediaire[0];

    
    char subbuff[25]; /* Contiendra la variable lue, puis le mot en entier */
    char subbuffbis[25]=""; /* Contiendra la lettre+1 du mot */
    
    int additionColonnes; /* Valeur servant dans les while. Il prendra la valeur de nbColonnes*1, puis nbColonnes*2, etc */
    int valeurIncrementee; /* Valeur servant dans les while. Il prendra la valeur de 1, puis 2, etc */
    
    int longueurMotActuel;
    
    char const* const cheminDico = "./RESSOURCES/dicos/dico";
    char nomDico[60]="./RESSOURCES/dicos/dico"; /* Variable qui contiendra le nom du dictionnaire à lire */
    char numDico[5]="";
    
    char tableauMotsTrouves[100][nbColonnes+1];
    char tableauCoordsTrouvees[100][nbColonnes+1];
    
    int posx_origine, posy_origine, posx_dest, posy_dest;
    char c_posx_origine[5], c_posy_origine[5], c_posx_dest[5], c_posy_dest[5], c_coords[22];
    
    int posLettreLue;
     
    FILE* fichierDico = NULL;
    
    
    for (posLettreLue = 0; posLettreLue<nbCaracteres; posLettreLue++)
    {
        if(posLettreLue-(nbColonnes+1)>=0) /* Test vertical supérieure possible */
        {
            longueurMotActuel=2;
            
            memcpy(subbuff, &grilleEnLigne[posLettreLue], 1); /* Récupération de la lettre lue */
            subbuff[1] = '\0';
            
            additionColonnes = nbColonnes+1; /* Initialisation de la variable additionColonnes*/
            
            
            while(posLettreLue-additionColonnes>=0)
            {
                memcpy(subbuffbis, &grilleEnLigne[posLettreLue-additionColonnes], 1);
                subbuffbis[1] = '\0';
                
                strcat(subbuff, subbuffbis);
                
                memset(subbuffbis, 0, 25);
                
               /* --- VERIFICATION DANS LE DICO --- */
               
                /*longueurMotActuel = strlen(subbuff);*/
                
                if(longueurMotActuel >=3)
                {
                    sprintf(numDico, "%d", longueurMotActuel);
                    strcat(nomDico,numDico);
                    strcat(nomDico,".txt");
                    
                    int motTrouve = 0;
                    
                    fichierDico = fopen(nomDico, "r");
                    
                    
                    if(fichierDico==NULL)
                    {
                        printf("Impossible de charger le dictionnaire suivant : ");
                        printf(nomDico);
                    }
                    
                    else
                    {
                        while (fgets(line, sizeof(line), fichierDico))
                        {
                            if(line!=NULL && motTrouve == 0)
                            { 
                                line[longueurMotActuel]='\0';
                                if(strcmp(line,subbuff)==0)
                                {
                                    strcpy(tableauMotsTrouves[idx2], line);
                                    
                                    printf(tableauMotsTrouves[idx2]);
                                    printf("\n");
                                    
                                    posx_origine = (posLettreLue/(nbColonnes+1))+1;
                                    posy_origine = (posLettreLue%(nbColonnes+1))+1;
                                    posx_dest = ((posLettreLue-additionColonnes)%(nbColonnes+1))+1;
                                    posy_dest = posy_origine;
                                    
                                    sprintf(c_posx_origine, "%d", posx_origine);
                                    sprintf(c_posy_origine, "%d", posy_origine);
                                    sprintf(c_posx_dest, "%d", posx_dest);
                                    sprintf(c_posy_dest, "%d", posy_dest);
                                    
                                    strcpy(c_coords, c_posx_origine);
                                    strcat(c_coords, c_posy_origine);
                                    strcat(c_coords, " ");
                                    strcat(c_coords, c_posx_dest);
                                    strcat(c_coords, c_posy_dest);
                                    
                                    strcpy(tableauCoordsTrouvees[idx2], c_coords);                                    
                                    
                                    printf(tableauCoordsTrouvees[idx2]);
                                    printf("\n");
                                    
                                    motTrouve=1;
                                    idx2++;
                                }

                            }
                        }
                    }
                    
                    fclose(fichierDico);
                    
                }
                
                /* --- FIN --- */
                
                additionColonnes = additionColonnes+nbColonnes+1;
                longueurMotActuel++;
                strcpy(nomDico, cheminDico);
            }
            
            memset(subbuff, 0, 25);
        }
        
        
        
        if((posLettreLue-nbColonnes>=0) && ((posLettreLue-nbColonnes)%(nbColonnes+1)!=0)) /* Test diagonale supérieure droite possible. Le deuxième test vérifie qu'il s'agit bien d'une diagonale, et non d'un retour à la ligne (cas où le caractère sélectionné est tout à droite). */
        {
            
            longueurMotActuel = 2;
            
            memcpy(subbuff, &grilleEnLigne[posLettreLue], 1); /* Récupération de la lettre lue */
            subbuff[1] = '\0';
            
            additionColonnes = nbColonnes+1; /* Initialisation de la variable additionColonnes*/
            
            while((posLettreLue-additionColonnes>=0) && ((posLettreLue-additionColonnes)%(nbColonnes+1)!=0))
            {
                memcpy(subbuffbis, &grilleEnLigne[posLettreLue-additionColonnes], 1);
                subbuffbis[1] = '\0';
                
                strcat(subbuff, subbuffbis);
                
                memset(subbuffbis, 0, 25);
                
                
                /* --- VERIFICATION DANS LE DICO --- */
               
                /*longueurMotActuel = strlen(subbuff);*/
                
                if(longueurMotActuel >=3)
                {
                    sprintf(numDico, "%d", longueurMotActuel);
                    strcat(nomDico,numDico);
                    strcat(nomDico,".txt");
                    
                    int motTrouve=0;
                    
                    fichierDico = fopen(nomDico, "r");
                    
                    if(fichierDico==NULL)
                    {
                        printf("Impossible de charger le dictionnaire suivant : ");
                        printf(nomDico);
                    }
                    
                    else
                    {
                        while (fgets(line, sizeof(line), fichierDico))
                        {
                            if(line!=NULL && motTrouve == 0)
                            { 
                                line[longueurMotActuel]='\0';
                                if(strcmp(line,subbuff)==0)
                                {
                                    strcpy(tableauMotsTrouves[idx2], line);
                                    
                                    printf(tableauMotsTrouves[idx2]);
                                    printf("\n");
                                    
                                    posx_origine = (posLettreLue/(nbColonnes+1))+1;
                                    posy_origine = (posLettreLue%(nbColonnes+1))+1;
                                    posx_dest = ((posLettreLue-additionColonnes)/(nbColonnes+1))+1;
                                    posy_dest = ((posLettreLue-additionColonnes)%(nbColonnes+1))+1;
                                    
                                    sprintf(c_posx_origine, "%d", posx_origine);
                                    sprintf(c_posy_origine, "%d", posy_origine);
                                    sprintf(c_posx_dest, "%d", posx_dest);
                                    sprintf(c_posy_dest, "%d", posy_dest);
                                    
                                    strcpy(c_coords, c_posx_origine);
                                    strcat(c_coords, c_posy_origine);
                                    strcat(c_coords, " ");
                                    strcat(c_coords, c_posx_dest);
                                    strcat(c_coords, c_posy_dest);
                                    
                                    strcpy(tableauCoordsTrouvees[idx2], c_coords);    
                                    
                                    printf(tableauCoordsTrouvees[idx2]);
                                    printf("\n");
                                    
                                    motTrouve=1;
                                    idx2++;
                                }

                            }
                        }
                    }
                    
                    fclose(fichierDico);
                    
                }
                
                /* --- FIN --- */
                
                
                additionColonnes = additionColonnes+nbColonnes;
                longueurMotActuel++;
                strcpy(nomDico, cheminDico);
            
            }
            
            memset(subbuff, 0, 25);
            
        }
        
        
        
        if((posLettreLue+1<nbCaracteres) && ((posLettreLue+1)%(nbColonnes+1)!=0)) /* Test horizontal droit possible. On vérifie que le prochain caractère n'est pas sur la ligne du dessous. */
        {
            
            longueurMotActuel=2;
            
            memcpy(subbuff, &grilleEnLigne[posLettreLue], 1); /* Récupération de la lettre lue */
            subbuff[1] = '\0';
            valeurIncrementee = 1; /* Initialisation de la variable valeurIncrementee*/
            
            
            while((posLettreLue+valeurIncrementee<nbCaracteres) && ((posLettreLue+valeurIncrementee)%(nbColonnes+1)!=0))
            {
                memcpy(subbuffbis, &grilleEnLigne[posLettreLue+valeurIncrementee], 1);
                subbuffbis[1] = '\0';
                
                
                strcat(subbuff, subbuffbis);
    
                /*printf(subbuff);
                printf(" ");*/
                
                memset(subbuffbis, 0, 25);
                
                
                /* --- VERIFICATION DANS LE DICO --- */
               
                /*longueurMotActuel = strlen(subbuff);*/
            
                if(longueurMotActuel >=3)
                {
                    sprintf(numDico, "%d", longueurMotActuel);
                    strcat(nomDico,numDico);
                    strcat(nomDico,".txt");
                    
                    int motTrouve=0;
                    
                    fichierDico = fopen(nomDico, "r");
                    
                    if(fichierDico==NULL)
                    {
                        printf("Impossible de charger le dictionnaire suivant : ");
                        printf(nomDico);
                    }
                    
                    else
                    {
                        /*printf(nomDico);*/
                        
                        while (fgets(line, sizeof(line), fichierDico))
                        {
                            
                            if(line!=NULL && motTrouve==0)
                            { 
                                line[longueurMotActuel]='\0';
                                
                                if(strcmp(line,subbuff)==0)
                                {
                                    strcpy(tableauMotsTrouves[idx2], line);
                                    
                                    printf(tableauMotsTrouves[idx2]);
                                    
                                    posx_origine = (posLettreLue/(nbColonnes+1))+1;
                                    posy_origine = (posLettreLue%(nbColonnes+1))+1;
                                    posx_dest = posx_origine;
                                    posy_dest = ((posLettreLue+valeurIncrementee)%(nbColonnes+1))+1;
                                    
                                    sprintf(c_posx_origine, "%d", posx_origine);
                                    sprintf(c_posy_origine, "%d", posy_origine);
                                    sprintf(c_posx_dest, "%d", posx_dest);
                                    sprintf(c_posy_dest, "%d", posy_dest);
                                    
                                    strcpy(c_coords, c_posx_origine);
                                    strcat(c_coords, c_posy_origine);
                                    strcat(c_coords, " ");
                                    strcat(c_coords, c_posx_dest);
                                    strcat(c_coords, c_posy_dest);
                                    
                                    strcpy(tableauCoordsTrouvees[idx2], c_coords);  
                                    
                                    printf(tableauCoordsTrouvees[idx2]);
                                    printf("\n");
                                    
                                    motTrouve=1;
                                    idx2++;
                                }

                            }
                            
                            
                        }
                    }
                    
                    fclose(fichierDico);
                    
                }
                
                /* --- FIN --- */
                
                
                valeurIncrementee++;
                longueurMotActuel++;
                strcpy(nomDico, cheminDico);
                
            }
            
            memset(subbuff, 0, 25);
            
        }
        
        
        
        if((posLettreLue+nbColonnes+2<nbCaracteres) && ((posLettreLue+nbColonnes+2)%(nbColonnes+1)!=0)) /* Test diagonale inférieure droite possible. Le deuxième test vérifie qu'il s'agit bien d'une diagonale, et non d'un retour à la ligne (cas où le caractère sélectionné est tout à droite). */
        {
            
            longueurMotActuel=2;
            
            memcpy(subbuff, &grilleEnLigne[posLettreLue], 1); /* Récupération de la lettre lue */
            subbuff[1] = '\0';
            
            additionColonnes = nbColonnes+2; /* Initialisation de la variable additionColonnes*/
            
            
            
            while((posLettreLue+additionColonnes<nbCaracteres) && ((posLettreLue+additionColonnes)%(nbColonnes+1)!=0))
            {
                memcpy(subbuffbis, &grilleEnLigne[posLettreLue+additionColonnes], 1);
                subbuffbis[1] = '\0';
                
                strcat(subbuff, subbuffbis);
                
                memset(subbuffbis, 0, 25);
                
                
                /* --- VERIFICATION DANS LE DICO --- */
               
                /*longueurMotActuel = strlen(subbuff);*/
                
                if(longueurMotActuel >=3)
                {
                    sprintf(numDico, "%d", longueurMotActuel);
                    strcat(nomDico,numDico);
                    strcat(nomDico,".txt");
                    
                    int motTrouve=0;
                    
                    fichierDico = fopen(nomDico, "r");
                    
                    if(fichierDico==NULL)
                    {
                        printf("Impossible de charger le dictionnaire suivant : ");
                        printf(nomDico);
                    }
                    
                    else
                    {
                        while (fgets(line, sizeof(line), fichierDico))
                        {
                            if(line!=NULL && motTrouve==0)
                            { 
                                line[longueurMotActuel]='\0';
                                if(strcmp(line,subbuff)==0)
                                {
                                    strcpy(tableauMotsTrouves[idx2], line);
                                    
                                    printf(tableauMotsTrouves[idx2]);
                                    printf("\n");
                                    
                                    posx_origine = (posLettreLue/(nbColonnes+1))+1;
                                    posy_origine = (posLettreLue%(nbColonnes+1))+1;
                                    posx_dest = ((posLettreLue+additionColonnes)/(nbColonnes+1))+1;
                                    posy_dest = ((posLettreLue+additionColonnes)%(nbColonnes+1))+1;
                                    
                                    sprintf(c_posx_origine, "%d", posx_origine);
                                    sprintf(c_posy_origine, "%d", posy_origine);
                                    sprintf(c_posx_dest, "%d", posx_dest);
                                    sprintf(c_posy_dest, "%d", posy_dest);
                                    
                                    strcpy(c_coords, c_posx_origine);
                                    strcat(c_coords, c_posy_origine);
                                    strcat(c_coords, " ");
                                    strcat(c_coords, c_posx_dest);
                                    strcat(c_coords, c_posy_dest);
                                    
                                    strcpy(tableauCoordsTrouvees[idx2], c_coords);  
                                    
                                    printf(tableauCoordsTrouvees[idx2]);
                                    printf("\n");
                                    
                                    motTrouve=1;
                                    idx2++;
                                }

                            }
                        }
                    }
                    
                    fclose(fichierDico);
                    
                }
                
                /* --- FIN --- */
                
                
                longueurMotActuel++;
                additionColonnes = additionColonnes+nbColonnes+2;
                strcpy(nomDico, cheminDico);
            }
            
            memset(subbuff, 0, 25);
            
        }
        
        
        
        
        
        
        
        
        if(posLettreLue+nbColonnes+1<nbCaracteres) /* Test vertical inférieur possible */
        {
            
            longueurMotActuel=2;
            
            memcpy(subbuff, &grilleEnLigne[posLettreLue], 1); /* Récupération de la lettre lue */
            subbuff[1] = '\0';
            additionColonnes = nbColonnes+1; /* Initialisation de la variable additionColonnes*/
            
            while(posLettreLue+additionColonnes<nbCaracteres)
            {
                memcpy(subbuffbis, &grilleEnLigne[posLettreLue+additionColonnes], 1);
                subbuffbis[1] = '\0';
                
                strcat(subbuff, subbuffbis);
                
                memset(subbuffbis, 0, 25);
                
                                
                /* --- VERIFICATION DANS LE DICO --- */
               
                /*longueurMotActuel = strlen(subbuff);*/
                
                if(longueurMotActuel >=3)
                {
                    sprintf(numDico, "%d", longueurMotActuel);
                    strcat(nomDico,numDico);
                    strcat(nomDico,".txt");
                    
                    int motTrouve = 0;
                    
                    fichierDico = fopen(nomDico, "r");
                    
                    if(fichierDico==NULL)
                    {
                        printf("Impossible de charger le dictionnaire suivant : ");
                        printf(nomDico);
                    }
                    
                    else
                    {
                        while (fgets(line, sizeof(line), fichierDico))
                        {
                            if(line!=NULL && motTrouve == 0)
                            { 
                                line[longueurMotActuel]='\0';
                                if(strcmp(line,subbuff)==0)
                                {
                                    strcpy(tableauMotsTrouves[idx2], line);
                                    
                                    printf(tableauMotsTrouves[idx2]);
                                    printf("\n");
                                    
                                    posx_origine = (posLettreLue/(nbColonnes+1))+1;
                                    posy_origine = (posLettreLue%(nbColonnes+1))+1;
                                    posx_dest = ((posLettreLue+additionColonnes)/(nbColonnes+1))+1;
                                    posy_dest = posy_origine;
                                    
                                    sprintf(c_posx_origine, "%d", posx_origine);
                                    sprintf(c_posy_origine, "%d", posy_origine);
                                    sprintf(c_posx_dest, "%d", posx_dest);
                                    sprintf(c_posy_dest, "%d", posy_dest);
                                    
                                    strcpy(c_coords, c_posx_origine);
                                    strcat(c_coords, c_posy_origine);
                                    strcat(c_coords, " ");
                                    strcat(c_coords, c_posx_dest);
                                    strcat(c_coords, c_posy_dest);
                                    
                                    strcpy(tableauCoordsTrouvees[idx2], c_coords);  
                                    
                                    printf(tableauCoordsTrouvees[idx2]);
                                    printf("\n");
                                    
                                    motTrouve=1;
                                    idx2++;
                                }

                            }
                        }
                    }
                    
                    fclose(fichierDico);
                    
                }
                
                /* --- FIN --- */
                
                longueurMotActuel++;
                additionColonnes = additionColonnes+nbColonnes+1;
                strcpy(nomDico, cheminDico);
                
            }
            
            memset(subbuff, 0, 25);
            
            
        }
        
        
        
        
        
        
        
        
        
        if((posLettreLue+nbColonnes<nbCaracteres) && ((posLettreLue+nbColonnes)%(nbColonnes+1)!=5)) /* Test diagonale inférieure gauche possible. Le deuxième test vérifie qu'il s'agit bien d'une diagonale, et non d'un retour à la ligne (cas où le caractère sélectionné est tout à gauche). */
        {
            
            longueurMotActuel=2;
            
            memcpy(subbuff, &grilleEnLigne[posLettreLue], 1); /* Récupération de la lettre lue */
            additionColonnes = nbColonnes; /* Initialisation de la variable additionColonnes*/
            
            
            
            while((posLettreLue+additionColonnes<nbCaracteres) && ((posLettreLue+additionColonnes)%(nbColonnes+1)!=5))
            {
                memcpy(subbuffbis, &grilleEnLigne[posLettreLue+additionColonnes], 1);
                
                subbuffbis[1] = '\0';
                
                strcat(subbuff, subbuffbis);
                
                memset(subbuffbis, 0, 25);
                
                
                
                /* --- VERIFICATION DANS LE DICO --- */
               
                /*longueurMotActuel = strlen(subbuff);*/
                
                if(longueurMotActuel >=3)
                {
                    sprintf(numDico, "%d", longueurMotActuel);
                    strcat(nomDico,numDico);
                    strcat(nomDico,".txt");
                    
                    int motTrouve=0;
                    
                    fichierDico = fopen(nomDico, "r");
                    
                    if(fichierDico==NULL)
                    {
                        printf("Impossible de charger le dictionnaire suivant : ");
                        printf(nomDico);
                    }
                    
                    else
                    {
                        while (fgets(line, sizeof(line), fichierDico))
                        {
                            if(line!=NULL && motTrouve ==0 )
                            { 
                                line[longueurMotActuel]='\0';
                                if(strcmp(line,subbuff)==0)
                                {
                                    strcpy(tableauMotsTrouves[idx2], line);
                                    
                                    printf(tableauMotsTrouves[idx2]);
                                    printf("\n");
                                    
                                    posx_origine = (posLettreLue/(nbColonnes+1))+1;
                                    posy_origine = (posLettreLue%(nbColonnes+1))+1;
                                    posx_dest = ((posLettreLue+additionColonnes)/(nbColonnes+1))+1;
                                    posy_dest = ((posLettreLue+additionColonnes)%(nbColonnes+1))+1;
                                    
                                    sprintf(c_posx_origine, "%d", posx_origine);
                                    sprintf(c_posy_origine, "%d", posy_origine);
                                    sprintf(c_posx_dest, "%d", posx_dest);
                                    sprintf(c_posy_dest, "%d", posy_dest);
                                    
                                    strcpy(c_coords, c_posx_origine);
                                    strcat(c_coords, c_posy_origine);
                                    strcat(c_coords, " ");
                                    strcat(c_coords, c_posx_dest);
                                    strcat(c_coords, c_posy_dest);
                                    
                                    strcpy(tableauCoordsTrouvees[idx2], c_coords);                                    
                                                                        
                                    printf(tableauCoordsTrouvees[idx2]);
                                    printf("\n");
                                    
                                    motTrouve=1;
                                    idx2++;
                                }

                            }
                        }
                    }
                    
                    fclose(fichierDico);
                    
                }
                
                /* --- FIN --- */
                
                
                longueurMotActuel++;
                additionColonnes = additionColonnes+nbColonnes;
                strcpy(nomDico, cheminDico);
                
            }
            
            memset(subbuff, 0, 25);
            
        }
        
        
        
        
        
        
        
        if((posLettreLue-1>=0) && ((posLettreLue-1)%nbColonnes!=5)) /* Test horizontal gauche possible. */
        {
            
            longueurMotActuel=2;
            
            memcpy(subbuff, &grilleEnLigne[posLettreLue], 1); /* Récupération de la lettre lue */
            
            subbuff[1] = '\0';
            
            valeurIncrementee = 1; /* Initialisation de la variable valeurIncrementee*/
            
            
            while((posLettreLue-valeurIncrementee>=0) && ((posLettreLue-valeurIncrementee)%(nbColonnes+1)!=5))
            {
                memcpy(subbuffbis, &grilleEnLigne[posLettreLue-valeurIncrementee], 1);
                
                subbuffbis[1] = '\0';
                
                strcat(subbuff, subbuffbis);
                
                memset(subbuffbis, 0, 25);
                
                
                /* --- VERIFICATION DANS LE DICO --- */
               
                /*longueurMotActuel = strlen(subbuff);*/
                
                if(longueurMotActuel >=3)
                {
                    sprintf(numDico, "%d", longueurMotActuel);
                    strcat(nomDico,numDico);
                    strcat(nomDico,".txt");
                    
                    int motTrouve=0;
                    
                    fichierDico = fopen(nomDico, "r");
                    
                    if(fichierDico==NULL)
                    {
                        printf("Impossible de charger le dictionnaire suivant : ");
                        printf(nomDico);
                    }
                    
                    else
                    {
                        while (fgets(line, sizeof(line), fichierDico))
                        {
                            if(line!=NULL && motTrouve==0)
                            { 
                                line[longueurMotActuel]='\0';
                                if(strcmp(line,subbuff)==0)
                                {
                                    strcpy(tableauMotsTrouves[idx2], line);
                                    
                                    printf(tableauMotsTrouves[idx2]);
                                    
                                    
                                    posx_origine = (posLettreLue/(nbColonnes+1))+1;
                                    posy_origine = (posLettreLue%(nbColonnes+1))+1;
                                    posx_dest = posx_origine;
                                    posy_dest = (posLettreLue-valeurIncrementee)%(nbColonnes+1)+1;
                                    
                                    sprintf(c_posx_origine, "%d", posx_origine);
                                    sprintf(c_posy_origine, "%d", posy_origine);
                                    sprintf(c_posx_dest, "%d", posx_dest);
                                    sprintf(c_posy_dest, "%d", posy_dest);
                                    
                                    strcpy(c_coords, c_posx_origine);
                                    strcat(c_coords, c_posy_origine);
                                    strcat(c_coords, " ");
                                    strcat(c_coords, c_posx_dest);
                                    strcat(c_coords, c_posy_dest);
                                    
                                    strcpy(tableauCoordsTrouvees[idx2], c_coords);

                                    printf(tableauCoordsTrouvees[idx2]);
                                    printf("\n");
                                    
                                    motTrouve = 1;
                                    idx2++;
                                }

                            }
                        }
                    }
                    
                    fclose(fichierDico);
                    
                }
                
                /* --- FIN --- */
                
                longueurMotActuel++;
                valeurIncrementee++;
                strcpy(nomDico, cheminDico);
                
            }
            
            memset(subbuff, 0, 25);
            
        }
        
        
        
        
        
        
        
        
        
        if((posLettreLue-nbColonnes-2>=0) && ((posLettreLue-nbColonnes-2)%nbColonnes!=5)) /* Test diagonale supérieure gauche possible. Le deuxième test vérifie qu'il s'agit bien d'une diagonale, et non d'un retour à la ligne (cas où le caractère sélectionné est tout à gauche). */
        {
            
            longueurMotActuel=2;
            
            memcpy(subbuff, &grilleEnLigne[posLettreLue], 1); /* Récupération de la lettre lue */
            
            subbuff[1] = '\0';
            
            additionColonnes = nbColonnes+2; /* Initialisation de la variable additionColonnes*/
            
            
            while((posLettreLue-additionColonnes>=0) && ((posLettreLue-additionColonnes)%nbColonnes!=5))
            {
                memcpy(subbuffbis, &grilleEnLigne[posLettreLue-additionColonnes], 1);
                
                subbuffbis[1] = '\0';
                
                strcat(subbuff, subbuffbis);
                
                memset(subbuffbis, 0, 25);
                
                
                /* --- VERIFICATION DANS LE DICO --- */
               
                /*longueurMotActuel = strlen(subbuff);*/
                
                if(longueurMotActuel >=3)
                {
                    sprintf(numDico, "%d", longueurMotActuel);
                    strcat(nomDico,numDico);
                    strcat(nomDico,".txt");
                    
                    int motTrouve = 0;
                    
                    fichierDico = fopen(nomDico, "r");
                    
                    if(fichierDico==NULL)
                    {
                        printf("Impossible de charger le dictionnaire suivant : ");
                        printf(nomDico);
                    }
                    
                    else
                    {
                        while (fgets(line, sizeof(line), fichierDico))
                        {
                            if(line!=NULL && motTrouve == 0)
                            { 
                                line[longueurMotActuel]='\0';
                                if(strcmp(line,subbuff)==0)
                                {
                                    strcpy(tableauMotsTrouves[idx2], line);
                                    
                                    printf(tableauMotsTrouves[idx2]);
                                    printf("\n");
                                    
                                    posx_origine = (posLettreLue/(nbColonnes+1))+1;
                                    posy_origine = (posLettreLue%(nbColonnes+1))+1;
                                    posx_dest = ((posLettreLue-additionColonnes)/(nbColonnes+1))+1;
                                    posy_dest = ((posLettreLue-additionColonnes)%(nbColonnes+1))+1;
                                    
                                    sprintf(c_posx_origine, "%d", posx_origine);
                                    sprintf(c_posy_origine, "%d", posy_origine);
                                    sprintf(c_posx_dest, "%d", posx_dest);
                                    sprintf(c_posy_dest, "%d", posy_dest);
                                    
                                    strcpy(c_coords, c_posx_origine);
                                    strcat(c_coords, c_posy_origine);
                                    strcat(c_coords, " ");
                                    strcat(c_coords, c_posx_dest);
                                    strcat(c_coords, c_posy_dest);
                                    
                                    strcpy(tableauCoordsTrouvees[idx2], c_coords);                                    
                                    
                                    printf(tableauCoordsTrouvees[idx2]);
                                    printf("\n");
                                    
                                    motTrouve = 1;
                                    idx2++;
                                }

                            }
                        }
                    }
                    
                    fclose(fichierDico);
                    
                }
                
                /* --- FIN --- */
                
                longueurMotActuel++;
                additionColonnes = additionColonnes+nbColonnes+2;
                strcpy(nomDico, cheminDico);
                
            }
            
            memset(subbuff, 0, 25);
            
        }
        
        
    }
    
    
    
    FILE* fichierWords = NULL;
    fichierWords = fopen("./RESSOURCES/WORDS.txt", "a");
    char ensembleMotsTrouves[255]="";
    
    if(fichierWords!=NULL)
    {
        
        char tableauMotsFinaux[100][nbColonnes+nbLignes+1];
        int idx3 = 0;
        int r;
        srand(time(NULL));
        int str_len;
    
        while(idx3<=(nbLignes+nbColonnes))
        {
            r = rand()%(idx2+1);
            if(
                (strcmp(tableauMotsTrouves[r], "")!=0) 
                && 
                strlen(tableauMotsTrouves[r])<nbColonnes+1
            )
            {
                printf("random: %d   ", r);
                char str1[25];
                strcpy(str1, tableauMotsTrouves[r]);
                char str2[25];
                strcpy(str2, tableauCoordsTrouvees[r]);
                strcat(str1, " ");
                
                strcat(ensembleMotsTrouves, str1);
                
                strcat(str1, str2);
                strcpy(tableauMotsFinaux[idx3], str1);
                strcpy(tableauMotsTrouves[r], "");
                fprintf(fichierWords, "%s\n", tableauMotsFinaux[idx3]);
                printf(tableauMotsFinaux[idx3]);
                printf("\n");
                idx3++;
            }
        }
    }
    
    else
        printf("Le fichier ne s'ouvre pas.");
    
    printf(ensembleMotsTrouves);
    
    

    
    


/* ENVOI DES MOTS SANS LES COORDONNEES */

    printf("\n----------------- ENVOI DE LA GRILLE ------------------\n\n");
    printf("ensembleMotsTrouves");

    zmq_send (responder, "ensembleMotsTrouves", 60, 0);  /*Envoi du message de confirmation*/

    printf("\n\n--------------------\n\n");
    
    return 1;

}
