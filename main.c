#include <stdio.h>

#define N 8
#define BUT 5

typedef enum joueur
  {NOIR, BLANC, VIDE}
  Joueur;

typedef Joueur (Tableau)[N][N];


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
gagne(Tableau tab[])
{
  for (int i = 0; i<N; i++)
    {
      Joueur actuel = *tab[i][0];
      int compteur = 1;
      for (int j = 0; j<N; j++)
	{
	  Joueur gagnant = a_gagne(&actuel, &compteur, *tab[i][j]) != VIDE;
	  if (gagnant != VIDE)
	    return gagnant;
	}
      
    }

  return VIDE;
}

int
main(void)
{
  return 0;
}
