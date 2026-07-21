#ifndef RESERVATIONS_H
#define RESERVATIONS_H

typedef enum {
    EN_ATTENTE,
    DISPONIBLE,
    ANNULEE
} EtatReservation;

typedef struct {
    int id;
    int idUtilisateur;
    int idLivre;
    char dateReservation[20];
    EtatReservation etat;
} Reservation;

void ajouterReservation(void);
void afficherReservations(void);
void annulerReservation(void);
void verifierEtMettreAJourReservation(int idLivre);
int genererIdReservation(void);

#endif
