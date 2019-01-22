#include <stdio.h>
#include <stdlib.h>
#include "joueur.h"
#include "alignement.h"

typedef struct _noeud_liste_align
{
  Alignement valeur;
  struct _noeud_liste_align* suivant;
} NoeudListeAlignements, *ListeAlignements;

Alignement
premier_element(ListeAlignements list)
{
  return list->valeur;
}

ListeAlignements
nouvelle_liste(Alignement valeur)
{
  ListeAlignements list = malloc(sizeof(NoeudListeAlignements));
  list->suivant = NULL;
  list->valeur  = valeur;
  return list;
}

ListeAlignements
ajouter_element_liste(ListeAlignements liste,
		      Alignement       element)
{
  ListeAlignements liste2 = nouvelle_liste(element);
  liste2->suivant = liste;
  return liste2;
}



void
print_ListeAlignements(ListeAlignements liste)
{
  if (liste == NULL)
    printf("[]");
  else
    {
      print_Alignement(liste->valeur);
      printf("->");
      print_ListeAlignements(liste->suivant);
    }
}
