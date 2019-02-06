typedef struct _noeud_arbre
{
  Tableau* plateau;
  int score_noir;
  int score_blanc;
  Joueur tour;
  struct _noeud_liste_arbres
  {
    struct _noeud_arbre* arbre;
    struct _noeud_liste_arbres* suivant;
  }* descendants;
} NoeudArbre, *Arbre;
typedef struct _noeud_liste_arbres NoeudListeArbre, *ListeArbres;



Arbre
nouvel_arbre_vide(void);

void
ajouter_fils(Arbre pere,
	     Tableau *plateau,
	     int score_noir,
	     int score_blanc,
	     Joueur tour);

void
ajouter_arbre_fils(Arbre pere,
		   Arbre fils);


void
afficher_liste_arbres(ListeArbres lst);

void
afficher_arbre(Arbre thierry);
