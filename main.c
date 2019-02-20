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
tronconne(Arbre arbre, int score, int table_des_scores[])
{
  if (arbre -> descendants)
  {
    ListeArbres lst_fils;
    
    Arbre meilleur_fils = arbre->descendants->arbre;

    for (lst_fils = arbre->descendants;
	 lst_fils != NULL;
	 lst_fils = lst_fils->suivant)
    { 
      int score_fils = tronconne(lst_fils->arbre, score, table_des_scores);
      if (score_fils > score)
      {
	meilleur_fils = lst_fils;
        score = score_fils;
      }
      else
      {
	lst_fils = supprime_premier_fils(lst_fils);
      }
     
    }
    return score;
    
  }
  else
  {
    int score_noir = 0;
    int score_blanc = 0;
    scores(*(arbre->plateau), &score_blanc, &score_noir, table_des_scores);
    return score_noir-score_blanc;
  }
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
		 {VIDE, VIDE,  VIDE, VIDE},
		 {VIDE,  VIDE,  VIDE, VIDE},
		 {VIDE,  VIDE,  VIDE, VIDE}
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
  printf("avant: %d\n", gerard);
  ajouter_fils(gerard,
	       &tab,
	       score_noir,
	       score_blanc,
	       NOIR
	       );
  ajouter_fils(gerard,
	       &tab,
	       score_noir,
	       score_blanc,
	       NOIR
	       );
  ajouter_fils(gerard,
	       &tab,
	       score_noir,
	       score_blanc,
	       NOIR
	       );
    ajouter_fils(gerard->descendants->arbre,
	       &tab,
	       score_noir,
	       score_blanc,
	       NOIR
	       );

  printf("après: %d\n", gerard);
  printf("AFFICHAGE DE THIERRY L'ARBRE:\n\n");

  afficher_arbre(gerard);


  
  for (int i=0, j = 0; j < N; iterator(&i, &j))
  {
    printf("%d %d\n", i, j);
  }

  printf("%d %d \n", sizeof(Tableau), sizeof(Joueur));

  affiche_tableau(clone_tableau(tab));

  Arbre arborescence = construit_arborescence(tab, NOIR, table_des_scores, 5);
  //afficher_arbre(arborescence);

  int score = 0;
  printf("\n\n\n%d\n", tronconne(arborescence, 0, table_des_scores));
  afficher_arbre(arborescence);

  while (1);
  
  return 0;
  
}
