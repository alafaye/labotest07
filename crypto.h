
/* Encrypt function taking input files and passwords as args
 * Returns the number of bytes written to the encrypted file
 */
int encrypt(FILE * fileIn, FILE * fileOut, char * password);

/* Decrypt function taking input files and passwords as args
 * Returns the number of bytes written to the decrypted file
 */
int decrypt(FILE * fileIn, FILE * fileOut, char * password);

/* Random number ]0, 1] generator, proposed by Lecuyer, replace bad rand()    */
double rando(char * password);
