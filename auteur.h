#ifndef AUTEUR_H
#define AUTEUR_H

#define MAX_AUTEURS 10000
#define FICHIER_AUTEURS "DATABASE/AUTHORS.dat"

typedef struct {
    int id;
    char nomComplet[100];
    char nationalite[50];
    char dateNaissance[11];
    char biographie[1000];
    int nombreLivresPublies;
} Auteur;

extern Auteur listeAuteurs[MAX_AUTEURS];
extern int nombreAuteurs;

void chargerAuteurs(void);
void sauvegarderAuteurs(void);
void ajouterAuteur(void);
void afficherAuteurs(void);
void supprimerAuteur(void);
int auteurExiste(int id);

#endif

