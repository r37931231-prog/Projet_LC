#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservations.h"
#include "books.h"

int genererIdReservation(void)
{
    FILE *f;
    Reservation res;
    int dernierId = 0;

    f = fopen("DATABASE/RESERVATIONS.dat", "rb");
    if (f == NULL)
    {
        return 1;
    }

    while (fread(&res, sizeof(Reservation), 1, f))
    {
        dernierId = res.id;
    }

    fclose(f);
    return dernierId + 1;
}

void ajouterReservation(void)
{
    Reservation res;
    Livre livre;
    FILE *fRes, *fBook;
    int livreTrouve = 0;

    printf("\n=== NOUVELLE RESERVATION ===\n");
    printf("Entrer l'ID du lecteur (utilisateur) : ");
    scanf("%d", &res.idUtilisateur);

    printf("Entrer l'ID du livre a reserver : ");
    scanf("%d", &res.idLivre);


    fBook = fopen("DATABASE/BOOKS.dat", "rb");
    if (fBook == NULL)
    {
        printf("Erreur : Impossible d'acceder a la base des livres.\n");
        return;
    }

    while (fread(&livre, sizeof(Livre), 1, fBook))
    {
        if (livre.id == res.idLivre)
        {
            livreTrouve = 1;
            if (livre.disponibles > 0)
            {
                printf("Impossible de reserver : il reste %d exemplaire(s) disponible(s) en rayon.\n", livre.disponibles);
                fclose(fBook);
                return;
            }
            break;
        }
    }
    fclose(fBook);

    if (!livreTrouve)
    {
        printf("Erreur : Aucun livre ne possede cet ID.\n");
        return;
    }

    res.id = genererIdReservation();
    printf("ID Reservation genere : %d\n", res.id);

    printf("Entrer la date de reservation (JJ/MM/AAAA) : ");
    scanf("%19s", res.dateReservation);

    res.etat = EN_ATTENTE;

    fRes = fopen("DATABASE/RESERVATIONS.dat", "ab");
    if (fRes == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier RESERVATIONS.dat.\n");
        return;
    }

    fwrite(&res, sizeof(Reservation), 1, fRes);
    fclose(fRes);

    printf("Reservation enregistree avec succes sous l'etat 'EN_ATTENTE' !\n");
}

void afficherReservations(void)
{
    Reservation res;
    FILE *f;

    f = fopen("DATABASE/RESERVATIONS.dat", "rb");
    if (f == NULL)
    {
        printf("Aucune reservation enregistree pour le moment.\n");
        return;
    }

    printf("\n===== LISTE DES RESERVATIONS =====\n");
    while (fread(&res, sizeof(Reservation), 1, f))
    {
        printf("\nID Reservation : %d", res.id);
        printf("\nID Utilisateur : %d", res.idUtilisateur);
        printf("\nID Livre       : %d", res.idLivre);
        printf("\nDate           : %s", res.dateReservation);

        printf("\nEtat           : ");
        switch (res.etat)
        {
            case EN_ATTENTE:  printf("EN_ATTENTE"); break;
            case DISPONIBLE:  printf("DISPONIBLE"); break;
            case ANNULEE:     printf("ANNULEE"); break;
        }
        printf("\n----------------------------------");
    }
    fclose(f);
}

void annulerReservation(void)
{
    Reservation res;
    FILE *f;
    int idRecherche;
    int trouve = 0;

    f = fopen("DATABASE/RESERVATIONS.dat", "rb+");
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier des reservations.\n");
        return;
    }

    printf("Entrer l'ID de la reservation a annuler : ");
    scanf("%d", &idRecherche);

    while (fread(&res, sizeof(Reservation), 1, f))
    {
        if (res.id == idRecherche)
        {
            trouve = 1;
            if (res.etat == ANNULEE)
            {
                printf("Cette reservation est deja annulee.\n");
            }
            else
            {
                res.etat = ANNULEE;
                fseek(f, -sizeof(Reservation), SEEK_CUR);
                fwrite(&res, sizeof(Reservation), 1, f);
                printf("La reservation ID %d a ete annulee avec succes !\n", idRecherche);
            }
            break;
        }
    }
    if (!trouve)
    {
        printf("Reservation introuvable.\n");
    }

    fclose(f);
}

void verifierEtMettreAJourReservation(int idLivre)
{
    Reservation res;
    FILE *f;
    int miseAJourFaite = 0;

    f = fopen("DATABASE/RESERVATIONS.dat", "rb+");
    if (f == NULL)
    {
        return;
    }
    while (fread(&res, sizeof(Reservation), 1, f))
    {
        if (res.idLivre == idLivre && res.etat == EN_ATTENTE)
        {
            res.etat = DISPONIBLE;

            fseek(f, -sizeof(Reservation), SEEK_CUR);
            fwrite(&res, sizeof(Reservation), 1, f);

            printf("\n[NOTIF RESERVATION] Le livre ID %d est maintenant DISPONIBLE pour l'utilisateur ID %d !\n",
                   res.idLivre, res.idUtilisateur);

            miseAJourFaite = 1;
            break;
        }
    }

    fclose(f);
}
