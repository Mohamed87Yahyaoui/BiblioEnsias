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

//static int num_books=0;


GtkBuilder *b_builder;

//ajout d un livre window
GtkWidget *i_window;
//gestion des livres windw
GtkWidget *b_window;
// print book window
GtkWidget *p_window;
// widget permettant de cree un tableau
GtkWidget *treeview;
// widget pour ajouter l'option du scroll
GtkWidget *scrolled_win;
// un store pour stocker les differants livres
GtkListStore *store;
// iterateur pour itterer dans l'ensembles des livres
GtkTreeIter iter;
// permet de creer des colonnes pour le tableau , s'utilise avec treeview
GtkCellRenderer *renderer;
// pour voir la colonne
GtkTreeViewColumn *column;

// entre d'ajout d'un livre
GtkWidget *E1;
GtkWidget *E2;
GtkWidget *E3;
GtkWidget *E4;
GtkWidget *E5;
GtkWidget *E6;

GtkWidget *E7;
GtkWidget *E8;
GtkWidget *E9;
GtkWidget *E10;
GtkWidget *E11;
GtkWidget *E12;


//boutton
GtkWidget *btn_add_book;
GtkWidget *btn_edit_book;
GtkWidget *btn_delete_book;
GtkWidget *btn_sort;
GtkWidget *btn_search_book;
GtkWidget *btn_show_books;
GtkWidget *btn_return_to_menu;
GtkWidget *btn_return_to_book_window;

GtkWidget *save_btn;

void book_window (GtkWidget *,gpointer);
void save_book(GtkButton *,gpointer);
void info_window (GtkWidget *,gpointer);
void hide_book_window();
void show_book_window();
void close_book_return_to_menu();


void setup_tree_view (GtkWidget *);
void print_books(GtkWidget *, gpointer);

int livre_exist(int );
void print_all();
void print_livre();

#endif // BOOK_H_INCLUDED
