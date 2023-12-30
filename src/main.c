// 900983 899454

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/modalita_interattiva.h"
#include "../lib/struttura_dati.h"
#include "../lib/controlli.h"

/* Progetto Domino Lineare di Bertoncello Nicolas, Derevytskyy Alessandro */

int main() {
    // Inizializza la generazione dei numeri casuali
    srand(time(NULL));
    // Richiesta da parte dell'utente per il numero di tessere
    unsigned int numero_tessere = inserisci_numero_tessere();
    // Inizializzazione delle colonne con il numero di tessere indicato
    unsigned int colonne = 4 * (numero_tessere - 1) + 2;
    // La mano del giocatore e' una matrice lineare
    matrice_t *mano_giocatore = crea_matrice(numero_tessere * 2);
    // Il piano di gioco e' una matrice con righe graduali
    matrice_t *piano_gioco = crea_matrice(colonne);
    // Generazione delle tessere nella mano del giocatore
    genera_tessere(mano_giocatore);
    // Inserimenti temporanei per verificarne le funzionalita'
    inserimento_orizzontale(piano_gioco, mano_giocatore->posizione[0] + (0 * 2), (coord_t) {0, 0});
    inserimento_verticale(piano_gioco, mano_giocatore->posizione[0] + (1 * 2), (coord_t) {0, 2});
    // Funzione per il proseguimento del gioco
    stampa_turno(mano_giocatore, piano_gioco);
    
    /*
    piano_gioco->posizione[0][centro + 2].valore = 1;
    piano_gioco->posizione[0][centro + 2].cardine = 'E';
    piano_gioco->posizione[0][centro + 3].valore = 6;
    piano_gioco->posizione[0][centro + 3].cardine = 'O';

    piano_gioco->posizione[0][centro + 4].valore = 6;
    piano_gioco->posizione[0][centro + 4].cardine = 'S';
    piano_gioco->posizione[1][centro + 4].valore = 2;
    piano_gioco->posizione[1][centro + 4].cardine = 'N';

    piano_gioco->posizione[1][centro + 2].valore = 3;
    piano_gioco->posizione[1][centro + 2].cardine = 'E';
    piano_gioco->posizione[1][centro + 3].valore = 2;
    piano_gioco->posizione[1][centro + 3].cardine = 'O';

    piano_gioco->posizione[0][centro - 1].valore = 5;
    piano_gioco->posizione[0][centro - 1].cardine = 'S';
    piano_gioco->posizione[1][centro - 1].valore = 6;
    piano_gioco->posizione[1][centro - 1].cardine = 'N';

    piano_gioco->posizione[1][centro - 3].valore = 4;
    piano_gioco->posizione[1][centro - 3].cardine = 'E';
    piano_gioco->posizione[1][centro - 2].valore = 6;
    piano_gioco->posizione[1][centro - 2].cardine = 'O';

    piano_gioco->posizione[1][centro + 0].valore = 6;
    piano_gioco->posizione[1][centro + 0].cardine = 'S';
    piano_gioco->posizione[2][centro + 0].valore = 3;
    piano_gioco->posizione[2][centro + 0].cardine = 'N';

    piano_gioco->posizione[2][centro + 1].valore = 3;
    piano_gioco->posizione[2][centro + 1].cardine = 'E';
    piano_gioco->posizione[2][centro + 2].valore = 5;
    piano_gioco->posizione[2][centro + 2].cardine = 'O';
    */
    
    // Libera la memoria occupata
    libera_matrice(mano_giocatore);
    libera_matrice(piano_gioco);
    // Terminazione del programma
    return 0;
}