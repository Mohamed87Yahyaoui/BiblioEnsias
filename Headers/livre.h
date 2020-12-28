typedef struct _auteur{
    char nom_aut[100];
    char prenom_aut[100];
}Auteur;

typedef struct _livre{
    int num_liv;
    char titre_liv[100];
    char categ_liv[21];
    Auteur auteur_liv;
    int emprunteur_liv;
}Livre;


Livre scan_livre();
void ajout_livre();
void print_all();