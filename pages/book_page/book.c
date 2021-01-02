#include "../main_page/acceuil.h"
#include "book.h"
#include <gtk/gtk.h>

void print_livre(Livre lv){
    g_print("Numero: %d\n",lv.num_liv);
    g_print("Titre: %s\n",lv.titre_liv);
    g_print("Catalogue: %s\n",lv.categ_liv);
    g_print("Nom de l'auteur: %s\n",lv.auteur_liv.nom_aut);
    g_print("Prenom de l'auteur: %s\n",lv.auteur_liv.prenom_aut);
    g_print("Numero d'adherant ayant emprunte le livre: %d\n",lv.emprunteur_liv);
}

void print_all(){
    FILE *pf=fopen("livre.dat","rb");
    if(!pf) {
        pf=fopen("livre.dat","w+b");
        exit(-1);
    }
    Livre temp;
    while (fread(&temp,sizeof(Livre),1,pf)==1){
        printf("--------------\n");
        print_livre(temp);
        printf("--------------\n");
    }
    fclose(pf);
}

void rechercher_livre(char *titre){
    FILE *fp=fopen("livre.dat","rb");
    Livre temp;
    while (fread(&temp,sizeof(Livre),1,fp)==1){
        if(!strcmp(temp.titre_liv,titre)){
            print_livre(temp);
            return ;
        }
    }
    g_print("no such autor\n");
}

int livre_exist(Livre lv){
    Livre temp;
    FILE *pf=fopen("livre.dat","rb");
    if(!pf) exit(-1);
    while (fread(&temp,sizeof(Livre),1,pf)==1){
        if(temp.num_liv==lv.num_liv) return 1;
    }
    fclose(pf);
    return 0;
}

void save_book(GtkButton *button,gpointer data){
    Livre lv;

    GtkWidget *E1=((multp *)data)->one;
    lv.num_liv=atoi(gtk_entry_get_text(GTK_ENTRY(E1)));

    GtkWidget *E2=((multp *)data)->two;
    strcpy(lv.titre_liv,gtk_entry_get_text(GTK_ENTRY(E2)));
    //const char *titrelv=gtk_entry_get_text(GTK_ENTRY(E2));

    GtkWidget *E3=((multp *)data)->three;
    strcpy(lv.categ_liv,gtk_entry_get_text(GTK_ENTRY(E3)));
    //const char *categlv=gtk_entry_get_text(GTK_ENTRY(E3));

    GtkWidget *E4=((multp *)data)->four;
    strcpy(lv.auteur_liv.nom_aut,gtk_entry_get_text(GTK_ENTRY(E4)));
    //const char *autnom=gtk_entry_get_text(GTK_ENTRY(E4));

    GtkWidget *E5=((multp *)data)->five;
    strcpy(lv.auteur_liv.prenom_aut,gtk_entry_get_text(GTK_ENTRY(E5)));
    //const char *autprenom=gtk_entry_get_text(GTK_ENTRY(E5));

    GtkWidget *E6=((multp *)data)->six;
    lv.emprunteur_liv=atoi(gtk_entry_get_text(GTK_ENTRY(E6)));

    // mode ab pour ajouter a la fin du fichier binaire
    FILE *fin=fopen("livre.dat","ab");
    if(!fin) {
        printf("cannot open file \n");
        exit(-1);
    }
    if(!livre_exist(lv)){
        //ecriture
        fwrite(&lv,sizeof(Livre),1,fin);
        printf("ecriture reussite !\n");
    }else printf("livre deja exist !\n");
    fclose(fin);
    gtk_window_close(GTK_WINDOW(i_window));
}


void info_window (GtkWidget *widget,gpointer data){
    b_builder=gtk_builder_new_from_file("livre.glade");
    i_window=GTK_WIDGET(gtk_builder_get_object (b_builder,"info_window"));

    E1=GTK_WIDGET(gtk_builder_get_object (b_builder,"E1"));
    E2=GTK_WIDGET(gtk_builder_get_object (b_builder,"E2"));
    E3=GTK_WIDGET(gtk_builder_get_object (b_builder,"E3"));
    E4=GTK_WIDGET(gtk_builder_get_object (b_builder,"E4"));
    E5=GTK_WIDGET(gtk_builder_get_object (b_builder,"E5"));
    E6=GTK_WIDGET(gtk_builder_get_object (b_builder,"E6"));

    T=(multp *)malloc(sizeof(multp));
    T->one=E1;
    T->two=E2;
    T->three=E3;
    T->four=E4;
    T->five=E5;
    T->six=E6;

    save_btn=GTK_WIDGET(gtk_builder_get_object (b_builder,"save_button"));

    g_signal_connect(save_btn,"clicked",G_CALLBACK (save_book),T);
    g_signal_connect(save_btn,"clicked",G_CALLBACK (show_book_window),NULL);

    gtk_widget_show_all(i_window);
}

void book_window (GtkWidget *widget,gpointer data){
    b_builder=gtk_builder_new_from_file("livre.glade");

    b_window=GTK_WIDGET(gtk_builder_get_object (b_builder,"livre_window"));

    btn_add_book=GTK_WIDGET(gtk_builder_get_object (b_builder,"btn_add_book"));
    btn_edit_book=GTK_WIDGET(gtk_builder_get_object (b_builder,"btn_edit_book"));
    btn_delete_book=GTK_WIDGET(gtk_builder_get_object (b_builder,"btn_delete_book"));
    btn_sort=GTK_WIDGET(gtk_builder_get_object (b_builder,"btn_sort"));
    btn_search_book=GTK_WIDGET(gtk_builder_get_object (b_builder,"btn_search_book"));
    btn_print_books=GTK_WIDGET(gtk_builder_get_object (b_builder,"btn_print_books"));
    btn_return_to_menu=GTK_WIDGET(gtk_builder_get_object (b_builder,"btn_return_to_menu"));

    g_signal_connect(btn_add_book,"clicked",G_CALLBACK(info_window),NULL);
    g_signal_connect(btn_return_to_menu,"clicked",G_CALLBACK(close_book_return_to_menu),NULL);
    gtk_widget_show_all(b_window);
}

void hide_book_window(){
    gtk_widget_hide(b_window);
}

void show_book_window(){
    gtk_widget_show(b_window);
}
void close_book_return_to_menu(){
    gtk_window_close(GTK_WINDOW(b_window));
    show_acceuil();
}
