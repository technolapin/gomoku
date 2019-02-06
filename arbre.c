#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "joueur.h"
#include "tableau.h"


typedef struct _noeud_arbre
{
  Tableau* plateau;
  int score_noir;
  int score_blanc;
  Joueur tour;
  struct _noeud_liste_arbres
  {
    struct _noeud_arbre* arbre;
    struct _noeud_liste_arbres* suivant;
  }* descendants;
} NoeudArbre, *Arbre;

typedef struct _noeud_liste_arbres NoeudListeArbre, *ListeArbres;


ListeArbres
nouvelle_liste_arbres_vide(void)
{
  return NULL;
}

ListeArbres
ajouter_element_liste_arbres(ListeArbres liste,
			     Arbre arbre)
{
  ListeArbres element = malloc(sizeof(NoeudListeArbre));
  element->arbre = arbre;
  element->suivant = liste;
  return element;
}

Arbre
nouvel_arbre_vide(void)
{
  return NULL;
}

void
ajouter_fils(Arbre pere,
	     Tableau *plateau,
	     int score_noir,
	     int score_blanc,
	     Joueur tour)
{
  Arbre arbre_fils = malloc(sizeof(NoeudArbre));
  arbre_fils -> plateau = plateau;
  arbre_fils -> score_noir = score_noir;
  arbre_fils -> score_blanc = score_blanc;
  arbre_fils -> tour = tour;
//  pere->descendants
}
/*
void
afficher_arbre(Arbre thierry)
{
  
}
*/
