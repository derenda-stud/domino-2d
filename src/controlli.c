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

bool posizione_valida(matrice_t *piano_gioco, coord_t coordinata, bool orientamento) {
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
    // Controlla che abbia almeno un collegamento tra l'estremo sinistro e quello destro
    if(!piano_gioco->posizione[coordinata.riga][coordinata.colonna - 1].cardine && !piano_gioco->posizione[coordinata.riga][coordinata.colonna + orientamento + 1].cardine) return false;
    // Per tutti i casi rimanenti la posizione risulta valida
    return true;
}

/*
      0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29
  0  --  --  --  --  --  --  --  --  --  --  --  --  --  {5  [5  1]  [1  6]  {6  --  --  --  --  --  --  --  --  --  --  --
  1  --  --  --  --  --  --  --  --  --  --  --  [4  6]  6}  {6  --  --  --  2}  {3  --  --  --  --  --  --  --  --  --  --
  2  --  --  --  --  --  --  --  --  --  --  --  --  --  --  3}  --  --  --  --  2}  --  --  --  --  --  --  --  --  --  --
*/

unsigned int sposta_indice(size_t dimensione, unsigned int attuale, int spostamento) {
    // Controlla che il nuovo indice rientri nelle dimensioni dell'array
    if(attuale + spostamento < 0 || attuale + spostamento > dimensione - 1)
        // Mantieni il valore dell'indice
        return attuale;
    // Modifica l'indice attuale in base allo spostamento
    return attuale += spostamento;
}

bool mosse_disponibili(vect_t *mano_giocatore, matrice_t *piano_gioco) {
    // Termina la partita dopo aver esaurite le tessere
    if(mano_giocatore->dimensione == 0) return false;
    // Continua la partita se non sono ancora state posizionate tessere
    if(prima_posizione(piano_gioco, 0) > ultima_posizione(piano_gioco, 0)) return true;
    // Confronta gli inserimenti in verticale ed orizzontale
    for(int orientamento = 0; orientamento <= 1; orientamento++) {
        // Calcola tutte le coordinate che presentano posizioni valide
        vect_t *coordinate = calcola_coordinate(piano_gioco, orientamento);
        // Per ciascuna tessera nella mano del giocatore
        for(size_t tessera = 0; tessera < mano_giocatore->dimensione; tessera++) {
            // Controlla che possa essere posizionata in una delle coordinate
            if(mossa_legale(piano_gioco, coordinate, elemento_ad_indice(mano_giocatore, tessera), orientamento)) {
                // Prima di terminare la funzione libera la memoria allocata
                libera_vettore(coordinate);
                // Ho trovato una mossa legale
                return true;
            }
        }
        // Libera la memoria prima di passare al prossimo ciclo
        libera_vettore(coordinate);
    }
    // Non ci sono mosse disponibili
    return false;
}

int mossa_legale(matrice_t *piano_gioco, vect_t *coordinate, tessera_t *tessera, bool orientamento) {
    int corrispondenza;
    // Per ciascuna coordinata con posizione valida
    for(size_t i = 0; i < coordinate->dimensione; i++) {
        coord_t *coordinata = elemento_ad_indice(coordinate, i);
        // Valuta se almeno uno dei due estremi adiacenti ha una corrispondenza
        if((corrispondenza = estremi_corrispondono(piano_gioco, coordinata, tessera, orientamento)) != 0) {
            return corrispondenza;
        }
    }
    // Non ho trovato nessuna mossa legale
    return 0;
}

int estremi_corrispondono(matrice_t *piano_gioco, coord_t *coordinata, tessera_t *tessera, bool orientamento) {
    // Calcola l'indirizzo dell'estremo del piano in base alla posizione fornita
    estremo_t *estremo_piano = &piano_gioco->posizione[coordinata->riga][coordinata->colonna];
    // Controlla che l'estremo sinistro sia presente
    if((estremo_piano - 1)->cardine) {
        // Controlla se l'estremo sinistro corrisponda alla speciale [0|0]
        if((estremo_piano - 1)->valore == 0) return 1;
        // Quando l'estremo sinistro della tessera corrisponde mantieni l'ordine
        if((estremo_piano - 1)->valore == tessera->sinistro) return 1;
        // Quando l'estremo destro della tessera corrisponde ruota la tessera
        if((estremo_piano - 1)->valore == tessera->destro) return 2;
    }
    // Controlla che l'estremo destro sia presente
    if((estremo_piano + orientamento + 1)->cardine) {
        // Controlla se l'estremo destro corrisponda alla speciale [0|0]
        if((estremo_piano + orientamento + 1)->valore == 0) return 1;
        // Mantieni l'ordine se in orizzontale, ruota la tessera se in verticale
        if((estremo_piano + orientamento + 1)->valore == tessera->destro) return 1 + !orientamento;
        // Mantieni l'ordine se in verticale, ruota la tessera se in orizzontale
        if((estremo_piano + orientamento + 1)->valore == tessera->sinistro) return 1 + orientamento;
    }
    // Non ho trovato nessuna corrispondenza
    return 0;
}