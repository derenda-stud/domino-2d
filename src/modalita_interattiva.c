#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../lib/modalita_interattiva.h"
#include "../lib/tessera.h"
#include "../lib/controlli.h"

void stampa_turno(vect_t *mano_giocatore, matrice_t *piano_gioco) {
    // Continua finche' rimangono tessere in mano e si possono effettuare delle mosse
    while(mosse_disponibili(mano_giocatore, piano_gioco)) {
        // Stampa il piano di gioco nello stato corrente
        printf("Piano di gioco:\n");
        stampa_piano(piano_gioco);
        // Stampa le tessere presenti nella mano del giocatore
        printf("Mano del giocatore:\n");
        stampa_mano(mano_giocatore);
        // Inserisci la prossima mossa da effettuare
        inserisci_scelta(mano_giocatore, piano_gioco);
    }
    // Stampa finale prima del termine della partita
    printf("Piano di gioco finale:\n");
    stampa_piano(piano_gioco);
}

void inserisci_scelta(vect_t *mano_giocatore, matrice_t *piano_gioco) {
    // Fornisci all'utente le scelte da effettuare durante il turno
    printf(" - Premi 1 per posizionare una tessera\n");
    printf(" - Premi 2 per ruotare una tessera\n");
    int scelta = inserisci_numero_compreso("Seleziona un'opzione", 1, 2);
    // In base alla scelta selezionata
    switch (scelta) {
        case 1: {
            // Inserisci la tessera presente ad un determinato indice
            seleziona_tessera(mano_giocatore, piano_gioco);
        } break;
        case 2: {
            // Ruota la tessera presente ad un determinato indice
            ruota_tessera(inserisci_indice(mano_giocatore, "ruotare"));
        } break;
    }
}

tessera_t *inserisci_indice(vect_t *mano_giocatore, char *azione) {
    // Messaggio da stampare a terminale
    char messaggio[50] = "Inserisci l'indice della tessera da ";
    // Inserisci un numero compreso tra 0 e l'indice dell'ultima tessera
    int indice_tessera = inserisci_numero_compreso(strcat(messaggio, azione), 0, mano_giocatore->dimensione - 1);
    // Restituisci l'indirizzo della tessera selezionata
    return elemento_ad_indice(mano_giocatore, indice_tessera);
}

void seleziona_tessera(vect_t *mano_giocatore, matrice_t *piano_gioco) {
    // Memorizza l'indirizzo della tessera all'indice selezionato dall'utente
    tessera_t *tessera = inserisci_indice(mano_giocatore, "posizionare");
    // Chiedi all'utente come intende posizionare la tessera selezionata
    bool orientamento = inserisci_numero_compreso("Come vuoi posizionare la tessera? (0 in verticale, 1 in orizzontale)", 0, 1);
    // Creazione del vettore creato dalle posizioni valide
    vect_t *coordinate = calcola_coordinate(piano_gioco, orientamento);
    // Seleziona la coordinate dove effettuare l'inserimento
    coord_t *coordinata = seleziona_posizione(coordinate);
    // Creazione delle informazioni da memorizzare per l'inserimento
    comb_t *risultato = crea_combinazione(*coordinata, orientamento);
    // Controlla se sia possibile posizionare la tessera
    if(mossa_legale(piano_gioco, coordinata, tessera, risultato) != 1) {
        printf("Mossa non valida, riprova con un altra tessera\n");
    } else {
        // Controlla l'inserimento delle tessere speciali
        if(tessera->speciale) funzionalita_aggiuntive(piano_gioco, tessera, risultato);
        // Preleva la tessera secondo la posizione e l'orientamento indicato
        preleva_tessera(piano_gioco, mano_giocatore, tessera, coordinata, orientamento);
    }
    // Libera la memoria occupata
    libera_vettore(coordinate);
    libera_combinazione(risultato);
}

coord_t *seleziona_posizione(vect_t *coordinate) {
    // Stampa a schermo le nuove coordinate ottenute
    stampa_coordinate(coordinate);
    // Se e' disponibile solo una coordinata non richiedere la selezione
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
        printf("La posizione attuale e': (%2d,%2d)\n", coordinata_attuale->riga, coordinata_attuale->colonna);
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

/*
   v              
  ╔══╦══╦══╦══╦══╗
  ║  ║[5║6]║{6║  ║ 
  ╠══╬══╬══╬══╬══╣
> ║  ║  ║{1║1}║  ║
  ╠══╬══╬══╬══╬══╣
  ║  ║{4║4}║  ║  ║
  ╠══╬══╬══╬══╬══╣
  ║  ║3}║[3║2]║  ║
  ╠══╬══╬══╬══╬══╣
  ║  ║  ║  ║  ║  ║
  ╚══╩══╩══╩══╩══╝

Scegli riga
Precedente posizione libera     A
Prossima posizione libera       D
Inserisci la tessera corrente   'Invio'

*/