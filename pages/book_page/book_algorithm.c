#include "book.h"
#include "book_algorithm.h"

void rechercher_livre_algo(const char *titre,const char *categorie){
    FILE *fp=fopen("livre.dat","rb");
    Livre temp;
    while (fread(&temp,sizeof(Livre),1,fp)==1){
        if(!strcmp(temp.titre_liv,titre) && !strcmp(temp.categ_liv,categorie) ){
            print_book_window(temp);
            return ;
        }
    }
    dialog_window("\nLivre Inexistant");
}