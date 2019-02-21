#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "joueur.h"
#include "tableau.h"

#include "arbre.h"




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
  Arbre arbre = malloc(sizeof(NoeudArbre));
  arbre->descendants = nouvelle_liste_arbres_vide();
  arbre->plateau = NULL;
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
  pere->descendants = ajouter_element_liste_arbres(pere->descendants, arbre_fils);
}

void
ajouter_arbre_fils(Arbre pere,
		   Arbre fils)
{
  pere -> descendants =
    ajouter_element_liste_arbres(pere->descendants,
				 fils);
}


void
afficher_liste_arbres(ListeArbres lst)
{
  if (lst != NULL)
  {
    afficher_arbre(lst->arbre);
    afficher_liste_arbres(lst->suivant);
  }
}

void
afficher_arbre(Arbre thierry)
{
  printf("{");
  if (thierry->plateau != NULL)
  {
    printf("\n Noir: %d   Blanc: %d", thierry->score_noir, thierry->score_blanc);
    printf("\nplateau:\n");
    affiche_tableau(*(thierry->plateau));
    printf("\n tour: ");
    print_joueur(thierry->tour);
  }
  else
  {
    printf("vide");
  }
  printf("\n descendants: (");
  afficher_liste_arbres(thierry->descendants);
  printf(") }\n");
}


ListeArbres
supprime_premier_fils(ListeArbres fils)
{
  if (fils)
  {
    ListeArbres suivant = fils->suivant;
    free(fils->arbre);
    return suivant;
  }
}

int
supprime_tete(ListeArbres *lst)
{
  if (*lst)
  {
    supprime_arbre(&(**lst).arbre);
    ListeArbres suivant = (**lst).suivant;
    free(*lst);
    *lst = suivant;
    return 1;
  }
  else
    return 0;
}

void
supprime_arbre(Arbre *robert)
{
  while(supprime_tete(&((*robert)->descendants)));
  free((*robert)->plateau);
  free((*robert));
}
