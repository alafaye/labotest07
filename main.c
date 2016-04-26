#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME_LIMIT 31

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
	encrypt(in_file, out_file, "test");
    }
    else if(mode==1){
	decrypt(in_file, out_file, "test");
    }
    return EXIT_SUCCESS;
}

/* Encrypt function taking input files and passwords as args
 * Returns the number of bytes written to the encrypted file
 */
int encrypt(FILE * fileIn, FILE * fileOut, char * password){
    int i=0;

    while(fileIn != EOF){
	fprintf(fileOut, fileIn);
	i++;
    }

    return EXIT_SUCCESS;
}

/* Decrypt function taking input files and passwords as args
 * Returns the number of bytes written to the decrypted file
 */
int decrypt(FILE * fileIn, FILE * fileOut, char * password){

    return EXIT_SUCCESS;
}

/* Random number ]0, 1] generator, proposed by Lecuyer, replace bad rand()    */
double rando(char * password)
{ 
    /* Password string -> ints*/
    
    static int x10 = 12345, x11 = 67890, x12 = 13579,          /* initial value */
	       x20 = 24680, x21 = 98765, x22 = 43210;               /* of seeds */
    const int m = 2147483647; const int m2 = 2145483479;
    const int a12= 63308; const int q12=33921; const int r12=12979;
    const int a13=-183326; const int q13=11714; const int r13=2883;
    const int a21= 86098; const int q21=24919; const int r21= 7417;
    const int a23=-539608; const int q23= 3976; const int r23=2071;
    const double invm = 4.656612873077393e-10;
    int h, p12, p13, p21, p23;
    h = x10/q13; p13 = -a13*(x10-h*q13)-h*r13;
    h = x11/q12; p12 =  a12*(x11-h*q12)-h*r12;
    if (p13 < 0) p13 = p13 + m; if (p12 < 0) p12 = p12 + m;
    x10 = x11; x11 = x12; x12 = p12-p13; if (x12 < 0) x12 = x12 + m;
    h = x20/q23; p23 = -a23*(x20-h*q23)-h*r23;
    h = x22/q21; p21 =  a21*(x22-h*q21)-h*r21;
    if (p23 < 0) p23 = p23 + m2; if (p21 < 0) p21 = p21 + m2;
    x20 = x21; x21 = x22; x22 = p21-p23; if(x22 < 0) x22 = x22 + m2;
    if (x12 < x22) h = x12 - x22 + m; else h = x12 - x22;
    if (h == 0) return(1.0);
    else return(h*invm);
}
