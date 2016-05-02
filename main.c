/*
 * Auteur: Alexandre Lafaye
 * Labo07: Files, args.
 *
 * But: Le but de ce laboratoire est de gérer l'ouverture/fermeture
 * des fichiers et les arguments dans le main.
 *
 * Date: 02.04.2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"

#define BASE_PASS "Justanotthatrandomandlongstring"
#define LIMIT_SIZE_PASS 32

/* 
 * Arguments should be given following this format:
 * Encryption:
 * -c name_file_in name_file_out
 * Decryption:
 * -d name_file_in name_file_out
 * There's also an optionnal arg password to add after the fields before
 * -p password
 */

int main(int argc, const char ** argv){
    /* Variable declaration */
    FILE *in_file, *out_file;
    char * in_file_name,  * out_file_name, * password, buffer_password[LIMIT_SIZE_PASS], accept;
    /* Mode: 0 for encryption, 1 for decryption */
    int mode, arg_nbr, in_file_name_length, out_file_name_length, password_length;

    /* Arguments mangement */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    if(argc != 4 && argc != 6){
	printf("Mauvais nombre d'arguments spécifié");
	return EXIT_FAILURE;
    }
    else{
	/*To correctly set the string size */
	in_file_name_length = strlen(argv[2]);
	out_file_name_length = strlen(argv[3]);

	/* Set correct file name for in_file */
	in_file_name = malloc(in_file_name_length * sizeof(char));
	if(in_file_name == NULL){
	    printf("Le nom du fichier d'entrée n'est pas valide!");
	    free(in_file_name);
	    return EXIT_FAILURE;
	}
	strcpy(in_file_name, argv[2]);

	/* Set correct file name for out_file */
	out_file_name = malloc(out_file_name_length * sizeof(char));
	if(out_file_name == NULL){
	    printf("Le nom du fichier de sortie n'est pas valide!");
	    free(in_file_name); free(out_file_name);
	    return EXIT_FAILURE;
	}
	strcpy(out_file_name, argv[3]);
    }

    /* 
     * Check if password is inputed by the user
     * If not use default password
     */
    if(argc == 6){
	if(strcmp(argv[4], "-p")==0){
	    password_length = strlen(argv[4]);
	    password = malloc(password_length * sizeof(char));
	    if(password == NULL){
		printf("Le mot de passe n'est pas valide!");
		free(in_file_name); free(out_file_name); free(password);
		return EXIT_FAILURE;
	    }
	    strcpy(password, argv[5]);
	}
	else{
	    password=NULL;
	    printf("Argument %s non reconnu!", argv[5]);
	    free(in_file_name); free(out_file_name); free(password);
	    return EXIT_FAILURE;
	}
    }
    else{
	/* If the user is not providing a password through argv, ask for one */
	printf("Entrez un mot de passe: ");
	arg_nbr = scanf("%s", buffer_password);
	while(getchar()!='\n');

	if(arg_nbr==1){
	    password_length = strlen(buffer_password);
	    password = malloc(password_length * sizeof(char));
	    if(password == NULL){
		printf("Le mot de passe n'est pas valide!");
		free(in_file_name); free(out_file_name); free(password);
		return EXIT_FAILURE;
	    }
	    strcpy(password, buffer_password);
	}
	else if(arg_nbr != 1){
	    /* If the user input is not recognised, using default pass */
	    printf("Mot de passe non reconnu! Mot de passe de base utilisé.\n");

	    password_length = strlen(BASE_PASS);
	    password = malloc(password_length * sizeof(char));
	    if(password == NULL){
		printf("Le mot de passe n'est pas valide!");
		free(in_file_name); free(out_file_name); free(password);
		return EXIT_FAILURE;
	    }
	    strcpy(password, BASE_PASS);
	}
    }

    /* Mode check an printing out to stdr the expected result */
    if(strcmp(argv[1], "-c")==0){
	printf("Encryption mode\n");
	mode = 0;
    }
    else if(strcmp(argv[1], "-d")==0){
	printf("Decryption mode\n");
	mode = 1;
    }
    else{
	printf("Mode non reconnu!");
	return EXIT_FAILURE;
    }

    /* File open and control 
     * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    */

    /* First check if input file exists */
    if((in_file = fopen(in_file_name, "rb")) == NULL){
	printf("Le fichier d'entrée n'existe pas!");
	free(in_file_name); free(out_file_name); free(password);
	return EXIT_FAILURE;
    }

    /* Then check if output file exists */
    if((out_file = fopen(out_file_name, "rb")) != NULL){
	fclose(out_file);
	/* Asking if the file need to be deleted */
	printf("Le fichier de sortie existe déjà, l'écraser? [y/n] : ");
	if(scanf("%c", &accept)!=1){
	    free(in_file_name); free(out_file_name); free(password);
	    return EXIT_FAILURE;
	}
	while(getchar()!='\n');

	if(accept=='y'){
	    if((out_file = fopen(out_file_name, "wb")) == NULL){
		printf("Echec de l'ouverture du fichier de sortie!");
		fclose(in_file);
		free(in_file_name); free(out_file_name); free(password);
		return EXIT_FAILURE;
	    }
	}
	else{
	    fclose(in_file);
	    fclose(out_file);
	    free(in_file_name); free(out_file_name); free(password);
	    return EXIT_FAILURE;
	}
    }
    else if((out_file = fopen(out_file_name, "wb")) == NULL){
	printf("Echec de l'ouverture du fichier de sortie!");
	fclose(in_file);
	free(in_file_name); free(out_file_name); free(password);
	return EXIT_FAILURE;
    }


    if(mode==0){
	encrypt(in_file, out_file, password);
    }
    else if(mode==1){
	decrypt(in_file, out_file, password);
    }

    /* Free memory */
    fclose(in_file);
    fclose(out_file);
    free(in_file_name);
    free(out_file_name);
    free(password);

    return EXIT_SUCCESS;
}
