#ifndef BOOKS_H
#define BOOKS_H

typedef struct
{
    int id;
    char isbn[20];
    char titre[100];
    int idAuteur;
    int idCategorie;
    char editeur[50];
    int anneePublication;
    char langue[30];
    int nbPages;
    int totalExemplaires;
    int disponibles;
    char emplacement[30];
    char resume[300];
    char dateAjout[20];

} Livre;

void ajouterLivre(void);
void afficherLivres(void);
void rechercherLivre(void);
void modifierLivre(void);
void supprimerLivre(void);
int genererIdLivre(void);

#endif
