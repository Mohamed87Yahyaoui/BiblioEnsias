#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "livre.h"

Livre scan_livre(){
    Livre lv;
    printf("Numero: ");
    scanf("%d%*c",&lv.num_liv);
    // le %*c est pour ignorer le caractere espace ('\n') que scanf laisse
    // pour que fgets ne le lit pas

    printf("\nTitre: ");
    fgets(lv.titre_liv,sizeof(lv.titre_liv),stdin);

    printf("\nCatalogue: ");
    fgets(lv.categ_liv,sizeof(lv.categ_liv),stdin);

    printf("\nNom de l'auteur: ");
    fgets(lv.auteur_liv.nom_aut,sizeof(lv.auteur_liv.nom_aut),stdin);

    printf("\nPrenom de l'auteur: ");
    fgets(lv.auteur_liv.prenom_aut,sizeof(lv.auteur_liv.nom_aut),stdin);

    printf("\nNumero d'adherant ayant emprunte le livre: ");
    scanf("%d",&lv.emprunteur_liv);

    return lv;
}

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

void ajout_livre(){
    // mode ab pour ajouter a la fin du fichier binaire
    FILE *fin=fopen("livre.bin","ab");
    if(!fin) {
        printf("cannot open file \n");
        exit(-1);
    }
    //lecture
    Livre lv=scan_livre();
    if(!livre_exist(lv)){
        //ecriture
        fwrite(&lv,sizeof(Livre),1,fin);
    }else printf("livre deja exist !\n");
    fclose(fin);
}



