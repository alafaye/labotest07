gcc -W -ansi -pedantic -Wall *.c -o crypto;
./crypto -c test passwordencrypt;
./crypto -d passwordencrypt vertigo;
vimdiff test vertigo;
rm passwordencrypt vertigo;
