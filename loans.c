#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "loans.h"

void genererNumeroEmprunt(char numero[])
{
    time_t t = time(NULL);
    struct tm *date = localtime(&t);

    sprintf(numero,
            "EMP_%04d%02d%02d%02d%02d%02d",
            date->tm_year + 1900,
            date->tm_mon + 1,
            date->tm_mday,
            date->tm_hour,
            date->tm_min,
            date->tm_sec);
}

int nombreEmpruntsUtilisateur(int idUtilisateur)
{
    Emprunt emprunt;
    FILE *f;
    int compteur = 0;

    f = fopen("LOANS.dat", "rb");

    if(f == NULL)
        return 0;

    while(fread(&emprunt, sizeof(Emprunt), 1, f))
    {

        if(emprunt.idUtilisateur == idUtilisateur &&
           emprunt.etat == 0){

                compteur++;
        }
    }

    fclose(f);
    return compteur;
}

void ajouterEmprunt()
{
    Emprunt emprunt;
    FILE *f;

    f = fopen("LOANS.dat", "ab");

    if(f == NULL)
    {
        printf("Erreur d'ouverture du fichier !");
        return;
    }

    printf("Entrer l'id de l'emprunt : ");
    scanf("%d", &emprunt.id);

    genererNumeroEmprunt(emprunt.numeroEmprunt);
    printf("Numero d'emprunt : %s\n", emprunt.numeroEmprunt);

    printf("Entrer l'id du livre : ");
    scanf("%d", &emprunt.idLivre);

    printf("Entrer l'id de l'utilisateur : ");
    scanf("%d", &emprunt.idUtilisateur);

    if(nombreEmpruntsUtilisateur(emprunt.idUtilisateur) >= 3)
    {
        printf("Erreur : cet utilisateur a deja atteint la limite de 3 emprunts.\n");
        fclose(f);
        return;
    }

    printf("Entrer la date d'emprunt (JJ/MM/AAAA) : ");
    scanf("%s", emprunt.dateEmprunt);

    printf("Entrer la date de retour (JJ/MM/AAAA) : ");
    scanf("%s", emprunt.dateRetourPrevue);

    int duree;

    printf("Entrer la duree de l'emprunt (en jours) : ");
    scanf("%d", &duree);

    if(duree > 14)
    {
        printf("Erreur : la duree maximale d'un emprunt est de 14 jours.\n");
        fclose(f);
        return;
    }

    printf("Etat (0 = en cours, 1 = retourne, 2=retard) : ");
    scanf("%d", &emprunt.etat);

    fwrite(&emprunt, sizeof(Emprunt), 1, f);

    fclose(f);

    printf("Emprunt ajoute avec succes !\n");
}

void afficherEmprunts()
{
    Emprunt emprunt;
    FILE *f;

    f = fopen("LOANS.dat", "rb");

    if(f == NULL)
    {
        printf("Erreur d'ouverture du fichier !");
        return;
    }

    printf("\n===== LISTE DES EMPRUNTS =====\n");

    while(fread(&emprunt, sizeof(Emprunt), 1, f))
    {
        printf("\nID Emprunt : %d", emprunt.id);
        printf("\nID Livre : %d", emprunt.idLivre);
        printf("\nID Utilisateur : %d", emprunt.idUtilisateur);
        printf("\nDate emprunt : %s", emprunt.dateEmprunt);
        printf("\nDate retour : %s", emprunt.dateRetourPrevue);

        printf("\nEtat : %d", emprunt.etat);

        printf("\n-----------------------------\n");
    }

    fclose(f);
}


void rechercherEmprunt()
{
    Emprunt emprunt;
    FILE *f;
    int id;
    int trouve = 0;

    f = fopen("LOANS.dat", "rb");

    if(f == NULL)
    {
        printf("Erreur d'ouverture du fichier !");
        return;
    }

    printf("Entrer l'id de l'emprunt a rechercher : ");
    scanf("%d", &id);

    while(fread(&emprunt, sizeof(Emprunt), 1, f))
    {
        if(emprunt.id == id)
        {
            printf("\n===== EMPRUNT TROUVE =====\n");

            printf("ID Emprunt : %d\n", emprunt.id);
            printf("ID Livre : %d\n", emprunt.idLivre);
            printf("ID Utilisateur : %d\n", emprunt.idUtilisateur);
            printf("Date emprunt : %s\n", emprunt.dateEmprunt);
            printf("Date retour : %s\n", emprunt.dateRetourPrevue);

            if(emprunt.etat == 0)
            {
                printf("Etat : En cours\n");
            }
            else
                if(emprunt.etat == 1)
            {
                printf("Etat : Retourne\n");
            }
            else{
                printf("Etat : Retard\n");
            }

            trouve = 1;
            break;
        }
    }

    if(trouve == 0)
    {
        printf("Emprunt introuvable !\n");
    }

    fclose(f);
}


void modifierEmprunt()
{
    Emprunt emprunt;
    FILE *f;
    int id;
    int trouve = 0;

    f = fopen("LOANS.dat", "rb+");

    if(f == NULL)
    {
        printf("Erreur d'ouverture du fichier !");
        return;
    }

    printf("Entrer l'id de l'emprunt a modifier : ");
    scanf("%d", &id);

    while(fread(&emprunt, sizeof(Emprunt), 1, f))
    {
        if(emprunt.id == id)
        {
            printf("\nEmprunt trouve !\n");

            printf("Nouvel id du livre : ");
            scanf("%d", &emprunt.idLivre);

            printf("Nouvel id de l'utilisateur : ");
            scanf("%d", &emprunt.idUtilisateur);

            printf("Nouvelle date d'emprunt : ");
            scanf("%s", emprunt.dateEmprunt);

            printf("Nouvelle date de retour : ");
            scanf("%s", emprunt.dateRetourPrevue);

            printf("Nouveau etat (0 = en cours, 1 = retourne) : ");
            scanf("%d", &emprunt.etat);

            fseek(f, -sizeof(Emprunt), SEEK_CUR);

            fwrite(&emprunt, sizeof(Emprunt), 1, f);

            trouve = 1;

            printf("Emprunt modifie avec succes !\n");

            break;
        }
    }

    if(trouve == 0)
    {
        printf("Emprunt introuvable !\n");
    }

    fclose(f);
}


void supprimerEmprunt()
{
    Emprunt emprunt;
    FILE *f;
    FILE *temp;

    int id;
    int trouve = 0;

    f = fopen("LOANS.dat", "rb");

    if(f == NULL)
    {
        printf("Erreur d'ouverture du fichier !");
        return;
    }

    temp = fopen("TEMP.dat", "wb");

    if(temp == NULL)
    {
        printf("Erreur de creation du fichier temporaire !");
        fclose(f);
        return;
    }

    printf("Entrer l'id de l'emprunt a supprimer : ");
    scanf("%d", &id);

    while(fread(&emprunt, sizeof(Emprunt), 1, f))
    {
        if(emprunt.id == id)
        {
            trouve = 1;
            continue;
        }

        fwrite(&emprunt, sizeof(Emprunt), 1, temp);
    }

    fclose(f);
    fclose(temp);

    remove("LOANS.dat");
    rename("TEMP.dat", "LOANS.dat");


    if(trouve)
    {
        printf("Emprunt supprime avec succes !\n");
    }
    else
    {
        printf("Emprunt introuvable !\n");
    }
}

