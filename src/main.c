#include <stdio.h>

#include "../lib/struttura_dati.h"
#include "../lib/modalita_interattiva.h"

int main() {
    // Dichiarazione dei parametri per la dimensione
    unsigned int numero_tessere = 2;
    unsigned int numero_estremi, colonne;
    // Inizializzazione con il numero di tessere indicato
    numero_estremi = numero_tessere * 2;
    colonne = 4 * (numero_tessere - 1) + 2;
    // Creazione delle strutture dati per la mano del giocatore e il piano di gioco
    unsigned int mano_giocatore[numero_estremi];
    // Il piano di gioco e' un vettore dinamico che contiene estremi, righe e colonne
    piano_t *piano_gioco = crea_piano(colonne);
    // Aggiungi la prima riga
    aggiungi_riga(piano_gioco);
    // Inserimento temporaneo di alcune tessere [0 : colonne - 1]
    piano_gioco->posizione[0][0].estremo = 1;
    piano_gioco->posizione[0][1].estremo = 6;
    
    piano_gioco->posizione[0][4].estremo = 3;
    piano_gioco->posizione[0][5].estremo = 4;
    // Generazione delle tessere nella mano del giocatore
    genera_tessere(mano_giocatore, numero_estremi);
    // Stampa delle tessere presenti nella mano del giocatore
    stampa_mano(mano_giocatore, numero_estremi);
    stampa_piano(piano_gioco);
    // Libera la memoria occupata
    libera_piano(piano_gioco);
    // Terminazione del programma
    return 0;
}