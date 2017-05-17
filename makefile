CC=gcc
CFLAGS=-Wall -std=c99 -O
LDFLAGS=
EXEC=jeuDeHex

all:	$(EXEC)

$(EXEC): main.o plateau.o case.o jouer.o
	$(CC) -o $@ $^ $(LDFLAGS)

plateau.o: plateau.c
	$(CC) -o $@ -c $< $(CFLAGS)

case.o: case.c
	$(CC) -o $@ -c $< $(CFLAGS)

jouer.o: jouer.c plateau.h case.h
	$(CC) -o $@ -c $< $(CFLAGS)

main.o: main.c jouer.h plateau.h case.h
	$(CC) -o $@ -c $< $(CFLAGS)

tu_case.o: tu_case.c case.o
	$(CC) -o $@ -c $< $(CFLAGS)

tu_plateau.o: tu_plateau.c plateau.h case.h
	$(CC) -o $@ -c $< $(CFLAGS)

tu_jouer.o: tu_jouer.c jouer.h plateau.h case.h
	$(CC) -o $@ -c $< $(CFLAGS)

tu_arbre.o: tu_arbre.c arbre.h plateau.h case.h
	$(CC) -o $@ -c $< $(CFLAGS)


tu_case: tu_case.o case.o
	$(CC) -o $@ $^ $(LDFLAGS)

tu_plateau: tu_plateau.o plateau.o case.o
	$(CC) -o $@ $^ $(LDFLAGS)

tu_jouer: tu_jouer.o jouer.o plateau.o case.o
	$(CC) -o $@ $^ $(LDFLAGS)

tu_arbre: tu_arbre.o arbre.o plateau.o case.o
	$(CC) -o $@ $^ $(LDFLAGS)

minclean:
	rm *.o

clean:
	rm *.o
	rm $(EXEC)

maxclean:
	rm *.o
	rm $(EXEC)
	rm tu_case
	rm tu_plateau
	rm tu_jouer

valgrind:
	make
	./scriptMakeFile/makeValgrind.sh $(EXEC)

install:
	./scriptMakeFile/makeInstall.sh
	make



