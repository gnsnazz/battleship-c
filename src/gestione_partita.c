/*PROLOGO IMPLEMENTAZIONE:
GRUPPO6 = Dinatale_Marco + Elmadhi_Nazim + Epifania_Cristiano + Ferrulli_Alessandro + Illuzzi_Gaetano ;
rev 1.0 - 08/06/22
*/

//MODULI DA INCLUDERE
#include "gestione_partita.h"
#include <stdio.h>
#include <stdlib.h>


/*
DESCRIZIONE:
In base ad una iterazione avente come condizione numero navi giocatore 1 !=0 OR numero navi giocatore 2 !=0
(le due condizioni necessarie per terminare il gioco uno dei giocatori non abbia piu navi nella sua flotta).
Se fine_turno FALSO.
Stampa a video il messaggio "Ora e' il turno di x" inserendo il nome del giocatore corrispondente: se e' una fase dispari sara' il giocatore 1, se e' una fase pari, sara' il giocatore 2.
Richiamera' le funzioni di stampa delle tabelle in modo tale che il giocatore possa vedere lo stato della sua flotta e quali navi potra' attaccare.
Richiama la funzione Scelta attacco e dopo aumenta il valore della fase
Fine_turno passa a VERO.
Alla sua fine si puo' scegliere di salvare o di salvare e tornare alla schermata iniziale.

INPUT:
partita - contiene i dati della partita - RECORD

OUTPUT:
Fine_turno - indica la fine del turno - booleano - VERO: turno finito  FALSO: turno iniziato

LAVORO:
decisione - variabile che contiene il valore del modulo di (fase:2)  per capire di quale dei 2 giocatori e' il tuno - intero - se =1 e' del giocatore 1 , se=0 e' del giocatore 2
consenso - determina la scelta del giocatore - carattere - S si N no

*/

void gestione_turno(partita *partita)
{
	system("@cls||clear");

	int decisione;
	char consenso;
	int esito;
	int fine_turno;

	fine_turno = 0;

	stampa_tabella_posizione_flotta(&partita->giocatori.giocatore_1, partita);

	while((leggere_numero_navi(&partita->giocatori.giocatore_1) != 0) && (leggere_numero_navi(&partita->giocatori.giocatore_2) != 0) && esito != -1)
	{
		if (fine_turno == 0)	//inizio turno
		{
			decisione = leggere_fase(partita) % 2;

			if (decisione == 0)		//fase pari = gioca il giocatore_2
			{
				system("@cls||clear");
				printf("E' il turno %d. Ora tocca a %s\n", leggere_turno(partita), leggere_nome(&partita->giocatori.giocatore_2));

				stampa_tabella_posizione_flotta(&partita->giocatori.giocatore_2, partita);
				stampa_tabella_colpi_sferrati(&partita->giocatori.giocatore_2, partita);

				fine_turno = scelta_attacco(&partita->giocatori.giocatore_2, &partita->giocatori.giocatore_1, partita, fine_turno);
			}
			else	//fase dispari = gioca il giocatore_1
			{
				system("@cls||clear");
				printf("E' il turno %d. Ora tocca a %s\n", leggere_turno(partita), leggere_nome(&partita->giocatori.giocatore_1));

				stampa_tabella_posizione_flotta(&partita->giocatori.giocatore_1, partita);
				stampa_tabella_colpi_sferrati(&partita->giocatori.giocatore_1, partita);

				fine_turno = scelta_attacco(&partita->giocatori.giocatore_1, &partita->giocatori.giocatore_2, partita, fine_turno);
			}
		}

		if (fine_turno == 1) 	//turno finito
		{
			scrivere_fase(partita, leggere_fase(partita) + 1);
			if((leggere_fase(partita) % 2) == 0)
			{
				scrivere_turno(partita, leggere_turno(partita) + 1);
			}
			fine_turno = 0;
			do
			{
				printf("\nVuoi salvare? S / N: ");
				scanf("%s", &consenso);
			}while ((consenso != 'S') && (consenso != 'N'));

			if (consenso == 'S')
			{
				do
				{
					esito = salvataggio(partita);
				}while (esito == 0);
			}
			do
			{
				printf("\nVuoi tornare alla schermata iniziale? S / N: ");
				scanf(" %c", &consenso);
			}while ((consenso != 'S') && (consenso != 'N'));

			if(consenso == 'S')
			{
				schermata_iniziale();
			}
		}
	}

	if (leggere_numero_navi(&partita->giocatori.giocatore_1) == 0)
	{
		system("@cls||clear");
		printf("\n%s HAI VINTO!\n", leggere_nome(&partita->giocatori.giocatore_2));
	}
	else
	{
		system("@cls||clear");
		printf("\n%s HAI VINTO!\n", leggere_nome(&partita->giocatori.giocatore_1));
	}

	do
	{
		printf("\nScrivere S per tornare alla schermata iniziale: ");
		scanf(" %c", &consenso);
	}while (consenso != 'S');

	schermata_iniziale();

  return;
}

/*
DESCRIZIONE:
Stampa una riga e colonna in piu alla tabella, aggiungendo i numeri delle colonne e le lettere delle righe come riferimento per il giocatore.
Tra un valore e l'altro ci sara il simbolo '|'
Al posto di 0 '~' (acqua), se e' -1 '*' (cella colpita dall'avversario) e per tutte le altre celle 'X'.

INPUT:
giocatore - record contenente i dati del giocatore - RECORD
partita - contiene i dati della partita - RECORD
DIMENSIONE TABELLA - valore delle dimensione di righe e colonne - costante - =16
ACQUA - valore delle celle contenenti acqua - costante - = 0
COLPITO - valore delle celle in cui c'e' una nave colpita - costante - = -1
AFFONDATO - valore delle celle in cui c'e' una nave affondata - costante - -2


OUTPUT:
-/-

LAVORO:
i - contatore che scandisce le righe - 1<=i<=DIMENSIONE TABELLA
j - contatore che scandisce le colonne - 1<=i<=DIMENSIONE TABELLA

*/

void stampa_tabella_posizione_flotta(giocatore *giocatore, partita *partita)
{
	int i;
	int j;

	printf("\nTABELLA POSIZIONE FLOTTA DI: %s", leggere_nome(giocatore));

	printf("\n\n+---++---++---++---++---++---++---++---++---++---++---++---++---++---++---++---++---++");

	printf("\n|%.2d || A || B || C || D || E || F || G || H || I || J || K || L || M || "
		 "N || O || P ||", leggere_turno(partita));

	printf("\n+---++---++---++---++---++---++---++---++---++---++---++---++---++---++---++---++---++");

	i = 0;
	printf("\n|%.2d |", i+1);
	while (i < DIMENSIONE_TABELLA)
	{
		j = 0;
		while (j < DIMENSIONE_TABELLA)
		{
			if (leggere_posizione_flotta(giocatore, i, j) == ACQUA)
			{
				printf("| ~ |"); //mare
			}
			else if (leggere_posizione_flotta(giocatore, i, j) == COLPITO)
			{
				printf("| o |"); //cella colpita
			}
			else if(leggere_posizione_flotta(giocatore, i, j) == AFFONDATO)
			{
				printf("| X |"); //cella colpita e affondata
			}
			else
			{
				printf("| # |"); //nave integra
			}
			j++;
		}
		printf("|");
		i++;
		if(i != DIMENSIONE_TABELLA)
		{
			printf("\n|%.2d |", i+1);
		}
	}
	printf("\n+---++---++---++---++---++---++---++---++---++---++---++---++---++---++---++---++---++");

	printf ("\nLEGENDA:\no = CELLA COLPITA  X = CELLA COLPITA E AFFONDATA  # = NAVE INTEGRA");
	printf("\n\n");

  return;
}


/*
DESCRIZIONE:
Stampa una riga e colonna in più alla tabella, aggiungendo i numeri delle
colonne e le lettere delle righe come riferimento per il giocatore. Tra un
valore e l'altro ci sarà il simbolo '|' Al posto di 0 '~ '  (acqua), se è -1 '*'
(cella colpita dall’avversario), se è # ‘R’ (nave individuata dal radar) e per
tutte le altre celle 'X'.

INPUT:
Giocatore - record contenente i dati del giocatore – record
DIMENSIONE TABELLA - valore delle dimensione di righe e colonne - costante - =16
ACQUA - valore delle celle contenenti acqua - costante - = 0
COLPITO - valore delle celle in cui c’è una nave colpita - costante - = -1
AFFONDATO - valore delle celle in cui c’è una nave affondata - costante - -2
RILEVATO - valore cella nave rilevata dal radar - costante - = 1
CELLA_NEUTRA - valore cella neutra in colpi sferrati - costante - = 2


OUTPUT:
-/-

LAVORO:
i - contatore che scandisce le righe - 1<=i<=DIMENSIONE TABELLA
j - contatore che scandisce le colonne - 1<=i<=DIMENSIONE TABELLA

*/

void stampa_tabella_colpi_sferrati(giocatore *giocatore, partita *partita)
{
	int i;
    int j;

    printf("\nTABELLA COLPI SFERRATI DI: %s", leggere_nome(giocatore));

    printf("\n\n+---++---++---++---++---++---++---++---++---++---++---++---++---++---++---++---++---++");

    printf("\n|%.2d || A || B || C || D || E || F || G || H || I || J || K || L || M || N || O || P ||", leggere_turno(partita));

    printf("\n+---++---++---++---++---++---++---++---++---++---++---++---++---++---++---++---++---++");

    i = 0;
    printf("\n|%.2d |", i+1);
    while (i < DIMENSIONE_TABELLA)
    {
        j = 0;
        while (j < DIMENSIONE_TABELLA)
        {
        	if (leggere_colpi_sferrati(giocatore, i, j) == ACQUA)
            {
                printf("| ~ |"); //cella mare dell'avversario colpito
            }
            else if (leggere_colpi_sferrati(giocatore, i, j) == COLPITO)
            {
                printf("| x |"); //cella nave dell'avversario colpita
            }
            else if (leggere_colpi_sferrati(giocatore, i, j) == AFFONDATO)
            {
            	printf("| / |"); //cella nave affondata dell'avversario
            }
            else if (leggere_colpi_sferrati(giocatore, i, j) == RILEVATO)
            {
            	printf("| @ |"); //cella nave rivelata dal radar con valore 1
            }
            else
            {
                printf("| ' |"); //cella neutra = 2
            }
        	j++;
        }
        printf("|");
        i++;
        if(i != DIMENSIONE_TABELLA)
        {
        	printf("\n|%.2d |", i+1);
        }
    }

    printf("\n+---++---++---++---++---++---++---++---++---++---++---++---++---++---++---++---++---++");

    printf ("\nLEGENDA:\nx = CELLA COLPITA  / = CELLA COLPITA E AFFONDATA  @ = NAVE RILEVATA DAL RADAR");

  return;
}


/*
DESCRIZIONE:
Scrivere su file i record Partita, Giocatori, Flotta e Navi
Stampa a video il messaggio "Salvataggio completato" o ERRORE DI APERTURA DEL FILE in base all'esito della funzione.

INPUT
partita - contiene i dati della partita - record
PERCORSO_FILE - indica il percorso del file - costante

OUTPUT
esito - indica se il salvataggio e' avvenuto con successo oppure no - booleano - VERO=salvato, FALSO=non salvato

LAVORO
salvataggio - nome del file su cui salvare i dati di una partita da salvare - FILE
decisione - permette al giocatore di indicare la sua scelta - intero -  =1 OR 2

*/


int salvataggio(partita *partita_da_salvare)
{
    int esito = 0;
    FILE *salvataggio;

    salvataggio = fopen(PERCORSO_SALVATAGGIO, "wb");	//aprire il file in modalita' scrittura

    if (salvataggio != NULL)
    {
    	//scriviamo su file binario i dati da salvare
    	fwrite(partita_da_salvare, sizeof(partita), 1, salvataggio);

        fclose(salvataggio);	//chiudere file dopo aver scritto su di esso
        esito = 1;
        printf("\n *SALVATAGGIO COMPLETATO* \n");
    }
    else
    {
        printf("ERRORE DI APERTUTA DEL FILE\n");
        esito = 0;
    }

  return esito;
}
