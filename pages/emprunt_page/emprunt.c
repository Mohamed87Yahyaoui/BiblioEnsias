#include<gtk/gtk.h>
#include<stdio.h>
#include "emprunt.h"
#include "adherent.h"
#include "book.h"

GtkBuilder *e_builder;
GtkBuilder *r_builder;

GtkWidget *e_window;
GtkWidget *er_window;

GtkWidget *e_window_adh;

GtkWidget *btn_emprunter;

GtkWidget *btn_livres_empruntes;
GtkWidget *btn_rendre_livre;
GtkWidget *btn_emprunteur;
GtkWidget *btn_return_to_menuempr;

GtkWidget *empr_window;
GtkWidget *E_num;
GtkWidget *E_adh;
GtkWidget *btn_empr;

GtkWidget *rdr_window;
GtkWidget *E_num2;
GtkWidget *E_adh2;
GtkWidget *btn_rendre;

GtkWidget *treeviewempr;
GtkWidget *scrolled_winempr;
GtkListStore *storeempr;
GtkTreeIter iterempr;


void emprunt_window(GtkWidget *widget , gpointer data){
    e_builder=gtk_builder_new_from_file("glade/emprunt.glade");

    e_window=GTK_WIDGET(gtk_builder_get_object (e_builder,"emprunt_window"));

    btn_emprunter=GTK_WIDGET(gtk_builder_get_object (e_builder,"btn_emprunter"));
    btn_livres_empruntes=GTK_WIDGET(gtk_builder_get_object (e_builder,"btn_livres_empruntes"));
    btn_rendre_livre=GTK_WIDGET(gtk_builder_get_object (e_builder,"btn_rendre_livre"));
    btn_emprunteur=GTK_WIDGET(gtk_builder_get_object (e_builder,"btn_emprunteurs"));
    btn_return_to_menuempr=GTK_WIDGET(gtk_builder_get_object (e_builder,"btn_return_to_menu"));

    g_signal_connect(btn_emprunter,"clicked",G_CALLBACK(emprunter_window),NULL);
    g_signal_connect(btn_return_to_menuempr,"clicked",G_CALLBACK(close_empr_return_to_menu),NULL);
    g_signal_connect(btn_livres_empruntes,"clicked",G_CALLBACK(print_books_emprunte),NULL);
    g_signal_connect(btn_rendre_livre,"clicked",G_CALLBACK(rendre_window),NULL);
    g_signal_connect(btn_emprunteur,"clicked",G_CALLBACK(rech_adh_liv),NULL);

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
    //CHECK num_adh is VALID AND CHECK IF nbre_emprunts_adh<3
    int FOUND_ADH=0;
    int FOUND_BOOK=0; 
    int CAN_BORROW=1;
    int ALREADY_BORROWED=0;
    fp_adh=fopen("adherent.dat","r+b");
    while (fread(&temp_adh,sizeof(adherent),1,fp_adh)==1){
        pos++;
        if(temp_adh.num_adh==num2){
            FOUND_ADH=1;
            if(temp_adh.nbre_emprunts_adh>=3) CAN_BORROW=0;
            break;
        }
    }
    if(!FOUND_ADH) dialog_window("\nAdherent Inexistant !");
    
    if(FOUND_ADH && !CAN_BORROW) dialog_window("\nAdherent trouvé mais ne peut plus emprunter !");
    if(FOUND_ADH && CAN_BORROW){
        //THEN MODIFY
        fp_book=fopen("livre.dat","r+b");
        while (fread(&temp_book,sizeof(Livre),1,fp_book)==1){
            if(temp_book.num_liv==num1){
                FOUND_BOOK=1;
                if(temp_book.emprunteur_liv!=-1){
                    ALREADY_BORROWED=1;
                    dialog_window("\nLivre déja emprunté !");
                }else{
                    temp_book.emprunteur_liv=num2;
                    unsigned long long int dep=-1*sizeof(Livre);
                    fseek(fp_book,dep,SEEK_CUR);
                    fwrite(&temp_book,sizeof(Livre),1,fp_book) ;
                }
            }
        }
        fclose(fp_book);
        // INCREMENT NUMBER OF BOOKS BORROWED BY adherent 
        
        if(FOUND_BOOK && !ALREADY_BORROWED) {
            rewind(fp_adh);
            unsigned long long int dep=sizeof(adherent)*(pos-1);
            fseek(fp_adh,dep,SEEK_SET);
            fread(&temp_adh,sizeof(adherent),1,fp_adh);
            temp_adh.nbre_emprunts_adh++;
            dep=-1*sizeof(adherent);
            fseek(fp_adh,dep,SEEK_CUR);
            if(fwrite(&temp_adh,sizeof(adherent),1,fp_adh)==1) dialog_window("\nOpération terminé avec succès !");
        }
        if(!FOUND_BOOK) dialog_window("\nLivre Inexistant !");
    }
    fclose(fp_adh);
    gtk_widget_destroy(empr_window);
}
void rendre_window(GtkWidget *widget , gpointer data){
    r_builder=gtk_builder_new_from_file("glade/emprunt.glade");
    rdr_window=GTK_WIDGET(gtk_builder_get_object(r_builder,"rendre_window"));
    E_num2=GTK_WIDGET(gtk_builder_get_object(r_builder,"E_num2"));
    E_adh2=GTK_WIDGET(gtk_builder_get_object(r_builder,"E_adh2"));
    btn_rendre=GTK_WIDGET(gtk_builder_get_object(r_builder,"btn_rendre"));

    g_signal_connect(btn_rendre,"clicked",G_CALLBACK(rendre_fonction),NULL);
    gtk_widget_show_all(rdr_window);
}
void rendre_fonction(GtkWidget *widget , gpointer data){
    Livre temp_book;
    adherent temp_adh;
    FILE *fp_book;
    FILE *fp_adh;
    int pos=0;
    int num1=atoi(gtk_entry_get_text(GTK_ENTRY(E_num2))); //numero du livre
    int num2=atoi(gtk_entry_get_text(GTK_ENTRY(E_adh2))); // numero d'adherent
    //CHECK num_adh is VALID AND CHECK IF nbre_emprunts_adh<4
    int FOUND_ADH=0;
    int FOUND_BOOK=0; 
    int CAN_RETURN=1;
    fp_adh=fopen("adherent.dat","r+b");
    while (fread(&temp_adh,sizeof(adherent),1,fp_adh)==1){
        pos++;
        if(temp_adh.num_adh==num2){
            FOUND_ADH=1;
            if(temp_adh.nbre_emprunts_adh==-1) CAN_RETURN=0;
        }
    }
    if(!FOUND_ADH) dialog_window("\n Adherent Inexistant !");
    if(FOUND_ADH && !CAN_RETURN) dialog_window("Adherent trouvé mais n'a emprunté aucun livre !");
    if(FOUND_ADH && CAN_RETURN){
        //THEN MODIFY
        fp_book=fopen("livre.dat","r+b");
        while (fread(&temp_book,sizeof(Livre),1,fp_book)==1){
            if(temp_book.num_liv==num1){
                FOUND_BOOK=1;
                temp_book.emprunteur_liv=-1;
                unsigned long long int dep=-1*sizeof(Livre);
                fseek(fp_book,dep,SEEK_CUR);
                fwrite(&temp_book,sizeof(Livre),1,fp_book) ;
            }
        }
        fclose(fp_book);
        // DECREMENT NUMBER OF BOOKS BORROWED BY adherent 
        if(FOUND_BOOK) {
            unsigned long long int dep;
            dep=sizeof(adherent)*(pos-1);
            fseek(fp_adh,dep,SEEK_SET);
            fread(&temp_adh,sizeof(adherent),1,fp_adh);
            temp_adh.nbre_emprunts_adh--;
            dep=-1*sizeof(adherent);
            fseek(fp_adh,dep,SEEK_CUR);
            if(fwrite(&temp_adh,sizeof(adherent),1,fp_adh)==1) dialog_window("\nOpération terminé avec succès !");
        }
        else dialog_window("\nLivre Inexistant!");
    }
    fclose(fp_adh);
    gtk_widget_destroy(rdr_window);
}

void rech_adh_liv(GtkWidget *widget , gpointer data){
    e_window_adh = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (e_window_adh), "Liste emprunteur de livre");
    gtk_container_set_border_width (GTK_CONTAINER (e_window_adh), 10);
    gtk_widget_set_size_request (e_window_adh, 900, 450);

    treeviewempr = gtk_tree_view_new ();
    setup_tree_view_adh (treeviewempr);
    // Create a new tree model with six columns, as 2 gint and 4 strings 
    storeempr = gtk_list_store_new (COLUMNSadh,
    G_TYPE_INT,
    G_TYPE_STRING ,
    G_TYPE_STRING ,
    G_TYPE_STRING ,
    G_TYPE_STRING ,
    G_TYPE_INT);
    
    adherent ad;
    FILE* fadh=fopen("adherent.dat","rb");
    while(fread(&ad,sizeof(adherent),1,fadh)==1){
        if(ad.nbre_emprunts_adh!=0){
            gtk_list_store_append (storeempr, &iterempr);
            gtk_list_store_set (storeempr, &iterempr,
            NUMadh, ad.num_adh ,
            NOMadh, ad.nom_adh,
            PRENOMadh, ad.prenom_adh,
            EMAIL,ad.email_adh,
            ADRESSE,ad.adress_adh,
            NB_EMPR,ad.nbre_emprunts_adh,
            -1);
        }
    }

    // Add the tree model to the tree view and unreference it so that the model will
    // be destroyed along with the tree view. 
    gtk_tree_view_set_model (GTK_TREE_VIEW (treeviewempr), GTK_TREE_MODEL (storeempr));
    g_object_unref (storeempr);
    // Add scrole feature
    scrolled_winempr = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_winempr),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_container_add (GTK_CONTAINER (scrolled_winempr), treeviewempr);
    gtk_container_add (GTK_CONTAINER (e_window_adh), scrolled_winempr);
    gtk_widget_show_all (e_window_adh);


    fclose(fadh);
}


void print_books_emprunte(GtkWidget *button , gpointer data){

    er_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (er_window), "Liste des livres empruntes");
    gtk_container_set_border_width (GTK_CONTAINER (er_window), 10);
    gtk_widget_set_size_request (er_window, 900, 450);

    treeviewempr = gtk_tree_view_new ();
    setup_tree_view (treeviewempr);
    // Create a new tree model with six columns, as 2 gint and 4 strings 
    storeempr = gtk_list_store_new (COLUMNS,
    G_TYPE_INT,
    G_TYPE_STRING ,
    G_TYPE_STRING ,
    G_TYPE_STRING ,
    G_TYPE_STRING ,
    G_TYPE_INT);

    // Add all of the products to the GtkListStore.
    FILE *fp=fopen("livre.dat","rb");
    Livre lv;
    while (fread(&lv,sizeof(Livre),1,fp)==1){
            if(lv.emprunteur_liv!=-1)
            {
                gtk_list_store_append (storeempr, &iterempr);
                gtk_list_store_set (storeempr, &iterempr,
                NUM, lv.num_liv ,
                TITRE, lv.titre_liv,
                CATEG, lv.categ_liv,
                NOM,lv.auteur_liv.nom_aut,
                PRENOM,lv.auteur_liv.prenom_aut,
                EMPR,lv.emprunteur_liv,
                -1);
            }
    }

    // Add the tree model to the tree view and unreference it so that the model will
    // be destroyed along with the tree view. 
    gtk_tree_view_set_model (GTK_TREE_VIEW (treeviewempr), GTK_TREE_MODEL (storeempr));
    g_object_unref (storeempr);
    // Add scrole feature
    scrolled_winempr = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_winempr),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_container_add (GTK_CONTAINER (scrolled_winempr), treeviewempr);
    gtk_container_add (GTK_CONTAINER (er_window), scrolled_winempr);


    gtk_widget_show_all (er_window);
}

void close_empr_return_to_menu(){
    gtk_window_close(GTK_WINDOW(e_window));
    show_acceuil();
}

