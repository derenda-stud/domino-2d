// 900983 899454

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/modalita_interattiva.h"
#include "../lib/modalita_ai.h"
#include "../lib/tessera.h"
#include "../lib/controlli.h"

/* Progetto Domino Lineare di Bertoncello Nicolas, Derevytskyy Alessandro */

int menu_selezione(void){
    printf("Seleziona una modalita' di gioco:\n");
    printf("\t[1] Modalita' interattiva\n");
    printf("\t[2] Modalita' AI\n");
    return inserisci_numero_compreso("Inserisci la modalita' con cui giocare", 1, 2);
}

int main(void) {
    // Inizializza la generazione dei numeri casuali
    srand(time(NULL));
    printf("Benvenuto nel domino lineare!\n");
    int scelta = menu_selezione();
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
    if(scelta == 1) stampa_turno(mano_giocatore, piano_gioco);
    else esegui_algoritmo(piano_gioco, mano_giocatore);
    //calcola il punteggio e lo visualizza a schermo
    printf("Hai effettuato %d punti!", calcola_punteggio(piano_gioco));
    // Libera la memoria occupata
    libera_vettore(mano_giocatore);
    libera_matrice(piano_gioco);
    // Terminazione del programma
    return 0;
}

/*

Prima della partita -> Inserisci numero tessere

Premi 1 per interattiva
Premi 2 per algoritmo AI
Premi 0 per uscire

Dopo ogni partita -> Calcola punteggio e libera memoria

* Stampa tra prima ed ultima posizione
* Documentazione Doxygen

*/