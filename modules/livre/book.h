#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED
#include<gtk/gtk.h>


// declaration de structure
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


enum{
NUM,
TITRE,
CATEG,
NOM,
PRENOM,
EMPR,
COLUMNS
};



void book_window (GtkWidget *,gpointer);
void save_book(GtkButton *,gpointer);
void info_window (GtkWidget *,gpointer);
void hide_book_window();
void show_book_window();
void close_book_return_to_menu();


void setup_tree_view (GtkWidget *);
void print_books(GtkWidget *, gpointer);

int livre_exist(int);
void print_all();
void print_livre();

void update_book(GtkButton *,gpointer);
void delete_book(GtkWidget *, gpointer);
void supprimer_livre(GtkButton *, gpointer);


void dialog_window(char *);
void print_book_window(Livre);
void rechercher_livre(GtkWidget *, gpointer);

void show_acceuil();
void hide_sh();

#endif // BOOK_H_INCLUDED
