/*PROLOGO INTERFACCIA: Contiene le funzioni utili per gestire le dinamiche della partita,
  come l’alternarsi dei giocatori, il salvataggio ed il mostrare la tabella di gioco.
*/

#ifndef GESTIONE_PARTITA_H_
#define GESTIONE_PARTITA_H_

//MODULI DA INCLUDERE
#include "main.h"
#include "attacco.h"
#include "strutture.h"
#include "nuova_partita.h"
#include "carica_partita.h"

//DEFINIZIONE COSTANTI
#define PERCORSO_SALVATAGGIO "./salvataggio.bin"

//PROTOTIPI
void gestione_turno(partita *partita);
void stampa_tabella_posizione_flotta(giocatore *giocatore, partita *partita);
void stampa_tabella_colpi_sferrati(giocatore *giocatore, partita *part);
int salvataggio(partita *partita);

#endif
