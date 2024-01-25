// 900983 899454

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/controlli.h"
#include "../lib/modalita_ai.h"
#include "../lib/modalita_interattiva.h"
#include "../lib/tessera.h"

/* Progetto Domino Lineare di Bertoncello Nicolas, Derevytskyy Alessandro */

unsigned int menu_selezione(void) {
    // Stampa delle principali modalita' e l'opzione per uscire
    printf(" - Premi 1 per giocare con la modalita' interattiva\n");
    printf(" - Premi 2 per giocare con la modalita' AI\n");
    printf(" - Premi 0 per terminare il programma\n");
    // Chiedi all'utente di selezionare una scelta tra quelle proposte
    return inserisci_numero_compreso("Inserisci la scelta", 0, 2);
}

int main(void) {
    // Inizializza la generazione dei numeri casuali
    srand(time(NULL));
    // Messaggio di stampa introduttivo
    printf("Benvenuto nel Domino 2D!\n");
    // Memorizza la selezione durante ciascuna partita
    unsigned int modalita;
    // Continua a giocare finche' viene selezionata una modalita'
    while ((modalita = menu_selezione()) != 0) {
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
        // Funzioni per il proseguimento del gioco
        switch (modalita) {
            case 1: stampa_turno(mano_giocatore, piano_gioco);
                    break;
            case 2: esegui_algoritmo(piano_gioco, mano_giocatore);
                    break;
        }
        // Calcola il punteggio e visualizzalo a schermo
        printf("Hai effettuato %d punti!\n", calcola_punteggio(piano_gioco));
        // Libera la memoria occupata
        libera_vettore(mano_giocatore);
        libera_matrice(piano_gioco);
    }
    // Terminazione del programma
    return 0;
}
