#ifndef ACCEUIL_H_INCLUDED
#define ACCEUIL_H_INCLUDED

#include<gtk/gtk.h>

GtkBuilder *builder;
GtkWidget *start_window;
GtkWidget *btn_livre;
GtkWidget *btn_emprunt;
GtkWidget *btn_adherant;
GtkWidget *btn_quit;


void acceuil_init();
void hide_acceuil();
void show_acceuil();

#endif // ACCEUIL_H_INCLUDED
