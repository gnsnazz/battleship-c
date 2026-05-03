 /*PROLOGO IMPLEMENTAZIONE:
GRUPPO6 = Dinatale_Marco + Elmadhi_Nazim + Epifania_Cristiano + Ferrulli_Alessandro + Illuzzi_Gaetano ;
rev 1.0 - 08/06/22
*/

//MODULI DA INCLUDERE
#include "carica_partita.h"
#include "nuova_partita.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 [DESCRIZIONE]:  Carica da file i record Partita, Giocatori, Flotta e Navi
Stampa a video il messaggio "Caricamento Completato" o “ERRORE DI APERTURA DEL FILE” in base all’esito della funzione.
Richiamando la funzione Gestione turno riprende la partita con i dati caricati.

INPUT
PERCORSO_FILE – indica il percorso del file - costante

OUTPUT
esito – indica se il caricamento è stato avvenuto con successo  - booleano – VERO=caricato, FALSO=non caricato

LAVORO
caricamento - indica il nome del file su cui caricare leggere i dati per caricare una partita - FILE
consenso - determina la scelta del giocatore - carattere - S si N no
*/

int caricare_partita(partita *partita_salvata)
{
	int esito;
	char consenso;
	FILE *caricamento;

	esito = 0;
	caricamento = fopen(PERCORSO_CARICAMENTO, "rb");	//apertura del file in modalia' lettura

	if(caricamento != NULL)
	{
		//leggiamo dal file i dati da caricare per proseguire una partita
		fread(partita_salvata, sizeof(partita), 1, caricamento);
		fclose(caricamento);	//chiudere il file dopo aver letto su di esso
		esito = 1;
		printf("\n*PARTITA CARICATA CORRETTAMENTE*\n");
		gestione_turno(partita_salvata);
	}
	else
	{
		printf("\nERRORE DI APERTURA DEL FILE\n");
		esito = 0;
	}
	do
    {
		printf("\nVuoi iniziare una nuova partita? S / N: \n");
		scanf("%c", &consenso);
    }while((consenso != 'S') && (consenso != 'N'));

	if(consenso == 'S')
	{
		nuova_partita(partita_salvata);
	}
	else schermata_iniziale();		//ritorno alla schermata iniziale

	return esito;
}
