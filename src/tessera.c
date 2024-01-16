#include <stdio.h>

#include "../lib/tessera.h"
#include "../lib/controlli.h"

void genera_estremi(vect_t *mano_giocatore) {
    // Per ciascuna posizione disponibile nella mano del giocatore
    for(size_t i=0; i<mano_giocatore->capacita; i++) {
        // Crea un estremo temporaneo da copiare dentro la mano
        tessera_t tessera_attuale;
        // Genera casualmente i valori contenuti nell'estremo
        tessera_attuale.sinistro = rand() % 6 + 1;
        tessera_attuale.destro = rand() % 6 + 1;
        // Inserisci l'estremo dentro la mano del giocatore
        inserimento_coda(mano_giocatore, &tessera_attuale);
    }
}

vect_t *calcola_coordinate(matrice_t *piano_gioco, bool orientamento) {
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
            if(posizione_valida(piano_gioco, attuale, orientamento)) {
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
    // Controlla se sia necessario aggiungere una nuova riga
    if(!orientamento && coordinata->riga + 1 >= piano_gioco->righe) aggiungi_riga(piano_gioco);
    // Inserisci la tessera selezionata sul piano di gioco
    tessera_t *tessera = elemento_ad_indice(mano_giocatore, indice);
    // Memorizza l'estremo sinistro nella posizione corrente
    piano_gioco->posizione[coordinata->riga][coordinata->colonna].valore = tessera->sinistro;
    // Memorizza l'estremo destro nella posizione successiva/sottostante
    piano_gioco->posizione[coordinata->riga + !orientamento][coordinata->colonna + orientamento].valore = tessera->destro;
    // Imposta i cardini delle due posizioni da occupare
    imposta_cardini(piano_gioco, coordinata, orientamento);
    // Rimuovi la tessera prelevata dalla mano del giocatore
    rimuovi_ad_indice(mano_giocatore, indice);
}

void imposta_cardini(matrice_t *piano_gioco, coord_t *coordinata, bool orientamento) {
    piano_gioco->posizione[coordinata->riga][coordinata->colonna].cardine = 1 + (!orientamento * 2);
    piano_gioco->posizione[coordinata->riga + !orientamento][coordinata->colonna + orientamento].cardine = 2 + (!orientamento * 2);
}

void ruota_tessera(vect_t *mano_giocatore, size_t indice) {
    tessera_t *tessera = elemento_ad_indice(mano_giocatore, indice);
    unsigned int temp = tessera->destro;
    tessera->destro = tessera->sinistro;
    tessera->sinistro = temp;
}