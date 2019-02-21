#include <stdio.h>
typedef enum joueur
  {NOIR, BLANC, VIDE}
  Joueur;

void
print_joueur(Joueur couleur)
{
  if (couleur == NOIR)
    printf("NOIR ");
  else if (couleur == BLANC)
    printf("BLANC");
  else if (couleur == VIDE)
    printf("VIDE ");
  else
    printf("ERRR ");

}
