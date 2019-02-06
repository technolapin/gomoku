#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "constantes.h"
#include "joueur.h"
#include "tableau.h"
#include "alignement.h"
#include "liste_alignements.h"
#include "arbre.h"



////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////



void
trouve_alignements_aux
( Joueur* actuel,
  int*    compteur,
  Joueur  case_regardee,
  ListeAlignements* liste
  )
{
  if (case_regardee == *actuel)
    {
      (*compteur)++;
    }
  else
    {
      if (*compteur > 1 && *actuel != VIDE)
	{
	  *liste = ajouter_element_liste
	    ( *liste,
	      nouvel_alignement(*actuel, *compteur)
	      );
	}
      *actuel = case_regardee;
      *compteur = 1;
    }
}


ListeAlignements
trouve_alignements(Tableau tab)
{

  ListeAlignements liste = nouvelle_liste_vide();
  
  //horizontale
  for (int i = 0; i<N; i++)
    {
      Joueur actuel = VIDE;
      int compteur = 1;
      for (int j = 0; j<N; j++)
	{
	  trouve_alignements_aux(&actuel, &compteur, tab[i][j], &liste);
	}
    }

  //verticale
    for (int j = 0; j<N; j++)
    {
      Joueur actuel = VIDE;
      int compteur = 1;
      for (int i = 0; i<N; i++)
	{
	  trouve_alignements_aux(&actuel, &compteur, tab[i][j], &liste);
	}
    }
    //diagonale 1
    for (int i = 0; i < N-BUT+1; i++)
      {
	Joueur actuel = VIDE;
	int compteur = 1;

	int j = 0;
	for (int k = 0; k < i; k++)
	  {
	    trouve_alignements_aux(&actuel, &compteur, tab[i][j], &liste);
	  }
      }

    for (int i = 1; i < N-BUT+1; i++)
      {
	Joueur actuel = VIDE;
	int compteur = 1;

	int j = 0;
	for (int k = 0; k < N-i; k++)
	  {
	    trouve_alignements_aux(&actuel, &compteur, tab[i][j], &liste);
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
	    trouve_alignements_aux(&actuel, &compteur, tab[i-k][j+k], &liste);
	  }
      }

    for (int i = 1; i < N-BUT+1; i++)
      {
	Joueur actuel = VIDE;
	int compteur = 1;

	int j = N-1;
	for (int k = 0; k <= N-i+1; k++)
	  {
	    trouve_alignements_aux(&actuel, &compteur, tab[i+k][j-k], &liste);
	  }
      }

    
  return liste;
}


void
scores_aux(ListeAlignements aligns, int* score_blanc, int* score_noir, int table_des_scores[])
{
  if (aligns != NULL)
    {
      if (aligns->valeur.couleur == BLANC)
	{
	  *score_blanc = table_des_scores[aligns->valeur.nombre-1];
	}
      else if (aligns->valeur.couleur == NOIR)
	{
	  *score_noir = table_des_scores[aligns->valeur.nombre-1];
	}
      else
	{
	  printf("ATTENTION: L'alignement est VIDE");
	}
      scores_aux(aligns->suivant, score_blanc, score_noir, table_des_scores);
    }
}


void
scores(Tableau tab, int* score_blanc, int* score_noir, int table_des_scores[])
{
  scores_aux(trouve_alignements(tab), score_blanc, score_noir, table_des_scores);
}



int
main(void)
{
  int table_des_scores[BUT];
  table_des_scores[0] = 1;
  for (int i = 1; i<BUT; i++)
  {
    table_des_scores[i] = table_des_scores[i-1]*2;
  }
  
  Tableau tab = {
		 {VIDE,  VIDE, VIDE, VIDE},
		 {VIDE, BLANC,  VIDE, NOIR},
		 {BLANC,  VIDE,  NOIR, BLANC},
		 {VIDE,  NOIR,  BLANC, VIDE}
  };
  Joueur gagnant = gagne(tab);

  printf("%d %d %d\n", gagnant==NOIR, gagnant==BLANC, gagnant==VIDE);

  printf("%d, %d, %d\n", NOIR, BLANC, VIDE);

  printf("LA RAISON N'A PLUS COURS CI-APRÈS\n");

  Alignement align  = nouvel_alignement(NOIR, 23);
  Alignement align1 = nouvel_alignement(NOIR, 3);
  Alignement align2 = nouvel_alignement(NOIR, 2);
  Alignement align3 = nouvel_alignement(NOIR, 0);
  
  ListeAlignements liste =
    ajouter_element_liste
     (ajouter_element_liste
      (ajouter_element_liste
       (ajouter_element_liste
	(nouvelle_liste_vide(),
	 align ),
	align1),
       align2),
      align3);

  print_Alignement(align);
  printf("\n\n");
  print_ListeAlignements(liste);
  printf("\n\n");
  printf("FIN DU ZBEUL");
  printf("\n\n");
  print_ListeAlignements(trouve_alignements(tab));
  printf("\n");

  int score_noir = 0;
  int score_blanc = 0;
  scores(tab, &score_blanc, &score_noir, table_des_scores);
  printf("NOIR: %d\nBLANC: %d\n", score_noir, score_blanc);

  affiche_tableau(tab);

  
  Arbre gerard = nouvel_arbre_vide();
  ajouter_fils(gerard,
	       &tab,
	       score_noir,
	       score_blanc,
	       NOIR
	       );
  return 0;
  
}
