#include <stdio.h>
#include <stdlib.h>

#include "../lib/struttura_dati.h"

piano_t *crea_piano(unsigned int colonne) {
    // Alloca la memoria necessaria a memorizzare il piano di gioco
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
    // Per ogni riga nel piano di gioco
    for(int i=0; i<piano_gioco->righe; i++) {
        printf("Stampo la riga con indice %d\n", i);
        // Stampa gli estremi in ciascuna colonna
        for(int j=0; j<piano_gioco->colonne; j++) {
            // Controlla che siano stati inseriti
            if(piano_gioco->posizione[i][j].estremo != 0) {
                printf("%d", piano_gioco->posizione[i][j].estremo);
            // Altrimenti stampa uno spazio vuoto
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void libera_piano(piano_t *piano_gioco) {
    // Libera tutte le righe del piano di gioco
    for(int i=0; i<piano_gioco->righe; i++) {
        free(piano_gioco->posizione[i]);
        piano_gioco->posizione[i] = NULL;
    }
    // Libera la memoria del puntatore iniziale
    free(piano_gioco->posizione);
    piano_gioco->posizione = NULL;
    // Libera la memoria della struttura dati del piano
    free(piano_gioco);
}