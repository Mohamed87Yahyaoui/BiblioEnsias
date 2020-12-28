#include "livre.h"
#include <stdlib.h>
#include <stdio.h>

Livre scan_livre(){
    Livre lv;
    printf("Numero: ");
    scanf("%d",&lv.num_liv);
    
    printf("\nTitre: ");
    scanf("%s",lv.titre_liv);
    
    printf("\nCatalogue: ");
    scanf("%s",lv.categ_liv);
    
    printf("\nNom de l'auteur: ");
    scanf("%s",lv.auteur_liv.nom_aut);
    
    printf("\nPrenom de l'auteur: ");
    scanf("%s",lv.auteur_liv.prenom_aut);
    
    printf("\nNumero d'adherant ayant emprunte le livre: ");
    scanf("%d",&lv.emprunteur_liv);

    return lv;
}

void print_livre(Livre lv){
    printf("Numero: %d",lv.num_liv);
    printf("\nTitre: %s",lv.titre_liv);
    printf("\nCatalogue: %s",lv.categ_liv);
    printf("\nNom de l'auteur: %s",lv.auteur_liv.nom_aut);
    printf("\nPrenom de l'auteur: %s",lv.auteur_liv.prenom_aut);
    printf("\nNumero d'adherant ayant emprunte le livre: %d",lv.emprunteur_liv);
}

void print_all(){
    FILE *pf=fopen("livre.dat","r+b");
    Livre temp;
    while (fread(&temp,sizeof(Livre),1,pf)==1){
        print_livre(temp);
    }
    fclose(pf);
}


void ajout_livre(){
    // mode ab pour ajouter a la fin du fichier binaire
    FILE *fin=fopen("livre.dat","ab");
    //lecture
    Livre lv=scan_livre();
    //ecriture
    fwrite(&lv,sizeof(Livre),1,fin);
}