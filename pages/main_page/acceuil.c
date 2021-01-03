#include "acceuil.h"
#include "book.h"

void acceuil_init(){
    builder=gtk_builder_new_from_file("acceuil.glade");
    start_window=GTK_WIDGET(gtk_builder_get_object (builder,"start_window"));
    btn_livre=GTK_WIDGET(gtk_builder_get_object (builder,"btn_livre"));
    btn_emprunt=GTK_WIDGET(gtk_builder_get_object (builder,"btn_emprunt"));
    btn_adherant=GTK_WIDGET(gtk_builder_get_object (builder,"btn_adherant"));
    btn_quit=GTK_WIDGET(gtk_builder_get_object (builder,"btn_quit"));

    g_signal_connect(start_window,"destroy",G_CALLBACK(gtk_main_quit),NULL);

    g_signal_connect (btn_livre, "clicked", G_CALLBACK (book_window), NULL);
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
