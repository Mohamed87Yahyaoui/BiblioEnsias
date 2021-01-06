#ifndef EMPRUNT_H_INCLUDED
#define EMPRUNT_H_INCLUDED
#include<gtk/gtk.h>

GtkBuilder *e_builder;

GtkWidget *e_window;

GtkWidget *btn_emprunter;
GtkWidget *btn_livres_empruntes;
GtkWidget *btn_rendre_livre;
GtkWidget *btn_emprunteur;
GtkWidget *btn_return_to_menu;

void emprunt_window(GtkWidget * , gpointer );
void close_empr_return_to_menu();

#endif