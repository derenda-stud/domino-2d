#include <stdlib.h>
#include <stdbool.h>

#include "../lib/modalita_interattiva.h"

void stampa_turno(mano_t *mano_giocatore, piano_t *piano_gioco) {
    // Stampa per la prima volta le tessere della mano del giocatore
    stampa_mano(mano_giocatore);
    // Proseguimento della partita
    stampa_piano(piano_gioco);
    stampa_cursori(piano_gioco);
}

coord_t cursione_precedente(piano_t *piano_gioco, coord_t successivo) {
    // Partendo dalla riga della coordinata successiva
    for(int i=successivo.x; i>=0; i--) {
        // Scorri tutte le colonne a ritroso
        int j;
        // Per il primo controllo comincia dalla colonna precedente
        if(i == successivo.x) j = successivo.y - 1;
        // Altrimenti comincia dall'ultima colonna
        else j = piano_gioco->colonne - 1;
        while(j>=0) {
            // Trova una posizione valida
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
        while(j<piano_gioco->colonne) {
            // Trova una posizione valida
            j++;
        }
    }
    // Se scorrendo il piano non ho trovato nuove posizioni ritorno quella attuale
    return precedente;
}

void stampa_cursori(piano_t *piano_gioco) {
    printf("Posizioni valide in relazione al centro:\n");
    unsigned int centro = piano_gioco->colonne / 2;
    // Per ciascuna riga
    for(int i=0; i<piano_gioco->righe; i++) {
        // Per ciascuna colonna
        for(int j=0; j<piano_gioco->colonne - 1; j++) {
            // Trova dove e' possibile posizionare una tessera
            // Vuoto sx e pieno dx -> inserisci a sx
            if(!piano_gioco->posizione[i][j].cardine && piano_gioco->posizione[i][j + 1].cardine) {
                printf("Sx: (%d, %d)\n", i, j - centro);
            }
            // Pieno sx e vuoto dx -> inserisci a dx
            if(j != 0 && piano_gioco->posizione[i][j - 1].cardine && !piano_gioco->posizione[i][j].cardine) {
                printf("Dx: (%d, %d)\n", i, j - centro);
            }
            /*
            if((bool) piano_gioco->posizione[i][j].cardine != (bool) piano_gioco->posizione[i][j + 1].cardine) {
                printf("(%d,%d)\n", i, j - centro);
            }
            */
        }
    }
}

// coordinata_t sposta_cursore(piano_t *piano_gioco, coordinata_t attuale) {
//     // Per ciascuna riga
//     for(int i=attuale->x; i<piano_gioco->righe; i++) {
//         // Per ciascuna colonna
//         for(int j=attuale->y; i<piano_gioco->colonne - 1; i++) {
//             // Trova dove e' possibile posizionare una tessera
//             // = Trova due estremi discordanti (uno vuoto e uno pieno)
//             if((bool) piano_gioco->posizione[i][j].cardine != (bool) piano_gioco->posizione[i][j].cardine) {
//                 coordinata_t nuova = {i, j};
//                 return nuova;
//             }
//         }
//     }
//     // Sono arrivato alla fine del piano di gioco
//     return NULL;
// }