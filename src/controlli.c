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
    // Se l'unica coordinate presente e' quella centrale
    if(coordinata->riga == 0 && coordinata->colonna == piano_gioco->colonne / 2 - 1) {
        // Controlla che non sia stata inserita una speciale diversa da [0|0]
        if(tessera->speciale && tessera->sinistro != 0) return false;
        // Altrimenti l'inserimento e' sempre valido
        return true;
    }
    // Recupera l'indirizzo dell'estremo del piano alla posizione indicata
    estremo_t *estremo_piano = &piano_gioco->posizione[coordinata->riga][coordinata->colonna];
    
    // Controlla che la tessera da inserire abbia almeno una corrispondenza
    int corrente = estremi_corrispondono(estremo_piano, coordinata, tessera, risultato);   
    // Per l'inserimento in orizzontale
    if(risultato->orientamento) {
        goto fine;
    // L'inserimento in verticale richiede invece ulteriori controlli
    } else {
        goto fine;
    }
    fine:
    // Imposta il valore della variabile booleana a [0/1]
    risultato->rotazione = corrente - 1;
    // Ritorna il valore ritornato dalla corrispondenza
    return corrente;
}

int estremi_corrispondono(estremo_t *estremo, coord_t *coordinata, tessera_t *tessera, comb_t *risultato) {
    // Memorizza i valori di controllo
    int controllo_sx = 0, controllo_dx = 0;
    // Controlla che esista l'estremo precedente
    if((estremo - 1)->cardine) {
        // Assegna la posizione precedente come coordinata adiacente
        *(risultato->adiacente) = (coord_t) {coordinata->riga, coordinata->colonna - 1};
        // Le tessere speciali non necessitano di controlli
        if(tessera->speciale) return true;
        // Controlla l'inserimento mantenendo l'ordine
        if((estremo - 1)->valore == tessera->sinistro) controllo_sx = 1;
        // Controlla l'inserimento girando la tessera
        else if((estremo - 1)->valore == tessera->destro) controllo_sx = 2;
    }
    // Controlla che esista l'estremo successivo
    if((estremo + risultato->orientamento + 1)->cardine) {
        // Assegna la posizione successiva come coordinata adiacente
        *(risultato->adiacente) = (coord_t) {coordinata->riga, coordinata->colonna + risultato->orientamento + 1};
        // Le tessere speciali non necessitano di controlli
        if(tessera->speciale) return true;
        /* In base all'orientamento della tessera l'estremo successivo corrisponde:
            - al valore sinistro in orizzontale -> inserisci girando la tessera
            - al valore sinistro in verticale   -> inserisci mantenendo l'ordine
        */
        if((estremo + risultato->orientamento + 1)->valore == tessera->sinistro) controllo_dx = 1 + risultato->orientamento;
        /*
            - al valore destro in orizzontale   -> inserisci mantenendo l'ordine
            - al valore destro in verticale     -> inserisci girando la tessera
        */
        else if((estremo + risultato->orientamento + 1)->valore == tessera->destro) controllo_dx = 1 + !risultato->orientamento;
    }
    // Il risultato del controllo e' stabilito tramite un'operazione bitwise
    int corrispondenza = controllo_sx ^ controllo_dx;
    // Se entrambi gli estremi appartengono alla speciale [0|0] posiziona mantenendo l'ordine
    if(!(estremo - 1)->valore && !(estremo + risultato->orientamento + 1)->valore) return true;
    // Non ci sono corrispondenze quando non ci sono estremi oppure i valori sono discordi
    if(corrispondenza == 0 || corrispondenza == 3) return false;
    // Altrimenti inserisci la tessera secondo la corrispondenza indicata
    return corrispondenza;
}