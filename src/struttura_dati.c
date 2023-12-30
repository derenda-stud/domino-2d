#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../lib/struttura_dati.h"
#include "../lib/controlli.h"

matrice_t *crea_matrice(size_t colonne) {
    // Alloca la memoria necessaria al puntatore iniziale
    matrice_t *matrice = malloc(sizeof(matrice_t));
    // Imposta i parametri con valori inizializzati
    matrice->posizione = NULL;
    matrice->righe = 0;
    matrice->colonne = colonne;
    // Aggiungi una riga come predefinito
    aggiungi_riga(matrice);
    // Ritorna il puntatore alla struttura dati creata
    return matrice;
}

void aggiungi_riga(matrice_t *matrice) {
    // Alloco la memoria necessaria per memorizzare la nuova riga
    matrice->posizione = realloc(matrice->posizione, sizeof(estremo_t *) * (matrice->righe + 1));
    // Alloco la memoria per memorizzare gli elementi della nuova riga
    matrice->posizione[matrice->righe] = calloc(matrice->colonne, sizeof(estremo_t));
    // Incrementa il numero di righe attuali
    matrice->righe++;
}

void stampa_matrice(matrice_t *matrice) {
    // Per ogni riga della matrice
    for(size_t i=0; i<matrice->righe; i++) {
        // Per ogni colonna della colonna
        for(size_t j=0; j<matrice->colonne; j++) {
            stampa_estremo(matrice->posizione[i][j]);
        }
        // Stampa la riga successiva
        printf("\n");
    }
}

void stampa_estremo(estremo_t estremo) {
    // In base al valore assunto dal cardine
    switch(estremo.cardine) {
        // Stampa correttamente l'estremo
        case 1: printf(" [%d ", estremo.valore);
                break;
        case 2: printf(" %d] ", estremo.valore);
                break;
        case 3: printf(" {%d ", estremo.valore);
                break;
        case 4: printf(" %d} ", estremo.valore);
                break;
        // Quando non e' stato memorizzato un valore stampa uno spazio vuoto
        default: printf(" -- ");
    }
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
    // Libera la memoria occupata dal puntatore iniziale
    free(matrice);
}

void genera_tessere(matrice_t *mano_giocatore) {
    // Per ciascun estremo della mano del giocatore
    for(size_t j=0; j<mano_giocatore->colonne; j++) {
        // Genera casualmente i suoi valori contenuti
        mano_giocatore->posizione[0][j].valore = rand() % 6 + 1;
        // Collega i due estremi memorizzando i loro cardini
        mano_giocatore->posizione[0][j].cardine = 1 + (j % 2);
    }
}

coord_t *calcola_coordinate(matrice_t *piano_gioco, size_t *posizioni) {
    // Inizializza il vettore contenente le coordinate
    coord_t *coordinate = NULL;
    // Per ciascuna riga
    for(size_t i=0; i<piano_gioco->righe; i++) {
        // Fino alla punultima colonna (attenzione al controllo)
        for(size_t j=0; j<piano_gioco->colonne - 2; j++) {
            // Trova dove e' possibile posizionare una tessera
            if(posizione_valida(piano_gioco, i, j, true)) {
                // Incrementa la dimensione dell'array di partenza
                (*posizioni)++;
                // Alloca la memoria necessaria per il nuovo elemento
                coordinate = realloc(coordinate, sizeof(coord_t) * (*posizioni));
                // Aggiungi l'elemento all'array
                coordinate[*posizioni - 1] = (coord_t) {i, j};
            }
        }
    }
    // Ritorna il nuovo vettore creato
    return coordinate;
}

void stampa_coordinate(coord_t *coordinate, size_t posizioni) {
    for(size_t i=0; i<posizioni; i++) {
        printf("(%2d,%2d)\n", coordinate[i].riga, coordinate[i].colonna);
    }
}

void inserimento_orizzontale(matrice_t *piano_gioco, estremo_t *estremo_sinistro, coord_t coordinata) {
    // Memorizza l'estremo sinistro nella posizione corrente
    piano_gioco->posizione[coordinata.riga][coordinata.colonna] = *estremo_sinistro;
    // Memorizza l'estremo destro nella posizione adiacente
    piano_gioco->posizione[coordinata.riga][coordinata.colonna + 1] = *(estremo_sinistro + 1);
}

// Rimuovi i due estremi posizionati dalla mano del giocatore
// sposta_estremi(mano_giocatore, indice);

void inserimento_verticale(matrice_t *piano_gioco, estremo_t *estremo_sinistro, coord_t coordinata) {
    // Controlla se sia necessario aggiungere una nuova riga
    if(piano_gioco->righe <= coordinata.riga) aggiungi_riga(piano_gioco);
    // Memorizza l'estremo sinistro nella posizione corrente
    piano_gioco->posizione[coordinata.riga][coordinata.colonna] = *estremo_sinistro;
    // Memorizza l'estremo destro nella posizione sottostante
    piano_gioco->posizione[coordinata.riga + 1][coordinata.colonna] = *(estremo_sinistro + 1);
    // Incrementa l'orientamento dei cardini
    incrementa_cardini(piano_gioco, coordinata);
}

void incrementa_cardini(matrice_t *piano_gioco, coord_t coordinata) {
    piano_gioco->posizione[coordinata.riga][coordinata.colonna].cardine += 2;
    piano_gioco->posizione[coordinata.riga + 1][coordinata.colonna].cardine += 2;
}