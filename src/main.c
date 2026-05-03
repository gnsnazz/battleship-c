/*PROLOGO IMPLEMENTAZIONE:
GRUPPO6 = Dinatale_Marco + Elmadhi_Nazim + Epifania_Cristiano + Ferrulli_Alessandro + Illuzzi_Gaetano ;
rev 1.0 - 22/06/22
*/

#include "main.h"
#include <stdio.h>
#include <stdlib.h>

//IMPLEMENTAZIONI

int main(void)
{
	schermata_iniziale();
	system("@cls||clear");
	system("pause");
return 0;
}

/*
DESCRIZIONE:
Stampa a video il titolo del gioco e "1.Nuova Partita 2.Continua Partita 3.Regole di Gioco 0.Fine"
e chiede al giocatore di dare in input un numero compreso tra 0 e 3, avviando poi la funzione corrispondente.
Se il valore e' 0 non fa nulla e quindi termina il programma.

INPUT:
PERCORSO_TITOLO - indica il percorso del file - costante

OUTPUT:
-/-

LAVORO
titolo - indica il nome del file dove leggere il titolo - FILE
i - contatore per scorrere le scelte - intero - >=0
c - variabile che memorizza l'n-esimo carattere di una stringa all'interno del file - carattere

*/

void schermata_iniziale() //guarda percorso file
{
	system("@cls||clear");
	int selezione;
	char c;
	partita *partita_nuova;
	partita *partita_salvata;

	FILE *titolo;

	partita_nuova = (partita *) malloc(sizeof(partita));	//allocare la memoria al record per la nuova partita
	partita_salvata = (partita *) malloc(sizeof(partita));	//allocare la memoria al record per una partita salvata

	titolo = fopen(PERCORSO_TITOLO, "r");	//aprire il file in modalita' lettura
	fgetc(titolo);
	while(c != EOF)
    {
		printf("%c", c);
		c = fgetc(titolo);
    }
	fclose(titolo);		//chiudere il file dopo aver letto su di esso

	selezione = 0;
	do
    {
		printf("\n[1] Nuova partita\n[2] Continua Partita\n[3] Regole di gioco\n[4] Exit\n");
		printf("\nInserire scelta: ");
		scanf("%d", &selezione);
		if(selezione == 1)	//nuova partita
		{
			nuova_partita(partita_nuova);
		}
		else if(selezione == 2)		//continuare partita
		{
			caricare_partita(partita_salvata);
		}
		else if(selezione == 3)		//regole di gioco
		{
			regole_gioco();
		}
		else if(selezione == 4)		//terminazione del programma
		{
			exit(0);	//permette di uscire dal programma intero restituendo 0
		}
    }while((selezione < 0) || (selezione > 4));

  return;
}
