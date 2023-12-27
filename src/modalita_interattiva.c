#include <stdlib.h>
#include <stdbool.h>

#include "../lib/modalita_interattiva.h"
#include "../lib/controlli.h"

void stampa_turno(mano_t *mano_giocatore, piano_t *piano_gioco) {
    // Stampa per la prima volta le tessere della mano del giocatore
    stampa_mano(mano_giocatore);
    // Proseguimento della partita
    
    coord_t *posizioni = calcola_posizioni(piano_gioco, &dimensione);
    mosse_disponibili(mano_giocatore, piano_gioco, posizioni);
    
    // posizione successiva e precedente
/*     posizioni[i].riga, posizioni[i].colonna;
    // orizzontale sx
    piano_gioco->posizione[riga][colonna + 0].valore/.cardine;
    piano_gioco->posizione[riga][colonna - 1].valore/.cardine;
    // orizzontale dx
    piano_gioco->posizione[riga][colonna + 0].valore/.cardine;
    piano_gioco->posizione[riga][colonna + 1].valore/.cardine;
    // verticale
    piano_gioco->posizione[riga + 0][colonna].valore/.cardine;
    piano_gioco->posizione[riga + 1][colonna].valore/.cardine; */
    
    stampa_piano(piano_gioco);
    stampa_cursori(piano_gioco);
    coord_t temp = {1, 15};
}
/*
if(ha_premuto 'A') -> -1
if(ha_premuto 'D') -> +1

if(ha_premuto 'Invio') ->posiziona(cursore[i]);

cursore = sposta_cursore(cursori, 1/-1);

if(nuovo_indice < 0 || nuovo_indice > dimensione - 1) return cursore[attuale];
else return cursore[attuale + nuovo_indice];

*/

coord_t *calcola_posizioni(piano_t *piano_gioco) {
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

void stampa_posizioni(coord_t *posizioni, size_t dimensione) {
    for(size_t i=0; i<dimensione; i++) {
        printf("(%2d,%2d)\n", posizioni[i].x, posizioni[i].y);
    }
}