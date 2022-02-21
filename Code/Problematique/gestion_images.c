/********
Fichier : gestion_images.c
Auteurs : Giuseppe Lomonaco
		  Milan Deve
Date    : 19 Fevrier 2022
Description : Fichier de distribution pour GEN145.
********/

#include <stdio.h>
#include <string.h>
#include "bibliotheque_images.h"

int image1[MAX_HAUTEUR][MAX_LARGEUR];
int image2[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB1[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB2[MAX_HAUTEUR][MAX_LARGEUR];

int main()
{
    int lignes1, colonnes1;
    int lignes2, colonnes2;
    int maxval;
    int histogramme[MAX_VALEUR+1];
    char nom[MAX_CHAINE];
    struct MetaData metadonnees;

	int retour;

    printf("-> Debut!\n");


	//nom = "Sherbrooke_Frontenac_nuit_pgm.txt";


	

	// Reading file
    retour = pgm_lire(nom, image1, 
                      &lignes1, &colonnes1, 
                      &maxval, &metadonnees);
     
	// Copying file
	//pgm_copier(image1, &lignes1, &colonnes1, image2, &lignes2, &colonnes2);

	// Writing file
    pgm_ecrire(nom, image1, 
               lignes1, colonnes1, 
               maxval, metadonnees);
               
               
               
               
               
	// Reading file ppm
    retour = ppm_lire(nom, image1, 
                      &lignes1, &colonnes1, 
                      &maxval, &metadonnees);
     
	// Writing file
    ppm_ecrire(nom, image1, 
               lignes1, colonnes1, 
               maxval, metadonnees);           
               
               
               
               
               
               
               
    // exemple detraitement d'un code de retour (erreur ou reussite)
	printf("-> Retour: ");
	
	if (retour == OK)
		printf("-> OK\n");
	else
		printf("-> ERREUR\n");           

    printf("-> Fin!\n");

    return 0;
}
