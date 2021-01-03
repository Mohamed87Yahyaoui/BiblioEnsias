#include "../main_page/acceuil.h"
#include "book.h"
#include <gtk/gtk.h>

void rechercher_livre(char *titre){
    FILE *fp=fopen("livre.dat","rb");
    Livre temp;
    while (fread(&temp,sizeof(Livre),1,fp)==1){
        if(!strcmp(temp.titre_liv,titre)){
//            print_livre(temp);
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

    E1=((multp *)data)->one;
    lv.num_liv=atoi(gtk_entry_get_text(GTK_ENTRY(E1)));

    E2=((multp *)data)->two;
    strcpy(lv.titre_liv,gtk_entry_get_text(GTK_ENTRY(E2)));
    //const char *titrelv=gtk_entry_get_text(GTK_ENTRY(E2));

    E3=((multp *)data)->three;
    strcpy(lv.categ_liv,gtk_entry_get_text(GTK_ENTRY(E3)));
    //const char *categlv=gtk_entry_get_text(GTK_ENTRY(E3));

    E4=((multp *)data)->four;
    strcpy(lv.auteur_liv.nom_aut,gtk_entry_get_text(GTK_ENTRY(E4)));
    //const char *autnom=gtk_entry_get_text(GTK_ENTRY(E4));

    E5=((multp *)data)->five;
    strcpy(lv.auteur_liv.prenom_aut,gtk_entry_get_text(GTK_ENTRY(E5)));
    //const char *autprenom=gtk_entry_get_text(GTK_ENTRY(E5));

    E6=((multp *)data)->six;
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

void print_books(GtkWidget *button , gpointer data){

    p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (p_window), "Liste de livres");
    gtk_container_set_border_width (GTK_CONTAINER (p_window), 10);
    gtk_widget_set_size_request (p_window, 600, 450);

    treeview = gtk_tree_view_new ();
    setup_tree_view (treeview);
    /* Create a new tree model with six columns, as 2 gint and 4 strings */
    store = gtk_list_store_new (COLUMNS, G_TYPE_INT, G_TYPE_STRING , G_TYPE_STRING ,
    G_TYPE_STRING , G_TYPE_STRING , G_TYPE_INT);


    // Add all of the products to the GtkListStore.
    FILE *fp=fopen("livre.dat","rb");
    Livre lv;
    while (fread(&lv,sizeof(Livre),1,fp)==1){
        gtk_list_store_append (store, &iter);
        gtk_list_store_set (store, &iter, NUM, lv.num_liv ,
        TITRE, lv.titre_liv, CATEG, lv.categ_liv,NOM,lv.auteur_liv.nom_aut,PRENOM,lv.auteur_liv.prenom_aut,EMPR,lv.emprunteur_liv, -1);
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


static void setup_tree_view (GtkWidget *treeview){
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
column = gtk_tree_view_column_new_with_attributes("Nombre Emprunteur", renderer, "text", EMPR, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);

}




void book_window (GtkWidget *widget,gpointer data){
    b_builder=gtk_builder_new_from_file("livre.glade");

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
