#ifndef LOANS_H
#define LOANS_H

typedef struct
{
    int id;
    char numeroEmprunt[19];
    int idUtilisateur;
    int idLivre;
    char dateEmprunt[11];
    char dateRetourPrevue[11];
    int etat;

} Emprunt;

void ajouterEmprunt(void);
void afficherEmprunts(void);
void rechercherEmprunt(void);
void modifierEmprunt(void);
void supprimerEmprunt(void);
void genererNumeroEmprunt(char numero[]);
int nombreEmpruntsUtilisateur(int idUtilisateur);

#endif



