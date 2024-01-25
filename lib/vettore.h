#ifndef vettore_h
#define vettore_h

#include <stdlib.h>

/// @brief Struttura dati di un vettore di tipo generico
typedef struct s_vect {
    void *posizione;    ///< Puntatore al primo elemento
    size_t spazio;      ///< Spazio occupato da ciascun elemento
    size_t dimensione;  ///< Memoria attualmente occupata
    size_t capacita;    ///< Memoria totale allocata
} vect_t;

/// @brief Crea un nuovo vettore inizializzandolo con una capacita' iniziale
/// @param spazio Spazio occupato dal tipo dell'elemento da memorizzare
/// @param capacita_iniziale Numero iniziale di elementi da memorizzare
/// @return Il puntatore al nuovo vettore creato
vect_t *crea_vettore(size_t spazio, size_t capacita_iniziale);

/// @brief Libera la memoria occupata da un vettore
/// @param vettore Puntatore al vettore da liberare
void libera_vettore(vect_t *vettore);

/// @brief Restituisce l'indirizzo di un elemento ad un particolare indice
/// @param vettore Vettore per ottenere la posizione al primo elemento
/// @param indice Indice numerico dell'elemento richiesto
/// @return L'indirizzo dell'elemento ricavato alla posizione indicata
void *elemento_ad_indice(vect_t *vettore, size_t indice);

/// @brief Inserisci un nuovo elemento in coda al vettore
/// @param vettore Vettore dentro al quale effettuare l'inserimento
/// @param elemento Puntatore all'elemento da inserire
void inserimento_coda(vect_t *vettore, void *elemento);

/// @brief Rimuovi un elemento da un vettore dato il suo indirizzo
/// @param vettore Vettore dal quale effettuare la rimozione
/// @param elemento Puntatore all'elemento da rimuovere
void rimuovi_elemento(vect_t *vettore, void *elemento);

#endif
