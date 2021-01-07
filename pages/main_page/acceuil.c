#include<gtk/gtk.h>
#include "acceuil.h"
#include "book.h"
#include "emprunt.h"
#include "adherant.h"

GtkBuilder *builder;

GtkWidget *start_window;
GtkWidget *btn_livre;
GtkWidget *btn_emprunt;
GtkWidget *btn_adherant;
GtkWidget *btn_quit;

GtkWidget *btn_quit;


void acceuil_init(){
    builder=gtk_builder_new_from_file("../acceuil.glade");
    start_window=GTK_WIDGET(gtk_builder_get_object (builder,"start_window"));
    btn_livre=GTK_WIDGET(gtk_builder_get_object (builder,"btn_livre"));
    btn_emprunt=GTK_WIDGET(gtk_builder_get_object (builder,"btn_emprunt"));
    btn_adherant=GTK_WIDGET(gtk_builder_get_object (builder,"btn_adherant"));
    btn_quit=GTK_WIDGET(gtk_builder_get_object (builder,"btn_quit"));

    g_signal_connect(start_window,"destroy",G_CALLBACK(gtk_main_quit),NULL);

    g_signal_connect(btn_emprunt,"clicked",G_CALLBACK(emprunt_window),NULL);
    g_signal_connect (btn_emprunt,"clicked", G_CALLBACK (hide_acceuil), NULL);

    g_signal_connect (btn_livre, "clicked", G_CALLBACK (book_window), NULL);
    g_signal_connect (btn_livre, "clicked", G_CALLBACK (hide_acceuil), NULL);

    g_signal_connect (btn_adherant, "clicked", G_CALLBACK (adh_window), NULL);
    g_signal_connect (btn_livre, "clicked", G_CALLBACK (hide_acceuil), NULL);

    g_signal_connect (btn_quit, "clicked", G_CALLBACK (gtk_main_quit), NULL);

    gtk_widget_show_all(start_window);
}

void hide_acceuil(){
    gtk_widget_hide(start_window);
}

void show_acceuil(){
    gtk_widget_show(start_window);
}

void dialog_window(char *message ){
    GtkWidget *dialog;
    /* Creation de la boite de message */
    /* Type : Information >
    GTK_MESSAGE_INFO */
    /* Bouton : 1 OK >
    GTK_BUTTONS_OK */
    dialog = gtk_message_dialog_new (NULL,
    GTK_DIALOG_MODAL,
    GTK_MESSAGE_INFO,
    GTK_BUTTONS_OK,
    "%s",message);
    /* Affichage de la boite de message */
    gtk_dialog_run(GTK_DIALOG(dialog));
    /* Destruction de la boite de message */
    gtk_widget_destroy(dialog);
}
