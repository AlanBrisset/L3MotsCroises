DIR_C         = ./FONCTIONS_C/
DIR_S         = ./FONCTIONS_S/


all: client server clean

client: join_c.o grid_c.o words_c.o found_c.o client.o 
	gcc -o client join.o grid.o words.o found.o client.o -lzmq

server: join_s.o grid_s.o words_s.o found_s.o server.o
	gcc -o server join.o grid.o words.o found.o server.o -lzmq

join_c.o: 
	gcc -o join.o -c $(DIR_C)JOIN.c -W -Wall -ansi -pedantic -lzmq

grid_c.o: 
	gcc -o grid.o -c $(DIR_C)GRID.c -W -Wall -ansi -pedantic -lzmq

words_c.o: 
	gcc -o words.o -c $(DIR_C)WORDS.c -W -Wall -ansi -pedantic -lzmq

found_c.o: 
	gcc -o found.o -c $(DIR_C)FOUND.c -W -Wall -ansi -pedantic -lzmq

client.o: client.c $(DIR_C)fonctions.h
	gcc -o client.o -c client.c -W -Wall -ansi -pedantic -lzmq

join_s.o: 
	gcc -o join.o -c $(DIR_S)JOIN.c -W -Wall -ansi -pedantic -lzmq

grid_s.o: 
	gcc -o grid.o -c $(DIR_S)GRID.c -W -Wall -ansi -pedantic -lzmq

words_s.o: 
	gcc -o words.o -c $(DIR_S)WORDS.c -W -Wall -ansi -pedantic -lzmq

found_s.o: 
	gcc -o words.o -c $(DIR_S)FOUND.c -W -Wall -ansi -pedantic -lzmq

server.o: server.c $(DIR_S)fonctions.h
	gcc -o server.o -c server.c -W -Wall -ansi -pedantic -lzmq

clean:
	rm -rf *.o

mrproper: clean
	rm -rf client server
