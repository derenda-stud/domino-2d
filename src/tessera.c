#include <stdio.h>

#include "../lib/tessera.h"
#include "../lib/controlli.h"

void genera_tessere(vect_t *mano_giocatore) {
    // Calcola la percentuale di tessere speciali
    int dimensione_speciali = mano_giocatore->capacita / 2;
    // Per le posizioni in cui inserire tessere normali
    for(size_t i=0; i<mano_giocatore->capacita - dimensione_speciali; i++) {
        // Crea una tessera temporanea da copiare dentro la mano
        tessera_t tessera_attuale;
        // Genera casualmente i valori contenuti nella tessera
        tessera_attuale.sinistro = rand() % 6 + 1;
        tessera_attuale.destro = rand() % 6 + 1;
        tessera_attuale.speciale = false;
        // Inserisci la tessera dentro la mano del giocatore
        inserimento_coda(mano_giocatore, &tessera_attuale);
    }
    // Struttura contenente le diverse tessere speciali
    tessera_t tessere_speciali[3] = {{0, 0, true}, {11, 11, true}, {12, 21, true}};
    // Per le posizioni rimanenti nella mano del giocatore
    for(size_t i=0; i<dimensione_speciali; i++) {
        // Seleziona casualmente una delle tessere speciali
        tessera_t speciale = tessere_speciali[rand() % 3];
        // Inserisci la tessera speciale generata nella mano
        inserimento_coda(mano_giocatore, &speciale);
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
    // Per ciascuna colonna fino a raggiungere il limite sinistro
    for(size_t j=0; j<piano_gioco->colonne - 2; j++) {
        // Controlla che ci sia una posizione occupata
        if(piano_gioco->posizione[riga][j].cardine) {
            // Ritorna la colonna precedente libera
            return j - 1;
        }
    }
    // Non avendo trovato colonne, ritorno l'ultima
    return piano_gioco->colonne - 1;
}

unsigned int ultima_posizione(matrice_t *piano_gioco, unsigned int riga) {
    // Dal limite sinistro fino alla prima colonna valida
    for(size_t j=piano_gioco->colonne - 2; j>=0; j--) {
        // Controlla che ci sia una posizione occupata
        if(piano_gioco->posizione[riga][j].cardine) {
            // Ritorna la colonna successiva libera
            return j + 1;
        }
    }
    // Non avendo trovato colonne, ritorno la prima
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

void preleva_tessera(matrice_t *piano_gioco, vect_t *mano_giocatore, tessera_t *tessera, coord_t *coordinata, bool orientamento) {
    // Controlla se sia necessario aggiungere una nuova riga
    if(!orientamento && coordinata->riga + 1 >= piano_gioco->righe) aggiungi_riga(piano_gioco);
    // Memorizza l'estremo sinistro nella posizione corrente
    piano_gioco->posizione[coordinata->riga][coordinata->colonna].valore = tessera->sinistro;
    // Memorizza l'estremo destro nella posizione successiva/sottostante
    piano_gioco->posizione[coordinata->riga + !orientamento][coordinata->colonna + orientamento].valore = tessera->destro;
    // Imposta i cardini delle due posizioni da occupare
    imposta_cardini(piano_gioco, coordinata, orientamento);
    // Rimuovi la tessera prelevata dalla mano del giocatore
    rimuovi_elemento(mano_giocatore, tessera);
}

void imposta_cardini(matrice_t *piano_gioco, coord_t *coordinata, bool orientamento) {
    // Il valore dei cardini corrisponde ad 1 e 2 per l'inserimento orizzontale, 3 e 4 in verticale
    piano_gioco->posizione[coordinata->riga][coordinata->colonna].cardine = 1 + (!orientamento * 2);
    piano_gioco->posizione[coordinata->riga + !orientamento][coordinata->colonna + orientamento].cardine = 2 + (!orientamento * 2);
}

void ruota_tessera(tessera_t *tessera) {
    // Esegui lo scambio di due variabili
    unsigned int temp = tessera->destro;
    tessera->destro = tessera->sinistro;
    tessera->sinistro = temp;
}

void incrementa_estremi(matrice_t *piano_gioco) {
    // Per ciascuna riga del piano di gioco
    for(size_t i=0; i<piano_gioco->righe; i++) {
        // Per ciascuna colonna del piano di gioco
        for(size_t j=0; j<piano_gioco->colonne; j++) {
            // Controlla che l'estremo attuale sia presente
            if(piano_gioco->posizione[i][j].cardine) {
                // Incrementa il valore dell'estremo corrente
                piano_gioco->posizione[i][j].valore = (piano_gioco->posizione[i][j].valore % 6) + 1;
            }
        }
    }
}

void funzionalita_aggiuntive(matrice_t *piano_gioco, tessera_t *tessera, comb_t *risultato) {
    // In base al valore della tessera da posizionare
    switch(tessera->sinistro) {
        // Copia i valori della tessera con corrispondenza
        case 11: {
            // Incrementa tutti gli estremi sul piano di gioco
            incrementa_estremi(piano_gioco);
            // Memorizza come valore l'estremo che ha una corrispondenza
            tessera->sinistro = tessera->destro = piano_gioco->posizione[risultato->adiacente->riga][risultato->adiacente->colonna].valore;
            break;
        }
        // Specchia gli estremi della tessera da posizionare
        case 12: case 21: {
            // In base al cardine dell'estremo con una corrispondenza
            switch(piano_gioco->posizione[risultato->adiacente->riga][risultato->adiacente->colonna].cardine) {
                // E' inserita in orizzontale ed ha un collegamento con l'estremo successivo 
                case 1: tessera->sinistro = piano_gioco->posizione[risultato->adiacente->riga][risultato->adiacente->colonna + 1].valore;
                        break;
                // E' inserita in orizzontale ed ha un collegamento con l'estremo precedente
                case 2: tessera->sinistro = piano_gioco->posizione[risultato->adiacente->riga][risultato->adiacente->colonna - 1].valore;
                        break;
                // E' inserita in verticale ed ha un collegamento con l'estremo sottostante
                case 3: tessera->sinistro = piano_gioco->posizione[risultato->adiacente->riga + 1][risultato->adiacente->colonna].valore;
                        break;
                // E' inserita in verticale ed ha un collegamento con l'estremo superiore
                case 4: tessera->sinistro = piano_gioco->posizione[risultato->adiacente->riga - 1][risultato->adiacente->colonna].valore;
                        break;
            }
            // Memorizza il valore dell'estremo destro pari alla posizione adiacente
            tessera->destro = piano_gioco->posizione[risultato->adiacente->riga][risultato->adiacente->colonna].valore;
            break;
        }
        // Per la tessera [0|0] non sono necessari controlli
    }
}