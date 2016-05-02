gcc -W -ansi -pedantic -Wall *.c -o crypto;
./crypto -c test passwordencrypt -p blabla;
./crypto -d passwordencrypt vertigo -p blabla;
vimdiff test vertigo;
rm passwordencrypt vertigo;
