CC=gcc
CFLAGS=-Wall -std=c99 -O
LDFLAGS=
EXEC=jeuDeHex

all:	$(EXEC)

$(EXEC): plateau.o case.o jouer.o
	$(CC) -o $@ $^ $(LDFLAGS)

plateau.o: plateau.c
	$(CC) -o $@ -c $< $(CFLAGS)

case.o: case.c
	$(CC) -o $@ -c $< $(CFLAGS)

jouer.o: jouer.c plateau.h case.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm *.o
	rm $(EXEC)

valgrind:
	make
	chmod 777 scriptMakeFile/makeValgrind.sh
	./scriptMakeFile/makeValgrind.sh $(EXEC) 



