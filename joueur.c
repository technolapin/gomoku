#include <stdio.h>
#include "joueur.h"

void
print_joueur(Joueur couleur)
{
  if (couleur == NOIR)
    printf("x ");
  else if (couleur == BLANC)
    printf("o ");
  else if (couleur == VIDE)
    printf("· ");
  else
    printf("E ");

}
