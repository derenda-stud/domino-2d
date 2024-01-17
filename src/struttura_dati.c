#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../lib/struttura_dati.h"

matrice_t *crea_matrice(size_t colonne) {
    // Alloca la memoria per il puntatore alla matrice
    matrice_t *matrice = malloc(sizeof(matrice_t));
    // Imposta i parametri con valori inizializzati
    matrice->posizione = NULL;
    matrice->righe = 0;
    matrice->colonne = colonne;
    // Aggiungi una riga come predefinito
    aggiungi_riga(matrice);
    // Ritorna la nuova matrice creata
    return matrice;
}

void aggiungi_riga(matrice_t *matrice) {
    // Alloco la memoria necessaria per il nuovo puntatore
    matrice->posizione = realloc(matrice->posizione, sizeof(estremo_t *) * (matrice->righe + 1));
    // Alloco la memoria necessaria per gli elementi della nuova riga
    matrice->posizione[matrice->righe] = calloc(matrice->colonne, sizeof(estremo_t));
    // Incrementa il numero di righe attuali
    matrice->righe++;
}

void libera_matrice(matrice_t *matrice) {
    // Libera tutte le righe della matrice
    for(size_t i=0; i<matrice->righe; i++) {
        free(matrice->posizione[i]);
        matrice->posizione[i] = NULL;
    }
    // Libera la memoria del puntatore alla prima posizione
    free(matrice->posizione);
    matrice->posizione = NULL;
    // Inizializza i parametri della matrice
    matrice->righe = 0;
    matrice->colonne = 0;
    // Libera la memoria occupata dal puntatore iniziale
    free(matrice);
}


void stampa_piano(matrice_t *piano_gioco) {
    // Stampa un intestazione contenente le colonne
    printf("    ");
    for(size_t j=0; j<piano_gioco->colonne; j++) {
        printf(" %2d ", j);
    }
    printf("\n");
    // Per ogni riga della piano_gioco
    for(size_t i=0; i<piano_gioco->righe; i++) {
        // Stampa l'indice della riga corrente
        printf(" %2d ", i);
        // Stampa gli elementi presenti nella riga
        stampa_estremi(piano_gioco->posizione[i], piano_gioco->colonne);
    }
}

void stampa_mano(vect_t *mano_giocatore) {
    // Stampa le tessere contenuti nella mano del giocatore
    for(size_t i=0; i<mano_giocatore->dimensione; i++){
        tessera_t *tessera = elemento_ad_indice(mano_giocatore, i);
        printf(" [%2d|%2d] ", tessera->sinistro, tessera->destro);
    }
    printf("\n");
    // Stampa gli indici sotto ciascuna tessera
    for(size_t i=0; i<mano_giocatore->dimensione; i++) {
        printf("   %2d    ", i);
    }
    printf("\n");
}

void stampa_estremi(estremo_t *estremi, size_t dimensione) {
    // Per ciascun estremo nella struttura dati
    for(size_t i=0; i<dimensione; i++) {
        // In base al valore assunto dal cardine
        switch(estremi[i].cardine) {
            // Stampa correttamente l'estremo
            case 1: printf(" [%d ", estremi[i].valore); // >
                    break;
            case 2: printf(" %d] ", estremi[i].valore); // <
                    break;
            case 3: printf(" {%d ", estremi[i].valore); // v
                    break;
            case 4: printf(" %d} ", estremi[i].valore); // ^
                    break;
            // Quando non e' stato memorizzato un valore stampa uno spazio vuoto
            default: printf(" -- ");
        }
    }
    // Stampa il carattere per andare a capo
    printf("\n");
}