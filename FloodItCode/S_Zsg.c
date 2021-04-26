#include <stdlib.h>
#include "S_Zsg.h"
#include <stdio.h>
#include <time.h>

S_Zsg * init_Zsg(int dim,int nbcl){
	S_Zsg * res=(S_Zsg *)(malloc(sizeof(S_Zsg)));
	res->dim=dim;
	res->nbcl=nbcl;
	res->Lzsg=NULL;
	res->B=(ListeCase *)(malloc(sizeof(ListeCase)*nbcl));
	int **App=(int **)(malloc(sizeof(int *)*dim));
	int i,j;	
	for(i=0;i<dim;i++){
		App[i]=(int *)(malloc(sizeof(int)*dim));
		for(j=0;j<dim;j++){
			App[i][j]=-2;
		}

	}
	res->App=App;
	return res;
}

void ajoute_Zsg(int i,int j,S_Zsg* S){
	Elnt_liste * tmp=S->Lzsg;
	Elnt_liste * el=(Elnt_liste *)(malloc(sizeof(Elnt_liste)));
	el->i=i;
	el->j=j;
	el->suiv=tmp;
	S->Lzsg=el;
}

void ajoute_Bordure(int i,int j,int cl,S_Zsg* S){
	Elnt_liste * tmp=(S->B)[cl];
	Elnt_liste * el=(Elnt_liste *)(malloc(sizeof(Elnt_liste)));
	el->i=i;
	el->j=j;
	el->suiv=tmp;
	(S->B)[cl]=el;

}

int appartient_Zsg(int i,int j,S_Zsg* S){
	return ((S->App)[i][j]==-1)?1:0;
}

int appartient_Bordure(int i,int j,int cl,S_Zsg* S){
	return ((S->App)[i][j]==cl)?1:0;
}
ListeCase supprimer_elnt(ListeCase L,int i,int j){
	Elnt_liste * res=L;	
	Elnt_liste * tmp=L;
	Elnt_liste * tmp2;
	if(L==NULL){
		return NULL;
	}
	if(tmp->i==i && tmp->j==j){
		tmp2=tmp->suiv;
		free(tmp);
		return tmp2;
	}
	while(tmp){
		if(tmp->i==i && tmp->j==j){
			tmp2->suiv=tmp->suiv;
			free(tmp);
			return res;
		}

		tmp2=tmp;
		tmp=tmp->suiv;
	}
	return res;
	
}
int agrandit_Zsg(int **M,S_Zsg *Z,int cl,int k,int l){
	//on repere la zone associée à k,l et de couleur cl
	int i,j;
	int res=0;
	for(i=k-1;i<=k+1;i++){
		for(j=l-1;j<=l+1;j++){
			if((i>=0 && i<Z->dim) && (j>=0 && j<Z->dim)){
				
				if(appartient_Zsg(i,j,Z)!=1 && M[i][j]==cl){
					ajoute_en_tete(&(Z->Lzsg),i,j);
					(Z->App)[i][j]=-1;					
					res++;
					res+=agrandit_Zsg(M,Z,cl,i,j);
				}
				else if(M[i][j]!=cl && appartient_Bordure(i,j,M[i][j],Z)!=1){
					ajoute_en_tete(&(Z->B[M[i][j]]),i,j);
					(Z->App)[i][j]=M[i][j];
				}
			}
		}
	}
	return res;
	
}
int strequence_aleatoire_rapide(int **M,S_Zsg *Z){
	srand(time(NULL));
	int res=0;
	int cpt=0;
	Elnt_liste * l;
	Elnt_liste * lp;	
	int cl;
	//on initialise les listes à liste vide
	Z->Lzsg=NULL;
	int i;
	for(i=0;i<Z->nbcl;i++){
		(Z->B)[i]=NULL;
	}
	
	//on commence à utiliser agrandit_zsg pour M[0][0]... 
	res+=agrandit_Zsg(M,Z,M[0][0],0,0);
	//...puis à chaque tour de jeu pour la bordure
	
	while(res<(Z->dim)*(Z->dim)){
		cpt++;
		cl=rand()%(Z->nbcl);
		//on colore les case de la Zsg de couleur cl
		l=Z->Lzsg;
		while(l){
			M[l->i][l->j]=cl;
			l=l->suiv;
		}
		//on utilise agrandit_zone pour chaque case de B[cl]
		l=(Z->B)[cl];
		while(l){	
			lp=l->suiv;			
			res+=agrandit_Zsg(M,Z,cl,l->i,l->j);
			//on libere les cases de B[cl]	
			//free(l);
			l=lp;
		}
				
		
	}
	return cpt;
}
