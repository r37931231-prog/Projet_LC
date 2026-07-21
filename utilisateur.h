#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <time.h>

#define LOGIN_LEN 6
#define Default_Password "Library123"
#define FILE_USERS "DATABASE/USERS.dat"
#define FILE_HISTORY "REPORTS/HISTORY.txt"


typedef enum {
    ADMIN,
    USER
} Role;

typedef enum {
    ACTIF,
    BLOQUE
} Etat;


typedef struct {
    int id;
    char nom[50];
    char prenom[50];
    char adresse[100];
    char telephone[20];
    char email[80];
    char login[LOGIN_LEN + 1];
    char mot_de_passe[64];
    Role role;
    Etat etat;
    time_t date_creation;
    time_t date_derniere_connexion;
} Utilisateur;


void crypter_decryptage_xor(char *mot_de_passe, char *cle);

void ecrire_historique(const char *login, const char *operation);

void initialiser_systeme();

void saisir_chaine(char *chaine, int taille);

void ajouter_utilisateur();

int connexion_utilisateur();

void changer_mot_de_passe(int id_utilisateur);

void lister_utilisateurs();

void changer_etat_utilisateur();

#endif
