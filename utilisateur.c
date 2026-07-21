#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <direct.h>
#include "utilisateur.h"

void initialiser_systeme() {
    _mkdir("DATABASE");
    _mkdir("REPORTS");

    fclose(fopen(FILE_USERS, "ab"));
    fclose(fopen(FILE_HISTORY, "a"));
}

void saisir_chaine(char *chaine, int taille) {
    fgets(chaine, taille, stdin);
    chaine[strcspn(chaine, "\n")] = '\0';
}


void crypter_decryptage_xor(char *mot_de_passe, char *cle) {
    int len_mdp = strlen(mot_de_passe);
    int len_cle = strlen(cle);
    for (int i = 0; i < len_mdp; i++) {
        mot_de_passe[i] = mot_de_passe[i] ^ cle[i % len_cle];
    }
}

void ecrire_historique(const char *login, const char *operation) {
    FILE *f = fopen(FILE_HISTORY, "a");
    if (f != NULL) {
        fprintf(f, "[%s] � %s\n", login, operation);
        fclose(f);
    }
}

int login_existe_deja(const char *login) {
    FILE *f = fopen(FILE_USERS, "rb");
    if (f == NULL) return 0;

    Utilisateur u;
    while (fread(&u, sizeof(Utilisateur), 1, f) == 1) {
        if (strcmp(u.login, login) == 0) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int login_est_valide(const char *login) {
    if (strlen(login) != LOGIN_LEN) return 0;
    for (int i = 0; i < LOGIN_LEN; i++) {
        if (!isupper((unsigned char)login[i])) return 0;
    }
    return 1;
}

void ajouter_utilisateur() {
    Utilisateur nouvel_util;
    FILE *f = fopen(FILE_USERS, "ab+");
    if (f == NULL) return;

    int nouvel_id = 1;
    Utilisateur temporaire;
    while (fread(&temporaire, sizeof(Utilisateur), 1, f) == 1) {
        nouvel_id = temporaire.id + 1;
    }
    nouvel_util.id = nouvel_id;

    printf("\n=== INSCRIPTION ===\n");
    printf("Nom : "); saisir_chaine(nouvel_util.nom, 50);
    printf("Prenom : "); saisir_chaine(nouvel_util.prenom, 50);
    printf("Adresse : "); saisir_chaine(nouvel_util.adresse, 100);
    printf("Telephone : "); saisir_chaine(nouvel_util.telephone, 20);
    printf("E-mail : "); saisir_chaine(nouvel_util.email, 80);

    do {
        printf("Login (6 MAJUSCULES) : ");
        saisir_chaine(nouvel_util.login, LOGIN_LEN + 1);
    } while (!login_est_valide(nouvel_util.login) || login_existe_deja(nouvel_util.login));

    printf("R�le (0 = ADMIN, 1 = USER) : ");
    int choix_role;
    scanf("%d", &choix_role);
    getchar();
    nouvel_util.role = (choix_role == 0) ? ADMIN : USER;
    nouvel_util.etat = ACTIF;
    nouvel_util.date_creation = time(NULL);
    nouvel_util.date_derniere_connexion = 0;

    strcpy(nouvel_util.mot_de_passe, "Library123");
    crypter_decryptage_xor(nouvel_util.mot_de_passe, "CLE_SECRETE_BIBLIO");

    fwrite(&nouvel_util, sizeof(Utilisateur), 1, f);
    fclose(f);

    printf("\nSucc�s : Utilisateur %s cr�� !\n", nouvel_util.login);
    ecrire_historique("SYSTEM", "Compte cree");
}


int connexion_utilisateur() {
    char login_saisi[30], mdp_saisi[64];

    printf("\n=== CONNEXION ===\n");
    printf("Login : "); saisir_chaine(login_saisi, 30);
    printf("Mot de passe : "); saisir_chaine(mdp_saisi, 64);

    FILE *f = fopen(FILE_USERS, "rb");
    if (f == NULL) return -1;

    Utilisateur u;
    int trouve = 0;

    while (fread(&u, sizeof(Utilisateur), 1, f) == 1) {
        if (strcmp(u.login, login_saisi) == 0) {
            char mdp_crypte[64];
            strcpy(mdp_crypte, mdp_saisi);
            crypter_decryptage_xor(mdp_crypte, "CLE_SECRETE_BIBLIO");

            if (strcmp(u.mot_de_passe, mdp_crypte) == 0) {
                trouve = 1;
                break;
            }
        }
    }
    fclose(f);

    if (trouve && u.etat == ACTIF) {
        printf("\nBienvenue %s !\n", u.prenom);
        return u.id;
    } else {
        printf("Erreur : Connexion refus�e (Identifiants faux ou compte bloqu�).\n");
        return -1;
    }
}

void lister_utilisateurs() {
    FILE *f = fopen(FILE_USERS, "rb");
    if (f == NULL) return;

    Utilisateur u;
    printf("\nID   | NOM             | PRENOM          | LOGIN\n");
    printf("------------------------------------------------\n");
    while (fread(&u, sizeof(Utilisateur), 1, f) == 1) {
        printf("%-4d | %-15s | %-15s | %-10s (%s)\n",
               u.id, u.nom, u.prenom, u.login, (u.etat == ACTIF) ? "ACTIF" : "BLOQUE");
    }
    fclose(f);
}

void changer_etat_utilisateur() {
    int id_cible;
    printf("\nID � modifier : ");
    scanf("%d", &id_cible);
    getchar();

    FILE *f_origine = fopen(FILE_USERS, "rb");
    FILE *f_temp = fopen("DATABASE/TEMP.dat", "wb");
    if (f_origine == NULL || f_temp == NULL) return;

    Utilisateur u;
    while (fread(&u, sizeof(Utilisateur), 1, f_origine) == 1) {
        if (u.id == id_cible) {
            u.etat = (u.etat == ACTIF) ? BLOQUE : ACTIF;
            printf("Nouvel �tat appliqu� pour l'ID %d !\n", id_cible);
        }
        fwrite(&u, sizeof(Utilisateur), 1, f_temp);
    }

    fclose(f_origine);
    fclose(f_temp);

    remove(FILE_USERS);
    rename("DATABASE/TEMP.dat", FILE_USERS);
}
