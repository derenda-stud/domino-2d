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
    for(size_t j=piano_gioco->colonne - 2; j>0; j--) {
        // Controlla che ci sia una posizione occupata
        if(piano_gioco->posizione[riga][j].cardine) {
            // Ritorna la colonna successiva libera
            return j + 1;
        }
    }
    // Non avendo trovato colonne, ritorno la prima
    return 0;
}

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
    // Inizializza la variabile contenente il risultato delle computazioni
    comb_t *risultato = crea_combinazione((coord_t) {0, 0}, false);
    do {
        // Calcola tutte le coordinate che presentano posizioni valide
        vect_t *coordinate = calcola_coordinate(piano_gioco, risultato->orientamento);
        // Per ciascuna tessera nella mano del giocatore
        for(size_t i = 0; i < mano_giocatore->dimensione; i++) {
            // Per ciascuna coordinata valida fornita
            for(size_t j=0; j<coordinate->dimensione; j++) {
                // Controlla se sia possibile inserire la tessera alla coordinata corrente
                if(mossa_legale(piano_gioco, elemento_ad_indice(coordinate, j), elemento_ad_indice(mano_giocatore, i), risultato)) {
                    // Prima di terminare la funzione libera la memoria allocata
                    libera_vettore(coordinate);
                    libera_combinazione(risultato);
                    // Posso continuare la partita
                    return true;
                }
            }
        }
        // Libera la memoria prima di passare al prossimo ciclo
        libera_vettore(coordinate);
    // Confronta gli inserimenti in verticale ed orizzontale
    } while(!risultato->orientamento++);
    // Libera la memoria prima di terminare la funzione
    libera_combinazione(risultato);
    // Non ci sono mosse disponibili
    return false;
}

int mossa_legale(matrice_t *piano_gioco, coord_t *coordinata, tessera_t *tessera, comb_t *risultato) {
    /* // Se l'unica coordinate presente e' quella centrale
    if(coordinata->riga == 0 && coordinata->colonna == piano_gioco->colonne / 2 - 1) {
        // Controlla che non sia stata inserita una speciale diversa da [0|0]
        if(tessera->speciale && tessera->sinistro != 0) return false;
        // Altrimenti l'inserimento e' sempre valido
        return true;
    } */
    // Nei casi rimanenti controlla che almeno uno degli estremi corrisponda
    int corrispondenza = estremi_corrispondono(piano_gioco, coordinata, tessera, risultato);
    risultato->rotazione = corrispondenza - 1;
    return corrispondenza;
}

int estremi_corrispondono(matrice_t *piano_gioco, coord_t *coordinata, tessera_t *tessera, comb_t *risultato) {
    // Calcola l'indirizzo dell'estremo del piano in base alla posizione fornita
    estremo_t *estremo_piano = &piano_gioco->posizione[coordinata->riga][coordinata->colonna];
    // Controlla che l'estremo sinistro sia presente
    if((estremo_piano - 1)->cardine) {
        // La coordinata adiacente corrisponde con quella precedente
        *(risultato->adiacente) = (coord_t) {coordinata->riga, coordinata->colonna - 1};
        // Inserisci mantenendo l'ordine quando stai lavorando con le tessere speciali
        if((estremo_piano - 1)->valore == 0 || tessera->speciale) return 1;
        // Quando l'estremo sinistro della tessera corrisponde mantieni l'ordine
        if((estremo_piano - 1)->valore == tessera->sinistro) return 1;
        // Quando l'estremo destro della tessera corrisponde ruota la tessera
        if((estremo_piano - 1)->valore == tessera->destro) return 2;
    }
    // Controlla che l'estremo destro sia presente
    if((estremo_piano + risultato->orientamento + 1)->cardine) {
        // La coordinata adiacente corrisponde con quella successiva in base all'orientamento
        *(risultato->adiacente) = (coord_t) {coordinata->riga, coordinata->colonna + risultato->orientamento + 1};
        // Inserisci mantenendo l'ordine quando stai lavorando con le tessere speciali
        if((estremo_piano + risultato->orientamento + 1)->valore == 0 || tessera->speciale) return 1;
        // Mantieni l'ordine se in orizzontale, ruota la tessera se in verticale
        if((estremo_piano + risultato->orientamento + 1)->valore == tessera->destro) return 1 + !risultato->orientamento;
        // Mantieni l'ordine se in verticale, ruota la tessera se in orizzontale
        if((estremo_piano + risultato->orientamento + 1)->valore == tessera->sinistro) return 1 + risultato->orientamento;
    }
    // Non ho trovato nessuna corrispondenza ???
    return !(estremo_piano - 1)->cardine && !(estremo_piano + risultato->orientamento + 1)->cardine;
}