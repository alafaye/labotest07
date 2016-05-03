/*
 * Auteur: Alexandre Lafaye
 * Labo07: Files, args.
 *
 * But: Le but de ce laboratoire est de gérer l'ouverture/fermeture
 * des fichiers et les arguments dans le main.
 *
 * Date: 03.05.2016
 */
int argparse(char ** in_file_name, char ** out_file_name, char ** password, int argc, char ** argv, int * mode);

int open_read(FILE ** in_file, char * in_file_name);

int open_write(FILE ** out_file, char * out_file_name);
