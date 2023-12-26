#include <stdio.h>
#include <stdlib.h>

#include "../lib/struttura_dati.h"

mano_t *crea_mano(unsigned int numero_tessere) {
    // Alloca la memoria per il puntatore iniziale
    mano_t *mano_giocatore = malloc(sizeof(mano_t));
    // Inizializza i parametri allocando la memoria per le tessere
    mano_giocatore->tessere = malloc(sizeof(tessera_t) * numero_tessere);
    // Memorizza la dimensione attuale dell'array
    mano_giocatore->dimensione = numero_tessere;
    // Ritorna il puntatore alla struttura dati creata
    return mano_giocatore;
}

void genera_tessere(mano_t *mano_giocatore) {
    // Per ciascuna posizione nella mano
    for(size_t i=0; i<mano_giocatore->dimensione; i++) {
        // Inizializza una tessera con estremi casuali
        mano_giocatore->tessere[i].estremo_sinistro = rand() % 6 + 1;
        mano_giocatore->tessere[i].estremo_destro = rand() % 6 + 1;
    }
}

void stampa_mano(mano_t *mano_giocatore) {
    // Stampa le tessere nella mano del giocatore
    for(size_t i=0; i<mano_giocatore->dimensione; i++) {
        printf("[%d|%d] ", mano_giocatore->tessere[i].estremo_sinistro, mano_giocatore->tessere[i].estremo_destro);
    }
    printf("\n");
    // Stampa gli indici per ogni tessera
    for(size_t i=0; i<mano_giocatore->dimensione; i++) {
        printf("  %d   ", i);
    }
    printf("\n");
}

void libera_mano(mano_t *mano_giocatore) {
    // Libera la memoria occupata dalle tessere
    free(mano_giocatore->tessere);
    mano_giocatore->tessere = NULL;
    // Libera la memoria del puntatore iniziale
    free(mano_giocatore);
}

piano_t *crea_piano(unsigned int colonne) {
    // Alloca la memoria necessaria per memorizzare il piano di gioco
    piano_t *piano_gioco = malloc(sizeof(piano_t));
    // Inizializza i parametri del piano di gioco
    piano_gioco->posizione = NULL;
    piano_gioco->righe = 0;
    piano_gioco->colonne = colonne;
    // Ritorna il puntatore alla nuova struttura dati
    return piano_gioco;
}

void aggiungi_riga(piano_t *piano_gioco) {
    // Alloco la memoria necessaria per memorizzare la nuova riga
    piano_gioco->posizione = realloc(piano_gioco->posizione, sizeof(dato_t *) * (piano_gioco->righe + 1));
    // Alloco la memoria per memorizzare gli elementi della nuova riga
    piano_gioco->posizione[piano_gioco->righe] = calloc(piano_gioco->colonne, sizeof(dato_t));
    // Incrementa il numero di righe attuali
    piano_gioco->righe++;
}

void stampa_piano(piano_t *piano_gioco) {
    // Stampa gli indici degli estremi
    printf("  ");
    for(size_t i=0; i<piano_gioco->colonne; i++) {
        printf(" %2d ", i);
    }
    printf("\n");
    // Per ogni riga nel piano di gioco
    for(size_t i=0; i<piano_gioco->righe; i++) {
        // Stampa la riga attuale
        printf("%2d", i);
        // Stampa gli estremi in ciascuna colonna
        for(size_t j=0; j<piano_gioco->colonne; j++) {
            // In base al valore assunto dal cardine
            switch(piano_gioco->posizione[i][j].cardine) {
                // Stampa correttamente l'estremo
                case 'N': {
                    printf(" {%d ", piano_gioco->posizione[i][j].estremo);
                    break;
                }
                case 'S': {
                    printf(" %d} ", piano_gioco->posizione[i][j].estremo);
                    break;
                }
                case 'E': {
                    printf(" [%d ", piano_gioco->posizione[i][j].estremo);
                    break;
                }
                case 'O': {
                    printf(" %d] ", piano_gioco->posizione[i][j].estremo);
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

void libera_piano(piano_t *piano_gioco) {
    // Libera tutte le righe del piano di gioco
    for(size_t i=0; i<piano_gioco->righe; i++) {
        free(piano_gioco->posizione[i]);
        piano_gioco->posizione[i] = NULL;
    }
    // Libera la memoria del puntatore iniziale
    free(piano_gioco->posizione);
    piano_gioco->posizione = NULL;
    // Libera la memoria della struttura dati del piano
    free(piano_gioco);
}