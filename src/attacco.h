/*PROLOGO INTERFACCIA: Modulo che contiene le funzioni d’attacco e quelle necessarie al loro funzionamento*/

#ifndef ATTACCO_H_
#define ATTACCO_H_

//MODULI DA INCLUDERE
#include "strutture.h"
#include "gestione_partita.h"

//DEFINIZIONE COSTANTI
#define SALTO 3
#define INIZIO_BOMBARDAMENTO_AEREO 10
#define PRIMA_LETTERA_COLONNA 'A'
#define ULTIMA_LETTERA_COLONNA 'P'
#define CELLA_NEUTRA 2					// valore cella neutra in colpi sferrati
#define RILEVATO 1						// valore cella nave rilevata dal radar
#define ACQUA 0							// valore di una cella in cui c’è il mare
#define COLPITO -1						// valore di una nave colpita
#define AFFONDATO -2					// valore di una nave colpita e affondata


//PROTOTIPI
int scelta_attacco(giocatore *attaccante, giocatore *difensore, partita *partita, int fine_turno);
coordinate *chiedere_coordinate(coordinate *coor);
celle_adiacenti *calcolare_celle_adiacenti(celle_adiacenti *celle_adiacenti, coordinate *coordinate);
int attacco(giocatore *attaccante, giocatore *difensore, coordinate *posizione);
int bombardamento_aereo(partita *partita, giocatore *attaccante, giocatore *difensore);
int colpo_largo_raggio(giocatore *attaccante, giocatore *difensore, coordinate *posizione_colpo, partita *partita);
int radar(giocatore *attaccante, giocatore *difensore, coordinate *coordinate, partita *partita);
void aggiornare_navi_affondate(giocatore *attaccante, giocatore *difensore, coordinate *pos);

#endif
