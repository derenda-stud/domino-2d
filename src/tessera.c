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
        // Calcolo la prima e l'ultima posizione utile
        unsigned int inizio = prima_posizione(piano_gioco, i) - orientamento;
        unsigned int fine = ultima_posizione(piano_gioco, i);
        // Scorri tutte le posizioni utili della riga corrente
        for(size_t j=inizio; j<=fine; j++) {
            // Memorizza la coordinata attuale
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

unsigned int prima_posizione(matrice_t *piano_gioco, unsigned int riga) {
    for(size_t j=0; j<piano_gioco->colonne - 2; j++) {
        if(piano_gioco->posizione[riga][j].cardine) {
            return j - 1;
        }
    }
    return piano_gioco->colonne;
}

unsigned int ultima_posizione(matrice_t *piano_gioco, unsigned int riga) {
    for(size_t j=piano_gioco->colonne - 2; j>=0; j--) {
        if(piano_gioco->posizione[riga][j].cardine) {
            return j + 1;
        }
    }
    return 0;
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

void preleva_tessera(matrice_t *piano_gioco, vect_t *mano_giocatore, size_t indice, coord_t *coordinata, bool orientamento) {
    // Inserisci la tessera selezionata sul piano di gioco
    if(orientamento) {
        inserimento_orizzontale(piano_gioco, elemento_ad_indice(mano_giocatore, indice), coordinata);
    } else {
        inserimento_verticale(piano_gioco, elemento_ad_indice(mano_giocatore, indice), coordinata);
    }
    // Rimuovi i due estremi posizionati dalla mano del giocatore
    for(size_t i=0; i<2; i++) {
        rimuovi_ad_indice(mano_giocatore, indice);
    }
}

void inserimento_orizzontale(matrice_t *piano_gioco, estremo_t *estremo_sinistro, coord_t *coordinata) {
    // Memorizza l'estremo sinistro nella posizione corrente
    piano_gioco->posizione[coordinata->riga][coordinata->colonna] = *estremo_sinistro;
    // Memorizza l'estremo destro nella posizione adiacente
    piano_gioco->posizione[coordinata->riga][coordinata->colonna + 1] = *(estremo_sinistro + 1);
}

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

void ruota_tessera(vect_t *mano_giocatore, size_t indice) {
    // Preleva il primo estremo alla posizione indicata
    estremo_t *sinistro = elemento_ad_indice(mano_giocatore, indice);
    // Effettua lo scambio del valore dei due estremi
    unsigned int valore_temporaneo = sinistro->valore;
    sinistro->valore = (sinistro + 1)->valore;
    (sinistro + 1)->valore = valore_temporaneo;
}