typedef struct alignement
{
  Joueur couleur;
     int nombre;
} Alignement;


Alignement
nouvel_alignement(Joueur couleur,
		  int nombre);

void
print_Alignement(Alignement align);
