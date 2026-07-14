#include <stdio.h>
#include <stdlib.h>
#include "books.h"
#include "loans.h"

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
        scanf("%d",&choix);


        switch(choix)
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

    }while(choix != 0);
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
        scanf("%d",&choix);
        switch(choix)
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

    }while(choix != 0);
}

int main()
{

    int choix;

    do
    {
        printf("\n===== SYSTEME DE GESTION BIBLIOTHEQUE =====\n");
        printf("1. Gestion des livres\n");
        printf("2. Gestion des emprunts\n");
        printf("0. Quitter\n");

        printf("Votre choix : ");
        scanf("%d",&choix);


        switch(choix)
        {
            case 1:
                menuLivres();
                break;

            case 2:
                menuEmprunts();
                break;

            case 0:
                printf("Au revoir !\n");
                break;

            default:
                printf("Choix invalide !\n");
        }

    }while(choix != 0);

    return 0;
}
