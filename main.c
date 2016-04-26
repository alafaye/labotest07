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

int main(int argc, char* argv){
    /* Variable declaration */
    FILE *in_file, *out_file;
    char in_file_name[FILE_NAME_LIMIT], out_file_name[FILE_NAME_LIMIT], accept,
	with_password=0, * password;
    int i, j, k;
    /* Mode: 0 for encryption, 1 for decryption */
    int mode;

    /* Get args */
    if(argc != 4 || argc != 6){
	printf("Mauvais nombre d'arguments spécifié");
	return EXIT_FAILURE;
    }

    /* 
     * Check if password is inputed by the user
     * If not use default password "test1234"
     * TODO specify password lenght
     */
    if(argc == 6){
	if(argv[4] == "-p"){
	    with_password=1;
	}
    }
    else{
	password = "test1234";
    }

    if(argv[1] == "-c"){
	printf("encryption mode\n");
	mode = 0;
    }
    else if(argv[1] == "-d"){
	printf("decryption mode\n");
	mode = 1;
    }
    else{
	printf("Mode non reconnu!");
	return EXIT_FAILURE;
    }

    /* File open and control */

    /* First check if input file exists */
    if(in_file = fopen(in_file_name, "r" == NULL)){
	printf("Le fichier d'entrée n'existe pas!");
	return EXIT_FAILURE;
    }

    /* Then check if output file exists */
    if(out_file = fopen(out_file_name, "r" != NULL)){
	fclose(out_file);
	printf("Le fichier de sortie existe déjà, l'écraser? [y/n] :");
	/* TODO securise buffers */
	scanf("%c", &accept);
	if(accept=='y'){
	    out_file = fopen(out_file_name, "w");
	}
	else{
	    printf("Spécifier un nouveau nom de fichier de sortie : ");
	    scanf("%s", out_file_name);
	    return EXIT_FAILURE;
	}
    }

    if(mode==0){
	encrypt(in_file, out_file, password);
    }
    else if(mode==1){
	decrypt(in_file, out_file, password);
    }
    return EXIT_SUCCESS;
}
