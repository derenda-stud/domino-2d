// 900983 899454

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/modalita_interattiva.h"
#include "../lib/struttura_dati.h"

/* Progetto Domino Lineare di Bertoncello Nicolas, Derevytskyy Alessandro */

int main() {
    // Inizializza la generazione dei numeri casuali
    srand(time(NULL));
    // Dichiarazione del numero di tessere richieste
    unsigned int numero_tessere = 2;
    // Inizializzazione colonne con il numero di tessere indicato
    unsigned int colonne = 4 * (numero_tessere - 1) + 2;
    // Creazione delle strutture dati per la mano del giocatore e il piano di gioco
    mano_t *mano_giocatore = crea_mano(numero_tessere);
    // Il piano di gioco e' un vettore dinamico che contiene estremi, righe e colonne
    piano_t *piano_gioco = crea_piano(colonne);
    // Generazione delle tessere nella mano del giocatore
    genera_tessere(mano_giocatore);
    // Funzione per il proseguimento del gioco
    stampa_turno(mano_giocatore, piano_gioco);
    // Libera la memoria occupata
    libera_mano(mano_giocatore);
    libera_piano(piano_gioco);
    // Terminazione del programma
    return 0;
}