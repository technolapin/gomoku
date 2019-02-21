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
	  *score_blanc += table_des_scores[aligns->valeur.nombre-1];
	}
      else if (aligns->valeur.couleur == NOIR)
	{
	  *score_noir += table_des_scores[aligns->valeur.nombre-1];
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

void
iterator(int *i, int *j)
{
  (*i)++;
  if (*i == N)
  {
    *i = 0;
    (*j)++;
  }
}

Arbre
construit_arborescence(Tableau tab,
		       Joueur joueur_actuel,
		       int table_des_scores[],
		       int profondeur)
{
  Arbre noeud = nouvel_arbre_vide();
  noeud->plateau = clone_tableau(tab);
  noeud->tour = joueur_actuel;
  noeud->score_blanc = 0;
  noeud->score_noir = 0;
  scores(tab, &noeud->score_blanc, &noeud->score_noir, table_des_scores);
  if (profondeur > 0)
  for (int i = 0, j = 0; j < N; iterator(&i, &j))
    {
      if (tab[i][j] == VIDE)
      {
	Tableau *p_clone = clone_tableau(tab);
	(*p_clone)[i][j] = joueur_actuel;

	Arbre fils = malloc(sizeof(NoeudArbre));
	fils = construit_arborescence(*p_clone,
				      1-joueur_actuel,
				      table_des_scores,
				      profondeur-1);

	ajouter_arbre_fils(noeud, fils);
      }
    }
  return noeud;
}
 
int
tronconne(Arbre arbre,
	  int score,
	  int table_des_scores[])
{
  if (arbre -> descendants)
  {
    ListeArbres lst_fils;
    int score_fils;
    for (lst_fils = arbre->descendants;
	 lst_fils;
	 lst_fils = lst_fils->suivant)
    {
      score_fils =
	tronconne(lst_fils->arbre,
		  score,
		  table_des_scores);
      
      if (arbre->tour == NOIR)
      {
	if (score_fils > score)
	  score = score_fils;
      }
      else
      {
	if (score_fils < score)
	  score = score_fils;
      }
    }
    return score;
  }
  else
  {
    return arbre->score_noir - arbre->score_blanc;
  }
}

void
entre_coordonnees(int *i, int *j, Tableau tab)
{
  printf("x: ");
  scanf("%d", i);
  printf("y: ");
  scanf("%d", j);
  if (*i < 0 || *i > N || *j < 0 || *j > N || tab[*i][*j]!=VIDE)
  {
    printf("Coordonnées invalides\n");
    entre_coordonnees(i, j, tab);
  }
}



Tableau*
meilleur_coup(Tableau tab, int profondeur, int table_des_scores[])
{
  Arbre arborescence = construit_arborescence(tab, NOIR, table_des_scores, profondeur);


  ListeArbres lst = arborescence->descendants;
  int score;
  int score_max
    = tronconne(lst->arbre,
		0,
		table_des_scores);
  Tableau *plateau_max = lst->arbre->plateau;
  for (;
       lst;
       lst = lst->suivant)
  {
    score = tronconne(lst->arbre,
		      0,
		      table_des_scores);
    if (score_max < score)
    {
      score_max = score;
      plateau_max = (lst->arbre->plateau);
    }
  }
  Tableau *meilleur = clone_tableau(*plateau_max);
  supprime_arbre(&arborescence);
  return meilleur;
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
		 {VIDE,  VIDE,  VIDE,  VIDE},
		 {VIDE,  VIDE,  VIDE,  VIDE},
		 {VIDE,  VIDE,  VIDE,  VIDE},
		 {VIDE,  VIDE,  VIDE,  VIDE}
  };
  Tableau *plateau = &tab;
  int i=-1;
  int j=-1;
  Joueur gagnant = VIDE;
  while (1)
  {
    printf("\nTOUR DES BLANCS \n");
    entre_coordonnees(&i,&j, *plateau);
    (*plateau)[i][j] = BLANC;
    affiche_tableau(*plateau);

    gagnant = gagne(*plateau);
    if (gagnant == BLANC)
    {
      printf("Vous avez gagné!\n");
      return 0;
    }
    
    printf("\nTOUR DES NOIRS \n");
    plateau = meilleur_coup(*plateau, 6, table_des_scores);
    affiche_tableau(*plateau);
    gagnant = gagne(*plateau);
    if (gagnant == NOIR)
    {
      printf("Vous avez perdu!\n");
      return 0;
    }
  }
  print_joueur(gagnant);
  return 0;
  
}

