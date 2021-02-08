#ifndef EMPRUNT_H_INCLUDED
#define EMPRUNT_H_INCLUDED
#include<gtk/gtk.h>

void emprunter_fonction(GtkWidget * , gpointer );
void emprunter_window(GtkWidget * , gpointer );

void rendre_fonction(GtkWidget * , gpointer );
void rendre_window(GtkWidget * , gpointer );

void emprunt_window(GtkWidget * , gpointer );
void close_empr_return_to_menu();
void show_acceuil();

void print_books_emprunte(GtkWidget * , gpointer );
void rech_adh_liv(GtkWidget * , gpointer);

#endif
