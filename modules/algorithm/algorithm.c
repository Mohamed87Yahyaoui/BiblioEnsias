#include<stdlib.h>
#include "book.h"
#include "adherent.h"
#include "algorithm.h"

/*---------------ALGORITHM DE GESTION DE LIVRE------------------- */

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

void ajouter_livre_algo(Livre lv){
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
}


void modifier_livre_algo(Livre lv){
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
}


void supprimer_livre_algo(int num){
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
}

void ordonner_livre_algo(){
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
    dialog_window("\nLivre Ordonne avec success !");
}


/*---------------ALGORITHM DE GESTION D'EMPRUNT ------------------- */

void emprunter_livre_algo(int num_lv,int num_adh){
    Livre temp_book;
    adherent temp_adh;
    FILE *fp_book;
    FILE *fp_adh;
    int pos=0;
    
    //CHECK num_adh is VALID AND CHECK IF nbre_emprunts_adh<3
    int FOUND_ADH=0;
    int FOUND_BOOK=0; 
    int CAN_BORROW=1;
    int ALREADY_BORROWED=0;
    fp_adh=fopen("adherent.dat","r+b");
    while (fread(&temp_adh,sizeof(adherent),1,fp_adh)==1){
        pos++;
        if(temp_adh.num_adh==num_adh){
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
            if(temp_book.num_liv==num_lv){
                FOUND_BOOK=1;
                if(temp_book.emprunteur_liv!=-1){
                    ALREADY_BORROWED=1;
                    dialog_window("\nLivre déja emprunté !");
                }else{
                    temp_book.emprunteur_liv=num_adh;
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
}

void rendre_livre_algo(int num_lv,int num_adh){
    Livre temp_book;
    adherent temp_adh;
    FILE *fp_book;
    FILE *fp_adh;
    int pos=0;
    //CHECK num_adh is VALID AND CHECK IF nbre_emprunts_adh<4
    int FOUND_ADH=0;
    int FOUND_BOOK=0; 
    int CAN_RETURN=1;
    fp_adh=fopen("adherent.dat","r+b");
    while (fread(&temp_adh,sizeof(adherent),1,fp_adh)==1){
        pos++;
        if(temp_adh.num_adh==num_adh){
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
            if(temp_book.num_liv==num_lv){
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
}



/*---------------ALGORITHM DE GESTION DES ADHERENTS ------------------- */


void rechercher_adherent_algo(const char *name){
    adherent adh1;
    strcpy(adh1.nom_adh,name);
    int found=0;
    FILE* f=fopen("adherent.dat","rb");

    adherent ad;
    while(fread(&ad,sizeof(adherent),1,f))
    {
        if(!strcmp(adh1.nom_adh,ad.nom_adh))
        {
            found=1;
            print_adh_window(ad);
            break;
        }
    }

    if(!found)
    {
        dialog_window("adherent innexistant");
    }
}


void ajouter_adherent_algo(adherent adh){
    adherent temp=adh;
// mode ab pour ajouter a la fin du fichier binaire
    FILE *fin=fopen("adherent.dat","ab");
    if(!fin) {
        printf("cannot open file \n");
        exit(-1);
    }
    if(!adh_exist(temp)){
        //ecriture
        fwrite(&temp,sizeof(adherent),1,fin);
        dialog_window("Adherent est ajoute avec succes");
    }else dialog_window("adherent deja exist !");
    fclose(fin);
}


void modifier_adherent_algo(adherent adh){
    adherent adh1;
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
}


void supprimer_adherent_algo(int num){
    FILE* ftemp;
    adherent adh1;
    adherent adh2;

    adh1.num_adh=num;

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
}


