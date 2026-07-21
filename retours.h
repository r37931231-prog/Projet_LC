#ifndef RETOURS_H
#define RETOURS_H

typedef struct {
    int idRetour;
    char idEmprunt[20];
    char dateRetour[11];
    char datePrevue[11];
    int joursRetard;
    float montant;
} Retour;

int calculerJoursRetard(char datePrevue[], char dateRetour[]);
void sauvegarderRetour(Retour r);
void traiterRetour(int idRetour, int idUtilisateur,  char idEmprunt[], char datePrevue[], char dateRetour[]);

#endif
