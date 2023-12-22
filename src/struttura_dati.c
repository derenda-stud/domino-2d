#include <stdio.h>

#include "../lib/struttura_dati.h"

void stampa_piano(dato **piano_gioco, size_t righe, size_t colonne) {
    printf("Piano di gioco :)\n");
    // Per ogni riga nel piano di gioco
    for(size_t i=0; i<righe && piano_gioco[righe] != NULL; i++) {
        // Stampa gli estremi in ciascuna colonna
        for(size_t j=0; j<colonne; j++) {
            // Controlla che siano stati inseriti
            if(piano_gioco[i][j].estremo != 0) {
                printf("%d", piano_gioco[i][j].estremo);
            // Altrimenti passa al successivo
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}