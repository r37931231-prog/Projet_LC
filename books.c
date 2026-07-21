#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"

void ajouterLivre(void)
{
    Livre livre;
    FILE *f;
    f = fopen("BOOKS.dat", "ab");

    if(f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    livre.id = genererIdLivre();
    printf("ID genere : %d\n", livre.id);

    printf("ISBN : ");
    scanf("%s", livre.isbn);

    getchar();

    printf("Titre : ");
    fgets(livre.titre, sizeof(livre.titre), stdin);

    printf("Entrer l'id de l'auteur : ");
    scanf("%d",&livre.idAuteur);

    if(!auteurExiste(livre.idAuteur))
    {
        printf("Erreur : auteur introuvable.\n");
        fclose(f);
        return;
    }

    printf("Entrer l'id de la categorie : ");
    scanf("%d",&livre.idCategorie);

    if(!categorieExiste(livre.idCategorie))
    {
        printf("Erreur : categorie introuvable.\n");
        fclose(f);
        return;
    }

    printf("Entrer l'editeur : ");
    scanf(" %49[^\n]", livre.editeur);

    printf("Entrer l'annee de publication : ");
    scanf("%d", &livre.anneePublication);

    printf("Entrer la langue : ");
    scanf(" %29[^\n]", livre.langue);

    getchar();

    printf("Entrer le nombre de pages : ");
    scanf("%d", &livre.nbPages);

    printf("Entrer le nombre total d'exemplaires : ");
    scanf("%d", &livre.totalExemplaires);

    printf("Entrer le nombre d'exemplaires disponibles : ");
    scanf("%d", &livre.disponibles);

    printf("Entrer l'emplacement : ");
    scanf(" %29[^\n]", livre.emplacement);

    printf("Entrer le resume : ");
    scanf(" %299[^\n]", livre.resume);

    printf("Entrer la date d'ajout (JJ/MM/AAAA) : ");
    scanf("%19s", livre.dateAjout);

    fwrite(&livre, sizeof(Livre), 1, f);

    fclose(f);

    printf("Livre ajoute avec succes !\n");
}


void afficherLivres(void)
{

    Livre livre;
    FILE *f;

    f = fopen("BOOKS.dat","rb");

    if(f == NULL)
    {
        printf("Erreur d'ouverture du fichier !");
        return;
    }

    printf("\n===== LISTE DES LIVRES =====\n");

    while(fread(&livre, sizeof(Livre), 1, f))
    {
        printf("\nID : %d", livre.id);
        printf("\nISBN : %s", livre.isbn);
        printf("\nTitre : %s", livre.titre);
        printf("\nAuteur : %d", livre.idAuteur);
        printf("\nCategorie : %d", livre.idCategorie);
        printf("\nnom editeur : %s", livre.editeur);
        printf("\nAnnee de publication : %d", livre.anneePublication);
        printf("\nLangue : %s", livre.langue);
        printf("\nnbr de pages : %d", livre.nbPages);
        printf("\nTotal exemplaire : %d", livre.totalExemplaires);
        printf("\nDispo : %d", livre.disponibles);
        printf("\nEmplacement: %s", livre.emplacement);
        printf("\nResume : %s", livre.resume);
        printf("\nDate ajout : %s", livre.dateAjout);
        printf("\n---------------------------");
    }

    fclose(f);
}

void rechercherLivre(void)
{

    Livre livre;
    FILE *f;
    int id;
    int trouve = 0;

    f = fopen("BOOKS.dat","rb");

    if(f == NULL)
    {
        printf("Erreur d'ouverture du fichier !");
        return;
    }

    printf("Entrer l'id du livre a rechercher : ");
    scanf("%d",&id);

    while(fread(&livre, sizeof(Livre), 1, f))
    {
        if(livre.id == id)
        {
            printf("\n===== LIVRE TROUVE =====\n");

            printf("ID : %d\n", livre.id);
            printf("ISBN : %s\n", livre.isbn);
            printf("Titre : %s\n", livre.titre);
            printf(" Auteur : %d\n", livre.idAuteur);
            printf("Categorie : %d\n", livre.idCategorie);
            printf("\n nom editeur : %s", livre.editeur);
            printf("\n Annee de publication : %d", livre.anneePublication);
            printf("\n Langue : %s", livre.langue);
            printf("\n nbr de pages : %d", livre.nbPages);
            printf("\n Total exemplaire : %d", livre.totalExemplaires);
            printf("\n Dispo : %d", livre.disponibles);
            printf("\n  Emplacement: %s", livre.emplacement);
            printf("\n Resume : %s", livre.resume);
            printf("\n Date ajout : %s", livre.dateAjout);

            trouve = 1;
            break;
        }
    }

    if(trouve == 0)
    {
        printf("Livre introuvable !\n");
    }

    fclose(f);
}

void modifierLivre(void)
{

  Livre livre;
    FILE *f;
    int id;
    int trouve = 0;

    f = fopen("BOOKS.dat","rb+");

    if(f == NULL)
    {
        printf("Erreur d'ouverture du fichier !");
        return;
    }

    printf("Entrer l'id du livre a modifier : ");
    scanf("%d",&id);

    while(fread(&livre, sizeof(Livre), 1, f))
    {
        if(livre.id == id)
        {
            printf("\nLivre trouve !\n");

            printf("Nouveau ISBN : ");
            scanf("%s",livre.isbn);

            printf("Nouveau titre : ");
            scanf("%s",livre.titre);

            printf("Nouvel id auteur : ");
            scanf("%d",&livre.idAuteur);

            printf("Nouvel id categorie : ");
            scanf("%d",&livre.idCategorie);

            printf(" Nouvel editeur : ");
            scanf("%49[^\n]", livre.editeur);

            printf("Nouvelle annee de publication : ");
            scanf("%d", &livre.anneePublication);

            printf("Nouvelle langue : ");
            scanf("%29[^\n]", livre.langue);

            getchar();

            printf("Nouveau nbr de pages : ");
            scanf("%d", &livre.nbPages);

            printf("Nouveau nbre total d'exemplaires : ");
            scanf("%d", &livre.totalExemplaires);

            printf("Nouveau nbre d'exemplaires disponibles : ");
            scanf("%d", &livre.disponibles);

            printf("Nouvel emplacement : ");
            scanf(" %29[^\n]", livre.emplacement);

            printf("Nouveau resume : ");
            scanf(" %299[^\n]", livre.resume);

            printf("Nouvelle date d'ajout (JJ/MM/AAAA) : ");
            scanf("%19s", livre.dateAjout);

            fseek(f, -sizeof(Livre), SEEK_CUR);
            fwrite(&livre, sizeof(Livre), 1, f);

            trouve = 1;

            printf("Livre modifie avec succes !\n");

            break;
        }
    }

    if(trouve == 0)
    {
        printf("Livre introuvable !\n");
    }

    fclose(f);
}


void supprimerLivre(void)
{
    Livre livre;
    FILE *f, *temp;
    int id;
    int trouve = 0;

    f = fopen("BOOKS.dat", "rb");

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

    printf("Entrer l'id du livre a supprimer : ");
    scanf("%d",&id);


    while(fread(&livre, sizeof(Livre), 1, f))
    {
        if(livre.id == id)
        {
            trouve = 1;
            continue;
        }

        fwrite(&livre, sizeof(Livre), 1, temp);
    }


    fclose(f);
    fclose(temp);


    remove("BOOKS.dat");
    rename("TEMP.dat", "BOOKS.dat");

    if(trouve)
    {
        printf("Livre supprime avec succes !\n");
    }
    else
    {
        printf("Livre introuvable !\n");
    }
}

int genererIdLivre(void)
{
    FILE *f;
    Livre livre;
    int dernierId = 0;

    f = fopen("BOOKS.dat","rb");

    if(f == NULL)
    {
        return 1;
    }

     while(fread(&livre, sizeof(Livre), 1, f))
    {
        dernierId = livre.id;
    }

    fclose(f);

    return dernierId + 1;
}

