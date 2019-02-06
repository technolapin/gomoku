#include <stdio.h>
#include <stdlib.h>
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


Tableau*
clone_tableau(Tableau tab)
{
  Tableau *nouveau = malloc(sizeof(Tableau));
  //  Tableau nouveau;
  for(int i=0; i<N; i++)
  {
    //    (*nouveau)[i] = malloc(sizeof(Joueur)*N);
    //Joueur ligne[N];
    for(int j=0; j<N; j++)
    {
      (*nouveau)[i][j] = tab[i][j];
    }
  }
  return nouveau;
}

