all: Flood-It_Partie1

API_Gene_instance.o: API_Gene_instance.c API_Gene_instance.h
	gcc -c API_Gene_instance.c `sdl2-config --cflags`

API_Grille.o: API_Grille.c API_Grille.h
	gcc -c API_Grille.c `sdl2-config --cflags`

Liste_case.o: Liste_case.c Liste_case.h
	gcc -c Liste_case.c `sdl2-config --cflags`

Fonctions_exo1.o: Fonctions_exo1.c Entete_Fonctions.h Liste_case.h
	gcc -c Fonctions_exo1.c `sdl2-config --cflags`

Fonctions_exo2.o: Fonctions_exo2.c Entete_Fonctions.h Liste_case.h
	gcc -c Fonctions_exo2.c `sdl2-config --cflags`

Flood-It_Partie1.o: Flood-It_Partie1.c
	gcc -c Flood-It_Partie1.c `sdl2-config --cflags`

S_Zsg.o: S_Zsg.c S_Zsg.h Liste_case.h
	gcc -c S_Zsg.c `sdl2-config --cflags`

Flood-It_Partie1: Flood-It_Partie1.o Liste_case.o  API_Grille.o API_Gene_instance.o Fonctions_exo1.o Fonctions_exo2.o S_Zsg.o
	gcc -o Flood-It_Partie1 Flood-It_Partie1.o Liste_case.o API_Grille.o API_Gene_instance.o Fonctions_exo1.o Fonctions_exo2.o S_Zsg.o `sdl2-config --libs` 

clean:
	rm -f *.o Flood-It_Partie1
