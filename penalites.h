#ifndef PENALITES_H
#define PENALITES_H

typedef struct {
    int id;
    int idUtilisateur;
    char idEmprunt[20];
    int joursRetard;
    float montant;
    char date[11];
} Penalite;

float calculerPenalite(int joursRetard);
void sauvegarderPenalite(Penalite p);

#endif
