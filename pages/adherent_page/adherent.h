#ifndef ADHERENT_H_INCLUDED
#define ADHERENT_H_INCLUDED
#include<gtk/gtk.h>

typedef struct _adherent{
    int num_adh;
    char nom_adh[100];
    char prenom_adh[100];
    char email_adh[100];
    char adress_adh[100];
    int nbre_emprunts_adh; // bit field
}adherent;

enum{
NUMadh,
NOMadh,
PRENOMadh,
EMAIL,
ADRESSE,
NB_EMPR,
COLUMNSadh
};



void adh_window (GtkWidget *,gpointer);
void save_adh(GtkButton *,gpointer);
void save_modif_adh(GtkButton *,gpointer);
void adh_info_window (GtkWidget *,gpointer);
void adh_supp_window (GtkWidget *,gpointer);
void adh_rech_window (GtkWidget *,gpointer);
void adh_modif_window(GtkWidget *,gpointer);
void adh_conf_modif_window(GtkWidget *, gpointer);
void delete_adh(GtkButton *,gpointer);
void modif_adh(GtkButton *,gpointer);
void rech_adh(GtkWidget *, gpointer);
void hide_adh_window();
void show_adh_window();
void close_adh_return_to_menu();
void dialog_window(char *);


void setup_tree_view_adh (GtkWidget *);
void print_adhs(GtkWidget *, gpointer);

int adh_exist(adherent);
void show_acceuil();

#endif
