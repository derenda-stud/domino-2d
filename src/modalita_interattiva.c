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
            ruota_tessera(inserisci_indice(mano_giocatore, "ruotare"));
        } break;
    }
}

tessera_t *inserisci_indice(vect_t *mano_giocatore, char *azione) {
    // Messaggio da stampare a terminale
    char messaggio[50] = "Inserisci l'indice della tessera da ";
    // Inserisci un numero compreso tra 0 e l'indice dell'ultimo estremo
    int indice_tessera = inserisci_numero_compreso(strcat(messaggio, azione), 0, mano_giocatore->dimensione - 1);
    // Restituisci l'indice dell'estremo sinistro
    return elemento_ad_indice(mano_giocatore, indice_tessera);
}

void seleziona_tessera(vect_t *mano_giocatore, matrice_t *piano_gioco) {
    // Memorizza l'indirizzo della tessera all'indice selezionato dall'utente
    tessera_t *da_posizionare = inserisci_indice(mano_giocatore, "posizionare");
    // Chiedi all'utente come intende posizionare la tessera selezionata
    bool orientamento = inserisci_numero_compreso("Come vuoi posizionare la tessera? (0 in verticale, 1 in orizzontale)", 0, 1);
    // Per il primo inserimento valuta se posizionarla al centro
    if(prima_posizione(piano_gioco, 0) > ultima_posizione(piano_gioco, 0)) {
        // Controlla che la tessera selezionata non corrisponda alle [11|11] e [12|21]
        if(da_posizionare->speciale && da_posizionare->sinistro != 0) {
            printf("Mossa non valida, riprova con un altra tessera\n");
            return;
        }
        // Posiziona la tessera al centro del piano di gioco
        coord_t centrale = {0, piano_gioco->colonne / 2 - 1};
        preleva_tessera(piano_gioco, mano_giocatore, da_posizionare, &centrale, orientamento);
        return;
    }
    // Restituisci il vettore creato dalle posizioni valide
    vect_t *coordinate = calcola_coordinate(piano_gioco, orientamento);
    // Seleziona la coordinate dove effettuare l'inserimento
    coord_t *coordinata = seleziona_posizione(coordinate);
    
    comb_t *risultato = crea_combinazione(*coordinata, orientamento);
    // Controlla che gli estremi della tessera selezionata corrispondano con quelli sul piano
    if(estremi_corrispondono(piano_gioco, da_posizionare, risultato) != 1) {
        printf("Mossa non valida, riprova con un altra tessera\n");
        return;
    }
    // Controlla l'inserimento delle tessere speciali
    if(da_posizionare->speciale) {
        funzionalita_aggiuntive(piano_gioco, da_posizionare, risultato);
    }
    // Preleva la tessera secondo la posizione e l'orientamento indicato
    preleva_tessera(piano_gioco, mano_giocatore, da_posizionare, coordinata, orientamento);
    // Libera la memoria occupata
    libera_vettore(coordinate);
    libera_combinazione(risultato);
}

coord_t *seleziona_posizione(vect_t *coordinate) {
    // Stampa a schermo le nuove coordinate ottenute
    stampa_coordinate(coordinate);
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