#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../lib/modalita_interattiva.h"
#include "../lib/tessera.h"
#include "../lib/controlli.h"

void stampa_turno(vect_t *mano_giocatore, matrice_t *piano_gioco) {
    // Continua la partita finche' rimangono mosse disponibili
    while(mosse_disponibili(mano_giocatore, piano_gioco)) {
        // Stampa il piano di gioco nello stato corrente
        stampa_piano(piano_gioco);
        // Stampa le tessere presenti nella mano del giocatore
        stampa_mano(mano_giocatore);
        // Inserisci la tessera presente ad un determinato indice
        seleziona_tessera(mano_giocatore, piano_gioco);
    }
    // Stampa finale prima del termine della partita
    stampa_piano(piano_gioco);
}

void seleziona_tessera(vect_t *mano_giocatore, matrice_t *piano_gioco) {
    // Inserisci un numero compreso tra 0 e l'indice dell'ultima tessera
    int indice_tessera = inserisci_numero_compreso("Inserisci l'indice della tessera da posizionare", 0, mano_giocatore->dimensione - 1);
    // Memorizza l'indirizzo della tessera all'indice selezionato dall'utente
    tessera_t *tessera = elemento_ad_indice(mano_giocatore, indice_tessera);
    // Chiedi all'utente come intende posizionare la tessera selezionata
    bool orientamento = inserisci_numero_compreso("Come vuoi posizionare la tessera? (1 in orizzontale, 0 in verticale)", 0, 1);
    // Creazione del vettore creato dalle posizioni valide
    vect_t *coordinate = calcola_coordinate(piano_gioco, orientamento);
    // Seleziona la coordinate dove effettuare l'inserimento
    coord_t *coordinata = seleziona_posizione(coordinate);
    // Creazione delle informazioni da memorizzare per l'inserimento
    comb_t *risultato = crea_combinazione(*coordinata, orientamento);
    // Controlla se sia possibile posizionare la tessera
    if(mossa_legale(piano_gioco, coordinata, tessera, risultato)) {
        // Controlla l'inserimento delle tessere speciali
        if(tessera->speciale) funzionalita_aggiuntive(piano_gioco, tessera, risultato);
        // Preleva la tessera secondo la posizione e l'orientamento indicato
        preleva_tessera(piano_gioco, mano_giocatore, tessera, coordinata, risultato);
    } else {
        printf("Mossa non valida, riprova con un altra tessera\n");
    }
    // Libera la memoria occupata
    libera_vettore(coordinate);
    libera_combinazione(risultato);
}

coord_t *seleziona_posizione(vect_t *coordinate) {
    // Se e' disponibile solo una coordinata e' richiesta la selezione
    if(coordinate->dimensione == 1) return elemento_ad_indice(coordinate, 0);
    // Stampa il menu per indicare le possibile scelte
    printf("Seleziona dove posizionare la tessera:\n");
    printf(" - Premi 1 per scorrere alla posizione precedente\n");
    printf(" - Premi 2 per scorrere alla posizione successiva\n");
    printf(" - Premi 0 per confermare la posizione selezionata\n");
    // Scorri le coordinate finche' non viene selezionata quella da posizionare
    unsigned int scelta, indice_attuale = 0;
    coord_t *coordinata_attuale;
    do {
        // Recupera la coordinata presente all'indice selezionato
        coordinata_attuale = elemento_ad_indice(coordinate, indice_attuale);
        printf("La posizione attuale e': (%2u,%2u)\n", coordinata_attuale->riga, coordinata_attuale->colonna);
        scelta = inserisci_numero_compreso("Seleziona un'opzione", 0, 2);
        switch(scelta) {
            // Sposta la coordinata indietro
            case 1: indice_attuale = sposta_indice(coordinate->dimensione, indice_attuale, -1);
                    break;
            // Sposta la coordinata avanti
            case 2: indice_attuale = sposta_indice(coordinate->dimensione, indice_attuale, 1);
                    break;
        }
    } while(scelta);
    // Ritorna la coordinata dopo aver confermato la selezione
    return elemento_ad_indice(coordinate, indice_attuale);
}
