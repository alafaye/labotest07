/*
 * Auteur: Alexandre Lafaye
 * Labo07: Files, args.
 *
 * But: Le but de ce laboratoire est de gérer l'ouverture/fermeture
 * des fichiers et les arguments dans le main.
 *
 * Date: 03.05.2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT_SIZE_PASS 128

/* Returns EXIT_SUCCESS or EXIT_FAILURE */
int argparse(char ** in_file_name, char ** out_file_name, char ** password,
	int argc, char ** argv, int * mode){

    /* Arguments management */
    if(argc != 4 && argc != 6){
	printf("Mauvais nombre d'arguments spécifié");
	return EXIT_FAILURE;
    }

    *in_file_name = argv[2];
    *out_file_name = argv[3];

    /* Mode check and printing out to stdr the expected result */
    if(strcmp(argv[1], "-c")==0){
	printf("Encryption mode\n");
	*mode = 0;
    }
    else if(strcmp(argv[1], "-d")==0){
	printf("Decryption mode\n");
	*mode = 1;
    }
    else{
	printf("Mode non reconnu!");
	return EXIT_FAILURE;
    }

    /* 
     * Check if password is inputed by the user
     * If not use default password
     */
    if(argc == 6){
	if(strcmp(argv[4], "-p")==0){
	    *password = argv[5];
	}
	else{
	    *password=NULL;
	    printf("Argument %s non reconnu!", argv[5]);
	    return EXIT_FAILURE;
	}
    }
    else{
	/* If the user is not providing a password through argv, ask for one */
	printf("Entrez un mot de passe: ");
	*password=malloc(LIMIT_SIZE_PASS*sizeof(char));
	if(*password==NULL){
	    printf("La mémoire pour le mot de passe n'a pas pu être réservée!");
	    free(*password);
	    return EXIT_FAILURE;
	}
	fgets(*password, LIMIT_SIZE_PASS, stdin);
    }
    return EXIT_SUCCESS;
}

/* Returns EXIT_SUCCESS or EXIT_FAILURE */
int open_read(FILE ** in_file, char * in_file_name){

    /* First check if input file exists */
    if((*in_file = fopen(in_file_name, "rb")) == NULL){
	printf("Le fichier d'entrée n'existe pas!");
	return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/* Returns EXIT_SUCCESS or EXIT_FAILURE */
int open_write(FILE ** out_file, char * out_file_name){

    char accept;
    /* Then check if output file exists */
    if((*out_file = fopen(out_file_name, "rb")) != NULL){
	fclose(*out_file);
	/* Asking if the file need to be deleted */
	printf("Le fichier de sortie : %s existe déjà, l'écraser? [y/n] : ",
		out_file_name);
	if(scanf("%c", &accept)!=1){
	    return EXIT_FAILURE;
	}
	while(getchar()!='\n');

	if(accept=='y'){
	    if((*out_file = fopen(out_file_name, "wb")) == NULL){
		printf("Echec de l'ouverture du fichier de sortie!");
		return EXIT_FAILURE;
	    }
	}
	else{
	    fclose(*out_file);
	    return EXIT_FAILURE;
	}
    }
    else if((*out_file = fopen(out_file_name, "wb")) == NULL){
	printf("Echec de l'ouverture du fichier de sortie!");
	return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
