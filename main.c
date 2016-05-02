#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"

#define FILE_NAME_LIMIT 31

/* Arguments should be given following this format:
 * Encryption:
 * -c name_file_in name_file_out
 * Decryption:
 * -d name_file_in name_file_out
 * There's also an optionnal arg password to add after the fields before
 * -p password
 */

int main(int argc, const char * * argv){
    /* Variable declaration */
    FILE *in_file, *out_file;
    char in_file_name[FILE_NAME_LIMIT], out_file_name[FILE_NAME_LIMIT];

    char * password, accept;
    /* Mode: 0 for encryption, 1 for decryption */
    int mode;

    /* Get args */
    if(argc != 4 && argc != 6){
	printf("Mauvais nombre d'arguments spécifié");
	return EXIT_FAILURE;
    }
    else{
	strcpy(in_file_name  , argv[2]);
	strcpy(out_file_name  , argv[3]);
    }

    /* 
     * Check if password is inputed by the user
     * If not use default password "test1234"
     * TODO specify password lenght
     */
    if(argc == 6){
	if(strcmp(argv[4], "-p")==0){
	    strcpy(password, argv[5]);
	}
	else{
	    printf("Argument %s non reconnu!", argv[5]);
	    return EXIT_FAILURE;
	}
    }
    else{
	password = "test1234";
    }

    if(strcmp(argv[1], "-c")==0){
	printf("encryption mode\n");
	mode = 0;
    }
    else if(strcmp(argv[1], "-d")==0){
	printf("decryption mode\n");
	mode = 1;
    }
    else{
	printf("Mode non reconnu!");
	return EXIT_FAILURE;
    }

    /* File open and control */

    /* First check if input file exists */
    if((in_file = fopen(in_file_name, "rb")) == NULL){
	printf("Le fichier d'entrée n'existe pas!");
	return EXIT_FAILURE;
    }

    /* Then check if output file exists */
    if((out_file = fopen(out_file_name, "rb")) != NULL){
	fclose(out_file);
	printf("Le fichier de sortie existe déjà, l'écraser? [y/n] : ");

	scanf("%c", &accept);
	while(getchar()!='\n');

	if(accept=='y'){
	    if((out_file = fopen(out_file_name, "wb")) == NULL){
		printf("Echec de l'ouverture du fichier de sortie!");
		return EXIT_FAILURE;
	    }
	}
	else{
	    return EXIT_FAILURE;
	}
    }
    else if((out_file = fopen(out_file_name, "wb")) == NULL){
	printf("Echec de l'ouverture du fichier de sortie!");
	return EXIT_FAILURE;
    }

    if(mode==0){
	encrypt(in_file, out_file, password);
    }
    else if(mode==1){
	decrypt(in_file, out_file, password);
    }

    fclose(in_file);
    fclose(out_file);

    return EXIT_SUCCESS;
}
