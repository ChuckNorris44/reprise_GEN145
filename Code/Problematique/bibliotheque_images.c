/********
Fichier	: bibliotheque_images.c
Auteurs	: Giuseppe Lomonaco
		  Milan Delev
Date	: 19 fevrier 2022
Description : Fichier de distribution pour GEN145.
********/

/*
 * L'anglais est utilise dans le code afin de faciliter la distinction
 * entre les variables et fonctions du code de depart et celui ecrit
 * par les deux etudiants mentionnes ci-haut.
 * 
 * S'il-vous-plait ne pas nous penaliser pour cette facon de 
 * fonctionner car les deux etudiants mentionnes ci-haut sont conscients
 * que lors de l'ecriture de code et de script, il est tres important
 * de n'utiliser qu'une seule langue.
*/





#include "bibliotheque_images.h"
#include <string.h>
#include <stdio.h>



// running in console
// C:/MinGW/bin/gcc.exe bibliotheque_images.c gestion_images.c -o gestion_images.o
// gestion_images.o


/*

 // Valeurs de retour des operations
#define OK 0
#define ERREUR -1
#define ERREUR_FICHIER -1
#define ERREUR_TAILLE -2
#define ERREUR_FORMAT -3
#define IDENTIQUES 0
#define DIFFERENTES 1

*/






////////////////////////////////////////////////////////////////
// 		OPERATIONS POUR LES IMAGES EN NOIR ET BLANC
///////////////////////////////////////////////////////////////

int pgm_lire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int *p_maxval, struct MetaData *p_metadonnees)
{
 
	nom_fichier = "Sherbrooke_Frontenac_nuit_pgm.txt";
	
	FILE *read_flow;
	 
	// file type is P2 for pgm file
	char file_type[MAX_VALEUR];
	char first_line[MAX_VALEUR];
	 
	char author_str[MAX_VALEUR];
	char date_str[MAX_VALEUR];
	char location_str[MAX_VALEUR];
	
	char first_char;
	int author = 0;
	int date = 0;
	int location = 0;
	 
	int i = 0;
	int j = 0;
	 
	
	printf("***Loading File PGM***\n");  
	read_flow = fopen(nom_fichier, "r");
	 
	// verifying that the file is not empty
	if(read_flow == NULL)	{
		printf("Unable to find file '%s' \n", nom_fichier);
		return ERREUR_FICHIER;
	}
	else
		printf("File '%s' load successfull\n", nom_fichier);

	
	// getting 1st char of file
	first_char = fgetc(read_flow);
	//printf("Value of first char is : %c \n", first_char);
	
	if (first_char == '#')	
	{
		// getting the first line data and printing
		fgets(first_line, MAX_VALEUR, read_flow);
		printf("First line is : %s \n", first_line);
		
		// getting author length
		while (first_line[author] != ';') {
			if (first_line[author] == '\0') {
				return ERREUR;
			}
			author++;
		}
		//printf("Author lenght is : %d \n", author);
		
		// getting date length
		date = author + 1;
		while (first_line[date] != ';') {
			if (first_line[date] == '\0') {
				return ERREUR;
			}
			date++;
		}
		//printf("Date lenght is : %d \n", date - author);
		
		// getting location length
		location = date;
		while (first_line[location] != '\0') {
			if (first_line[location] == '\0') {
				return ERREUR;
			}
			location++;
		}
		//printf("Location lenght is : %d \n", location - date);
	
	
	// copying strings author, date and location
	strncpy(author_str, first_line, author);
	printf("Author value is : %s \n", author_str);
	
	strncpy(date_str, (first_line + author + 1), date - author - 1);
	printf("Date value is : %s \n", date_str);
	
	strncpy(location_str, (first_line + date + 1), location - date - 1);
	printf("Location value is : %s \n", location_str);
	
	// copying strings into metadata structure
	strcpy(p_metadonnees->auteur, author_str);
	strcpy(p_metadonnees->dateCreation, date_str);	
	strcpy(p_metadonnees->lieuCreation, location_str);
	}
	
	
	// verifying format make sure its color (P2)
	fgets(file_type, 3, read_flow);
	printf("format : %s\n", file_type);
	
	if (first_char == '#')	{
		if (file_type[1] != '2' || file_type[0] != 'P')	{
			return ERREUR_FORMAT;
		}
	} 
	else if (first_char != 'P' && file_type[1] != '2')	{
		return ERREUR_FORMAT;
	}
	
	// Scanning lines and columns
	fscanf(read_flow, "%d", p_colonnes);
	fscanf(read_flow, "%d", p_lignes);
	
	if (*p_lignes > 256 || *p_colonnes > 256)	{
		return ERREUR_TAILLE;
	}
	
	// Scanning max_val
	fscanf(read_flow, "%d", p_maxval);
	printf("Maxval value is : %d \n", *p_maxval);
	
	// Reading matrix
	while(i < *p_lignes && j < *p_colonnes)	{
		fscanf(read_flow, "%d", & matrice[i][j]);
		//printf("%d ", matrice[i][j]);
		j++;
		
		if (j == *p_colonnes)	{
			j = 0;	
			i++;
		}
	}
	
	// closing file / freeing RAM
	fclose(read_flow);
	printf("***End of pgm_lire()***\n\n\n");  
	return OK;
}








int pgm_ecrire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, struct MetaData metadonnees)
{
	printf("***Writing File PGM***\n"); 
	
	nom_fichier = "resultats_pgm.txt";
	
	FILE *write_flow;
	
	char comments[50];	
	char type[4] = "P2";
	
	write_flow = fopen(nom_fichier, "w");
	
	// getting comment line and writing data to file
	strcpy(comments, "#");
	strcat(comments, metadonnees.auteur);
	strcat(comments, ";");
	strcat(comments, metadonnees.dateCreation);
	strcat(comments, ";");
	strcat(comments, metadonnees.lieuCreation);
	fprintf(write_flow, "%s\n", comments);
	printf("Comment line value is : %s \n", comments);
	fprintf(write_flow, "%s\n", type);
	printf("File type is : %s \n", type);
	fprintf(write_flow, "%d %d\n", colonnes, lignes);
	//printf("%d %d\n", colonnes, lignes);
	fprintf(write_flow, "%d\n", maxval);
	printf("Max value is : %d \n", maxval);
	
	for (int i = 0; i < lignes; i++) {
		for (int j = 0; j < colonnes; j++) {
			fprintf(write_flow, "%d ", matrice[i][j]);
			//printf(" %d", matrice[i][j]);
		}
    fprintf(write_flow, "\n");
	}
  
	if (matrice[lignes - 1][colonnes - 1] == NULL) {
		return ERREUR_TAILLE;
	}

	// closing file / freeing ram
	fclose(write_flow);
	printf("***End of pgm_ecrire()***\n\n\n");
	return OK;
}









int pgm_copier(int matrice1[MAX_HAUTEUR][MAX_LARGEUR],int lignes1, int colonnes1, int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2)
{
	printf("***Copying File PGM***\n");
	
	for (int i = 0; i < lignes1; i++) {
		for (int j = 0; j < colonnes1; j++) {
			matrice2[i][j] = matrice1[i][j];
		}
	}
	
	if (matrice2[lignes1 - 1][colonnes1 - 1] == NULL) {
		return ERREUR_TAILLE;
	}
  
	* p_lignes2 = lignes1;
	* p_colonnes2 = colonnes1;

	printf("***End of pgm_copier()***\n");
	return OK;
}








int pgm_creer_histogramme(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int histogramme[MAX_VALEUR+1])
{
	
	
	
	
	
	return OK;
}










int pgm_couleur_preponderante(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes)
{
	
	
	
	
	
	return OK;
}








int pgm_eclaircir_noircir(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, int valeur)
{
	
	
	
	
	
	return OK;
}









int pgm_creer_negatif(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval)
{
	
	
	
	
	
	return OK;
}








int pgm_extraire(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int lignes2, int colonnes2, int *p_lignes, int *p_colonnes)
{
	
	
	
	
	
	return OK;
}








int pgm_sont_identiques(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2)
{
	
	
	
	
	
	return OK;
}









int pgm_pivoter90(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens)
{
	
	
	
	
	
	return OK;
}






















////////////////////////////////////////////////////////////////
// 			OPERATIONS POUR LES IMAGES EN COULEUR
///////////////////////////////////////////////////////////////

int ppm_lire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int *p_maxval, struct MetaData *p_metadonnees)
{
	nom_fichier = "Sherbrooke_Frontenac_nuit_ppm.txt";
	
	FILE *read_flow;
	 
	// file type is P2 for pgm file
	char file_type[MAX_VALEUR];
	char first_line[MAX_VALEUR];
	 
	char author_str[MAX_VALEUR];
	char date_str[MAX_VALEUR];
	char location_str[MAX_VALEUR];
	
	char first_char;
	int author = 0;
	int date = 0;
	int location = 0;
	 
	int i = 0;
	int j = 0;
	 
	
	printf("***Loading File PPM***\n");  
	read_flow = fopen(nom_fichier, "r");
	 
	// verifying that the file is not empty
	if(read_flow == NULL)	{
		printf("Unable to find file '%s' \n", nom_fichier);
		return ERREUR_FICHIER;
	}
	else
		printf("File '%s' load successfull\n", nom_fichier);

	
	// getting 1st char of file
	first_char = fgetc(read_flow);
	//printf("Value of first char is : %c \n", first_char);
	
	if (first_char == '#')	
	{
		// getting the first line data and printing
		fgets(first_line, MAX_VALEUR, read_flow);
		printf("First line is : %s \n", first_line);
		
		// getting author length
		while (first_line[author] != ';') {
			if (first_line[author] == '\0') {
				return ERREUR;
			}
			author++;
		}
		//printf("Author lenght is : %d \n", author);
		
		// getting date length
		date = author + 1;
		while (first_line[date] != ';') {
			if (first_line[date] == '\0') {
				return ERREUR;
			}
			date++;
		}
		//printf("Date lenght is : %d \n", date - author);
		
		// getting location length
		location = date;
		while (first_line[location] != '\0') {
			if (first_line[location] == '\0') {
				return ERREUR;
			}
			location++;
		}
		//printf("Location lenght is : %d \n", location - date);
	
	
	// copying strings author, date and location
	strncpy(author_str, first_line, author);
	printf("Author value is : %s \n", author_str);
	
	strncpy(date_str, (first_line + author + 1), date - author - 1);
	printf("Date value is : %s \n", date_str);
	
	strncpy(location_str, (first_line + date + 1), location - date - 1);
	printf("Location value is : %s \n", location_str);
	
	// copying strings into metadata structure
	strcpy(p_metadonnees->auteur, author_str);
	strcpy(p_metadonnees->dateCreation, date_str);	
	strcpy(p_metadonnees->lieuCreation, location_str);
	}
	
	
	// verifying format make sure its color (P2)
	fgets(file_type, 3, read_flow);
	printf("format : %s\n", file_type);
	
	if (first_char == '#')	{
		if (file_type[1] != '3' || file_type[0] != 'P')	{
			return ERREUR_FORMAT;
		}
	} 
	else if (first_char != 'P' && file_type[1] != '3')	{
		return ERREUR_FORMAT;
	}
	
	// Scanning lines and columns
	fscanf(read_flow, "%d", p_colonnes);
	fscanf(read_flow, "%d", p_lignes);
	
	if (*p_lignes > 256 || *p_colonnes > 256)	{
		return ERREUR_TAILLE;
	}
	
	// Scanning max_val
	fscanf(read_flow, "%d", p_maxval);
	printf("Maxval value is : %d \n", *p_maxval);
	
	// Reading matrix
	while(i < *p_lignes && j < *p_colonnes)	{
		fscanf(read_flow, "%d", & matrice[i][j].valeurR);
		fscanf(read_flow, "%d", & matrice[i][j].valeurG);
		fscanf(read_flow, "%d", & matrice[i][j].valeurB);
		j++;
		
		if (j == *p_colonnes)	{
			j = 0;	
			i++;
		}
	}
	
	// closing file / freeing RAM
	fclose(read_flow);
	printf("***End of ppm_lire()***\n\n\n");  
	return OK;
}








int ppm_ecrire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, struct MetaData metadonnees)
{
	printf("***Writing File PGM***\n"); 
	
	nom_fichier = "resultats_ppm.txt";
	
	FILE *write_flow;
	
	char comments[50];	
	char type[4] = "P3";
	
	write_flow = fopen(nom_fichier, "w");
	
	// getting comment line and writing data to file
	strcpy(comments, "#");
	strcat(comments, metadonnees.auteur);
	strcat(comments, ";");
	strcat(comments, metadonnees.dateCreation);
	strcat(comments, ";");
	strcat(comments, metadonnees.lieuCreation);
	fprintf(write_flow, "%s\n", comments);
	printf("Comment line value is : %s \n", comments);
	fprintf(write_flow, "%s\n", type);
	printf("File type is : %s \n", type);
	fprintf(write_flow, "%d %d\n", colonnes, lignes);
	//printf("%d %d\n", colonnes, lignes);
	fprintf(write_flow, "%d\n", maxval);
	printf("Max value is : %d \n", maxval);
	
	for (int i = 0; i < lignes; i++) {
		for (int j = 0; j < colonnes; j++) {
			fprintf(write_flow, "%d ", matrice[i][j].valeurR);
			fprintf(write_flow, "%d ", matrice[i][j].valeurG);
			fprintf(write_flow, "%d ", matrice[i][j].valeurB);
			//printf(" %d", matrice[i][j]);
		}
    fprintf(write_flow, "\n");
	}
  
	//if (matrice[lignes - 1][colonnes - 1] == NULL) {
	//	return ERREUR_TAILLE;
	//}

	// closing file / freeing ram
	fclose(write_flow);
	printf("***End of ppm_ecrire()***\n\n\n");
	return OK;
	
	
	
	
	return OK;
}







int ppm_copier(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2)
{
	
	
	
	
	
	return OK;
}








int ppm_sont_identiques(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2)
{
	
	
	
	
	
	return OK;
}








int ppm_pivoter90(struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens)
{
	
	
	
	
	
	return OK;
}









