#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../lib/modalita_interattiva.h"
#include "../lib/controlli.h"

void stampa_turno(matrice_t *mano_giocatore, matrice_t *piano_gioco) {
    // Continua finche' rimangono tessere in mano e sono rimaste mosse disponibili
    // while(mosse_disponibili(mano_giocatore, piano_gioco));
    // Stampa il piano di gioco nello stato corrente
    printf("Piano di gioco:\n");
    stampa_matrice(piano_gioco);
    // Stampa le tessere presenti nella mano del giocatore
    printf("Mano del giocatore:\n");
    stampa_matrice(mano_giocatore);
    // Inserisci la prossima mossa da effettuare
    printf(" - Premi 1 per posizionare una tessera\n");
    printf(" - Premi 2 per ruotare una tessera\n");
    inserisci_scelta(mano_giocatore, piano_gioco);
}

void inserisci_scelta(matrice_t *mano_giocatore, matrice_t *piano_gioco) {
    int scelta = inserisci_numero_compreso("Seleziona un'opzione", 1, 2);
    switch (scelta) {
        case 1: {
            // Inserisci la tessera presente ad un determinato indice
            seleziona_tessera(mano_giocatore, piano_gioco);
        } break;
        case 2: {
            // Ruota la tessere presente ad un determinato indice
            // ruota_tessera(inserisci_indice(mano_giocatore, "ruotare"));
        } break;
    }
}

void seleziona_tessera(matrice_t *mano_giocatore, matrice_t *piano_gioco) {
    // Trova la tessere da prelevare dalla mano del giocatore
    estremo_t *da_posizionare = inserisci_indice(mano_giocatore, "posizionare");
    
    bool orizzontale = inserisci_numero_compreso("Come vuoi posizionare la tessera? (1 in orizzontale, 0 in verticale)", 0, 1);
    
    // Crea un nuovo vettore contenete le coordinate delle posizioni valide
    size_t posizioni = 0;
    coord_t *coordinate = calcola_coordinate(piano_gioco, da_posizionare, &posizioni, orizzontale);
    
    // Controlla se sia possibile effettuare almeno una mossa
    if(!posizioni) {
        printf("Nessuna mossa disponibile con questa tessera\n");
        return;
    }
    
    printf("Ho calcolato le coordinate\n");
    
    // Stampa a schermo le nuove coordinate ottenute
    stampa_coordinate(coordinate, posizioni);
    
    printf("Seleziona dove posizionare la tessera:\n");
    printf(" - Premi 1 per scorrere alla posizione precedente\n");
    printf(" - Premi 2 per scorrere alla posizione successiva\n");
    printf(" - Premi 0 per confermare la posizione selezionata\n"); /* TODO ... */
    
    unsigned int scelta, attuale = 0;
    do {
        printf("La posizione attuale e': (%2d,%2d)\n", coordinate[attuale].riga, coordinate[attuale].colonna);
        scelta = inserisci_numero_compreso("Seleziona un'opzione", 0, 2);
        switch(scelta) {
            // Sposta la coordinata indietro
            case 1: attuale = sposta_indice(posizioni, attuale, -1);
                    break;
            // Sposta la coordinata avanti
            case 2: attuale = sposta_indice(posizioni, attuale, 1);
                    break;
        }
    } while(scelta);
    
    printf("Hai selezionato la posizione: (%2d,%2d)\n", coordinate[attuale].riga, coordinate[attuale].colonna);
    // Libera la memoria occupata
    free(coordinate);
}

estremo_t *inserisci_indice(matrice_t *mano_giocatore, char *azione) {
    // Messaggio da stampare a terminale
    char messaggio[50] = "Inserisci l'indice della tessera da ";
    // Inserisci un numero compreso tra 0 e l'indice dell'ultima tessera
    int indice_tessera = inserisci_numero_compreso(strcat(messaggio, azione), 0, mano_giocatore->colonne - 1);
    // Restituisci la tessera trovata all'indice indicato
    return &mano_giocatore->posizione[0][indice_tessera * 2];
}

/*
   v   riga=y, colonna=x                   
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

while(mosse_disponibili) {
    menu_scelta()
}

_menu_scelta_
switch(scelta): {
    case A -> sposta(-1)
    case D -> sposta(+1)
    case Invio -> posiziona(attuale)
}

    if(nuovo_indice < 0 || nuovo_indice > posizioni->dimensione - 1) return posizioni->coordinate[attuale];
    else return cursore[attuale + nuovo_indice];
*/