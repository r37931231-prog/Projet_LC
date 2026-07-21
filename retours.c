#include <stdio.h>
#include <string.h>
#include "retours.h"
#include "penalites.h"

int calculerJoursRetard(char datePrevue[], char dateRetour[]) {
    int anP, moiP, jourP;
    int anR, moiR, jourR;

    sscanf(datePrevue, "%d-%d-%d", &anP, &moiP, &jourP);
    sscanf(dateRetour, "%d-%d-%d", &anR, &moiR, &jourR);

    int joursP = anP * 360 + moiP * 30 + jourP;
    int joursR = anR * 360 + moiR * 30 + jourR;

    int retard = joursR - joursP;
    if (retard < 0) retard = 0;

    return retard;
}

void sauvegarderRetour(Retour r) {
    FILE *f = fopen("DATABASE/RETURNS.dat", "a");
    if (f == NULL) {
        printf("Erreur ouverture fichier retours\n");
        return;
    }
    fprintf(f, "%d;%s;%s;%d;%.2f\n", r.idRetour, r.idEmprunt, r.dateRetour, r.joursRetard, r.montant);
    fclose(f);
}

void traiterRetour(int idRetour, int idUtilisateur, char idEmprunt[], char datePrevue[], char dateRetour[]) {

    int retard = calculerJoursRetard(datePrevue, dateRetour);
    float penalite = calculerPenalite(retard);

    Retour r;
    r.idRetour = idRetour;
    strcpy(r.idEmprunt , idEmprunt);
    strcpy(r.dateRetour, dateRetour);
    r.joursRetard = retard;
    r.montant = penalite;
    sauvegarderRetour(r);

    if (retard > 0) {
        Penalite p;
        p.id = idRetour;
        p.idUtilisateur = idUtilisateur;
        strcpy(p.idEmprunt , idEmprunt);
        p.joursRetard = retard;
        p.montant = penalite;
        strcpy(p.date, dateRetour);
        sauvegarderPenalite(p);
    }

    printf("Retour enregistre. Retard: %d jour(s). Penalite: %.2f FCFA\n", retard, penalite);
}
