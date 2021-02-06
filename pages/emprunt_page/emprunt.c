#include<gtk/gtk.h>
#include<stdio.h>
#include "emprunt.h"
#include "adherent.h"
#include "book.h"

GtkBuilder *e_builder;
GtkBuilder *r_builder;

GtkWidget *e_window;

GtkWidget *btn_emprunter;
GtkWidget *btn_livres_empruntes;
GtkWidget *btn_rendre_livre;
GtkWidget *btn_emprunteur;
GtkWidget *btn_return_to_menuempr;

GtkWidget *empr_window;
GtkWidget *E_num;
GtkWidget *E_adh;
GtkWidget *btn_empr;

void emprunt_window(GtkWidget *widget , gpointer data){
    e_builder=gtk_builder_new_from_file("glade/emprunt.glade");

    e_window=GTK_WIDGET(gtk_builder_get_object (e_builder,"emprunt_window"));

    btn_emprunter=GTK_WIDGET(gtk_builder_get_object (e_builder,"btn_emprunter"));
    btn_livres_empruntes=GTK_WIDGET(gtk_builder_get_object (e_builder,"btn_livres_empruntes"));
    btn_rendre_livre=GTK_WIDGET(gtk_builder_get_object (e_builder,"btn_rendre_livre"));
    btn_emprunteur=GTK_WIDGET(gtk_builder_get_object (e_builder,"btn_emprunteur"));
    btn_return_to_menuempr=GTK_WIDGET(gtk_builder_get_object (e_builder,"btn_return_to_menu"));

    g_signal_connect(btn_emprunter,"clicked",G_CALLBACK(emprunter_window),NULL);
    g_signal_connect(btn_return_to_menuempr,"clicked",G_CALLBACK(close_empr_return_to_menu),NULL);
    //g_signal_connect(btn_livres_empruntes,"clicked",G_CALLBACK(),NULL);
   //g_signal_connect(btn_rendre_livre,"clicked",G_CALLBACK(),NULL);
   //g_signal_connect(btn_emprunteur,"clicked",G_CALLBACK(),NULL);

    gtk_widget_show_all(e_window);
}
void emprunter_window(GtkWidget *widget , gpointer data){
    r_builder=gtk_builder_new_from_file("glade/emprunt.glade");
    empr_window=GTK_WIDGET(gtk_builder_get_object(r_builder,"emprunter_window"));
    E_num=GTK_WIDGET(gtk_builder_get_object(r_builder,"E_num"));
    E_adh=GTK_WIDGET(gtk_builder_get_object(r_builder,"E_adh"));
    btn_empr=GTK_WIDGET(gtk_builder_get_object(r_builder,"btn_empr"));

    g_signal_connect(btn_empr,"clicked",G_CALLBACK(emprunter_fonction),NULL);
    gtk_widget_show_all(empr_window);
}
void emprunter_fonction(GtkWidget *widget , gpointer data){
    Livre temp_book;
    adherent temp_adh;
    FILE *fp_book;
    FILE *fp_adh;
    int pos=0;
    int num1=atoi(gtk_entry_get_text(GTK_ENTRY(E_num))); //numero du livre
    int num2=atoi(gtk_entry_get_text(GTK_ENTRY(E_adh))); // numero d'adherent
    //CHECK num_adh is VALID AND CHECK IF nbre_emprunts_adh<4
    int FOUND_ADH=0;
    int FOUND_BOOK=0; 
    int CAN_BORROW=1;
    fp_adh=fopen("adherent.dat","r+b");
    while (fread(&temp_adh,sizeof(adherent),1,fp_adh)==1){
        pos++;
        if(temp_adh.num_adh==num2){
            FOUND_ADH=1;
            if(temp_adh.nbre_emprunts_adh>3) CAN_BORROW=0;
        }
    }
    if(!FOUND_ADH) dialog_window("NO SUCH ADHERENT !\n");
    if(FOUND_ADH && !CAN_BORROW) dialog_window("Found adherent but cannot borrow (max is 3) !\n");
    if(FOUND_ADH && CAN_BORROW){
        //THEN MODIFY
        fp_book=fopen("livre.dat","r+b");
        while (fread(&temp_book,sizeof(Livre),1,fp_book)==1){
            if(temp_book.num_liv==num1){
                FOUND_BOOK=1;
                temp_book.emprunteur_liv=num2;
                unsigned long long int dep=-1*sizeof(Livre);
                fseek(fp_book,dep,SEEK_CUR);
                fwrite(&temp_book,sizeof(Livre),1,fp_book) ;
            }
        }
        fclose(fp_book);
        // INCREMENT NUMBER OF BOOKS BORROWED BY adherent 
        if(FOUND_BOOK) {
            unsigned long long int dep;
            dep=sizeof(adherent)*(pos-1);
            fseek(fp_adh,dep,SEEK_SET);
            fread(&temp_adh,sizeof(adherent),1,fp_adh);
            temp_adh.nbre_emprunts_adh++;
            dep=-1*sizeof(adherent);
            fseek(fp_adh,dep,SEEK_CUR);
            if(fwrite(&temp_adh,sizeof(adherent),1,fp_adh)==1) dialog_window("BORROWED SUCCEFULLY\n");
        }
        else dialog_window("NO SUCH BOOK\n");
    }
    fclose(fp_adh);
    gtk_widget_destroy(empr_window);
}

void close_empr_return_to_menu(){
    gtk_window_close(GTK_WINDOW(e_window));
    show_acceuil();
}
