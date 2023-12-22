#include <stdio.h>
#include <stdlib.h>

#include "../lib/struttura_dati.h"

dato **crea_piano(size_t righe, size_t colonne) {
    // Alloca la memoria necessaria a memorizzare il piano di gioco
    dato **piano_gioco = calloc(righe, sizeof(dato *));
    // Crea la prima riga dove posizionare gli estremi
    aggiungi_riga(piano_gioco, righe, colonne);
    // Ritorna il puntatore alla nuova struttura dati
    return piano_gioco;
}

void aggiungi_riga(dato **piano_gioco, size_t righe, size_t colonne) {
    // Dichiarazione dell'indice su cui effettuare le operazioni
    size_t indice;
    // Raggiungi la prima riga vuota del piano di gioco
    for(indice = 0; piano_gioco[indice] != NULL; indice++);
    // Alloca la memoria necessaria per la nuova riga
    piano_gioco[indice] = calloc(colonne, sizeof(dato));
}

void stampa_piano(dato **piano_gioco, size_t righe, size_t colonne) {
    // Per ogni riga nel piano di gioco
    for(size_t i=0; i<righe && piano_gioco[i] != NULL; i++) {
        printf("Stampo la riga con indice %d\n", i);
        // Stampa gli estremi in ciascuna colonna
        for(size_t j=0; j<colonne; j++) {
            // Controlla che siano stati inseriti
            if(piano_gioco[i][j].estremo != 0) {
                printf("%d", piano_gioco[i][j].estremo);
            // Altrimenti passa al successivo
            } else {
                printf("0");
            }
        }
        printf("\n");
    }
}

void libera_piano(dato **piano_gioco, size_t righe) {
    // Libera tutte le righe del piano di gioco
    for(size_t i=0; i<righe; i++) {
        free(piano_gioco[i]);
    }
    // Libera la memoria del puntatore iniziale
    free(piano_gioco);
}