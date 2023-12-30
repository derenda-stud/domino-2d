#include <stdlib.h>
#include <stdbool.h>

#include "../lib/modalita_interattiva.h"
#include "../lib/controlli.h"

void stampa_turno(matrice_t *mano_giocatore, matrice_t *piano_gioco) {
    // Crea un nuovo vettore contenete le coordinate delle posizioni valide
    size_t posizioni = 0;
    coord_t *coordinate = calcola_coordinate(piano_gioco, &posizioni);
    // Continua finche' rimangono tessere in mano e sono rimaste mosse disponibili
    while(mosse_disponibili(mano_giocatore, piano_gioco, coordinate, posizioni)) {
        // Stampa il piano di gioco nello stato corrente
        printf("Piano di gioco:\n");
        stampa_matrice(piano_gioco);
        // Stampa le tessere presenti nella mano del giocatore
        printf("Mano del giocatore:\n");
        stampa_matrice(mano_giocatore);
        // Inserisci la prossima mossa da effettuare
        printf(" - Premi 1 per posizionare una tessera\n");
        printf(" - Premi 2 per ruotare una tessera\n");
        printf("Inserisci l'indice della tessera da posizionare/ruotare:\n");
        printf("Come vuoi posizionare la tessera? (1 in orizzontale, 0 in verticale):\n");
        
        printf("Seleziona dove posizionare la tessera:\n");
        printf(" - Premi 1 per scorrere alla posizione precedente\n");
        printf(" - Premi 2 per scorrere alla posizione successiva\n");
        printf(" - Premi 0 per confermare la posizione selezionata\n");
        
        break;
    }
    // Stampa a schermo le nuove coordinate ottenute
    stampa_coordinate(coordinate, posizioni);
    // Libera la memoria occupata
    free(coordinate);
}

/*
if(ha_premuto 'A') -> -1
if(ha_premuto 'D') -> +1

if(ha_premuto 'Invio') ->posiziona(cursore[i]);

cursore = sposta_cursore(cursori, 1/-1);

if(nuovo_indice < 0 || nuovo_indice > dimensione - 1) return cursore[attuale];
else return cursore[attuale + nuovo_indice];

*/


//   0        1       2       3       4       5       6
// (0, 12) ( 0,19) ( 1,10) ( 1,15) ( 1,19) ( 2,13) ( 2,15)

// coord_t sposta_posizione(pos_t *posizioni, int nuovo_indice) {
    
// }

/*

           v           
  ╔═╦═╦═╦═╦═╗
> ║ ║5║6║6║ ║
  ╠═╬═╬═╬═╬═╣
  ║ ║ ║ ║1║ ║
  ╠═╬═╬═╬═╬═╣
  ║ ║ ║ ║ ║ ║
  ╠═╬═╬═╬═╬═╣
  ║ ║ ║ ║ ║ ║
  ╠═╬═╬═╬═╬═╣
  ║ ║ ║ ║ ║ ║
  ╚═╩═╩═╩═╩═╝

Scegli riga
Precedente posizione libera     A
Prossima posizione libera       D
Inserisci la tessera corrente   'Invio'

while(mosse_disponibili) {
    menu_scelta()
}

_menu_scelta_
switch(scelta): {
    case A -> sposta(-1)
    case D -> sposta(+1)
    case Invio -> posiziona(attuale)
}

    if(nuovo_indice < 0 || nuovo_indice > posizioni->dimensione - 1) return posizioni->coordinate[attuale];
    else return cursore[attuale + nuovo_indice];
*/