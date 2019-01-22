#include <stdio.h>
#include <stdlib.h>

#define N 4
#define BUT 3

#include "joueur.h"
#include "tableau.h"
#include "alignement.h"
#include "liste_alignements.h"





Joueur
a_gagne(Joueur* actuel,
	int*    compteur,
	Joueur  case_regardee)
{
  if (case_regardee == *actuel)
    {
      (*compteur)++;
      if (*compteur == BUT &&
	  *actuel != VIDE)
	{
	  return *actuel;
	}
    }
  else
    {
      *compteur = 1;
      *actuel = case_regardee;
    }
  return VIDE;
}

Joueur
gagne(Tableau tab)
{
  //horizontale
  for (int i = 0; i<N; i++)
    {
      Joueur actuel = VIDE;
      int compteur = 1;
      for (int j = 0; j<N; j++)
	{
	  Joueur gagnant = a_gagne(&actuel, &compteur, tab[i][j]);
	  if (gagnant != VIDE)
	    return gagnant;
	}
      
    }

  //verticale
    for (int j = 0; j<N; j++)
    {
      Joueur actuel = VIDE;
      int compteur = 1;
      for (int i = 0; i<N; i++)
	{
	  Joueur gagnant = a_gagne(&actuel, &compteur, tab[i][j]);
	  if (gagnant != VIDE)
	    return gagnant;
	}
    }
    //diagonale 1
    for (int i = 0; i < N-BUT+1; i++)
      {
	Joueur actuel = VIDE;
	int compteur = 1;

	int j = 0;
	for (int k = 0; k < N-i; k++)
	  {
	    Joueur gagnant = a_gagne(&actuel, &compteur, tab[i+k][j+k]);
	    if (gagnant != VIDE)
	      return gagnant;
	    
	  }
      }

    for (int i = 1; i < N-BUT+1; i++)
      {
	Joueur actuel = VIDE;
	int compteur = 1;

	int j = 0;
	for (int k = 0; k < N-i; k++)
	  {
	    Joueur gagnant = a_gagne(&actuel, &compteur, tab[j+k][i+k]);
	    if (gagnant != VIDE)
	      return gagnant;
	    
	  }
      }


    //diagonale 2

    for (int i = BUT-1; i < N; i++)
      {
	Joueur actuel = VIDE;
	int compteur = 1;

	int j = 0;
	for (int k = 0; k <= i; k++)
	  {
	    Joueur gagnant = a_gagne(&actuel, &compteur, tab[i-k][j+k]);
	    if (gagnant != VIDE)
	      return gagnant;
	    
	  }
      }

    for (int i = 1; i < N-BUT+1; i++)
      {
	Joueur actuel = VIDE;
	int compteur = 1;

	int j = N-1;
	for (int k = 0; k <= N-i+1; k++)
	  {
	    Joueur gagnant = a_gagne(&actuel, &compteur, tab[j-k][i+k]);
	    if (gagnant != VIDE)
	      return gagnant;
	    
	  }
      }

    
  return VIDE;
}


int
main(void)
{

  Tableau tab = {
		 {VIDE, VIDE, BLANC, NOIR},
		 {VIDE, BLANC, VIDE, NOIR},
		 {BLANC, VIDE, NOIR, VIDE},
		 {VIDE, NOIR, VIDE, VIDE}
  };
  Joueur gagnant = gagne(tab);

  printf("%d %d %d\n", gagnant==NOIR, gagnant==BLANC, gagnant==VIDE);

  printf("%d, %d, %d\n", NOIR, BLANC, VIDE);

  printf("LA RAISON N'A PLUS COURS CI-APRÈS\n");

  Alignement align = nouvel_alignement(NOIR, 23);
  Alignement align1 = nouvel_alignement(NOIR, 3);
  Alignement align2 = nouvel_alignement(NOIR, 2);
  Alignement align3 = nouvel_alignement(NOIR, 0);
  ListeAlignements liste =
    ajouter_element_liste
     (ajouter_element_liste
      (ajouter_element_liste
       (nouvelle_liste(align), align1),
       align2),
      align3);

  print_Alignement(align);
  printf("\n\n");
  print_ListeAlignements(liste);

  return 0;
}
