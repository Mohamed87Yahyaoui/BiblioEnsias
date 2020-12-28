typedef struct _auteur{
    char nom_aut[100];
    char prenom_aut[100];
}auteur;

typedef struct _livre{
    int num_liv;
    char titre_liv[100];
    char categ_liv[21];
    auteur auteur_liv;
    int emprunteur_liv;
}livre;
