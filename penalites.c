#include <stdio.h>
#include <string.h>
#include "penalites.h"

float calculerPenalite(int joursRetard) {
    return joursRetard * 500;
}

void sauvegarderPenalite(Penalite p) {
    FILE *f = fopen("DATABASE/PENALTIES.dat", "a");
    if (f == NULL) {
        printf("Erreur ouverture fichier penalites\n");
        return;
    }
    fprintf(f, "%d;%d;%s;%d;%.2f;%s\n", p.id, p.idUtilisateur, p.idEmprunt, p.joursRetard, p.montant, p.date);
    fclose(f);
}
