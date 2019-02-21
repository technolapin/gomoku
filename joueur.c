#include <stdio.h>
#include "joueur.h"

void
print_joueur(Joueur couleur)
{
  if (couleur == NOIR)
    printf("NOIR");
  else if (couleur == BLANC)
    printf("BLANC");
  else
    printf("VIDE");
}
