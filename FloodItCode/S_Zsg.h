#ifndef __S_ZSG__
#define __S_ZSG__

#include "Liste_case.h"
typedef struct{
	int dim;
	int nbcl;

	ListeCase Lzsg;
	ListeCase * B;
	int ** App;
} S_Zsg;

S_Zsg * init_Zsg(int dim,int nbcl);
void ajoute_Zsg(int i,int j,S_Zsg* S);
void ajoute_Bordure(int i,int j,int cl,S_Zsg* S);
int appartient_Zsg(int i,int j,S_Zsg* S);
int appartient_Bordure(int i,int j,int cl,S_Zsg* S);
int agrandit_Zsg(int **M,S_Zsg *Z,int cl,int k,int l);
int strequence_aleatoire_rapide(int **M,S_Zsg *Z);

#endif

