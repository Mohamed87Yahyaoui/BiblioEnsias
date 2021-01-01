#include <stdio.h>
#include <gtk/gtk.h>
#include "livre.h"

typedef struct multp{
GtkWidget *one,*two,*three,*four,*five,*six;
}multp;

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
    gtk_window_close(GTK_WINDOW(button));
}

void book_window (GtkWidget *widget,gpointer data){
    GtkBuilder *b_builder=gtk_builder_new_from_file("ui.glade");
    GtkWidget *b_window=GTK_WIDGET(gtk_builder_get_object (b_builder,"b_window"));

    GtkWidget *E1=GTK_WIDGET(gtk_builder_get_object (b_builder,"E1"));
    GtkWidget *E2=GTK_WIDGET(gtk_builder_get_object (b_builder,"E2"));
    GtkWidget *E3=GTK_WIDGET(gtk_builder_get_object (b_builder,"E3"));
    GtkWidget *E4=GTK_WIDGET(gtk_builder_get_object (b_builder,"E4"));
    GtkWidget *E5=GTK_WIDGET(gtk_builder_get_object (b_builder,"E5"));
    GtkWidget *E6=GTK_WIDGET(gtk_builder_get_object (b_builder,"E6"));

    multp *T=(multp *)malloc(sizeof(multp));
    T->one=E1;
    T->two=E2;
    T->three=E3;
    T->four=E4;
    T->five=E5;
    T->six=E6;
    GtkWidget *save_btn=GTK_WIDGET(gtk_builder_get_object (b_builder,"save_button"));
    g_signal_connect(save_btn,"clicked",G_CALLBACK (save_book),T);

    gtk_widget_show_all(b_window);
}

void acceuil_window(GtkApplication *app , gpointer user_data){
    GtkBuilder *builder=gtk_builder_new_from_file("ui.glade");
    GtkWidget *window=GTK_WIDGET(gtk_builder_get_object (builder,"window"));;
    GtkWidget *button=GTK_WIDGET(gtk_builder_get_object (builder,"button"));;

    g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect (button, "clicked", G_CALLBACK (book_window), NULL);
    gtk_widget_show_all(window);
    gtk_main();
}

int main(int argc,char **argv){

    GApplication * app;
    gtk_init(&argc, &argv);
    app=g_application_new("test.test",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(acceuil_window),NULL);
    int status=g_application_run(G_APPLICATION(app),argc,argv);
    g_object_unref(app);
    return status;
   // print_all();
}

