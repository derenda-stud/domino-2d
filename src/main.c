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
    unsigned int numero_tessere = 8;
    // Inizializzazione colonne con il numero di tessere indicato
    unsigned int colonne = 4 * (numero_tessere - 1) + 2;
    printf("Numero di colonne: %d\n", colonne);
    // Creazione delle strutture dati per la mano del giocatore e il piano di gioco
    mano_t *mano_giocatore = crea_mano(numero_tessere);
    // Il piano di gioco e' un vettore dinamico che contiene estremi, righe e colonne
    piano_t *piano_gioco = crea_piano(colonne);
    
    // Inserimenti temporanei: aggiungi 3 righe al piano di gioco
    for(int i=0; i<3; i++) {
        aggiungi_riga(piano_gioco);
    }
    size_t centro = colonne / 2;
    // 8 tessere = 30 colonne = posizioni [0:29]
    piano_gioco->posizione[0][centro + 0].estremo = 5;
    piano_gioco->posizione[0][centro + 0].cardine = 'E';
    piano_gioco->posizione[0][centro + 1].estremo = 1;
    piano_gioco->posizione[0][centro + 1].cardine = 'O';
    
    piano_gioco->posizione[0][centro + 2].estremo = 1;
    piano_gioco->posizione[0][centro + 2].cardine = 'E';
    piano_gioco->posizione[0][centro + 3].estremo = 6;
    piano_gioco->posizione[0][centro + 3].cardine = 'O';
    
    piano_gioco->posizione[0][centro + 4].estremo = 6;
    piano_gioco->posizione[0][centro + 4].cardine = 'S';
    piano_gioco->posizione[1][centro + 4].estremo = 2;
    piano_gioco->posizione[1][centro + 4].cardine = 'N';
    
    piano_gioco->posizione[1][centro + 2].estremo = 3;
    piano_gioco->posizione[1][centro + 2].cardine = 'E';
    piano_gioco->posizione[1][centro + 3].estremo = 2;
    piano_gioco->posizione[1][centro + 3].cardine = 'O';
    
    piano_gioco->posizione[0][centro - 1].estremo = 5;
    piano_gioco->posizione[0][centro - 1].cardine = 'S';
    piano_gioco->posizione[1][centro - 1].estremo = 6;
    piano_gioco->posizione[1][centro - 1].cardine = 'N';
    
    piano_gioco->posizione[1][centro - 3].estremo = 4;
    piano_gioco->posizione[1][centro - 3].cardine = 'E';
    piano_gioco->posizione[1][centro - 2].estremo = 6;
    piano_gioco->posizione[1][centro - 2].cardine = 'O';
    
    piano_gioco->posizione[1][centro + 0].estremo = 6;
    piano_gioco->posizione[1][centro + 0].cardine = 'S';
    piano_gioco->posizione[2][centro + 0].estremo = 3;
    piano_gioco->posizione[2][centro + 0].cardine = 'N';
    
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