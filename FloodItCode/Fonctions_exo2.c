#include<stdio.h>
#include "Entete_Fonctions.h"
#include <time.h>

int est_dansliste(ListeCase *L, int i, int j){
	Elnt_liste* tmp= *L;
	while(tmp){
		if (tmp->i==i && tmp->j==j)
		{
			return 1;
		}
		tmp=tmp->suiv;
	}
	return 0;
}

void trouve_zone_imp(int **M, int nbcase, int i, int j, int *taille, ListeCase *L){
	int cl=M[i][j];
	int s =i;
	int v =j;

	if (est_dansliste(L,i,j)==0)
	{
		ajoute_en_tete(L,i,j);
		(*taille)++;
	}
	else{
		return;
	}
	       
	while(s<nbcase){
		while( (v<nbcase) && (M[s][v]==cl) ){
			if (est_dansliste(L,s,v)==0)
			{
				ajoute_en_tete(L, s, v);
				(*taille)++;
			}
			v++;
		}
		v =j;
		while((v>0) && (M[s][v]==cl) ){
			if (est_dansliste(L,s,v)==0)
			{
				ajoute_en_tete(L, s, v);
				(*taille)++;
			}
			v--;
		}
		s++;
	}
	s =i;
	v =j;
	
	while(s>0){
		while( (v<nbcase) && (M[s][v]==cl) ){
			if (est_dansliste(L,s,v)==0)
			{
				ajoute_en_tete(L, s, v);
				(*taille)++;
			}
			v++;
		}
		v =j;
		while((v>0) && (M[s][v]==cl) ){
			if (est_dansliste(L,s,v)==0)
			{
				ajoute_en_tete(L, s, v);
				(*taille)++;
			}
			v--;
		}
		s--;
	}



}



int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff){
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
		
		trouve_zone_imp(M,dim,0,0,taille,l);
		
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


