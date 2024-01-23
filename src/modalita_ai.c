#include "../lib/modalita_ai.h"

#include <stdio.h>
#include <string.h>

#include "../lib/tessera.h"
#include "../lib/controlli.h"

void esegui_algoritmo(matrice_t *piano_gioco, vect_t *mano_giocatore) {
    // Crea la combinazione dentro cui salvare il risultato delle operazioni
    comb_t *risultato = crea_combinazione((coord_t) {0, 0}, false);
    // Tessera da prelevare ciascun turno
    tessera_t *da_inserire;
    
    // Continua la partita finche' sono disponbili tessere da posizionare
    while((da_inserire = most_frequent(piano_gioco, mano_giocatore, risultato)) != NULL) {
        // Stampa le tessere rimaste nella mano del giocatore
        stampa_mano(mano_giocatore);
        printf("Ho deciso di posizionare la tessera [%d|%d]\n", da_inserire->sinistro, da_inserire->destro);
        // Stabilisci se sia necessario ruotare la tessera
        if(risultato->rotazione) {
            ruota_tessera(da_inserire);
        }
        // In caso di tessera speciale esegui le opportune operazioni
        if(da_inserire->speciale) {
            funzionalita_aggiuntive(piano_gioco, da_inserire, risultato);
        }
        // Esegui l'inserimento della tessera sul piano di gioco
        preleva_tessera(piano_gioco, mano_giocatore, da_inserire, risultato->inserimento, risultato->orientamento);
        // Inizializza i parametri per eseguire i controlli
        inizializza_combinazione(risultato);
        // Stampa lo stato corrente del piano di gioco
        stampa_piano(piano_gioco);
    }
}

tessera_t *first_match(matrice_t *piano_gioco, vect_t *mano_giocatore, comb_t *risultato) {
    // Termina la partita dopo aver esaurite le tessere
    if(mano_giocatore->dimensione == 0) return NULL;
    do {
        // Calcola tutte le coordinate in cui e' possibile posizionare una tessera
        vect_t *coordinate = calcola_coordinate(piano_gioco, risultato->orientamento);
        // Per ciascuna tessera nella mano del giocatore
        for (size_t i=0; i < mano_giocatore->dimensione; i++) {
            // Memorizza l'indirizzo della tessera corrente
            tessera_t *tessera = elemento_ad_indice(mano_giocatore, i);
            // Per ciascuna posizione valida fornita
            for(size_t j=0; j<coordinate->dimensione; j++) {
                // Se una delle posizioni fornite permette l'inserimento della tessera
                if (mossa_legale(piano_gioco, elemento_ad_indice(coordinate, j), tessera, risultato)) {
                    // Aggiorna la nuova posizione di inserimento
                    risultato->inserimento = elemento_ad_indice(coordinate, j);
                    // Ritorna l'indirizzo della tessera trovata
                    return tessera;
                }
            }
        }
        // Libera la memoria allocata
        libera_vettore(coordinate);
    // Ripeti per le posizioni in verticale (0) e in orizzontale (1)
    } while(!risultato->orientamento++);
    // Non ho trovato nessuna tessera da posizionare
    return NULL;
}

/*

piano di gioco vuoto -> coordinata centrale



frequenze hor?
frequenze ver?

 1  2  3  4  5  6
[0][1][2][3][4][5]


 0  0  0  0  0  0   inizio controllo
 2  1  1  1  3  1   piano di gioco vuoto -> in verticale, no rotazione
 
[ 2| 6]  [ 5| 1]  [ 5| 3]  [ 4| 5]
        
      0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29
  0  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  {1  --  --  --  --  --  --  --  --  --  --  --  --  --  --
  1  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  5}  --  --  --  --  --  --  --  --  --  --  --  --  --  --

      0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29
  0  --  --  --  --  --  --  --  --  --  --  --  --  --  {5  [5  1]  [1  6]  {6  --  --  --  --  --  --  --  --  --  --  --
  1  --  --  --  --  --  --  --  --  --  --  --  [4  6]  6}  {6  --  [3  2]  2}  --  --  --  --  --  --  --  --  --  --  --
  2  --  --  --  --  --  --  --  --  --  --  --  --  --  --  3}  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --

do {
    
} hor/ver //il ciclo viene ripetuto 2 volte

*/

tessera_t *most_frequent(matrice_t *piano_gioco, vect_t *mano_giocatore, comb_t *risultato) {
    // Inizializza la tessera migliore
    tessera_t *migliore = NULL;
    // Crea un array per memorizzare le frequenze [1-6]
    unsigned int *frequenze = calloc(sizeof(unsigned int), 6);
    comb_t *temporaneo = crea_combinazione((coord_t) {0, 0}, false);
    // Calcola le coordinate di inserimento in base all'orientamento
    size_t speciali = mano_giocatore->dimensione / 4;
    do {
        vect_t *coordinate = calcola_coordinate(piano_gioco, temporaneo->orientamento);
        // Per ciascuna tessera normale nella mano del giocatore
        for(size_t t=0; t<mano_giocatore->dimensione - speciali; t++) {
            tessera_t *corrente = elemento_ad_indice(mano_giocatore, t);
            // Per ciascuna coordinata disponibile fornita
            for(size_t i=0; i<coordinate->dimensione; i++) {
                // Memorizza la coordinata attuale
                coord_t *coordinata = elemento_ad_indice(coordinate, i);
                // Stabilisci se e' possibile effettuare un inserimento
                if((mossa_legale(piano_gioco, coordinata, corrente, temporaneo)) != 0) {
                    // A questo punto dovrei avere le informazioni sulla posizione adiacente
                    estremo_t *estremo = &piano_gioco->posizione[temporaneo->adiacente->riga][temporaneo->adiacente->colonna];
                    if(!estremo->cardine) {
                        frequenze[corrente->sinistro - 1]++;
                        frequenze[corrente->destro - 1]++;
                    } else {
                        // Incrementa la frequenza dell'estremo adiacente
                        frequenze[estremo->valore - 1]++;
                    }
                    // Stabilisci se ho trovato una tessera migliore
                    if(migliore == NULL || sostituisci_frequenze(frequenze, corrente, migliore)) {
                        // Sostituisci la tessera migliore
                        migliore = corrente;
                        // Copia tutto
                        memcpy(risultato, temporaneo, sizeof(comb_t));
                        // Memorizza la coordinata di inserimento
                        risultato->inserimento = coordinata;
                    }
                }
            }
        }
    } while(!temporaneo->orientamento++);
    // Stampa frequenze
    for(size_t i=0; i<6; i++) {
        printf("%2d ", i+1);
    }
    printf("\n");
    for(size_t i=0; i<6; i++) {
        printf("%2u ", frequenze[i]);
    }
    printf("\n");
    // Libera la memoria allocata
    free(frequenze);
    libera_combinazione(temporaneo);
    // Ritorna la migliore tessera trovata
    return migliore;
}

bool sostituisci_frequenze(unsigned int *frequenze, tessera_t *corrente, tessera_t *migliore) {
    // Calcola il valore delle frequenze tramite gli estremi delle tessere
    unsigned int frequenza_corrente = frequenze[corrente->sinistro - 1] + frequenze[corrente->destro - 1];
    unsigned int frequenza_massima = frequenze[migliore->sinistro - 1] + frequenze[migliore->destro - 1];
    // Se la tessera che sto confrontando ha minor frequenza non considerarla
    if(frequenza_corrente < frequenza_massima) return false;
    // A parita' di frequenze, confronta i valori delle tessere
    if(frequenza_corrente == frequenza_massima && corrente->sinistro + corrente->destro < migliore->sinistro + migliore->destro) {
        // In quanto il valore della tessera e' minore lascio la precedente
        return false;
    }
    // La tessera migliore puo' essere sostituita
    return true;
}