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




/* 
 * *******************************************************************
 * 						QUESTIONS POUR DOMINGO
 * *******************************************************************
 * Demander a Domingo si il faut ecrire RETURN OK; ou ecrire RETURN 0;
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * *******************************************************************
*/

// running compiler in console
// C:/MinGW/bin/gcc.exe bibliotheque_images.c gestion_images.c -o gestion_images.o
// gestion_images.o



/*

 // Valeurs de retour des operations
#define OK 0
#define ERREUR -1
#define ERREUR_FICHIER -1
#define ERREUR_TAILLE -2	// taille is the number of pixels
#define ERREUR_FORMAT -3	// format is either P1, P2, P3
#define IDENTIQUES 0
#define DIFFERENTES 1

*/





















#include "bibliotheque_images.h"
#include <string.h>
#include <stdio.h>
//#include <iostream>


////////////////////////////////////////////////////////////////
// 		OPERATIONS POUR LES IMAGES EN NOIR ET BLANC
///////////////////////////////////////////////////////////////

int pgm_lire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int *p_maxval, struct MetaData *p_metadonnees)
{
	printf("--------------------------------------------------------\n");
	printf("***Loading File PGM (pgm_lire)***\n");  
	printf("--------------------------------------------------------\n");
	
	FILE *read_flow;
	read_flow = fopen(nom_fichier, "r");
	 
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
			//printf("Valeur : %d \n", location);
			if (first_line[location] == '\0') {
				return ERREUR;
			}
			location++;
		}
		printf("Location lenght is : %d \n", location - date);
	
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
	
	// Reading matrix and verifying format
	int pixels_count = 0;
	while(i < *p_lignes && j < *p_colonnes)	{
		fscanf(read_flow, "%d", & matrice[i][j]);
		//printf("%d ", matrice[i][j]);
		j++;
		pixels_count++;
		
		if (j == *p_colonnes)	{
			j = 0;	
			i++;
		}
	}
	
	// printing total pixels count simply lines times columns 
	int total_pixels = (*p_colonnes)*(*p_lignes);
	printf("Total pixels count is: %d \n", total_pixels);
	
	if (pixels_count != total_pixels)	{
		return ERREUR_TAILLE;
	}
	
	// closing file / freeing RAM
	printf("***End of pgm_lire()***\n\n\n\n"); 
	fclose(read_flow);
	return OK;
}



int pgm_ecrire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, struct MetaData metadonnees)
{
	printf("--------------------------------------------------------\n");
	printf("***Writing File PGM***\n"); 
	printf("--------------------------------------------------------\n");
	
	//nom_fichier = "resultats_pgm.txt";
	nom_fichier = "resultats.pgm";
	
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
	fprintf(write_flow, "%s", comments);
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
	printf("***End of pgm_ecrire()***\n\n\n\n");
	fclose(write_flow);
	return OK;
}




int pgm_copier(int matrice1[MAX_HAUTEUR][MAX_LARGEUR],int lignes1, int colonnes1, int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2)
{
	printf("--------------------------------------------------------\n");
	printf("***Copying File PGM***\n");
	printf("--------------------------------------------------------\n");
	
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

	printf("***End of pgm_copier()***\n\n\n\n");
	return OK;
}




int pgm_creer_histogramme(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int histogramme[MAX_VALEUR+1])
{
	printf("--------------------------------------------------------\n");
	printf("***Creating Histogramme PGM***\n");
	printf("--------------------------------------------------------\n");
	
	int histo = 0;
	
	for (int i = 0; i < MAX_VALEUR + 1; i++)	{
		printf("%d\n", histogramme[i]);
		histogramme[i] = 0;
	}
	
	for (int i = 0; i < lignes; i++)	{
		for (int j = 0; j < colonnes; j++)	{
			histo = matrice[i][j];
			//printf("%d\n", histo);
			histogramme[histo]++;
		}
	}
		
	printf("***End of pgm_creer_histogramme()***\n\n\n\n");
	return OK;
}






int pgm_couleur_preponderante(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes)
{
	printf("--------------------------------------------------------\n");
	printf("***Couleur preponderante PGM***\n");
	printf("--------------------------------------------------------\n");
	
	int couleur[MAX_VALEUR + 1];
	int freq = 0;
	int color = 0;
	for (int i = 0; i < MAX_VALEUR + 1; i++) {
		couleur[i] = 0;
	}

	int h = 0;

	for (int i = 0; i < lignes; i++) {
		for (int j = 0; j < colonnes; j++) {
			h = matrice[i][j];
			couleur[h]++;
		}
	}
	
	for (int i = 0; i < MAX_VALEUR + 1; i++) {
		if (couleur[i] > freq) {
			freq = couleur[i];
			color = i;
		}
	}

	printf("La couleur preponderante est : %d\n", color);
		
	printf("***End of pgm_couleur_preponderante()***\n\n\n\n");
	return color;
}





int pgm_eclaircir_noircir(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, int valeur)
{
	printf("--------------------------------------------------------\n");
	printf("***Eclaircir Noircir PGM***\n");
	printf("--------------------------------------------------------\n");
	
	for (int i = 0; i < lignes; i++) {
		for (int j = 0; j < colonnes; j++) {
			if (matrice[i][j] + valeur < maxval && matrice[i][j] + valeur > 0) {
				matrice[i][j] = matrice[i][j] + valeur;
			}
			else if (matrice[i][j] + valeur < maxval) {
				matrice[i][j] = 0;
			} 
			else {
				matrice[i][j] = maxval;
			}
		}
		if (matrice[lignes - 1][colonnes - 1] < 0 || matrice[lignes - 1][colonnes - 1] > 256) {
			return ERREUR_TAILLE;
		}
	}
		
	printf("***End of pgm_eclaircir_noircir()***\n\n\n\n");
	return OK;
}





int pgm_creer_negatif(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval)
{
	printf("--------------------------------------------------------\n");
	printf("***Creating Negative PGM***\n");
	printf("--------------------------------------------------------\n");
	
	for (int i = 0; i < lignes; i++) {
		for (int j = 0; j < colonnes; j++) {
			matrice[i][j] = maxval - matrice[i][j];
		}
	}
	
	if (matrice[lignes - 1][colonnes - 1] == NULL) {
		return ERREUR;
	}
		
	printf("***End of pgm_creer_negatif()***\n\n\n\n");
	return OK;
}






int pgm_extraire(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int lignes2, int colonnes2, int *p_lignes, int *p_colonnes)
{
	printf("--------------------------------------------------------\n");
	printf("***Extracting PGM***\n");
	printf("--------------------------------------------------------\n");
	
	/*
	 * A VERIFIER
	 * 
	 * 
	 * 
	 * int largeur = colonnes2 - colonnes1 + 1;
  int hauteur = lignes2 - lignes1 + 1;

  int matricetemp[hauteur][largeur];
  int x = 0;
  int y = 0;
  if (lignes1 > lignes2 || colonnes1 > colonnes2 || lignes2 > 2 || colonnes2 > 2) {
    return -2;
  }
  for (int i = lignes1; i <= lignes2; i++) {
    x = 0;
    for (int j = colonnes1; j <= colonnes2; j++) {

      matricetemp[y][x] = matrice[i][j];
      x++;
    }
    y++;
  }
  for (int i = 0; i < * p_lignes; i++) {
    for (int j = 0; j < * p_colonnes; j++) {
      matrice[i][j] = 0;
    }
  }
  * p_lignes = hauteur;
  * p_colonnes = largeur;
  for (int i = 0; i <= * p_lignes; i++) {
    for (int j = 0; j <= * p_colonnes; j++) {
      matrice[i][j] = matricetemp[i][j];
    }
  }
  return 0;
	 * 
	 * 
	 * 
	 * 
	 * 
	 */
	
	
	
	printf("***End of pgm_extraire()***\n\n\n\n");
	return OK;
}





int pgm_sont_identiques(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2)
{
	printf("--------------------------------------------------------\n");
	printf("***Is identical PGM***\n");
	printf("--------------------------------------------------------\n");
	
	
	
	printf("***End of pgm_sont_identiques()***\n\n\n\n");
	return OK;
}



int pgm_pivoter90(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens)
{
	printf("--------------------------------------------------------\n");
	printf("***Rotation 90 degrees PGM***\n");
	printf("--------------------------------------------------------\n");
	
	int tempo_matrice[MAX_HAUTEUR][MAX_LARGEUR];
	int tempo = 0;
	
	int nb_lines = *p_lignes;
	printf("Number of lines Originally : %d \n", nb_lines);
	
	int nb_columns = *p_colonnes;
	printf("Number of columns Originally: %d \n", nb_columns);
	
	for (int i = 0; i < *p_lignes; i++)	{
		for (int j = 0; j < *p_colonnes; j++)	{
			tempo_matrice[i][j] = matrice[i][j];
			matrice[i][j] = 0;
		}
	}
	
	// clockwise rotation
	if (sens == 1)	{
		for (int i = 0; i < *p_colonnes; i++)	{
			for (int j = 0; j < *p_lignes; j++)	{
				tempo = nb_lines - j;
				matrice[i][j] = tempo_matrice[tempo][i];
			}
		}
	}
	
	// counter-clockwise rotation
	if (sens == 0)	{
		for (int i = 0; i < *p_colonnes; i++)	{
			for (int j = 0; j < *p_lignes; j++)	{
				tempo = nb_columns - i;
				matrice[i][j] = tempo_matrice[j][tempo];
			}
		}
	}
	
	if (sens != 0 && sens != 1)	{
		return ERREUR;
	}
	
	// changing pointers lines and columns values
	int tempo_lines = *p_lignes;
	int tempo_columns = *p_colonnes;
	*p_lignes = tempo_columns;
	*p_colonnes = tempo_lines;
	
	// printing image size after rotation
	printf("Number of lines after rotation : %d \n", *p_lignes);
	printf("Number of columns after rotation : %d \n", *p_colonnes);
	
	// Quitting function
	printf("***End of pgm_pivoter90()***\n\n\n\n");
	return OK;
}
////////////////////////////////////////////////////////////////













////////////////////////////////////////////////////////////////
// 			OPERATIONS POUR LES IMAGES EN COULEUR
///////////////////////////////////////////////////////////////

int ppm_lire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int *p_maxval, struct MetaData *p_metadonnees)
{
	printf("--------------------------------------------------------\n");
	printf("***Loading File PPM (ppm_lire)***\n");  
	printf("--------------------------------------------------------\n");
	
	FILE *read_flow;
	read_flow = fopen(nom_fichier, "r");
	 
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
	//printf("Lenght of file_type is : %s\n", file_type);
	
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
	printf("***End of ppm_lire()***\n\n\n\n");  
	fclose(read_flow);
	return OK;
}



int ppm_ecrire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, struct MetaData metadonnees)
{
	printf("--------------------------------------------------------\n");
	printf("***Writing File PPM (ppm_ecrire)***\n"); 
	printf("--------------------------------------------------------\n");
	
	FILE *write_flow;
	write_flow = fopen(nom_fichier, "w");
	
	char comments[50];	
	char type[4] = "P3";
		
	if (*metadonnees.auteur != NULL)	{
		strcpy(comments, "#");
		strcat(comments, metadonnees.auteur);	
	}
	
	if (*metadonnees.dateCreation != NULL)	{
		strcat(comments, ";");
		strcat(comments, metadonnees.dateCreation);
	}
		
	if (*metadonnees.lieuCreation != NULL)	{
		strcat(comments, ";");
		strcat(comments, metadonnees.lieuCreation);
	}
	
	//int comments_lenght = strlen(comments);
	
	//if (comments_lenght < 5)	{
	//printf("Strlen comments : %d \n", strlen(comments));
	//	comments = NULL;
	//}
			
	if (comments != NULL)	{
		// here theres no \n to prevent empty line in file
		fprintf(write_flow, "%s", comments);
		printf("Comment line value is : %s", comments);
	}
	else
	{
		printf("No comments line\n");
	}
		

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
  
	//if ((matrice[lignes][colonnes]) == NULL) {
	//	return ERREUR_TAILLE;
	//}

	// closing file / freeing ram
	printf("***End of ppm_ecrire()***\n\n\n\n");
	fclose(write_flow);
	return OK;
}



int ppm_copier(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2)
{
	printf("--------------------------------------------------------\n");
	printf("***Copy image1RGB to image2RGB PPM***\n");
	printf("--------------------------------------------------------\n");
	
	for (int i = 0; i < lignes1; i++) {
		for (int j = 0; j < colonnes1; j++) {
			matrice2[i][j].valeurR = matrice1[i][j].valeurR;
			matrice2[i][j].valeurG = matrice1[i][j].valeurG;
			matrice2[i][j].valeurB = matrice1[i][j].valeurB;
		}
	}
	
	if (matrice2[lignes1 - 2][colonnes1 - 2].valeurR == NULL || matrice2[lignes1 - 2][colonnes1 - 2].valeurG == NULL || matrice2[lignes1 - 2][colonnes1 - 2].valeurB == NULL) {
		return ERREUR;
	}
	
	* p_lignes2 = lignes1;
	* p_colonnes2 = colonnes1;
	
	// Quitting function
	printf("***End of ppm_copier()***\n\n\n\n");
	return OK;
}



int ppm_sont_identiques(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2)
{
	printf("--------------------------------------------------------\n");
	printf("***Is image1RGB identical to image2RGB PPM***\n");
	printf("--------------------------------------------------------\n");
	
	int RETURN = IDENTIQUES;
	
	if(lignes1 != lignes2 || colonnes1 != colonnes2)	{
		printf("Les images ont un format differents\n");
		RETURN = DIFFERENTES;
	}
	
	else if (lignes1 == lignes2 && colonnes1 == colonnes2)
	{
		for (int i = 0; i < lignes1; i++)	{
			for (int j = 0; j < colonnes1; j++)	{
				if (matrice1[i][j].valeurR != matrice2[i][j].valeurR || matrice1[i][j].valeurG != matrice2[i][j].valeurG || matrice1[i][j].valeurB != matrice2[i][j].valeurB)	{
					printf("Les images sont differentes\n");
					RETURN = DIFFERENTES;
				}
			
			}
		}
	}
	else	
	
	if (RETURN != DIFFERENTES && RETURN != IDENTIQUES)	{
		printf("Il y a une erreur: NI identique, NI Differentes\n");
		RETURN = ERREUR;
	}
	
	// Quitting function
	printf("***End of ppm_sont_identiques()***\n\n\n\n");
	return RETURN;
}



int ppm_pivoter90(struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens)
{
	printf("--------------------------------------------------------\n");
	printf("***Rotation COLOR image 90 degrees (ppm_pivoter90)***\n");
	printf("--------------------------------------------------------\n");
	
	struct RGB tempo_matrice[MAX_HAUTEUR][MAX_LARGEUR];
	int tempo = 0;
	
	int nb_lines = *p_lignes;
	printf("Number of lines Originally : %d \n", nb_lines);
	
	int nb_columns = *p_colonnes;
	printf("Number of columns Originally: %d \n", nb_columns);
	
	for (int i = 0; i < *p_lignes; i++)	{
		for (int j = 0; j < *p_colonnes; j++)	{
			tempo_matrice[i][j].valeurR = matrice[i][j].valeurR;
			tempo_matrice[i][j].valeurG = matrice[i][j].valeurG;
			tempo_matrice[i][j].valeurB = matrice[i][j].valeurB;
			matrice[i][j].valeurR = 0;
			matrice[i][j].valeurG = 0;
			matrice[i][j].valeurB = 0;
			
		}
	}
	
	// clockwise rotation
	if (sens == 1)	{
		for (int i = 0; i < *p_colonnes; i++)	{
			for (int j = 0; j < *p_lignes; j++)	{
				tempo = nb_lines - j;
				matrice[i][j].valeurR = tempo_matrice[tempo][i].valeurR;
				matrice[i][j].valeurG = tempo_matrice[tempo][i].valeurG;
				matrice[i][j].valeurB = tempo_matrice[tempo][i].valeurB;	
			}
		}
	
	}
	
	// counter-clockwise rotation
	if (sens == 0)	{
		for (int i = 0; i < *p_colonnes; i++)	{
			for (int j = 0; j < *p_lignes; j++)	{
				tempo = nb_columns - i;
				matrice[i][j].valeurR = tempo_matrice[j][tempo].valeurR;
				matrice[i][j].valeurG = tempo_matrice[j][tempo].valeurG;
				matrice[i][j].valeurB = tempo_matrice[j][tempo].valeurB;	
			}
		}
	
	}
	
	if (sens != 0 && sens != 1)	{
		return ERREUR;
	}
	
	// changing pointers lines and columns values
	int tempo_lines = *p_lignes;
	int tempo_columns = *p_colonnes;
	*p_lignes = tempo_columns;
	*p_colonnes = tempo_lines;
	
	// printing image size after rotation
	printf("Number of lines after rotation : %d \n", *p_lignes);
	printf("Number of columns after rotation : %d \n", *p_colonnes);
	
	// Quitting function
	printf("***End of ppm_pivoter90()***\n\n\n\n");
	return OK;
}






