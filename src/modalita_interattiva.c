#include <stdlib.h>
#include <stdbool.h>

#include "../lib/modalita_interattiva.h"
#include "../lib/controlli.h"

void stampa_turno(mano_t *mano_giocatore, piano_t *piano_gioco) {
    // Stampa per la prima volta le tessere della mano del giocatore
    stampa_mano(mano_giocatore);
    // Proseguimento della partita
    stampa_piano(piano_gioco);
    stampa_cursori(piano_gioco);
    coord_t temp = {1, 15};
    coord_t precedente = temp, successivo = temp;
    for(int i=0; i<10; i++) {
        printf("Precedente: (%2d,%2d)\n", precedente.x, precedente.y);
        printf("Successivo: (%2d,%2d)\n\n", successivo.x, successivo.y);
        precedente = cursore_precedente(piano_gioco, precedente);
        successivo = cursore_successivo(piano_gioco, successivo);
    }
}

coord_t cursore_precedente(piano_t *piano_gioco, coord_t successivo) {
    // Partendo dalla riga della coordinata successiva
    for(int i=successivo.x; i>=0; i--) {
        // Scorri tutte le colonne a ritroso
        int j;
        // Per il primo controllo comincia dalla colonna precedente
        if(i == successivo.x) j = successivo.y - 1;
        // Altrimenti comincia dall'ultima colonna
        else j = piano_gioco->colonne - 1;
        while(j>=0) {
            // Se ho trovato una posizione valida
            if(posizione_valida(piano_gioco, i, j)) {
                // Ritorno le nuove coordinate
                return (coord_t) {i, j};
            }
            // Vai alla colonna precedente
            j--;
        }
    }
    // Se scorrendo il piano non ho trovato nuove posizioni ritorno quella attuale
    return successivo;
}

coord_t cursore_successivo(piano_t *piano_gioco, coord_t precedente) {
    // Partendo dalla riga della coordinata precedente
    for(int i=precedente.x; i<piano_gioco->righe; i++) {
        // Scorri tutte le colonne in avanti
        int j;
        // Per il primo controllo comincia dalla colonna successiva
        if(i == precedente.x) j = precedente.y + 1;
        // Altrimenti comincia dalla prima colonna
        else j = 0;
        while(j<piano_gioco->colonne - 1) {
            // Se ho trovato una posizione valida
            if(posizione_valida(piano_gioco, i, j)) {
                // Ritorno le nuove coordinate
                return (coord_t) {i, j};
            }
            // Vai alla colonna successiva
            j++;
        }
    }
    // Se scorrendo il piano non ho trovato nuove posizioni ritorno quella attuale
    return precedente;
}

void stampa_cursori(piano_t *piano_gioco) {
    printf("Posizioni valide in relazione al centro:\n");
    // Per ciascuna riga
    for(size_t i=0; i<piano_gioco->righe; i++) {
        // Per ciascuna colonna
        for(size_t j=0; j<piano_gioco->colonne - 1; j++) {
            // Trova dove e' possibile posizionare una tessera
            if(posizione_valida(piano_gioco, i, j)) {
                printf("(%2d,%2d)\n", i, j);
            }
        }
    }
}