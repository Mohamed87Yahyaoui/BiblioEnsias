#include<gtk/gtk.h>
#include<stdlib.h>
#include "book.h"
#include "algorithm.h"


//builers
GtkBuilder *b_builder;
GtkBuilder *d_builder;
GtkBuilder *s_builder;
GtkBuilder *sh_builder;

//ajout d un livre window
GtkWidget *i_window;
//gestion des livres windw
GtkWidget *b_window;
// print book window
GtkWidget *p_window;
// search window
GtkWidget *search_window;
// delete book window
GtkWidget *d_window;
// widget permettant de cree un tableau
GtkWidget *sh_window;

GtkWidget *prei_window;

GtkWidget *treeview;
// widget pour ajouter l'option du scroll
GtkWidget *scrolled_win;
// un store pour stocker les differants livres
GtkListStore *store;
// iterateur pour itterer dans l'ensembles des livres
GtkTreeIter iter;
// permet de creer des colonnes pour le tableau , s'utilise avec treeview
GtkCellRenderer *renderer;
// pour voir la colonne
GtkTreeViewColumn *column;

// entre d'ajout
GtkWidget *E1;
GtkWidget *E2;
GtkWidget *E3;
GtkWidget *E4;
GtkWidget *E5;

GtkWidget *E7;
GtkWidget *E8;
GtkWidget *E9;
GtkWidget *E10;
GtkWidget *E11;
GtkWidget *E12;

GtkWidget *E_delete;
GtkWidget *E_search1;
GtkWidget *E_search2;

GtkWidget *entry_num;

//Sortie
GtkWidget *S_num;
GtkWidget *S_nom;
GtkWidget *S_prenom;
GtkWidget *S_categ;
GtkWidget *S_titre;
GtkWidget *S_empr;


//boutton
GtkWidget *btn_add_book;
GtkWidget *btn_edit_book;
GtkWidget *btn_delete_book;
GtkWidget *btn_sort;
GtkWidget *btn_search_book;
GtkWidget *btn_show_books;
GtkWidget *btn_return_to_menu;
GtkWidget *btn_return_to_book_window;
GtkWidget *btn_delete;
GtkWidget *btn_search;
GtkWidget *btn_search;
GtkWidget *btn_retour;
GtkWidget *dialog;
GtkWidget *save_btn;
GtkWidget *search_num_btn;

int edit_num;
GtkWidget *num_label;

void print_book_window(Livre lv){
    char buffer[50];
    sh_builder=gtk_builder_new_from_file("glade/livre.glade");
    sh_window=GTK_WIDGET(gtk_builder_get_object (sh_builder,"show_book_window"));

    S_num=GTK_WIDGET(gtk_builder_get_object (sh_builder,"S_num"));
    S_categ=GTK_WIDGET(gtk_builder_get_object (sh_builder,"S_categ"));
    S_titre=GTK_WIDGET(gtk_builder_get_object (sh_builder,"S_titre"));
    S_nom=GTK_WIDGET(gtk_builder_get_object (sh_builder,"S_nom"));
    S_prenom=GTK_WIDGET(gtk_builder_get_object (sh_builder,"S_prenom"));
    S_empr=GTK_WIDGET(gtk_builder_get_object (sh_builder,"S_empr"));
    // sprintf pour ecrire dans buffer(de type string)
    sprintf(buffer,"%d",lv.num_liv);
    gtk_label_set_text(GTK_LABEL(S_num),buffer);
    gtk_label_set_text(GTK_LABEL(S_categ),lv.categ_liv);
    gtk_label_set_text(GTK_LABEL(S_titre),lv.titre_liv);
    gtk_label_set_text(GTK_LABEL(S_nom),lv.auteur_liv.nom_aut);
    gtk_label_set_text(GTK_LABEL(S_prenom),lv.auteur_liv.prenom_aut);
    sprintf(buffer,"%d",lv.emprunteur_liv);
    gtk_label_set_text(GTK_LABEL(S_empr),buffer);

    btn_retour=GTK_WIDGET(gtk_builder_get_object (sh_builder,"return_button"));

    g_signal_connect(btn_retour,"clicked",G_CALLBACK (hide_sh),NULL);

    gtk_widget_show_all(sh_window);
}

void rechercher_livre(GtkWidget *widget , gpointer data){
    const char *titre=gtk_entry_get_text(GTK_ENTRY(E_search1));
    const char *categorie=gtk_entry_get_text(GTK_ENTRY(E_search2));
    rechercher_livre_algo(titre,categorie);
}

int livre_exist(int num){
    Livre temp;
    FILE *pf=fopen("livre.dat","rb");
    if(!pf) exit(-1);
    while (fread(&temp,sizeof(Livre),1,pf)==1){
        if(temp.num_liv==num) return 1;
    }
    fclose(pf);
    return 0;
}

void save_book(GtkButton *button,gpointer data){
    Livre lv;

    lv.num_liv=atoi(gtk_entry_get_text(GTK_ENTRY(E1)));

    strcpy(lv.titre_liv,gtk_entry_get_text(GTK_ENTRY(E2)));

    strcpy(lv.categ_liv,gtk_entry_get_text(GTK_ENTRY(E3)));
 
    strcpy(lv.auteur_liv.nom_aut,gtk_entry_get_text(GTK_ENTRY(E4)));

    strcpy(lv.auteur_liv.prenom_aut,gtk_entry_get_text(GTK_ENTRY(E5)));

    lv.emprunteur_liv=-1;
    // mode ab pour ajouter a la fin du fichier binaire
 
    ajouter_livre_algo(lv);
    
    gtk_window_close(GTK_WINDOW(i_window));
}

void info_window (GtkWidget *widget,gpointer data){
    b_builder=gtk_builder_new_from_file("glade/livre.glade");
    i_window=GTK_WIDGET(gtk_builder_get_object (b_builder,"info_window"));

    E1=GTK_WIDGET(gtk_builder_get_object (b_builder,"E1"));
    E2=GTK_WIDGET(gtk_builder_get_object (b_builder,"E2"));
    E3=GTK_WIDGET(gtk_builder_get_object (b_builder,"E3"));
    E4=GTK_WIDGET(gtk_builder_get_object (b_builder,"E4"));
    E5=GTK_WIDGET(gtk_builder_get_object (b_builder,"E5"));

    save_btn=GTK_WIDGET(gtk_builder_get_object (b_builder,"save_button"));

    g_signal_connect(save_btn,"clicked",G_CALLBACK (save_book),NULL);
    g_signal_connect(save_btn,"clicked",G_CALLBACK (show_book_window),NULL);

    gtk_widget_show_all(i_window);
}

void print_books(GtkWidget *button , gpointer data){

    p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (p_window), "Liste de livres");
    gtk_container_set_border_width (GTK_CONTAINER (p_window), 10);
    gtk_widget_set_size_request (p_window, 900, 450);

    treeview = gtk_tree_view_new ();
    setup_tree_view (treeview);
    /* Create a new tree model with six columns, as 2 gint and 4 strings */
    store = gtk_list_store_new (COLUMNS,
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
        gtk_list_store_append (store, &iter);
        gtk_list_store_set (store, &iter,
        NUM, lv.num_liv ,
        TITRE, lv.titre_liv,
        CATEG, lv.categ_liv,
        NOM,lv.auteur_liv.nom_aut,
        PRENOM,lv.auteur_liv.prenom_aut,
        EMPR,lv.emprunteur_liv,
        -1);
    }

    /* Add the tree model to the tree view and unreference it so that the model will
    * be destroyed along with the tree view. */
    gtk_tree_view_set_model (GTK_TREE_VIEW (treeview), GTK_TREE_MODEL (store));
    g_object_unref (store);
    // Add scrole feature
    scrolled_win = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_container_add (GTK_CONTAINER (scrolled_win), treeview);
    gtk_container_add (GTK_CONTAINER (p_window), scrolled_win);


    gtk_widget_show_all (p_window);
}


void setup_tree_view (GtkWidget *treeview){
    /* Create a new GtkCellRendererText, add it to the tree view column and
    * append the column to the tree view. */
    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes("Numero", renderer, "text", NUM, NULL);
    gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);

    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes("Titre", renderer, "text", TITRE, NULL);
    gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);

    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes("Categorie", renderer, "text", CATEG, NULL);
    gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);

    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes("Nom Auteur", renderer, "text", NOM, NULL);
    gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);

    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes("Prenom Auteur", renderer, "text", PRENOM, NULL);
    gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);

    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes("Numero d'Emprunteur", renderer, "text", EMPR, NULL);
    gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);

}

void update_book(GtkButton *button,gpointer data){
    Livre lv;

    lv.num_liv=edit_num;
    strcpy(lv.titre_liv,gtk_entry_get_text(GTK_ENTRY(E8)));
    strcpy(lv.categ_liv,gtk_entry_get_text(GTK_ENTRY(E9)));
    strcpy(lv.auteur_liv.nom_aut,gtk_entry_get_text(GTK_ENTRY(E10)));
    strcpy(lv.auteur_liv.prenom_aut,gtk_entry_get_text(GTK_ENTRY(E11)));
    lv.emprunteur_liv=atoi(gtk_entry_get_text(GTK_ENTRY(E12)));

    modifier_livre_algo(lv);

    gtk_window_close(GTK_WINDOW(i_window));
}

void edit_book (GtkWidget *widget,gpointer data){
    b_builder=gtk_builder_new_from_file("glade/livre.glade");
    edit_num=atoi(gtk_entry_get_text(GTK_ENTRY(entry_num)));
    if(!livre_exist(edit_num)){
        dialog_window("\nlivre non existant !");
    }else {
        i_window=GTK_WIDGET(gtk_builder_get_object (b_builder,"edit_book_window"));
        char temp[50];
        num_label=GTK_WIDGET(gtk_builder_get_object (b_builder,"num_label"));
        sprintf(temp, "%d", edit_num); 
        gtk_label_set_text(GTK_LABEL(num_label),temp);
        E8=GTK_WIDGET(gtk_builder_get_object (b_builder,"E8"));
        E9=GTK_WIDGET(gtk_builder_get_object (b_builder,"E9"));
        E10=GTK_WIDGET(gtk_builder_get_object (b_builder,"E10"));
        E11=GTK_WIDGET(gtk_builder_get_object (b_builder,"E11"));
        E12=GTK_WIDGET(gtk_builder_get_object (b_builder,"E12"));

        save_btn=GTK_WIDGET(gtk_builder_get_object (b_builder,"save_book"));

        g_signal_connect(save_btn,"clicked",G_CALLBACK (update_book),NULL);
        //g_signal_connect(save_btn,"clicked",G_CALLBACK (show_book_window),NULL);
        gtk_widget_show_all(i_window);
    }
    gtk_widget_destroy(prei_window);
}


void pre_edit_book(GtkWidget*widget,gpointer data){
    b_builder=gtk_builder_new_from_file("glade/livre.glade");
    prei_window=GTK_WIDGET(gtk_builder_get_object (b_builder,"pre_edit_book_window"));
    entry_num=GTK_WIDGET(gtk_builder_get_object (b_builder,"entry_num"));
    search_num_btn=GTK_WIDGET(gtk_builder_get_object (b_builder,"search_num"));
    g_signal_connect(search_num_btn,"clicked",G_CALLBACK (edit_book),NULL);
    gtk_widget_show_all(prei_window);
}

void delete_book(GtkWidget *widget, gpointer data){
    d_builder=gtk_builder_new_from_file("glade/livre.glade");
    d_window=GTK_WIDGET(gtk_builder_get_object(d_builder,"delete_window"));
    btn_delete=GTK_WIDGET(gtk_builder_get_object(d_builder,"btn_delete"));
    E_delete=GTK_WIDGET(gtk_builder_get_object(d_builder,"E_delete"));
    g_signal_connect(btn_delete,"clicked",G_CALLBACK(supprimer_livre),NULL);
    gtk_widget_show_all(d_window);
}

void supprimer_livre(GtkButton *button, gpointer data){
    int num=atoi(gtk_entry_get_text(GTK_ENTRY(E_delete)));
    supprimer_livre_algo(num);
    gtk_window_close(GTK_WINDOW(d_window));
}


void search_book(GtkWidget *widget , gpointer data){
    s_builder=gtk_builder_new_from_file("glade/livre.glade");
    search_window=GTK_WIDGET(gtk_builder_get_object(s_builder,"search_window"));
    E_search1=GTK_WIDGET(gtk_builder_get_object(s_builder,"E_search1"));
    E_search2=GTK_WIDGET(gtk_builder_get_object(s_builder,"E_search2"));
    btn_search=GTK_WIDGET(gtk_builder_get_object(s_builder,"btn_search"));

    g_signal_connect(btn_search,"clicked",G_CALLBACK(rechercher_livre),NULL);
    gtk_widget_show_all(search_window);
}

void book_window (GtkWidget *widget,gpointer data){
    b_builder=gtk_builder_new_from_file("glade/livre.glade");

    b_window=GTK_WIDGET(gtk_builder_get_object (b_builder,"livre_window"));

    btn_add_book=GTK_WIDGET(gtk_builder_get_object (b_builder,"btn_add_book"));
    btn_edit_book=GTK_WIDGET(gtk_builder_get_object (b_builder,"btn_edit_book"));
    btn_delete_book=GTK_WIDGET(gtk_builder_get_object (b_builder,"btn_delete_book"));
    btn_sort=GTK_WIDGET(gtk_builder_get_object (b_builder,"btn_sort"));
    btn_search_book=GTK_WIDGET(gtk_builder_get_object (b_builder,"btn_search_book"));
    btn_show_books=GTK_WIDGET(gtk_builder_get_object (b_builder,"btn_show_books"));
    btn_return_to_menu=GTK_WIDGET(gtk_builder_get_object (b_builder,"btn_return_to_menu"));

    g_signal_connect(btn_add_book,"clicked",G_CALLBACK(info_window),NULL);
    g_signal_connect(btn_return_to_menu,"clicked",G_CALLBACK(close_book_return_to_menu),NULL);
    g_signal_connect(btn_show_books,"clicked",G_CALLBACK(print_books),NULL);
    g_signal_connect(btn_edit_book,"clicked",G_CALLBACK(pre_edit_book),NULL);
    g_signal_connect(btn_delete_book,"clicked",G_CALLBACK(delete_book),NULL);
    g_signal_connect(btn_sort,"clicked",G_CALLBACK(ordonner_livre_algo),NULL);
    g_signal_connect(btn_search_book,"clicked",G_CALLBACK(search_book),NULL);
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

void hide_sh(){
    gtk_window_close(GTK_WINDOW(sh_window));
    gtk_window_close(GTK_WINDOW(search_window));
}
