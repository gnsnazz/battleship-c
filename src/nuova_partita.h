/*PROLOGO INTERFACCIA: Contiene tutte le funzioni necessarie per avviare una nuova partita,
  inserendo i dati di entrambi i giocatori ed inizializzando le strutture che poi saranno usate negli altri moduli
*/

#ifndef NUOVA_PARTITA_H_
#define NUOVA_PARTITA_H_

//MODULI DA INCLUDERE
#include "strutture.h"
#include "gestione_partita.h"
#include "attacco.h"

//DEFINIZIONE COSTANTI
#define NUMERO_NAVI_5 1
#define NUMERO_NAVI_4 2
#define NUMERO_NAVI_3 3
#define NUMERO_NAVI_2 4
#define NUMERO_NAVI_1 5

#define DIMENSIONE_NAVI_5 5
#define DIMENSIONE_NAVI_4 4
#define DIMENSIONE_NAVI_3 3
#define DIMENSIONE_NAVI_2 2
#define DIMENSIONE_NAVI_1 1


//PROTOTIPI
partita *nuova_partita(partita *partita);
giocatori *inizializzare_giocatori(giocatori *giocatori, partita *partita);
giocatore *inizializzare_navi(giocatore *giocatore);
giocatore *identificare_navi(giocatore *giocatore, int dimensione_navi, int i, int j);
giocatore *disporre_flotta(giocatore *giocatore, partita *part);
celle_adiacenti *calcolare_celle_navi(celle_adiacenti *celle_nave, coordinate *cella_iniziale, coordinate *cella_finale, int dimensione_nave);
float verificare_celle_libere(giocatore *giocatore, celle_adiacenti *celle_nave, int dimensione_nave);
int verificare_dimensione(coordinate *cella_iniziale, coordinate *cella_finale, int dimensione);
giocatore *inizializzare_tabelle(giocatore *giocatore);

#endif
