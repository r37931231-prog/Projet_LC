#include <stdio.h>
#include <string.h>
#include <time.h>
#include "categorie.h"

Categorie listeCategories[MAX_CATEGORIES];
int nombreCategories = 0;

static void nettoyerChaine(char *chaine) {
    chaine[strcspn(chaine, "\n")] = '\0';
}

void chargerCategories() {
    FILE *f = fopen(FICHIER_CATEGORIES, "rb");
    if (f == NULL) {
    nombreCategories = 0;
    return;
    }
    fread(&nombreCategories, sizeof(int), 1, f);
    fread(listeCategories, sizeof(Categorie), nombreCategories, f);
    fclose(f);
    printf("[Categories] %d categorie(s) chargee(s) depuis le fichier.\n", nombreCategories);
}

void sauvegarderCategories(void) {
    FILE *f = fopen(FICHIER_CATEGORIES, "wb");
    if (f == NULL) {
        printf("Impossible d'enregistrer dans les categories.\n");
        return;
    }
    fwrite(&nombreCategories, sizeof(int), 1, f);
    fwrite(listeCategories, sizeof(Categorie), nombreCategories, f);
    fclose(f);
}

void ajouterCategorie(void) {
    if (nombreCategories >= MAX_CATEGORIES) {
        printf("Impossible d'ajouter la liste des categories est pleine.\n");
        return;
    }

    Categorie c;
    c.id = nombreCategories + 1;

    printf("\n--- Ajouter d'une categorie ---\n");

    printf("Libelle : ");
    fgets(c.libelle, sizeof(c.libelle), stdin);
    nettoyerChaine(c.libelle);

    printf("Description : ");
    fgets(c.description, sizeof(c.description), stdin);
    nettoyerChaine(c.description);

    time_t t = time(NULL);
    struct tm *dateDuJour = localtime(&t);
    sprintf(c.dateCreation, "%02d/%02d/%d",
    dateDuJour->tm_mday, dateDuJour->tm_mon + 1, dateDuJour->tm_year + 1900);

    listeCategories[nombreCategories] = c;
    nombreCategories++;

    sauvegarderCategories();
    printf("-> Categorie ajoutee avec succes (id = %d).\n", c.id);
}

void afficherCategories(void) {
    printf("\n--- Liste des categories (%d) ---\n", nombreCategories);
    if (nombreCategories == 0) {
        printf("Aucune categorie enregistree.\n");
        return;
    }
    for (int i = 0; i < nombreCategories; i++) {
        printf("ID:%d | %s | %s | cree le %s\n",
        listeCategories[i].id,
        listeCategories[i].libelle,
        listeCategories[i].description,
        listeCategories[i].dateCreation);
    }
}

void supprimerCategorie(void) {
    int id;
    printf("ID de la categorie a supprimer : ");
    scanf("%d", &id);
    getchar();

    int index = -1;
    for (int i = 0; i < nombreCategories; i++) {
        if (listeCategories[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Categorie introuvable.\n");
    return;
    }

    for (int i = index; i < nombreCategories - 1; i++) {
        listeCategories[i] = listeCategories[i + 1];
    }
        nombreCategories--;

        sauvegarderCategories();
        printf("-> Categorie supprimee.\n");
}

int categorieExiste(int id) {
    for (int i = 0; i < nombreCategories; i++) {
        if (listeCategories[i].id == id) {
        return 1;
        }
    }
return 0;
}
