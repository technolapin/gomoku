#include <stdio.h>
#include "joueur.h"
#include "alignement.h"


Alignement
nouvel_alignement(Joueur couleur,
		  int nombre)
{
  Alignement align;
  align.couleur = couleur;
  align.nombre  = nombre;
  return align;

}


void
print_Alignement(Alignement align)
{
  printf("[");
  print_joueur(align.couleur);
  printf(":%d]", align.nombre);
}
