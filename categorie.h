#ifndef CATEGORIE_H
#define CATEGORIE_H

#define MAX_CATEGORIES 10000
#define FICHIER_CATEGORIES "DATABASE/CATEGORIES.dat"

typedef struct {
    int id;
    char libelle[50];
    char description[200];
    char dateCreation[11];
} Categorie;

extern Categorie listeCategories[MAX_CATEGORIES];
extern int nombreCategories;

void chargerCategories(void);
void sauvegarderCategories(void);
void ajouterCategorie(void);
void afficherCategories(void);
void supprimerCategorie(void);
int categorieExiste(int id);

#endif
