/*PROLOGO INTERFACCIA: Modulo che contiene la funzione di Caricamento del gioco*/

#ifndef CARICA_PARTITA_H_
#define CARICA_PARTITA_H_

//MODULI DA INCLUDERE
#include "strutture.h"
#include "gestione_partita.h"


//DEFINIZIONE COSTANTI
#define PERCORSO_CARICAMENTO "./salvataggio.bin"

//PROTOTIPI
int caricare_partita(partita *partita_salvata);

#endif
