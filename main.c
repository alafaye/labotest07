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
#include "crypto.h"
#include "utils.h"

/* 
 * Arguments should be given following this format:
 * Encryption:
 * -c name_file_in name_file_out
 * Decryption:
 * -d name_file_in name_file_out
 * There's also an optionnal arg password to add after the fields before
 * -p password
 */

int main(int argc, char ** argv){
    /* Variable declaration */
    FILE *in_file, *out_file;
    char * in_file_name,  * out_file_name, * password;
    /* Mode: 0 for encryption, 1 for decryption */
    int mode, bytes_written;

    /* Arguments parsing */
    if(argparse(&in_file_name, &out_file_name, &password,
		argc, argv, &mode)==EXIT_FAILURE){
	return EXIT_FAILURE;
    }

    /* Opening files */
    if(open_read(&in_file, in_file_name)==EXIT_FAILURE){
	return EXIT_FAILURE;
    }
    if(open_write(&out_file, out_file_name)==EXIT_FAILURE){
	return EXIT_FAILURE;
    }

    /* Encrypt or decrypt following the mode */
    if(mode==0){
	bytes_written = encrypt(in_file, out_file, password);
    }
    else if(mode==1){
	bytes_written = decrypt(in_file, out_file, password);
    }

    printf("%d octets ont été écrits.\n", bytes_written);

    /* Free memory */
    fclose(in_file);
    fclose(out_file);

    return EXIT_SUCCESS;
}
