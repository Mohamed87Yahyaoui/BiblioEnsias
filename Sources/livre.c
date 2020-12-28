#include <livre.h>
#include <stdlib.h>
#include <stdio.h>

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
    printf("Numero: %d\n",lv.num_liv);
    printf("Titre: %s\n",lv.titre_liv);
    printf("Catalogue: %s\n",lv.categ_liv);
    printf("Nom de l'auteur: %s\n",lv.auteur_liv.nom_aut);
    printf("Prenom de l'auteur: %s\n",lv.auteur_liv.prenom_aut);
    printf("Numero d'adherant ayant emprunte le livre: %d\n",lv.emprunteur_liv);
}

void print_all(){
    FILE *pf=fopen("livre.dat","rb");
    if(!pf) {
        printf("cannot open file \n");
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


void ajout_livre(){
    // mode ab pour ajouter a la fin du fichier binaire
    FILE *fin=fopen("livre.dat","ab");
    if(!fin) {
        printf("cannot open file \n");
        exit(-1);
    }
    //lecture
    Livre lv=scan_livre();
    //ecriture
    fwrite(&lv,sizeof(Livre),1,fin);
    fclose(fin);
}
