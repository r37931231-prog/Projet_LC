#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utilisateur.h"
#include "books.h"
#include "loans.h"
#include "categorie.h"
#include "auteur.h"
#include "reservations.h"
#include "statistiques.h"

void menuUtilisateurs()
{
    int choix;

    do
    {
        printf("\n===== GESTION DES UTILISATEURS =====\n");
        printf("1. Se connecter (Login)\n");
        printf("2. Creer un compte (Inscription)\n");
        printf("3. Afficher la liste des utilisateurs\n");
        printf("4. Bloquer / Debloquer un utilisateur\n");
        printf("0. Retour\n");

        printf("Votre choix : ");
        if (scanf("%d", &choix) != 1)
        {
            choix = -1;
        }

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        switch (choix)
        {
        case 1:
            connexion_utilisateur();
            break;

        case 2:
            ajouter_utilisateur();
            break;

        case 3:
            lister_utilisateurs();
            break;

        case 4:
            changer_etat_utilisateur();
            break;

        case 0:
            printf("Retour au menu principal...\n");
            break;

        default:
            printf("Choix invalide !\n");
        }

    } while (choix != 0);
}

void menuLivres()
{
    int choix;

    do
    {
        printf("\n===== GESTION DES LIVRES =====\n");
        printf("1. Ajouter un livre\n");
        printf("2. Afficher les livres\n");
        printf("3. Rechercher un livre\n");
        printf("4. Modifier un livre\n");
        printf("5. Supprimer un livre\n");
        printf("0. Retour\n");

        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            ajouterLivre();
            break;

        case 2:
            afficherLivres();
            break;

        case 3:
            rechercherLivre();
            break;

        case 4:
            modifierLivre();
            break;

        case 5:
            supprimerLivre();
            break;

        case 0:
            printf("Retour au menu principal...\n");
            break;

        default:
            printf("Choix invalide !\n");
        }

    } while (choix != 0);
}

void menuEmprunts()
{
    int choix;

    do
    {
        printf("\n===== GESTION DES EMPRUNTS =====\n");
        printf("1. Ajouter un emprunt\n");
        printf("2. Afficher les emprunts\n");
        printf("3. Rechercher un emprunt\n");
        printf("4. Modifier un emprunt\n");
        printf("5. Supprimer un emprunt\n");
        printf("0. Retour\n");

        printf("Votre choix : ");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            ajouterEmprunt();
            break;

        case 2:
            afficherEmprunts();
            break;

        case 3:
            rechercherEmprunt();
            break;

        case 4:
            modifierEmprunt();
            break;

        case 5:
            supprimerEmprunt();
            break;

        case 0:
            printf("Retour au menu principal...\n");
            break;

        default:
            printf("Choix invalide !\n");
        }

    } while (choix != 0);
}

void menuCategories()
{
    int choix;
    do
    {
        printf("\n===== GESTION DES CATEGORIES =====\n");
        printf("1. Ajouter une categorie\n");
        printf("2. Afficher toutes les categories\n");
        printf("3. Supprimer une categorie\n");
        printf("0. Retour au menu principal\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar();

        switch (choix)
        {
        case 1:
            ajouterCategorie();
            break;
        case 2:
            afficherCategories();
            break;
        case 3:
            supprimerCategorie();
            break;
        case 0:
            printf("Retour...\n");
            break;
        default:
            printf("Choix invalide.\n");
        }
    } while (choix != 0 && choix > 3);
}

void menuAuteurs()
{
    int choix;
    do
    {
        printf("\n===== GESTION DES AUTEURS =====\n");
        printf("1. Ajouter un auteur\n");
        printf("2. Afficher tous les auteurs\n");
        printf("3. Supprimer un auteur\n");
        printf("0. Retour au menu principal\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar();

        switch (choix)
        {
        case 1:
            ajouterAuteur();
            break;
        case 2:
            afficherAuteurs();
            break;
        case 3:
            supprimerAuteur();
            break;
        case 0:
            printf("Retour...\n");
            break;
        default:
            printf("Choix invalide.\n");
        }
    } while (choix != 0 && choix > 3);
}

void menuReservations()
{
    int choix;

    do
    {
        printf("\n===== GESTION DES RESERVATIONS =====\n");
        printf("1. Effectuer une reservation\n");
        printf("2. Afficher la liste des reservations\n");
        printf("3. Annuler une reservation\n");
        printf("0. Retour au menu principal\n");

        printf("Votre choix : ");
        if (scanf("%d", &choix) != 1)
            choix = -1;

        switch (choix)
        {
        case 1:
            ajouterReservation();
            break;
        case 2:
            afficherReservations();
            break;
        case 3:
            annulerReservation();
            break;
        case 0:
            printf("Retour au menu principal...\n");
            break;
        default:
            printf("Choix invalide !\n");
        }

    } while (choix != 0);
}

void menuStatistiques()
{
    int choix;

    do
    {
        printf("\n===== STATISTIQUES ET RAPPORTS =====\n");
        printf("1. Tableau de bord global\n");
        printf("2. Generer le rapport journalier (Fichier Texte)\n");
        printf("0. Retour au menu principal\n");

        printf("Votre choix : ");
        if (scanf("%d", &choix) != 1)
            choix = -1;

        switch (choix)
        {
        case 1:
            afficherStatistiquesGlobales();
            break;
        case 2:
            printf("\nGeneration du rapport journalier...\n");
            genererRapportJournalier(time(NULL));
            break;
        case 0:
            printf("Retour au menu principal...\n");
            break;
        default:
            printf("Choix invalide !\n");
        }

    } while (choix != 0);
}

int main()
{
    initialiser_systeme();

#ifdef _WIN32
    system("mkdir DATABASE > nul 2>&1");
    system("mkdir REPORTS\\DAILY > nul 2>&1");
#else
    system("mkdir -p DATABASE > /dev/null 2>&1");
    system("mkdir -p REPORTS/DAILY > /dev/null 2>&1");
#endif

    int choix;
    do
    {
        printf("\n===== SYSTEME DE GESTION BIBLIOTHEQUE =====\n");
        printf("1. Gestion des utilisateurs\n");
        printf("2. Gestion des auteurs\n");
        printf("3. Gestion des categories\n");
        printf("4. Gestion des livres\n");
        printf("5. Gestion des emprunts\n");
        printf("6. Gestion des reservations\n");
        printf("7. Statistiques & Rapports\n");
        printf("0. Quitter\n");

        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            menuUtilisateurs();
            break;

        case 2:
            menuAuteurs();
            break;

        case 3:
            menuCategories();
            break;

        case 4:
            menuLivres();
            break;

        case 5:
            menuEmprunts();
            break;

        case 6:
            menuReservations();
            break;

        case 7:
            menuStatistiques();
            break;

        case 0:
            printf("Au revoir !\n");
            break;

        default:
            printf("Choix invalide !\n");
        }

    } while (choix != 0);

    return 0;
}
