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
            // Ruota la tessere presente ad un determinato indice
            ruota_tessera(mano_giocatore, inserisci_indice(mano_giocatore, "ruotare"));
        } break;
    }
}

size_t inserisci_indice(vect_t *mano_giocatore, char *azione) {
    // Messaggio da stampare a terminale
    char messaggio[50] = "Inserisci l'indice della tessera da ";
    // Inserisci un numero compreso tra 0 e l'indice dell'ultimo estremo
    int indice_tessera = inserisci_numero_compreso(strcat(messaggio, azione), 0, mano_giocatore->dimensione - 1);
    // Restituisci l'indice dell'estremo sinistro
    return indice_tessera;
}

void seleziona_tessera(vect_t *mano_giocatore, matrice_t *piano_gioco) {
    // Trova i due estremi da prelevare dalla mano del giocatore
    size_t indice_tessera = inserisci_indice(mano_giocatore, "posizionare");
    // Chiedi all'utente come intende posizionare la tessera selezionata
    bool orientamento = inserisci_numero_compreso("Come vuoi posizionare la tessera? (0 in verticale, 1 in orizzontale)", 0, 1);
    // Per il primo inserimento valuta se posizionarla al centro
    if(prima_posizione(piano_gioco, 0) > ultima_posizione(piano_gioco, 0)) {
        coord_t centrale = {0, piano_gioco->colonne / 2 - 1};
        preleva_tessera(piano_gioco, mano_giocatore, indice_tessera, &centrale, orientamento);
        return;
    }
    // Restituisci il vettore creato dalle posizioni valide
    vect_t *coordinate = calcola_coordinate(piano_gioco, orientamento);
    // Seleziona la coordinate dove effettuare l'inserimento
    coord_t *coordinata = seleziona_posizione(coordinate);
    
    // if(estremi_corrispondono(piano_gioco, coordinata, tessera, orientamento))
    if(estremi_corrispondono(&piano_gioco->posizione[coordinata->riga][coordinata->colonna], elemento_ad_indice(mano_giocatore, indice_tessera), orientamento) != 1) {
        printf("Mossa non valida :c, riprova con un altra tessera\n");
        return;
    }
    // Preleva la tessera secondo l'orientamento indicato
    preleva_tessera(piano_gioco, mano_giocatore, indice_tessera, coordinata, orientamento);
    // Libera la memoria occupata
    libera_vettore(coordinate);
}

coord_t *seleziona_posizione(vect_t *coordinate) {
    // Stampa a schermo le nuove coordinate ottenute
    stampa_coordinate(coordinate);
    // Stampa il menu per indicare le possibile scelte
    printf("Seleziona dove posizionare la tessera:\n");
    printf(" - Premi 1 per scorrere alla posizione precedente\n");
    printf(" - Premi 2 per scorrere alla posizione successiva\n");
    printf(" - Premi 0 per confermare la posizione selezionata\n");
    
    unsigned int scelta, indice_attuale = 0;
    coord_t *coordinata_attuale;
    do {
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
    
    printf("Hai selezionato la posizione: (%2d,%2d)\n", coordinata_attuale->riga, coordinata_attuale->colonna);
    
    return elemento_ad_indice(coordinate, indice_attuale);
}

/*
   v                      
  ╔═╦═╦═╦═╦═╗
  ║ ║5║6║6║ ║ 
  ╠═╬═╬═╬═╬═╣
> ║ ║ ║ ║1║ ║
  ╠═╬═╬═╬═╬═╣
  ║ ║ ║ ║ ║ ║
  ╠═╬═╬═╬═╬═╣
  ║ ║ ║ ║ ║ ║
  ╠═╬═╬═╬═╬═╣
  ║ ║ ║ ║ ║ ║
  ╚═╩═╩═╩═╩═╝

Scegli riga
Precedente posizione libera     A
Prossima posizione libera       D
Inserisci la tessera corrente   'Invio'

*/