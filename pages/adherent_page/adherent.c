#include <gtk/gtk.h>
#include <stdlib.h>
#include "adherent.h"


GtkBuilder *a_builder;

//ajout d un adherent window
GtkWidget *adh_i_window;
//gestion des adherents windw
GtkWidget *a_window;

GtkWidget *adh_supprimer_window;

GtkWidget *adh_rechercher_window;

GtkWidget *adh_modification_window;

GtkWidget *adh_modifier_window;


GtkBuilder* sh_builder_adh;
GtkWidget* sh_window_adh;
GtkWidget* S_nomadh;
GtkWidget* S_prenomadh;
GtkWidget* S_numadh;
GtkWidget* S_email;
GtkWidget* S_adresse;
GtkWidget* S_nbliv;








GtkWidget *p_window_adh;
// widget permettant de cree un tableau
GtkWidget *treeview_adh;
// widget pour ajouter l'option du scroll
GtkWidget *scrolled_win_adh;
// un store_adh pour stocker les differants livres
GtkListStore *store_adh;
// iterateur pour itterer dans l'ensembles des livres
GtkTreeIter iter_adh;
// permet de creer des colonnes pour le tableau , s'utilise avec treeview_adh
GtkCellRenderer *renderer_adh;
// pour voir la colonne
GtkTreeViewColumn *column_adh;


// entre d'ajout d'un adherent
GtkWidget *E1adh;
GtkWidget *E2adh;
GtkWidget *E3adh;
GtkWidget *E4adh;
GtkWidget *E5adh;
GtkWidget *E6adh;
GtkWidget *E7adh;
GtkWidget *E8adh;
GtkWidget *E9adh;
GtkWidget *E10adh;
GtkWidget *E11adh;
GtkWidget *E12adh;
GtkWidget *Esupp;
GtkWidget *Erech;
GtkWidget *Emodif;


//boutton
GtkWidget *btn_add_adh;
GtkWidget *btn_edit_adh;
GtkWidget *btn_delete_adh;
GtkWidget *btn_rech_adh;
GtkWidget *btn_show_adhs;
GtkWidget *conf_delete_adh;
GtkWidget *conf_rech_adh;
GtkWidget *conf1_modif_adh;
GtkWidget *valider_modification_adh;
GtkWidget *btn_return_to_menuadh;
GtkWidget *btn_return_to_adh_window;

GtkWidget *save_btn_adh;

int num_modif;

int adh_exist(adherent adh){
    adherent temp;
    FILE *pf=fopen("adherent.dat","rb");
    if(!pf) exit(-1);
    while (fread(&temp,sizeof(adherent),1,pf)==1){
        if(temp.num_adh==adh.num_adh) return 1;
    }
    fclose(pf);
    return 0;
}

void save_adh(GtkButton *button,gpointer data){
    adherent adh;

    adh.num_adh=atoi(gtk_entry_get_text(GTK_ENTRY(E1adh)));

    strcpy(adh.nom_adh,gtk_entry_get_text(GTK_ENTRY(E2adh)));

    strcpy(adh.prenom_adh,gtk_entry_get_text(GTK_ENTRY(E3adh)));

    strcpy(adh.email_adh,gtk_entry_get_text(GTK_ENTRY(E4adh)));

    strcpy(adh.adress_adh,gtk_entry_get_text(GTK_ENTRY(E5adh)));

    //adh.nbre_emprunts_adh=atoi(gtk_entry_get_text(GTK_ENTRY(E6adh)));

    adh.nbre_emprunts_adh=0;

    // mode ab pour ajouter a la fin du fichier binaire
    FILE *fin=fopen("adherent.dat","ab");
    if(!fin) {
        printf("cannot open file \n");
        exit(-1);
    }
    if(!adh_exist(adh)){
        //ecriture
        fwrite(&adh,sizeof(adherent),1,fin);
        dialog_window("Adherent est ajoute avec succes");
    }else dialog_window("adherent deja exist !");
    fclose(fin);
    gtk_window_close(GTK_WINDOW(adh_i_window));
}

void adh_info_window (GtkWidget *widget,gpointer data){
    a_builder=gtk_builder_new_from_file("glade/adherent.glade");
    adh_i_window=GTK_WIDGET(gtk_builder_get_object (a_builder,"adh_info_window"));

    E1adh=GTK_WIDGET(gtk_builder_get_object (a_builder,"E1adh"));
    E2adh=GTK_WIDGET(gtk_builder_get_object (a_builder,"E2adh"));
    E3adh=GTK_WIDGET(gtk_builder_get_object (a_builder,"E3adh"));
    E4adh=GTK_WIDGET(gtk_builder_get_object (a_builder,"E4adh"));
    E5adh=GTK_WIDGET(gtk_builder_get_object (a_builder,"E5adh"));
    //E6adh=GTK_WIDGET(gtk_builder_get_object (a_builder,"E6adh"));


    save_btn_adh=GTK_WIDGET(gtk_builder_get_object (a_builder,"save_button_adh"));

    g_signal_connect(save_btn_adh,"clicked",G_CALLBACK (save_adh),NULL);
    g_signal_connect(save_btn_adh,"clicked",G_CALLBACK (show_adh_window),NULL);

    gtk_widget_show_all(adh_i_window);
}



void delete_adh(GtkButton *button,gpointer data)
{
    FILE* ftemp;
    adherent adh1;
    adherent adh2;

    E1adh=Esupp;
    adh1.num_adh=atoi(gtk_entry_get_text(GTK_ENTRY(E1adh)));

    FILE *fin=fopen("adherent.dat","rb");
    if(!fin) {
        printf("cannot open file \n");
        exit(-1);
    }
    if(adh_exist(adh1)){
        ftemp=fopen("adherenttemp.dat","w+b");
        while(fread(&adh2, sizeof(adherent), 1, fin))
        {
            if(adh2.num_adh!=adh1.num_adh)
            {
                fwrite(&adh2, sizeof(adherent), 1, ftemp);
            }
        }
        fclose(fin);
        fclose(ftemp);
        ftemp=fopen("adherenttemp.dat","rb");
        fin=fopen("adherent.dat","w+b");
        while(fread(&adh1, sizeof(adherent), 1, ftemp))
        {
            fwrite(&adh1, sizeof(adherent), 1, fin);
        }
        dialog_window("Suppression reussie");
    }else dialog_window("adherent n existe pas !");
    fclose(fin);
    fclose(ftemp);
    gtk_window_close(GTK_WINDOW(adh_supprimer_window));
}



void adh_supp_window(GtkWidget *widget, gpointer data)
{
    a_builder=gtk_builder_new_from_file("glade/adherent.glade");
    adh_supprimer_window=GTK_WIDGET(gtk_builder_get_object (a_builder,"adh_supp_window"));

    Esupp=GTK_WIDGET(gtk_builder_get_object (a_builder,"Esupp"));
    conf_delete_adh=GTK_WIDGET(gtk_builder_get_object (a_builder,"conf_delete_adh"));

    g_signal_connect(conf_delete_adh, "clicked", G_CALLBACK (delete_adh), Esupp);
    g_signal_connect(conf_delete_adh, "clicked", G_CALLBACK (show_adh_window), NULL);

    gtk_widget_show_all(adh_supprimer_window);//it works

}

void adh_rech_window(GtkWidget *widget, gpointer data)
{
    a_builder=gtk_builder_new_from_file("glade/adherent.glade");
    adh_rechercher_window=GTK_WIDGET(gtk_builder_get_object (a_builder,"adh_rech_window"));

    Erech=GTK_WIDGET(gtk_builder_get_object (a_builder,"Erech"));
    conf_rech_adh=GTK_WIDGET(gtk_builder_get_object (a_builder,"conf_rech_adh"));

    g_signal_connect(conf_rech_adh, "clicked", G_CALLBACK (rechercher_adherent), Erech);
    g_signal_connect(conf_rech_adh, "clicked", G_CALLBACK (show_adh_window), NULL);

    gtk_widget_show_all(adh_rechercher_window);
}

void rechercher_adherent(GtkWidget *widget , gpointer data){

    adherent adh1;
    adh1.num_adh=atoi(gtk_entry_get_text(GTK_ENTRY(Erech)));
    if(adh_exist(adh1))
    {
        FILE* f=fopen("adherent.dat","rb");

        adherent ad;
        while(fread(&ad,sizeof(adherent),1,f))
        {

            if(adh1.num_adh==ad.num_adh)
            {

                print_adh_window(ad);
            }
        }
    }
    else
    {
        dialog_window("adherent innexistant");
    }

}



void print_adh_window(adherent ad){
    char buffer[50];
    sh_builder_adh=gtk_builder_new_from_file("glade/adherent.glade");
    sh_window_adh=GTK_WIDGET(gtk_builder_get_object (sh_builder_adh,"show_adherent_window"));

    S_numadh=GTK_WIDGET(gtk_builder_get_object (sh_builder_adh,"S_num"));
    S_nomadh=GTK_WIDGET(gtk_builder_get_object (sh_builder_adh,"S_nom"));
    S_prenomadh=GTK_WIDGET(gtk_builder_get_object (sh_builder_adh,"S_prenom"));
    S_email=GTK_WIDGET(gtk_builder_get_object (sh_builder_adh,"S_email"));
    S_adresse=GTK_WIDGET(gtk_builder_get_object (sh_builder_adh,"S_adresse"));
    S_nbliv=GTK_WIDGET(gtk_builder_get_object (sh_builder_adh,"S_nbliv"));
    // sprintf pour ecrire dans buffer(de type string)
    sprintf(buffer,"%d",ad.num_adh);
    gtk_label_set_text(GTK_LABEL(S_numadh),buffer);
    gtk_label_set_text(GTK_LABEL(S_nomadh),ad.nom_adh);
    gtk_label_set_text(GTK_LABEL(S_prenomadh),ad.prenom_adh);
    gtk_label_set_text(GTK_LABEL(S_email),ad.email_adh);
    gtk_label_set_text(GTK_LABEL(S_adresse),ad.adress_adh);
    sprintf(buffer,"%d",ad.nbre_emprunts_adh);
    gtk_label_set_text(GTK_LABEL(S_nbliv),buffer);

    //btn_retour=GTK_WIDGET(gtk_builder_get_object (sh_builder,"return_button"));

    //g_signal_connect(btn_retour,"clicked",G_CALLBACK (hide_sh),NULL);

    gtk_widget_show_all(sh_window_adh);
}










void adh_window (GtkWidget *widget,gpointer data){
    a_builder=gtk_builder_new_from_file("glade/adherent.glade");

    a_window=GTK_WIDGET(gtk_builder_get_object (a_builder,"adh_window"));

    btn_add_adh=GTK_WIDGET(gtk_builder_get_object (a_builder,"btn_add_adh"));
    btn_edit_adh=GTK_WIDGET(gtk_builder_get_object (a_builder,"btn_edit_adh"));
    btn_delete_adh=GTK_WIDGET(gtk_builder_get_object (a_builder,"btn_delete_adh"));
    btn_rech_adh=GTK_WIDGET(gtk_builder_get_object (a_builder,"btn_search_adh"));
    btn_show_adhs=GTK_WIDGET(gtk_builder_get_object (a_builder,"btn_show_adhs"));
    btn_return_to_menuadh=GTK_WIDGET(gtk_builder_get_object (a_builder,"btn_return_to_menu"));

    g_signal_connect(btn_add_adh,"clicked",G_CALLBACK(adh_info_window),NULL);
    g_signal_connect(btn_edit_adh,"clicked",G_CALLBACK(adh_modif_window),NULL);
    g_signal_connect(btn_delete_adh,"clicked",G_CALLBACK(adh_supp_window),NULL);
    g_signal_connect(btn_rech_adh,"clicked",G_CALLBACK(adh_rech_window),NULL);
    g_signal_connect(btn_show_adhs,"clicked",G_CALLBACK(print_adhs),NULL);
    g_signal_connect(btn_return_to_menuadh,"clicked",G_CALLBACK(close_adh_return_to_menu),NULL);
    //g_signal_connect(btn_show_adhs,"clicked",G_CALLBACK(print_all),NULL);

    gtk_widget_show_all(a_window);
}



void print_adhs(GtkWidget *button , gpointer data){

    p_window_adh = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (p_window_adh), "Liste des adherents");
    gtk_container_set_border_width (GTK_CONTAINER (p_window_adh), 10);
    gtk_widget_set_size_request (p_window_adh, 600, 450);

    treeview_adh = gtk_tree_view_new ();
    setup_tree_view_adh (treeview_adh);
    /* Create a new tree model with six columns, as 2 gint and 4 strings */
    store_adh = gtk_list_store_new (COLUMNSadh,
    G_TYPE_INT,
    G_TYPE_STRING ,
    G_TYPE_STRING ,
    G_TYPE_STRING ,
    G_TYPE_STRING ,
    G_TYPE_INT);


    // Add all of the products to the GtkListStore.
    FILE *fpadh=fopen("adherent.dat","rb");
    adherent ad;
    while (fread(&ad,sizeof(adherent),1,fpadh)==1){
        gtk_list_store_append (store_adh, &iter_adh);
        gtk_list_store_set (store_adh, &iter_adh,
        NUMadh, ad.num_adh ,
        NOMadh, ad.nom_adh,
        PRENOMadh, ad.prenom_adh,
        EMAIL,ad.email_adh,
        ADRESSE,ad.adress_adh,
        NB_EMPR,ad.nbre_emprunts_adh,
        -1);
    }

    /* Add the tree model to the tree view and unreference it so that the model will
    * be destroyed along with the tree view. */
    gtk_tree_view_set_model (GTK_TREE_VIEW (treeview_adh), GTK_TREE_MODEL (store_adh));
    g_object_unref (store_adh);
    // Add scrole feature
    scrolled_win_adh = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win_adh),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_container_add (GTK_CONTAINER (scrolled_win_adh), treeview_adh);
    gtk_container_add (GTK_CONTAINER (p_window_adh), scrolled_win_adh);


    gtk_widget_show_all (p_window_adh);
}



void setup_tree_view_adh (GtkWidget *treeview_adh){
    /* Create a new GtkCellRendererText, add it to the tree view column and
     append the column to the tree view. */
    renderer_adh = gtk_cell_renderer_text_new ();
    column_adh = gtk_tree_view_column_new_with_attributes("Numero", renderer_adh, "text", NUMadh, NULL);
    gtk_tree_view_append_column (GTK_TREE_VIEW (treeview_adh), column_adh);

    renderer_adh = gtk_cell_renderer_text_new ();
    column_adh = gtk_tree_view_column_new_with_attributes("Nom", renderer_adh, "text", NOMadh, NULL);
    gtk_tree_view_append_column (GTK_TREE_VIEW (treeview_adh), column_adh);

    renderer_adh = gtk_cell_renderer_text_new ();
    column_adh = gtk_tree_view_column_new_with_attributes("Prenom", renderer_adh, "text", PRENOMadh, NULL);
    gtk_tree_view_append_column (GTK_TREE_VIEW (treeview_adh), column_adh);

    renderer_adh = gtk_cell_renderer_text_new ();
    column_adh = gtk_tree_view_column_new_with_attributes("Email", renderer_adh, "text", EMAIL, NULL);
    gtk_tree_view_append_column (GTK_TREE_VIEW (treeview_adh), column_adh);

    renderer_adh = gtk_cell_renderer_text_new ();
    column_adh = gtk_tree_view_column_new_with_attributes("Adresse", renderer_adh, "text", ADRESSE, NULL);
    gtk_tree_view_append_column (GTK_TREE_VIEW (treeview_adh), column_adh);

    renderer_adh = gtk_cell_renderer_text_new ();
    column_adh = gtk_tree_view_column_new_with_attributes("Nombre de livre empruntes", renderer_adh, "text", NB_EMPR, NULL);
    gtk_tree_view_append_column (GTK_TREE_VIEW (treeview_adh), column_adh);

}

void adh_modif_window(GtkWidget *widget, gpointer data)
{
    a_builder=gtk_builder_new_from_file("glade/adherent.glade");
    adh_modifier_window=GTK_WIDGET(gtk_builder_get_object (a_builder,"modif_adh_conf"));

    Emodif=GTK_WIDGET(gtk_builder_get_object (a_builder,"Emodif"));
    conf1_modif_adh=GTK_WIDGET(gtk_builder_get_object (a_builder,"conf1_modif_adh"));


    g_signal_connect(conf1_modif_adh, "clicked", G_CALLBACK (adh_conf_modif_window), NULL);
    g_signal_connect(conf1_modif_adh, "clicked", G_CALLBACK (show_adh_window), NULL);

    gtk_widget_show_all(adh_modifier_window);
}

void adh_conf_modif_window(GtkWidget *widget, gpointer data)
{
    adherent adh1;
    num_modif=atoi(gtk_entry_get_text(GTK_ENTRY(Emodif)));
    adh1.num_adh=num_modif;
    FILE *fin=fopen("adherent.dat","rb");
    if(!fin) {
        printf("cannot open file \n");
        exit(-1);
    }
    if(adh_exist(adh1)){
        a_builder=gtk_builder_new_from_file("glade/adherent.glade");
        adh_modification_window=GTK_WIDGET(gtk_builder_get_object (a_builder,"adh_modif_window"));


        E8adh=GTK_WIDGET(gtk_builder_get_object (a_builder,"E8adh"));
        E9adh=GTK_WIDGET(gtk_builder_get_object (a_builder,"E9adh"));
        E10adh=GTK_WIDGET(gtk_builder_get_object (a_builder,"E10adh"));
        E11adh=GTK_WIDGET(gtk_builder_get_object (a_builder,"E11adh"));
        E12adh=GTK_WIDGET(gtk_builder_get_object (a_builder,"E12adh"));


        valider_modification_adh=GTK_WIDGET(gtk_builder_get_object (a_builder,"validemodif_button_adh"));

        g_signal_connect(valider_modification_adh,"clicked",G_CALLBACK (modif_adh),NULL);
        g_signal_connect(valider_modification_adh,"clicked",G_CALLBACK (show_adh_window),NULL);

        gtk_widget_show_all(adh_modification_window);

    }
    else dialog_window("adherent n existe pas !");
    fclose(fin);
    gtk_widget_show_all(adh_modifier_window);
}

void modif_adh(GtkButton * button, gpointer data)
{
    adherent adh,adh1;

    adh.num_adh=num_modif;

    strcpy(adh.nom_adh,gtk_entry_get_text(GTK_ENTRY(E8adh)));

    strcpy(adh.prenom_adh,gtk_entry_get_text(GTK_ENTRY(E9adh)));

    strcpy(adh.email_adh,gtk_entry_get_text(GTK_ENTRY(E10adh)));

    strcpy(adh.adress_adh,gtk_entry_get_text(GTK_ENTRY(E11adh)));

    adh.nbre_emprunts_adh=atoi(gtk_entry_get_text(GTK_ENTRY(E12adh)));

    // mode ab pour ajouter a la fin du fichier binaire
    FILE *fin=fopen("adherent.dat","r+b");
    if(!fin) {
        printf("cannot open file \n");
        exit(-1);
    }
    else
    {
        while(fread(&adh1, sizeof(adherent), 1, fin))
        {
            if(adh1.num_adh==adh.num_adh)
            {
                 long long unsigned int dep =-1*sizeof(adherent);
                 fseek(fin,dep,SEEK_CUR);
                 if(fwrite(&adh,sizeof(adherent),1,fin)==1)
                 {
                     dialog_window("Adherent mis a jour!");
                 }
                 else
                 {
                     dialog_window("Erreur de modification!");
                 }
                 break;
            }
        }
        fclose(fin);
    }
    gtk_window_close(GTK_WINDOW(adh_modification_window));
}



void hide_adh_window(){
    gtk_widget_hide(a_window);
}

void show_adh_window(){
    gtk_widget_show(a_window);
}

void close_adh_return_to_menu(){
    gtk_window_close(GTK_WINDOW(a_window));
    show_acceuil();
}






