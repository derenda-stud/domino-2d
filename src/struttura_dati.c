#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../lib/struttura_dati.h"

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
            // In base al valore assunto dal cardine
            switch(matrice->posizione[i][j].cardine) {
                // Stampa correttamente l'estremo
                case 1: {
                    printf(" [%d ", matrice->posizione[i][j].valore);
                    break;
                }
                case 2: {
                    printf(" %d] ", matrice->posizione[i][j].valore);
                    break;
                }
                case 3: {
                    printf(" {%d ", matrice->posizione[i][j].valore);
                    break;
                }
                case 4: {
                    printf(" %d} ", matrice->posizione[i][j].valore);
                    break;
                }
                // Quando non e' stato memorizzato un valore
                default: {
                    // Stampa uno spazio vuoto
                    printf(" -- ");
                    break;
                }
            }
        }
        // Stampa la riga successiva
        printf("\n");
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

void inserisci_tessera(matrice_t *mano_giocatore, matrice_t *piano_gioco, int indice, coord_t coordinata, bool orientamento) {
    // Memorizza l'estremo sinistro della mano del giocatore nel piano di gioco
    piano_gioco->posizione[coordinata.riga][coordinata.colonna] = mano_giocatore->posizione[0][indice * 2];
    // In base all'orientamento, memorizza l'estremo destro nella posizione adiacente/sottostante
    piano_gioco->posizione[coordinata.riga + orientamento][coordinata.colonna + !orientamento] = mano_giocatore->posizione[0][indice * 2 + 1];
    // Se posizionata in verticale cambia i cardini perche' corrispondano agli orientamenti 3 e 4
    piano_gioco->posizione[coordinata.riga][coordinata.colonna].cardine += (orientamento * 2);
    piano_gioco->posizione[coordinata.riga + 1][coordinata.colonna].cardine += (orientamento * 2);
    // Rimuovi i due estremi posizionati dalla mano del giocatore
    // sposta_estremi(mano_giocatore, indice);
}

/* Inserimento in orizzontale:
        - Memorizza la posizione attuale ed adiacente
        - Mantieni gli stessi cardini
    */
   /*
    if(!orientamento) {
        piano_gioco->posizione[coordinata.riga][coordinata.colonna] = mano_giocatore->posizione[0][indice * 2];
        piano_gioco->posizione[coordinata.riga][coordinata.colonna + 1] = mano_giocatore->posizione[0][indice * 2 + 1];
    } else {  
        piano_gioco->posizione[coordinata.riga][coordinata.colonna] = mano_giocatore->posizione[0][indice * 2];
        piano_gioco->posizione[coordinata.riga + 1][coordinata.colonna] = mano_giocatore->posizione[0][indice * 2 + 1];
        piano_gioco->posizione[coordinata.riga][coordinata.colonna].cardine += 2;
        piano_gioco->posizione[coordinata.riga + 1][coordinata.colonna].cardine += 2;
    }
    */
    /* Inserimento in verticale:
        - Memorizza la posizione attuale e sottostante
        - Cambia il valore dei cardini (incrementalo di 2)
    */