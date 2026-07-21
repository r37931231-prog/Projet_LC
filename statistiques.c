#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "statistiques.h"
#include "books.h"
#include "loans.h"
#include "reservations.h"
#include "retours.h"
#include "penalites.h"

int obtenirUtilisateurLePlusActif(void)
{
    Emprunt emp;
    int maxId = 0;

    FILE *f = fopen("DATABASE/LOANS.dat", "rb");
    if (!f)
        return -1;

    while (fread(&emp, sizeof(Emprunt), 1, f))
    {
        if (emp.idUtilisateur > maxId)
        {
            maxId = emp.idUtilisateur;
        }
    }

    if (maxId == 0)
    {
        fclose(f);
        return -1;
    }

    int *frequences = (int *)calloc(maxId + 1, sizeof(int));
    rewind(f);

    while (fread(&emp, sizeof(Emprunt), 1, f))
    {
        frequences[emp.idUtilisateur]++;
    }
    fclose(f);

    int idMaxActif = -1;
    int maxEmprunts = 0;
    for (int i = 1; i <= maxId; i++)
    {
        if (frequences[i] > maxEmprunts)
        {
            maxEmprunts = frequences[i];
            idMaxActif = i;
        }
    }

    free(frequences);
    return idMaxActif;
}

void obtenirLivreLePlusEmprunte(char titreDest[100])
{
    strcpy(titreDest, "Aucun emprunt");
    FILE *f = fopen("DATABASE/LOANS.dat", "rb");
    if (!f)
        return;

    Emprunt emp;
    int maxId = 0;

    while (fread(&emp, sizeof(Emprunt), 1, f))
    {
        if (emp.idLivre > maxId)
            maxId = emp.idLivre;
    }

    if (maxId == 0)
    {
        fclose(f);
        return;
    }

    int *frequences = (int *)calloc(maxId + 1, sizeof(int));
    rewind(f);

    while (fread(&emp, sizeof(Emprunt), 1, f))
    {
        frequences[emp.idLivre]++;
    }
    fclose(f);

    int idLivreMax = -1;
    int maxFreq = 0;
    for (int i = 1; i <= maxId; i++)
    {
        if (frequences[i] > maxFreq)
        {
            maxFreq = frequences[i];
            idLivreMax = i;
        }
    }
    free(frequences);

    if (idLivreMax != -1)
    {
        FILE *fBook = fopen("DATABASE/BOOKS.dat", "rb");
        if (fBook)
        {
            Livre liv;
            while (fread(&liv, sizeof(Livre), 1, fBook))
            {
                if (liv.id == idLivreMax)
                {
                    strcpy(titreDest, liv.titre);
                    break;
                }
            }
            fclose(fBook);
        }
    }
}

void afficherStatistiquesGlobales(void)
{
    FILE *f;
    int totalLivres = 0, totalDispo = 0, totalUsers = 0;
    int totalEmprunts = 0, totalReservations = 0;
    float cumulPenalites = 0;

    f = fopen("DATABASE/BOOKS.dat", "rb");
    if (f)
    {
        Livre L;
        while (fread(&L, sizeof(Livre), 1, f))
        {
            totalLivres += L.totalExemplaires;
            totalDispo += L.disponibles;
        }
        fclose(f);
    }

    f = fopen(FILE_USERS, "rb");
    if (f)
    {
        Utilisateur U;
        while (fread(&U, sizeof(Utilisateur), 1, f))
            totalUsers++;
        fclose(f);
    }

    f = fopen("DATABASE/LOANS.dat", "rb");
    if (f)
    {
        Emprunt E;
        while (fread(&E, sizeof(Emprunt), 1, f))
            totalEmprunts++;
        fclose(f);
    }

    f = fopen("DATABASE/RESERVATIONS.dat", "rb");
    if (f)
    {
        Reservation R;
        while (fread(&R, sizeof(Reservation), 1, f))
            totalReservations++;
        fclose(f);
    }

    f = fopen("DATABASE/PENALTIES.dat", "rb");
    if (f)
    {
        Penalite P;
        while (fread(&P, sizeof(Penalite), 1, f))
            cumulPenalites += P.montant;
        fclose(f);
    }

    char livreTop[100];
    obtenirLivreLePlusEmprunte(livreTop);
    int userTop = obtenirUtilisateurLePlusActif();

    printf("\n============================================\n");
    printf("        TABLEAU DE BORD STATISTIQUE         \n");
    printf("============================================\n");
    printf("Nombre total d'utilisateurs  : %d\n", totalUsers);
    printf("Livres totaux en stock       : %d\n", totalLivres);
    printf("Livres physiques disponibles  : %d\n", totalDispo);
    printf("Volume total d'emprunts       : %d\n", totalEmprunts);
    printf("Nombre total de reservations  : %d\n", totalReservations);
    printf("Montant cumule des penalites  : %.2f FCFA\n", cumulPenalites);
    printf("Livre le plus populaire      : %s\n", livreTop);
    if (userTop != -1)
        printf("Lecteur le plus actif (ID)    : %d\n", userTop);
    else
        printf("Lecteur le plus actif (ID)    : Aucun\n");
    printf("============================================\n");
}

void genererRapportJournalier(time_t dateDuJour)
{
    struct tm *tm_info = localtime(&dateDuJour);
    if (!tm_info) return;
    struct tm target_tm = *tm_info;

    char dateAffichage[20];
    char dateClean[20];

    strftime(dateAffichage, sizeof(dateAffichage), "%d/%m/%Y", tm_info);
    strftime(dateClean, sizeof(dateClean), "%Y%m%d", tm_info);

    char cheminFichier[100];
    sprintf(cheminFichier, "REPORTS/DAILY/REPORT_%s.txt", dateClean);

#ifdef _WIN32
    system("mkdir REPORTS\\DAILY > nul 2>&1");
#else
    system("mkdir -p REPORTS/DAILY > /dev/null 2>&1");
#endif

    FILE *fRapport = fopen(cheminFichier, "w");
    if (!fRapport)
    {
        printf("Erreur : Impossible de creer le rapport au chemin %s\n", cheminFichier);
        return;
    }

    int empJour = 0, retJour = 0, resJour = 0, userJour = 0, penJour = 0;
    float montPenJour = 0;

    FILE *f;
    f = fopen("DATABASE/LOANS.dat", "rb");
    if (f)
    {
        Emprunt E;
        while (fread(&E, sizeof(Emprunt), 1, f))
        {
            int j, m, a;
            if (sscanf(E.dateEmprunt, "%d/%d/%d", &j, &m, &a) == 3)
            {
                if (j == tm_info->tm_mday && (m - 1) == tm_info->tm_mon && (a - 1900) == tm_info->tm_year)
                    empJour++;
            }
        }
        fclose(f);
    }

    f = fopen("DATABASE/RESERVATIONS.dat", "rb");
    if (f)
    {
        Reservation R;
        while (fread(&R, sizeof(Reservation), 1, f))
        {
            int j, m, a;
            if (sscanf(R.dateReservation, "%d/%d/%d", &j, &m, &a) == 3)
            {
                if (j == tm_info->tm_mday && (m - 1) == tm_info->tm_mon && (a - 1900) == tm_info->tm_year)
                    resJour++;
            }
        }
        fclose(f);
    }

    f = fopen("DATABASE/PENALTIES.dat", "rb");
    if (f)
    {
        Penalite P;
        while (fread(&P, sizeof(Penalite), 1, f))
        {
            int j, m, a;
            if (sscanf(P.date, "%d/%d/%d", &j, &m, &a) == 3)
            {
                if (j == tm_info->tm_mday && (m - 1) == tm_info->tm_mon && (a - 1900) == tm_info->tm_year)
                {
                    penJour++;
                    montPenJour += P.montant;
                }
            }
        }
        fclose(f);
    }

    f = fopen(FILE_USERS, "rb");
    if (f)
    {
        Utilisateur U;
        while (fread(&U, sizeof(Utilisateur), 1, f))
        {
            struct tm *tm_user = localtime(&U.date_creation);
            if (tm_user && tm_user->tm_mday == tm_info->tm_mday &&
                tm_user->tm_mon == tm_info->tm_mon &&
                tm_user->tm_year == tm_info->tm_year)
            {
                userJour++;
            }
        }
        fclose(f);
    }

    char livreTop[100];
    obtenirLivreLePlusEmprunte(livreTop);
    int userTop = obtenirUtilisateurLePlusActif();

    fprintf(fRapport, "==================================================\n");
    fprintf(fRapport, "          ETAT JOURNALIER - DATE : %s             \n", dateAffichage);
    fprintf(fRapport, "==================================================\n");
    fprintf(fRapport, "• Nombre d'emprunts            : %d\n", empJour);
    fprintf(fRapport, "• Nombre de retours            : %d\n", retJour);
    fprintf(fRapport, "• Nombre de reservations       : %d\n", resJour);
    fprintf(fRapport, "• Nombre de nouveaux utilisateurs: %d\n", userJour);
    fprintf(fRapport, "• Nombre de penalites          : %d\n", penJour);
    fprintf(fRapport, "• Montant total des penalites  : %.2f FCFA\n", montPenJour);
    fprintf(fRapport, "• Livre le plus emprunte       : %s\n", livreTop);
    if (userTop != -1)
        fprintf(fRapport, "• Utilisateur le plus actif    : ID %d\n", userTop);
    else
        fprintf(fRapport, "• Utilisateur le plus actif    : Aucun\n");
    fprintf(fRapport, "==================================================\n");

    fclose(fRapport);
    printf("Rapport journalier enregistre avec succes dans : %s\n", cheminFichier);
}
