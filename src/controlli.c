#include "../lib/controlli.h"

#include <stdio.h>

unsigned int inserisci_numero_tessere() {
    int numero_tessere;
    printf("Inserisci il numero di tessere con cui vuoi giocare: ");
    do {
        scanf("%d", &numero_tessere);
        if (numero_tessere <= 0) {
            printf("Inserisci un numero valido: ");
        }
    } while (numero_tessere <= 0);
    return (unsigned) numero_tessere;
}

unsigned int inserisci_numero_compreso(char *messaggio, unsigned int minimo, unsigned int massimo) {
    int numero;
    printf("%s: ", messaggio);
    do {
        scanf("%d", &numero);
        if (numero < minimo || numero > massimo) {
            printf("Inserisci un numero valido: ");
        }
    } while (numero < minimo || numero > massimo);
    return (unsigned) numero;
}

bool posizione_valida(matrice_t *piano_gioco, estremo_t *da_confrontare, coord_t coordinata, bool orientamento) {
    // Controlla che la posizione attuale sia libera
    if(piano_gioco->posizione[coordinata.riga][coordinata.colonna].cardine) return false;
    // Per le tessere posizionate in orizzontale
    if(orientamento) {
        // Controlla che la posizione adiacente sia libera
        if(piano_gioco->posizione[coordinata.riga][coordinata.colonna + 1].cardine) return false;
    // Altrimenti per quelle posizionate in verticale
    } else {
        // Controlla di rientrare nella riga e che la posizione sottostante sia libera
        if(coordinata.riga + 1 < piano_gioco->righe && piano_gioco->posizione[coordinata.riga + 1][coordinata.colonna].cardine) return false;
    }
    // Controlla che rientri nel limite sinistro e che abbia un estremo collegato
    if(coordinata.colonna > 0 && piano_gioco->posizione[coordinata.riga][coordinata.colonna - 1].valore == da_confrontare->valore) return true;
    // Controlla che rientri nel limite destro e che abbia un estremo collegato
    if(coordinata.colonna < piano_gioco->colonne - (orientamento + 1) && piano_gioco->posizione[coordinata.riga][coordinata.colonna + orientamento + 1].valore == (da_confrontare + 1)->valore) return true;
    // Per tutti i casi rimanenti la posizione non risulta valida
    return false;
}

unsigned int sposta_indice(size_t posizioni, unsigned int attuale, int spostamento) {
    // Controlla che il nuovo indice rientri nelle dimensioni dell'array
    if(attuale + spostamento < 0 || attuale + spostamento > posizioni - 1)
        // Mantieni il valore dell'indice
        return attuale;
    // Modifica l'indice attuale in base allo spostamento
    return attuale += spostamento;
}

/*
int estremi_corrispondono(int estremo_piano, int primo, int secondo) {
    if(estremo_piano == primo) return 1;
    if(estremo_piano == secondo) return 2;
    return 0;
}
*/

bool mosse_disponibili(matrice_t *mano_giocatore, matrice_t *piano_gioco, coord_t *coordinate, size_t posizioni) {
    // Termina la partita dopo aver esaurite le tessere
    if(mano_giocatore->colonne == 0) return false;
    // Altrimenti per ogni tessera presente nella mano del giocatore
    for(size_t i=0; i<mano_giocatore->colonne; i++) {
        // Per ogni posizione valida
        for(size_t j=0; j<posizioni; j++) {
            // Controlla se la tessera combacia in quella posizione
            if(mossa_legale(mano_giocatore, piano_gioco, i, coordinate[j])) {
                return true;
            }
        }
    }
    // Non ho trovato nessuna mossa legale
    return false;
}

bool mossa_legale(matrice_t *mano_giocatore, matrice_t *piano_gioco, size_t indice, coord_t coordinata) {
    return true;
}