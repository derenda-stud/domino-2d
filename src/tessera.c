#include <stdio.h>

#include "../lib/tessera.h"
#include "../lib/controlli.h"

void genera_estremi(vect_t *mano_giocatore) {
    // Per ciascuna posizione disponibile nella mano del giocatore
    for(size_t i=0; i<mano_giocatore->capacita; i++) {
        // Crea un estremo temporaneo da copiare dentro la mano
        estremo_t estremo_attuale;
        // Genera casualmente i valori contenuti nell'estremo
        estremo_attuale.valore = rand() % 6 + 1;
        // Collega i due estremi memorizzando i loro cardini
        estremo_attuale.cardine = 1 + (i % 2);
        // Inserisci l'estremo dentro la mano del giocatore
        inserimento_coda(mano_giocatore, &estremo_attuale);
    }
}

vect_t *calcola_coordinate(matrice_t *piano_gioco, estremo_t *da_confrontare, bool orientamento) {
    // Crea il vettore contenente le coordinate
    vect_t *coordinate = crea_vettore(sizeof(coord_t), 0);
    // Per ciascuna riga del piano di gioco
    for(size_t i=0; i<piano_gioco->righe; i++) {
        // Per ciascuna colonna del piano di gioco
        for(size_t j=0; j<piano_gioco->colonne; j++) {
            // Memorizza la posizione attuale
            coord_t attuale = {i, j};
            // Trova dove e' possibile posizionare una tessera
            if(posizione_valida(piano_gioco, da_confrontare, attuale, orientamento)) {
                // Inserisci la nuova coordinata valida
                inserimento_coda(coordinate, &attuale);
            }
        }
    }
    // Ritorna il nuovo vettore creato
    return coordinate;
}

void stampa_coordinate(vect_t *coordinate) {
    // Per ciascun elemento salvato dentro il vettore
    for(size_t i=0; i<coordinate->dimensione; i++) {
        // Preleva la coordinata attuale alla posizione indicata
        coord_t *attuale = elemento_ad_indice(coordinate, i);
        // Stampa formattata della riga e della colonna attuale
        printf("(%2d,%2d)\n", attuale->riga, attuale->colonna);
    }
}

void inserimento_orizzontale(matrice_t *piano_gioco, estremo_t *estremo_sinistro, coord_t *coordinata) {
    // Memorizza l'estremo sinistro nella posizione corrente
    piano_gioco->posizione[coordinata->riga][coordinata->colonna] = *estremo_sinistro;
    // Memorizza l'estremo destro nella posizione adiacente
    piano_gioco->posizione[coordinata->riga][coordinata->colonna + 1] = *(estremo_sinistro + 1);
}

// Rimuovi i due estremi posizionati dalla mano del giocatore
// for(int i=0; i<2; i++) rimuovi_ad_indice(mano_giocatore, indice);

void inserimento_verticale(matrice_t *piano_gioco, estremo_t *estremo_sinistro, coord_t *coordinata) {
    // Controlla se sia necessario aggiungere una nuova riga
    if(coordinata->riga + 1 >= piano_gioco->righe) aggiungi_riga(piano_gioco);
    // Memorizza l'estremo sinistro nella posizione corrente
    piano_gioco->posizione[coordinata->riga][coordinata->colonna] = *estremo_sinistro;
    // Memorizza l'estremo destro nella posizione sottostante
    piano_gioco->posizione[coordinata->riga + 1][coordinata->colonna] = *(estremo_sinistro + 1);
    // Incrementa l'orientamento dei cardini
    incrementa_cardini(piano_gioco, coordinata);
}

void incrementa_cardini(matrice_t *piano_gioco, coord_t *coordinata) {
    piano_gioco->posizione[coordinata->riga][coordinata->colonna].cardine += 2;
    piano_gioco->posizione[coordinata->riga + 1][coordinata->colonna].cardine += 2;
}