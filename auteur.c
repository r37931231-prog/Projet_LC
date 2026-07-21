#include <stdio.h>
#include <string.h>
#include "auteur.h"

Auteur listeAuteurs[MAX_AUTEURS];
int nombreAuteurs = 0;

static void nettoyerChaine(char *chaine) {
    chaine[strcspn(chaine, "\n")] = '\0';
}

void chargerAuteurs (void){
     FILE *f = fopen(FICHIER_AUTEURS, "rb");
    if (f == NULL) {
        nombreAuteurs = 0;
        return;
    }
    fread(&nombreAuteurs,sizeof(int),1,f);
    fread(listeAuteurs,sizeof(Auteur),nombreAuteurs,f);
    fclose(f);
    printf("[Auteurs] %d auteur(s) charge(s) depuis le fichier.\n", nombreAuteurs);
}

void sauvegarderAuteurs(void) {
    FILE *f = fopen(FICHIER_AUTEURS, "wb");
    if (f == NULL) {
        printf("Erreur : impossible d'enregistrer les auteurs.\n");
        return;
    }
    fwrite(&nombreAuteurs,sizeof(int),1,f);
    fwrite(listeAuteurs,sizeof(Auteur),nombreAuteurs,f);
    fclose(f);
}

void ajouterAuteur(void) {
    if (nombreAuteurs>=MAX_AUTEURS){
            printf("Impossible limite d'ajout est atteint \n");
        return;
    }
    Auteur a;
    a.id = nombreAuteurs + 1;
    printf("\n--- Ajouter un auteur ---\n");

    printf("Nom complet : ");
    fgets(a.nomComplet, sizeof(a.nomComplet), stdin);
    nettoyerChaine(a.nomComplet);

    printf("Nationalite : ");
    fgets(a.nationalite, sizeof(a.nationalite), stdin);
    nettoyerChaine(a.nationalite);

    printf("Date de naissance : ");
    fgets(a.dateNaissance, sizeof(a.dateNaissance), stdin);
    nettoyerChaine(a.dateNaissance);

    printf("Biographie : ");
    scanf("%s",a.biographie);
    getchar();

    printf("Nombre de livres publies : ");
    scanf("%d", &a.nombreLivresPublies);
    getchar();
    listeAuteurs[nombreAuteurs] = a;
    nombreAuteurs++;

    sauvegarderAuteurs();
    printf("-> Auteur ajoute avec succes (id = %d).\n", a.id);
}

void afficherAuteurs(void){
    printf("\n--- Liste des auteurs (%d) ---\n", nombreAuteurs);
    if (nombreAuteurs==0){
        printf("Aucun auteur enregistrer \n");
        return;
    }
    for (int i = 0; i < nombreAuteurs; i++) {
        printf("ID:%d | %s | %s | ne(e) le %s | %d livre(s) publie(s)\n",
        listeAuteurs[i].id,
        listeAuteurs[i].nomComplet,
        listeAuteurs[i].nationalite,
        listeAuteurs[i].dateNaissance,
        listeAuteurs[i].nombreLivresPublies);
    }
}

void supprimerAuteur(void){
     int id, cpt;
    printf("ID de l'auteur a supprimer : ");
    scanf("%d", &id);
    getchar();
    int index = -1;
    for (int i = 0; i < nombreAuteurs; i++) {
        if (listeAuteurs[i].id == id && listeAuteurs[i].nombreLivresPublies==0){
            index = i;
            cpt=listeAuteurs[i].nombreLivresPublies;
    break;
    }
    }
    if (index == -1 || cpt!=0) {
        printf("Auteur associee à un livre.\n");
        return;
    }
    if (index == -1) {
        printf("Auteur introuvable.\n");
        return;
    }
    for (int i = index; i < nombreAuteurs - 1; i++) {
        listeAuteurs[i] = listeAuteurs[i + 1];
    }
    nombreAuteurs--;

    sauvegarderAuteurs();
    printf("-> Auteur supprime.\n");
}


int auteurExiste(int id) {
    for (int i = 0; i < nombreAuteurs; i++) {
        if (listeAuteurs[i].id == id) {
        return 1;
        }
    }
    return 0;
}


