#include<stdio.h>
#include "Entete_Fonctions.h"
#include <time.h>

void trouve_zone_rec(int **M, int nbcase, int i, int j, int *taille, ListeCase *L){
	//on verifie que i,j n'est pas déjà dans L
	
	Elnt_liste* tmp=*L;
	while(tmp){
		if(tmp->i==i && tmp->j==j){
			return;
		}
		tmp=tmp->suiv;
	}
	//OK
	
	ajoute_en_tete(L,i,j);
	
	(*taille)++;
	//On regarde les cases adjacentes
	int ki,kj;
	for(ki=i-1;ki<=i+1;ki++){
		for(kj=j-1;kj<=j+1;kj++){
			if((ki>=0 && ki<nbcase) && (kj>=0 && kj<nbcase)){
				if(M[ki][kj]==M[i][j]){
					trouve_zone_rec(M,nbcase,ki,kj,taille,L);
				}
			}
		}
	}
	
}


int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff){
	srand(time(NULL));
	int cpt=-1;
	int i,j;
	int nouv_coul;
	Elnt_liste* tmp;
	
	ListeCase * l=(ListeCase *)(malloc(sizeof(ListeCase)));
	init_liste(l);
	
	int* taille=(int *)(malloc(sizeof(int)));
	(*taille)=0;
	
	//tant que la Zsg ne remplit pas toute la grille
	while((*taille)<dim*dim){
		cpt++;
		
		init_liste(l);
		*taille=0;
		//On calcule la nouvelle Zsg
		
		trouve_zone_rec(M,dim,0,0,taille,l);
		
		tmp=*l;				
		//on prend une nouvelle coileur que la Zsg
		do{
			nouv_coul=rand()%nbcl;
		}while(nouv_coul==M[0][0]);
		
		//On change la couleur de la nouvelle Zsg
		while(tmp){
			M[tmp->i][tmp->j]=nouv_coul;
			if(aff){
				Grille_attribue_couleur_case(G,tmp->i,tmp->j,M[tmp->i][tmp->j]);
			}
			tmp=tmp->suiv;
		}
		if(aff){
			Grille_attente_touche();	
			Grille_redessine_Grille(G);
		}
	}
	return cpt;
}


