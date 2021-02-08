#ifndef ALGORITHM_H_INCLUDED
#define ALGORITHM_H_INCLUDED

#include "book.h"
#include "adherent.h"

void rechercher_livre_algo(const char *,const char *);
void ajouter_livre_algo(Livre);
void modifier_livre_algo(Livre);
void supprimer_livre_algo(int);
void ordonner_livre_algo();


void emprunter_livre_algo(int , int);
void rendre_livre_algo(int , int);


void ajouter_adherent_algo(adherent);
void supprimer_adherent_algo(int);
void rechercher_adherent_algo(const char *);
void modifier_adherent_algo(adherent);




#endif
