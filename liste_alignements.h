typedef struct _noeud_liste_align
{
  Alignement valeur;
  struct _noeud_liste_align* suivant;
} NoeudListeAlignements, *ListeAlignements;

Alignement
premier_element(ListeAlignements list);

ListeAlignements
nouvelle_liste_vide(void);

ListeAlignements
nouvelle_liste(Alignement valeur);

ListeAlignements
ajouter_element_liste(ListeAlignements liste,
		      Alignement       element);
void
print_ListeAlignements(ListeAlignements liste);
