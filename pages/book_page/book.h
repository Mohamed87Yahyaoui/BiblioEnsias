#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED
#include<gtk/gtk.h>

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


typedef struct multp{
GtkWidget *one,*two,*three,*four,*five,*six;
}multp;

GtkBuilder *b_builder;

GtkWidget *i_window;
GtkWidget *b_window;

GtkWidget *E1;
GtkWidget *E2;
GtkWidget *E3;
GtkWidget *E4;
GtkWidget *E5;
GtkWidget *E6;
multp *T;

GtkWidget *btn_add_book;
GtkWidget *btn_edit_book;
GtkWidget *btn_delete_book;
GtkWidget *btn_sort;
GtkWidget *btn_search_book;
GtkWidget *btn_print_books;
GtkWidget *btn_return_to_menu;

GtkWidget *save_btn;

void book_window (GtkWidget *,gpointer);
void save_book(GtkButton *,gpointer);
void info_window (GtkWidget *,gpointer);
void hide_book_window();
void show_book_window();
void close_book_return_to_menu();

int livre_exist(Livre);
void print_all();
void print_livre();

#endif // BOOK_H_INCLUDED
