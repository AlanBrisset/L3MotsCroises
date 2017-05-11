#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>

#include <time.h>

int GRID(void *responder){

    FILE* grilleFinie = NULL;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
  
/* RECEVOIR DU RIEN */
    char buffer11[0];
    zmq_recv(responder, buffer11, 0, 0); /* Réception du message de confirmation */




/* --- DIMENSIONS DE LA GRILLE --- */
    
    int dimLigne = 5;
    int dimColonne = 6; 
    
/*const char *motsLigneGrille[dimLigne];  /*Variable qui contiendra les mots générant la grille : chaque ligne sera constituée d'un mot.*/
/*strcpy(motsLigneGrille[4], "@"); /* On insère le symbole @ dans la dernière ligne de la grille. Cela nous permettra de savoir si toute la grille a été générée ou non (si le symbole @ a disparu, cela signifie qu'il a été remplacé par un mot).*/
    
    char motsLigneGrille[dimLigne][dimColonne+1];
    
    int j,k = 0; /* j sera une valeur aléatoire, k sera l'index de la variable motsLigneGrille.*/
    
    srand(time(NULL)); /*Initialisation de la donnée seed (calcul aléatoire).*/
    
    
    char nomDico[30] = "./RESSOURCES/dicos/dico";
    char nbCaracteres[15];
    sprintf(nbCaracteres, "%d", dimColonne);
    FILE* fichier2 = NULL;
    fichier2 = fopen ("./RESSOURCES/GRID.txt", "a");
    grilleFinie = fopen ("./RESSOURCES/GRID.txt", "r");
    char * tabGrille[255];
    char *p=tabGrille;
    
    
    strcat (nomDico, nbCaracteres); /*nomDico a le bon nom par rapport au nb de caractères demandés.*/
    
    strcat (nomDico, ".txt");
    
    char dest[256]; /* Contiendra le mot générateur */
    
   
/* VERIFIER SI LE FICHIER EST VIDE */
    
    int caracterePremier = 0;
 
    /*On lit le prmeier caractère du fichier*/
    caracterePremier = fgetc(fichier2);
    if(caracterePremier==EOF)
    {
    
    while(k<5)
    {
    
        FILE* fichier = NULL;
        fichier = fopen (nomDico, "r");
    
        if(fichier==NULL)
        {
            printf(nomDico);
            printf("Impossible d'afficher le dictionnaire de génération de grille.");
        }
        else
        {
    
            char * line = NULL;
            size_t len = 0;
            ssize_t read;
    
        
        
            while ((k<5) && (read = getline(&line, &len, fichier)) != -1)
            {
            
                j = rand() % (6000 + 1); /* Nombre aléatoire entre 1 et 6000*/
            
                if (j==1298 && (k<5) && strlen(line)>3) /* On choisit une valeur fixe. On a une chance sur 6000 de passer dans ce if.*/
                {
                    line[6]='\0';
                    strcpy(motsLigneGrille[k], line);
                    k++;
                    
                    if (fichier2 != NULL)
                    {
                    fprintf (fichier2,"%s\n",line);
                    }
                    else{
                        
                    printf("Impossible d'exporter la grille");
                        
                    }
                    

        
                }
            }
        }
        
        
        fclose(fichier);
    }

    fclose(fichier2);
    printf("\n----------------- AFFICHAGE DES LIGNES DE LA GRILLE ------------------\n\n");
    
    printf("1: ");
    printf(motsLigneGrille[0]);
    printf("\n");
            
    printf("2: ");
    printf(motsLigneGrille[1]);
    printf("\n");
            
    printf("3: ");
    printf(motsLigneGrille[2]);
    printf("\n");
            
    printf("4: ");
    printf(motsLigneGrille[3]);
    printf("\n");
            
    printf("5: ");
    printf(motsLigneGrille[4]);
    printf("\n");
        
    printf("\n--------------------");
    printf("\n");
    
    

    strcpy(tabGrille, "GRID ");

    char nbLignesChar[15];
    sprintf(nbLignesChar, "%d", dimLigne);

    char nbColonnesChar[15];
    sprintf(nbColonnesChar, "%d", dimColonne);

    strcat(tabGrille, nbLignesChar);
    strcat(tabGrille, " ");
    strcat(tabGrille, nbColonnesChar);
    strcat(tabGrille, " ");


    while ((read = getline(&line, &len, grilleFinie)) != -1) {

	strcat(tabGrille, line);
	p[strlen(p)-1] = '\0' ;
    }
    }

    printf("\n----------------- ENVOI DE LA GRILLE ------------------\n\n");



    printf(tabGrille);
	

    fclose(grilleFinie);

    zmq_send (responder, tabGrille, 60, 0);  /*Envoi du message de confirmation*/

    printf("\n\n--------------------\n\n");
    
    return 1;

}


