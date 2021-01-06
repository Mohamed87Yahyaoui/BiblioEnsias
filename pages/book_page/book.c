#include "acceuil.h"
#include "book.h"
#include <gtk/gtk.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

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

void hide_sh(){
    gtk_window_close(GTK_WINDOW(sh_window));
    gtk_window_close(GTK_WINDOW(search_window));
}

void print_book_window(Livre lv){
    char buffer[50];
    sh_builder=gtk_builder_new_from_file("livre.glade");
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
    /*
    for (int i = 0; i < strlen(titre); i++){
        titre[i]=toupper(titre[i]);
    }
    for (int i = 0; i < strlen(titre); i++){
        categorie[i]=toupper(categorie[i]);
    }
    */
    FILE *fp=fopen("livre.dat","rb");
    Livre temp;
    while (fread(&temp,sizeof(Livre),1,fp)==1){
        if(!strcmp(temp.titre_liv,titre) && !strcmp(temp.categ_liv,categorie) ){
            print_book_window(temp);
            return ;
        }
    }
    g_print("no such autor\n");
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
/*
    for (int i = 0; i < strlen(lv.titre_liv); i++){
        lv.titre_liv[i]=toupper(lv.titre_liv[i]);
    }

    for (int i = 0; i < strlen(lv.categ_liv); i++){
        lv.categ_liv[i]=toupper(lv.categ_liv[i]);
    }
    
 */
    strcpy(lv.auteur_liv.nom_aut,gtk_entry_get_text(GTK_ENTRY(E4)));

    strcpy(lv.auteur_liv.prenom_aut,gtk_entry_get_text(GTK_ENTRY(E5)));

    lv.emprunteur_liv=atoi(gtk_entry_get_text(GTK_ENTRY(E6)));

    // mode ab pour ajouter a la fin du fichier binaire
    FILE *fin=fopen("livre.dat","ab");
    if(!fin) {
        dialog_window("\ncannot open file");
        exit(-1);
    }
    if(!livre_exist(lv.num_liv)){
        //ecriture
        fwrite(&lv,sizeof(Livre),1,fin);
        //num_books++;
        dialog_window("\necriture reussite !");
    }else 
        dialog_window("\nlivre deja exist !");
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

    save_btn=GTK_WIDGET(gtk_builder_get_object (b_builder,"save_button"));

    g_signal_connect(save_btn,"clicked",G_CALLBACK (save_book),NULL);
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
    column = gtk_tree_view_column_new_with_attributes("Nombre Emprunteur", renderer, "text", EMPR, NULL);
    gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);

}

void update_book(GtkButton *button,gpointer data){
    Livre lv;

    lv.num_liv=atoi(gtk_entry_get_text(GTK_ENTRY(E7)));
    strcpy(lv.titre_liv,gtk_entry_get_text(GTK_ENTRY(E8)));
    strcpy(lv.categ_liv,gtk_entry_get_text(GTK_ENTRY(E9)));
    strcpy(lv.auteur_liv.nom_aut,gtk_entry_get_text(GTK_ENTRY(E10)));
    strcpy(lv.auteur_liv.prenom_aut,gtk_entry_get_text(GTK_ENTRY(E11)));
    lv.emprunteur_liv=atoi(gtk_entry_get_text(GTK_ENTRY(E12)));

    // mode w+n pour mise a jour
    FILE *fp=fopen("livre.dat","r+b");
    Livre temp;
    int found =0;
    if(!fp) {
        dialog_window("\ncannot open file");
        exit(-1);
    }
    while (fread(&temp,sizeof(Livre),1,fp)==1){
        if(temp.num_liv==lv.num_liv){
            unsigned long long int dep=-1*sizeof(Livre);
            fseek(fp,dep,SEEK_CUR);
            if(fwrite(&lv,sizeof(Livre),1,fp)==1) dialog_window("\nmise a jour reussite !");
            found=1;
        }
    }
    
    if(!found) 
        dialog_window("\nlivre non existant !");
    fclose(fp);
    gtk_window_close(GTK_WINDOW(i_window));
}

void edit_book (GtkWidget *widget,gpointer data){
    b_builder=gtk_builder_new_from_file("livre.glade");
    i_window=GTK_WIDGET(gtk_builder_get_object (b_builder,"edit_book_window"));

    E7=GTK_WIDGET(gtk_builder_get_object (b_builder,"E7"));
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


void delete_book(GtkWidget *widget, gpointer data){
    d_builder=gtk_builder_new_from_file("livre.glade");
    d_window=GTK_WIDGET(gtk_builder_get_object(d_builder,"delete_window"));
    btn_delete=GTK_WIDGET(gtk_builder_get_object(d_builder,"btn_delete"));
    E_delete=GTK_WIDGET(gtk_builder_get_object(d_builder,"E_delete"));
    g_signal_connect(btn_delete,"clicked",G_CALLBACK(supprimer_livre),NULL);
    gtk_widget_show_all(d_window);
}

void supprimer_livre(GtkButton *button, gpointer data){
    int num=atoi(gtk_entry_get_text(GTK_ENTRY(E_delete)));
    FILE *fp=fopen("livre.dat","rb");
    FILE *fp_temp=fopen("livre_temp.dat","w+b");
    Livre temp;
    int found =0;
    if(!fp || !fp_temp) {
        dialog_window("\ncannot open files");
        exit(-1);
    }
    while (fread(&temp,sizeof(Livre),1,fp)==1){
        if(temp.num_liv==num) {found=1;continue;}
        fwrite(&temp,sizeof(Livre),1,fp_temp);
    }
    fclose(fp);
    fclose(fp_temp);
    if(found) dialog_window("\nSuppression reussite");
    else  dialog_window("\nLivre inexistant !");
    remove("livre.dat");
    rename("livre_temp.dat","livre.dat");
    gtk_window_close(GTK_WINDOW(d_window));
}

void sort_books(GtkButton *button , gpointer data){
    //Implement Bubble Sort
    FILE *fp=fopen("livre.dat","r+b");
    int swapped=1;
    while (swapped){
        rewind(fp);
        swapped=0;
        Livre temp1,temp2;
        fread(&temp1,sizeof(Livre),1,fp);
        fread(&temp2,sizeof(Livre),1,fp);
        while (!feof(fp)){
            if(strcmp(temp1.categ_liv,temp2.categ_liv)>0){
                swapped=1;
                unsigned long long int dep=-2*sizeof(Livre);
                fseek(fp,dep,SEEK_CUR);
                fwrite(&temp2,sizeof(Livre),1,fp);
                fwrite(&temp1,sizeof(Livre),1,fp);
            }
            else{
                temp1=temp2;
            }
            fread(&temp2,sizeof(Livre),1,fp);
        }
    }
    dialog_window("\nBooks Sorted Succefully !");
}

void search_book(GtkWidget *widget , gpointer data){
    s_builder=gtk_builder_new_from_file("livre.glade");
    search_window=GTK_WIDGET(gtk_builder_get_object(s_builder,"search_window"));
    E_search1=GTK_WIDGET(gtk_builder_get_object(s_builder,"E_search1"));
    E_search2=GTK_WIDGET(gtk_builder_get_object(s_builder,"E_search2"));
    btn_search=GTK_WIDGET(gtk_builder_get_object(s_builder,"btn_search"));

    g_signal_connect(btn_search,"clicked",G_CALLBACK(rechercher_livre),NULL);
    gtk_widget_show_all(search_window);
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
    g_signal_connect(btn_edit_book,"clicked",G_CALLBACK(edit_book),NULL);
    g_signal_connect(btn_delete_book,"clicked",G_CALLBACK(delete_book),NULL);
    g_signal_connect(btn_sort,"clicked",G_CALLBACK(sort_books),NULL);
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
