#include "../lib/vettore.h"

#include <string.h>

vect_t *crea_vettore(size_t spazio, size_t capacita_iniziale) {
    // Alloca la memoria per il puntatore iniziale
    vect_t *vettore = malloc(sizeof(vect_t));
    // Alloca lo spazio necessario a memorizzare gli elementi richiesti
    vettore->posizione = calloc(capacita_iniziale, spazio);
    // Inizializza i parametri del vettore
    vettore->spazio = spazio;
    vettore->dimensione = 0;
    vettore->capacita = capacita_iniziale;
    // Restituisci il puntatore alla struttura dati creata
    return vettore;
}

void libera_vettore(vect_t *vettore) {
    // Libera la memoria degli elementi contenuti nel vettore
    free(vettore->posizione);
    vettore->posizione = NULL;
    // Inizializza i parametri del vettore
    vettore->spazio = 0;
    vettore->dimensione = 0;
    vettore->capacita = 0;
    // Libera la memoria del puntatore iniziale
    free(vettore);
}

void *elemento_ad_indice(vect_t *vettore, size_t indice) {
    // Calcola l'indirizzo effettivo del puntatore
    return vettore->posizione + (vettore->spazio * indice);
}

void inserimento_coda(vect_t *vettore, void *elemento) {
    // Controlla che sia possibile effettuare l'inserimento
    if(vettore->capacita <= vettore->dimensione) {
        // Incrementa la capacita' del vettore
        vettore->posizione = realloc(vettore->posizione, vettore->spazio * (vettore->capacita + 1));
        vettore->capacita += 1;
    }
    // Inserisci l'elemento nell'ultima posizione del vettore
    memcpy(elemento_ad_indice(vettore, vettore->dimensione), elemento, vettore->spazio);
    // Incrementa la dimensione del vettore
    vettore->dimensione += 1;
}

void rimuovi_elemento(vect_t *vettore, void *elemento) {
    // Recupera il numero di byte da copiare
    size_t quantita = elemento_ad_indice(vettore, vettore->dimensione - 1) - elemento;
    // Sovrascrivi tutti i valori precedenti a partire dalla posizione successiva
    memmove(elemento, elemento + vettore->spazio, quantita);
    // Decrementa la dimensione effettiva
    vettore->dimensione -= 1;
}