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

/* Random number ]0, 1] generator, proposed by Lecuyer, replace bad rand()    */
double rando(char * password)
{ 
    static int x10 = 12345, x11 = 67890, x12 = 13579,          /* initial value */
	       x20 = 24680, x21 = 98765, x22 = 43210;               /* of seeds */
    const int m = 2147483647; const int m2 = 2145483479;
    const int a12= 63308; const int q12=33921; const int r12=12979;
    const int a13=-183326; const int q13=11714; const int r13=2883;
    const int a21= 86098; const int q21=24919; const int r21= 7417;
    const int a23=-539608; const int q23= 3976; const int r23=2071;
    const double invm = 4.656612873077393e-10;
    int h, p12, p13, p21, p23;
    int i=0, pass_seed=0;

    /* Password string -> ints */
    while(password[i] != '\0'){
	/* To avoid most collisions */
	if((i%2)==0){
	    pass_seed += (int)password[i];
	}
	else if((i%3)==0){
	    pass_seed -= (int)password[i];
	}
	else{
	    pass_seed =+ 2*(int)password[i];
	}
	i++;
    }
    x10 -= pass_seed; x11 += pass_seed; x12 -= pass_seed;     /* To modify seeds with the password */
    x20 += pass_seed; x21 -= pass_seed; x22 += pass_seed;

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

/* 
 * Encrypt function taking input files and passwords as args
 * Returns the number of bytes written to the encrypted file
 */
int encrypt(FILE * fileIn, FILE * fileOut, char * password){
    char c;
    int bytes_written=0;
    while((c = fgetc(fileIn)) != EOF){
	fprintf(fileOut, "%c", (char)(c+(int)(rando(password)*100)));
	bytes_written += sizeof(char);
    }
    return bytes_written;
}

/* 
 * Decrypt function taking input files and passwords as args
 * Returns the number of bytes written to the decrypted file
 */
int decrypt(FILE * fileIn, FILE * fileOut, char * password){
    char c;
    int bytes_written=0;
    while((c = fgetc(fileIn)) != EOF){
	fprintf(fileOut, "%c", (char)(c-(int)(rando(password)*100)));
	bytes_written += sizeof(char);
    }
    return bytes_written;
}

