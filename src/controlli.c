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
    if(orientamento){
        // Controlla che la posizione successiva sia libera
        if(piano_gioco->posizione[coordinata.riga][coordinata.colonna + 1].cardine) return false;
    // Altrimenti per quelle posizionate in verticale
    } else {
        // Controlla di rientrare nella riga e che la posizione sottostante sia libera
        if(piano_gioco->righe > coordinata.riga + 1 && piano_gioco->posizione[coordinata.riga + 1][coordinata.colonna].cardine) return false;
    }
    // Controlla che l'estremo posizionato a sinistra corrisponda
    if(piano_gioco->posizione[coordinata.riga][coordinata.colonna - 1].cardine && piano_gioco->posizione[coordinata.riga][coordinata.colonna - 1].valore != da_confrontare->valore) return false;
    // Controlla che l'estremo posizionato a destra corrisponda
    if(piano_gioco->posizione[coordinata.riga][coordinata.colonna + (orientamento + 1)].cardine && piano_gioco->posizione[coordinata.riga][coordinata.colonna + (orientamento + 1)].valore != (da_confrontare + orientamento)->valore) return false;
    // Controlla che almeno uno dei collegamenti sia valido
    if(!piano_gioco->posizione[coordinata.riga][coordinata.colonna - 1].cardine && !piano_gioco->posizione[coordinata.riga][coordinata.colonna + (orientamento + 1)].cardine) return false;
    // Per tutti i casi rimanenti la posizione risulta valida
    return true;
}

/*
      0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29
  0  --  --  --  --  --  --  --  --  --  --  --  --  --  {5  [5  1]  [1  6]  {6  --  --  --  --  --  --  --  --  --  --  --
  1  --  --  --  --  --  --  --  --  --  --  --  [4  6]  6}  {6  --  --  {3  2}  --  --  --  --  --  --  --  --  --  --  --
  2  --  --  --  --  --  --  --  --  --  --  --  --  --  --  3}  3   4   2}  --  --  --  --  --  --  --  --  --  --  --  --
  
    if(valore sinistro non coincide) false;
    if(valore destro non coincide) false;
    per tutti gli altri casi -> true;
*/

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

bool mosse_disponibili(vect_t *mano_giocatore, matrice_t *piano_gioco) {
    // Termina la partita dopo aver esaurite le tessere
    if(mano_giocatore->dimensione == 0) return false;
    // Continua la partita se non sono ancora state posizionate tessere
    if(prima_posizione(piano_gioco, 0) > ultima_posizione(piano_gioco, 0)) return true;
    // Altrimenti per ogni estremo presente nella mano del giocatore
    for(size_t i=0; i<mano_giocatore->dimensione; i+=2) {
        // Confronta gli inserimenti in verticale ed orizzontale
        for(size_t orientamento = 0; orientamento <= 1; orientamento++) {
            // Calcola le coordinate per la tessera corrente
            vect_t *coordinate = calcola_coordinate(piano_gioco, elemento_ad_indice(mano_giocatore, i), orientamento);
            // Controlla se esiste almeno una coordinata valida
            bool valida = coordinate->dimensione;
            // Libera la memoria allocata dalle coordinate
            libera_vettore(coordinate);
            // Termina il ciclo in presenza di una coordinata valida
            if(valida) return true;
        }
    }
    // Non ho trovato nessuna mossa legale
    return false;
}