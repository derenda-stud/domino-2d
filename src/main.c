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
    estremo_t estremi_temp[] = {
        // [5|1]        [1|6]         {5          [4|6]         {6          [3|2]         {6
        //                            6}                        2}                        3}
        {5,1},{1,2}, {1,1},{6,2}, {5,1},{6,2}, {4,1},{6,2}, {6,1},{2,2}, {3,1},{2,2}, {6,1},{3,2}
    };
    unsigned int centro = colonne / 2 - 1;
    coord_t coordinate_temp[] = {
        {0,centro+0},{0,centro+2},{0,centro-1},{1,centro-3},{0,centro+4},{1,centro+2},{1,centro+0}
    };
    bool orizzontali[] = {
        true,            true,       false,        true,         false,        true,       false
    };
    for(int i=0; i<7; i++) {
        if(orizzontali[i]) {
            inserimento_orizzontale(piano_gioco, estremi_temp + (i * 2), coordinate_temp[i]);
        }
        else {
            inserimento_verticale(piano_gioco, estremi_temp + (i * 2), coordinate_temp[i]);
        }
    }
    //inserimento_verticale(piano_gioco, mano_giocatore->posizione[0] + (1 * 2), (coord_t) {0, 2});
    // Funzione per il proseguimento del gioco
    stampa_turno(mano_giocatore, piano_gioco);
    
    // Libera la memoria occupata
    libera_matrice(mano_giocatore);
    libera_matrice(piano_gioco);
    // Terminazione del programma
    return 0;
}