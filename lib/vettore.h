#ifndef vettore_h
#define vettore_h

#include <stdlib.h>

// Struttura dati di un vettore di tipo generico
typedef struct s_vect {
    void *posizione;    // Puntatore al primo elemento
    size_t spazio;      // Spazio occupato da ciascun elemento
    size_t dimensione;  // Memoria attualmente occupata
    size_t capacita;    // Memoria totale allocata
} vect_t;

// Crea un nuovo vettore inizializzandolo con una capacita' iniziale
vect_t *crea_vettore(size_t spazio, size_t capacita_iniziale);
// Libera la memoria occupata da un vettore
void libera_vettore(vect_t *vettore);
// Restituisce l'indirizzo di un elemento ad un particolare indice
void *elemento_ad_indice(vect_t *vettore, size_t indice);
// Inserisci un nuovo elemento in coda al vettore
void inserimento_coda(vect_t *vettore, void *elemento);
// Rimuovi un elemento di un vettore ad un particolare indice
void rimuovi_ad_indice(vect_t *vettore, size_t indice);

#endif