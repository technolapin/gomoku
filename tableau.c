#include <stdio.h>
#include "constantes.h"

#include "joueur.h"

#include "tableau.h"


void
affiche_tableau(Tableau tab)
{
  for(int i=0; i<N; i++)
  {
    for(int j=0; j<N; j++)
    {
      print_joueur(tab[i][j]);
      printf(" ");
    }
    printf("\n");
  }
}
