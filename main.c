#include <stdio.h>

#include "struttura_dati.h"

int main() {
    // Dichiarazione dei parametri per la dimensione
    int numero_tessere = 10;
    unsigned int righe, colonne;
    size_t numero_estremi, dimensione;
    // Inizializzazione con il numero di tessere indicato
    numero_estremi = numero_tessere * 2;
    righe = numero_estremi + 1;
    colonne = 4 * (numero_estremi - 1) + 2;
    dimensione = righe * colonne;
    printf("Righe: %d, Colonne: %d, Matrice: %d\n", righe, colonne, dimensione);
    // Creazione delle strutture dati per la mano del giocatore e il piano di gioco
    dati mano_giocatore[numero_estremi];
    dati piano_gioco[dimensione];
    return 0;
}