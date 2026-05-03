/*PROLOGO IMPLEMENTAZIONE:
GRUPPO6 = Dinatale_Marco + Elmadhi_Nazim + Epifania_Cristiano + Ferrulli_Alessandro + Illuzzi_Gaetano ;
rev 1.0 - 22/06/22
*/

//MODULI DA INCLUDERE
#include "regole_gioco.h"
#include "main.h"
#include <stdlib.h>
#include <stdio.h>

/*
DESCRIZIONE:
Funzione che stampa le regole di gioco

INPUT:
PERCORSO_REGOLE - percorso del file contenente le regole di gioco - costante
OUTPUT:
-/-

LAVORO:
regole - indica il nome del file dove leggere le regole - FILE
c - variabile che memorizza l'n-esimo carattere di una stringa all'interno del file - carattere
decisione - permette al giocatore di indicare la sua scelta - carattere
*/


void regole_gioco()
{
	system("@cls||clear");

	FILE *regole;
	char c;
	char decisione;

	if((regole = fopen(PERCORSO_REGOLE, "r")) == NULL)
	{
		printf("Errore nell'apertura del file!\n");
	}
	else
	{
		c = fgetc(regole);
		while(c != EOF)
		{
			printf("%c", c);
			c = fgetc(regole);
		}
		fclose(regole);
		do
		{
			printf("\n\nScrivere S per tornare alla schermata iniziale: ");
			scanf(" %c", &decisione);
		}while((decisione != 'S') && (decisione != 's'));
	}
	system("clear");
	schermata_iniziale();
	return;
}
