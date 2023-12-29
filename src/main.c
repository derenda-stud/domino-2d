// 900983 899454

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/modalita_interattiva.h"
#include "../lib/struttura_dati.h"

/* Progetto Domino Lineare di Bertoncello Nicolas, Derevytskyy Alessandro */
#include <stdbool.h>

int main() {
    // Inizializza la generazione dei numeri casuali
    srand(time(NULL));
    // Dichiarazione del numero di tessere richieste
    int numero_tessere = 3;
    // Inizializzazione colonne con il numero di tessere indicato
    unsigned int colonne = 4 * (numero_tessere - 1) + 2;
    printf("Numero di colonne: %d\n", colonne);
    // La mano del giocatore e' una matrice lineare
    matrice_t *mano_giocatore = crea_matrice(numero_tessere * 2);
    // Il piano di gioco e' una matrice graduale
    matrice_t *piano_gioco = crea_matrice(colonne);
    aggiungi_riga(piano_gioco);
    
    // Generazione delle tessere nella mano del giocatore
    genera_tessere(mano_giocatore);
    
    // Funzione per il proseguimento del gioco
    stampa_turno(mano_giocatore, piano_gioco);
    
    coord_t prima = {0, 0}, seconda = {0, 2};
    inserisci_tessera(mano_giocatore, piano_gioco, 0, prima, false);
    inserisci_tessera(mano_giocatore, piano_gioco, 1, seconda, true);
    
    stampa_matrice(piano_gioco);
    
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