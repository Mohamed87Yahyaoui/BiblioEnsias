#include "acceuil.h"
#include "emprunt.h"
#include<gtk/gtk.h>

void emprunt_window(GtkWidget *widget , gpointer data){
    e_builder=gtk_builder_new_from_file("emprunt.glade");

    e_window=GTK_WIDGET(gtk_builder_get_object (e_builder,"emprunt_window"));

    btn_emprunter=GTK_WIDGET(gtk_builder_get_object (e_builder,"btn_emprunter"));
    btn_livres_empruntes=GTK_WIDGET(gtk_builder_get_object (e_builder,"btn_livres_empruntes"));
    btn_rendre_livre=GTK_WIDGET(gtk_builder_get_object (e_builder,"btn_rendre_livre"));
    btn_emprunteur=GTK_WIDGET(gtk_builder_get_object (e_builder,"btn_emprunteur"));
    btn_return_to_menu=GTK_WIDGET(gtk_builder_get_object (e_builder,"btn_return_to_menu"));
/*
    g_signal_connect(btn_emprunter,"clicked",G_CALLBACK(),NULL);
    g_signal_connect(btn_return_to_menu,"clicked",G_CALLBACK(close_empr_return_to_menu),NULL);
    g_signal_connect(btn_livres_empruntes,"clicked",G_CALLBACK(),NULL);
    g_signal_connect(btn_rendre_livre,"clicked",G_CALLBACK(),NULL);
    g_signal_connect(btn_emprunteur,"clicked",G_CALLBACK(),NULL);
*/
    gtk_widget_show_all(e_window);
}