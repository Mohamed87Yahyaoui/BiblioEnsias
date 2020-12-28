typedef struct _adherant{
    int num_adh;
    char nom_adh[100];
    char prenom_adh[100];
    char email_adh[100];
    int nbre_emprunts_adh : 2; // bit field
}adherant;
