#include <stdio.h>
#include <stdlib.h>

#include "../lib/struttura_dati.h"
#include "../lib/modalita_interattiva.h"

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
    unsigned int mano_giocatore[numero_estremi];
    // Il piano di gioco e' un array di puntatori di righe
    dato **piano_gioco = calloc(righe, sizeof(dato *));
    // Generazione delle tessere nella mano del giocatore
    genera_tessere(mano_giocatore, numero_estremi);
    // Stampa delle tessere presenti nella mano del giocatore
    stampa_mano(mano_giocatore, numero_estremi);
    stampa_piano(piano_gioco, righe, colonne);
    // Libera la memoria occupata
    free(piano_gioco);
    // Terminazione del programma
    return 0;
}