// 900983 899454

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/modalita_interattiva.h"
#include "../lib/modalita_ai.h"
#include "../lib/tessera.h"
#include "../lib/controlli.h"

/* Progetto Domino Lineare di Bertoncello Nicolas, Derevytskyy Alessandro */

int main() {
    // Inizializza la generazione dei numeri casuali
    srand(time(NULL));
    // Richiesta da parte dell'utente per il numero di tessere
    unsigned int numero_tessere = inserisci_numero_tessere();
    // Inizializzazione delle colonne con il numero di tessere indicato
    unsigned int colonne = 4 * numero_tessere;
    // La mano del giocatore e' un vettore lineare
    vect_t *mano_giocatore = crea_vettore(sizeof(tessera_t), numero_tessere);
    // Il piano di gioco e' una matrice con righe graduali
    matrice_t *piano_gioco = crea_matrice(colonne);
    // Generazione delle tessere nella mano del giocatore
    genera_tessere(mano_giocatore);
    // Funzione per il proseguimento del gioco
    esegui_algoritmo(piano_gioco, mano_giocatore);
    // stampa_turno(mano_giocatore, piano_gioco);
    // Libera la memoria occupata
    libera_vettore(mano_giocatore);
    libera_matrice(piano_gioco);
    // Terminazione del programma
    return 0;
}