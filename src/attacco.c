/*PROLOGO IMPLEMENTAZIONE:
GRUPPO6 = Dinatale_Marco + Elmadhi_Nazim + Epifania_Cristiano + Ferrulli_Alessandro + Illuzzi_Gaetano ;
rev 1.0 - 22/06/22
*/

#include "attacco.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*
DESCRIZIONE:
Scrive a video i nomi degli attacchi disponibili, incluso quello normale, ed in
quale numero. Riceve da tastiera il valore corrispondente all'attacco. Richiama
la funzione chiedere coordinate In base all'attacco richiama la funzione
dell'attacco scelto fine_turno diventa VERO.
Il primo  record giocatore dato in input è quello dell’attaccante, mentre il
secondo è il difensore

INPUT:
attaccante – contiene i dati del giocatore che attacca, in base al turno può essere il giocatore 1 o il giocatore 2 – giocatore
difensore – contiene i dati del giocatore che è attaccato, in base al turno può essere il giocatore 1 o il giocatore 2 – giocatore
fine_turno – indica la fine del turno – booleano – VERO: turno finito  FALSO: turno iniziato
partita – record contenente i dati della partita - RECORD

OUTPUT:
fine_turno – indica la fine del turno – booleano – VERO: turno finito  FALSO: turno iniziato

LAVORO
coordinate – coordinate.x è la riga della cella, mentre coordinate.y è la colonna della cella- record
colpi_disponibili - contatore che indica quanti attacchi di quello scelto siano disponibili - intero - >=0
scelta - scelta dell’attacco del giocatore - carattere- >=’1’ AND scelta <=’4’
*/

int scelta_attacco(giocatore *attaccante, giocatore *difensore, partita *partita, int fine_turno)
{
	coordinate *posizione; 	// coordinate.x è la riga della cella, mentre coordinate.y è la colonna della cella- record
	int colpi_disponibili;  // contatore che indica quanti attacchi di quello scelto siano disponibili - intero - >=0
	char scelta; 			// scelta dell’attacco del giocatore - intero - >=1 AND scelta <=4

	posizione = (coordinate *) malloc(sizeof(coordinate));

	scrivere_coordinata_x(posizione, 0);
	scrivere_coordinata_y(posizione, 0);

	while (fine_turno == 0) // esce quando il giocatore sferra un attacco
	{
		do
		{
			printf("\n\n\nScegliere l'attacco da effettuare: \n[1] Attacco\n[2] Colpo a largo raggio\n[3] Bombardamento aereo\n[4] Radar\n");
			printf("\nInserire scelta: ");
			scanf(" %c", &scelta);
		}while((scelta < '1') || (scelta > '4'));
		if (scelta == '1')		//attacco
		{
			chiedere_coordinate(posizione);
			fine_turno = attacco(attaccante, difensore, posizione);
		}
		else if (scelta == '2')		//colpo a largo raggio
		{
			colpi_disponibili = leggere_colpo_largo_raggio(attaccante);
			printf("Il numero di colpi a largo raggio e': %d\n", colpi_disponibili);
			if (colpi_disponibili != 0)
			{
				posizione = chiedere_coordinate(posizione);
				fine_turno = colpo_largo_raggio(attaccante, difensore, posizione, partita);
			}
			else printf("Hai esaurito i colpi a disposizione\n");
		}
		else if (scelta == '3')		//bombardamento aereo
		{
			colpi_disponibili = leggere_bombardamento_aereo(attaccante);
			printf("Il numero di bombardamento aereo e': %d\n", colpi_disponibili);
			if (colpi_disponibili != 0)
			{
				fine_turno = bombardamento_aereo(partita, attaccante, difensore);
			}
			else printf("Hai esaurito i colpi a disposizione\n");
		}
		else if (scelta == '4')		//radar
		{
			colpi_disponibili = leggere_radar(attaccante);
			printf("Il numero di radar e': %d\n", colpi_disponibili);
			if (colpi_disponibili != 0)
			{
				chiedere_coordinate(posizione);
				fine_turno = radar(attaccante, difensore, posizione, partita);
			}
			else printf("Hai esaurito i colpi a disposizione\n");
		}
	}

	free(posizione);

  return fine_turno;
}

/*
DESCRIZIONE:
Chiede in input il valore di riga e colonna della cella da attaccare
Verificando che i valori siano compresi tra 0 e 16

INPUT:
coordinate – coordinate.x è la riga della cella, mentre coordinate.y è la
colonna della cella- record

OUTPUT:
coordinate -record modificato - coordinate.x è la riga della cella, mentre
coordinate.y è la colonna della cella- record

LAVORO:
riga - indica il numero di riga della tabella – intero - >0 e <17
colonna - indica il numero di colonna della tabella – carattere - >0 e <17
*/

coordinate *chiedere_coordinate(coordinate *coordinate)
{
	char colonna;
	char *riga;
	int temp;
	int len;
	int i;

	riga = (char *) malloc(sizeof(char)*3);

	//chiediamo la coordinata colonna
	do
	{
		printf("\nInserire colonna (A-P): ");
		scanf(" %c", &colonna);
	}while((colonna < PRIMA_LETTERA_COLONNA) || (colonna > ULTIMA_LETTERA_COLONNA));

	colonna -= PRIMA_LETTERA_COLONNA; 	//convertire lettera in numero
	scrivere_coordinata_y(coordinate, colonna);

	//chiediamo la coordinata riga
	do
	{
		temp = 0;
	    printf("\nInserire riga (1-16): ");
	    scanf("%s", riga);
	    i = 0;
	    len = strlen(riga);

	    while (i < strlen(riga))
	    {
	    	len--;
	        temp += riga[i] - '0';
	        temp = temp *pow(10,len);
	        i++;
	    }
	}while((temp < 0) || (temp > DIMENSIONE_TABELLA));

    scrivere_coordinata_x(coordinate, temp - 1);

  return coordinate;
}

/*
DESCRIZIONE:
Determina il contenuto della cella da colpire:

se è ACQUA 0) aggiorna la tabella colpi sferrati dell'attaccante segnando in quella posizione COLPITO (-1) e dando come messaggio "Acqua";
se è stato già colpito (-1) e come messaggio "Cella già colpita";
c'è un valore diverso, lo cercherà nel campo nave.identificativo del difensore.
Il contenuto della cella di difensore passerà a -1 (COLPITO) e nella stessa posizione, ma nella tabella colpi sferrati dell'attaccante, sarà segnato 1.
Decrementerà l’integrità della nave
Se il valore di nave.integrità è maggiore di 0, stamperà il messaggio "colpito".
Se valore del campo nave.integrità è =0, decrementerà il campo flotta.numero_navi e darà come messaggio "colpito e affondato").


INPUT:
attaccante – tipo di dato contenente i dati del primo giocatore – giocatore
difensore – tipo di dato contenente i dati del secondo giocatore – giocatore
coordinate – coordinate.x è la riga della cella, mentre coordinate.y è la
colonna della cella- record navi - record contenente i dati delle navi – record
ACQUA - valore delle celle contenenti acqua - costante - = 0
COLPITO - valore delle celle in cui c’è una nave colpita - costante - = -1
AFFONDATO - valore delle celle in cui c’è una nave affondata - costante - -2


OUTPUT:
fine_turno – indica la fine del turno – booleano – VERO: turno finito  FALSO:
turno iniziato

LAVORO:
valore - indica il valore letto nella tabella posizione flotta del difensore - float
identificativo_nave –  identificativo di una nave  – float
integrita – indica il numero di celle colpite della nave - intero
decisione - indica di quale giocatore è il turno
i- contatore che scandisce il record identificativo_nave di difensore - intero
trovato - indica se un elemento è stato trovato - booleano - VERO = trovato
FALSO= non trovato numero - variabile per aggiornare il campo numero navi -
intero
*/

int attacco(giocatore *attaccante, giocatore *difensore, coordinate *coordinate)
{
/*  Possibili valori di:
-> colpi sferrati: CELLA_NEUTRA, RILEVATO, ACQUA, COLPITO, AFFONDATO
-> posizione flotta: ACQUA, ID della nave integra, COLPITO, AFFONDATO
*/
	float valore;
	int fine_turno;
	int integrita;
	int i;
	int trovato;
	int numero;
	char carattere;

	trovato = 0;
	fine_turno = 0;

	valore = leggere_posizione_flotta(difensore, leggere_coordinata_x(coordinate), leggere_coordinata_y(coordinate));
	carattere = PRIMA_LETTERA_COLONNA + coordinate->y;

	if (valore == 0) // cella mare
	{
		// indichiamo di aver colpito quella cella a vuoto
		scrivere_colpi_sferrati(attaccante, leggere_coordinata_x(coordinate), leggere_coordinata_y(coordinate), ACQUA);

		printf("\n[%c - %d] - ACQUA\n", carattere, leggere_coordinata_x(coordinate)+1);
	}
	else if ((valore == COLPITO) || (valore == AFFONDATO))		//cella gia' colpita in precedenza
	{
		printf("\n[%c - %d] - GIA' COLPITA\n", carattere, leggere_coordinata_x(coordinate)+1);
	}
	else		//celle contenenti l’ID di una nave
	{
		i = 0;
		while ((i < DIMENSIONE_CAMPI_NAVI) && (trovato == 0))
		{
			if (leggere_identificativo_nave(difensore, i) == valore)
			{
				trovato = 1;
			}
			else
			{
				i++;
			}
		}

		scrivere_posizione_flotta(difensore, leggere_coordinata_x(coordinate), leggere_coordinata_y(coordinate), COLPITO); //cella colpita su tabella difensore
		scrivere_colpi_sferrati(attaccante, leggere_coordinata_x(coordinate), leggere_coordinata_y(coordinate), COLPITO); //cella colpita su tabella attaccante
		integrita = leggere_integrita_nave(difensore, i) -1;	//indichiamo che la nave ha perso una cella
		scrivere_integrita_nave(difensore, integrita, i);

		if (integrita > 0)
		{
			printf("\n[%c - %d] - COLPITO\n", carattere, leggere_coordinata_x(coordinate)+1);
		}
		else
		{
			printf("\nNave %.1f COLPITO E AFFONDATO \n", leggere_identificativo_nave(difensore, i));
			//indichiamo le celle della nave affondata con un valore diverso da colpito
			aggiornare_navi_affondate(attaccante, difensore, coordinate);
			numero = leggere_numero_navi(difensore) - 1;		//il difensore ha una nave in meno
			scrivere_numero_navi(difensore, numero);
		}
	}

	fine_turno = 1;

  return fine_turno;
}

/*
DESCRIZIONE:
Partendo dalle coordinate dell’ultima cella colpita determina la presenza delle altre celle della nave affondata e le aggiorna con il valore AFFONDATO.
si ferma nel momento in cui trova un cella in cui c’è il mare (ACQUA) (ogni nave è circondata in tutte le direzioni dal mare) o supera il limite della tabella.

INPUT:
attaccante – tipo di dato contenente i dati del primo giocatore – giocatore
difensore – tipo di dato contenente i dati del secondo giocatore – giocatore
coordinate – coordinate.x è la riga della cella, mentre coordinate.y è la colonna della cella- record
partita – record contenente i dati della partita - record
ACQUA - valore delle celle contenenti acqua - costante - = 0
COLPITO - valore delle celle in cui c’è una nave colpita - costante - = -1
AFFONDATO - valore delle celle in cui c’è una nave affondata - costante - -2
DIMENSIONE_ TABELLA - dimensione delle tabelle colpi sferrati e posizione flotta - costante -  =16

OUTPUT:
partita – record contenente i dati della partita - record

LAVORO:
valore - indica il valore letto nella tabella posizione flotta del difensore - float
trovato - indica se è stato trovato il mare (0) - booleano - VERO = trovato  FALSO= non trovato
x - indica la riga delle celle da aggiornare - intero - compreso tra 1 e 16
y - indica la riga delle celle da aggiornare - intero - compreso tra 1 e 16
*/


void aggiornare_navi_affondate(giocatore *attaccante, giocatore *difensore, coordinate *coordinate)
{
	float valore;
	int trovato;
	int x;
	int y;

	x = leggere_coordinata_x(coordinate);
	y = leggere_coordinata_y(coordinate);

	//controllo verso destra
	trovato = 0;

	while ((trovato == 0) && (y < DIMENSIONE_TABELLA))
	{
		// Si ferma se trova il mare o va oltre il limite della tabella
		valore = leggere_posizione_flotta(difensore, x, y);
		if ((valore == COLPITO) || (valore == AFFONDATO))
		{
			scrivere_colpi_sferrati(attaccante, x, y, AFFONDATO);
			scrivere_posizione_flotta (difensore, x, y, AFFONDATO);
			y++;  //incrementiamo le colonne
		}
		else
		{
			trovato = 1;
		}
	}

	//controllo verso sinistra
	trovato = 0;
	y = leggere_coordinata_y(coordinate);  //reset della y

	while ((trovato == 0) && (y >= 0))
	{
		// Si ferma se trova il mare o va oltre il limite della tabella
		valore = leggere_posizione_flotta(difensore, x, y);
		if ((valore == COLPITO) || (valore == AFFONDATO))
		{
			scrivere_colpi_sferrati(attaccante, x, y, AFFONDATO);
			scrivere_posizione_flotta (difensore, x, y, AFFONDATO);
			y--;  //decrementiamo le colonne
		}
		else		//valore = ACQUA
		{
			trovato = 1;
		}
	}

	//controllo verso sopra
	trovato = 0;
	y = leggere_coordinata_y(coordinate);  //reset della y

	while ((trovato == 0) && (x >= 0))
	{
		// Si ferma se trova il mare o va oltre il limite della tabella
		valore = leggere_posizione_flotta(difensore, x, y);
		if ((valore == COLPITO) || (valore == AFFONDATO))
		{
			scrivere_colpi_sferrati(attaccante, x, y, AFFONDATO);
			scrivere_posizione_flotta (difensore, x, y, AFFONDATO);
			x--;  //decrementiamo le righe
		}
		else
		{
			trovato = 1;
		}
	}

	//controllo verso sotto
	trovato = 0;
	x = leggere_coordinata_x(coordinate); //reset della x

	while ((trovato == 0) && (x < DIMENSIONE_TABELLA))
	{
		// Si ferma se trova il mare o va oltre il limite della tabella
		valore = leggere_posizione_flotta(difensore, x, y);
		if ((valore == COLPITO) || (valore == AFFONDATO))
		{
			scrivere_colpi_sferrati(attaccante, x, y, AFFONDATO);
			scrivere_posizione_flotta (difensore, x, y, AFFONDATO);
			x++;	//incrementiamo le righe
		}
		else		// valore = ACQUA
		{
			trovato = 1;
		}
	}

  return;
}


/*
DESCRIZIONE:
Verifica che il turno di gioco sia almeno 10.
Chiede se delle coordinate date in input dobbiamo considerare il valore delle
righe o delle colonne. Si inizia un ciclo con un contatore "i" il cui valore è
compreso tra 1 e 16. Si applica la funzione Attacco ad ogni cella della riga o
colonna data in input. Decrementerà il valore del campo
giocatore.bombardamento_aereo

INPUT:
partita – record contenente i dati della partita - record
coordinate - coordinate.x è la riga della cella, mentre coordinate.y è la
colonna della cella -  record – valore dei campi compresi tra 1 a 16 attaccante
– tipo di dato contenente i dati del primo giocatore – giocatore difensore –
tipo di dato contenente i dati del secondo giocatore – giocatore navi - record
contenente i dati delle navi – record

DIMENSIONE_ TABELLA - dimensione delle tabelle colpi sferrati e posizione flotta
- costante -  =16 INIZIO_BOMBARDAMENTO_AEREO - indica da quale turno possiamo
usare il bombardamento aereo - costante - = 10 OUTPUT: fine_turno – indica la
fine del turno – booleano – VERO: turno finito  FALSO: turno iniziato

LAVORO:
selezione - indica se si è scelto di attaccare una riga o colonna - intero -  1
=riga  2 =colonna coordinate_bombardamento – progressivamente acquisirà il
valore delle celle da bombardare – coordinate – ogni campo avrà valori compresi
tra 1 e 16 i – contatore delle celle della stessa riga o colonna – intero – tra
1 e DIMENSIONE_ TABELLA utilizzi - contiene il numero di utilizzi dell’attacco -
intero - >= del campo Radar del record Giocatore

*/

int bombardamento_aereo(partita *partita, giocatore *attaccante, giocatore *difensore)
{
	int fine_turno;
	char selezione;
	coordinate *coordinate_bombardamento;
	int i;
	int utilizzi;
	int riga;
	char colonna;

	coordinate_bombardamento = (coordinate *) malloc(sizeof(coordinate));

	utilizzi = leggere_bombardamento_aereo(attaccante);
	if (utilizzi > 0)
	{
		if (leggere_turno(partita) >= INIZIO_BOMBARDAMENTO_AEREO)
		{
			selezione = 0;
			do
			{
				printf("\nCosa vuoi colpire?\n[1] Colonna\n[2] Riga");
				printf("\nInserire scelta: ");
				scanf(" %c", &selezione);
			}while((selezione != '1') && (selezione != '2'));
			i = 0;
			if (selezione == '1')     //attacco ad una colonna
			{
				do
				{
					printf("Inserire colonna (A-P): ");
					scanf(" %c", &colonna);
				}while((colonna < PRIMA_LETTERA_COLONNA) || (colonna > ULTIMA_LETTERA_COLONNA));

				colonna -= PRIMA_LETTERA_COLONNA;
				scrivere_coordinata_y(coordinate_bombardamento, colonna);

				system("@cls||clear");
				printf("\nRisultato del Bombardamento aereo:\n");

				while (i < DIMENSIONE_TABELLA)
				{
					scrivere_coordinata_x(coordinate_bombardamento, i);
					fine_turno = attacco(attaccante, difensore, coordinate_bombardamento);
					i++;
				}
				scrivere_bombardamento_aereo(attaccante, utilizzi-1);
			}
			else    //attacco ad una riga
			{
				do
				{
					printf("Inserire riga (1-16): ");
					scanf("%d", &riga);
				}while((riga <= 1) || (riga >= DIMENSIONE_TABELLA));
				scrivere_coordinata_x(coordinate_bombardamento, riga - 1);

				system("@cls||clear");
				printf("\nRisultato del Bombardamento aereo:\n");

				while (i < DIMENSIONE_TABELLA)
				{
					scrivere_coordinata_y(coordinate_bombardamento, i);
					fine_turno = attacco(attaccante, difensore, coordinate_bombardamento);
					i++;
				}
			scrivere_bombardamento_aereo(attaccante, utilizzi-1);
			}
		}
		else
		{
			printf("Attacco non disponibile. Il bombardamento sara' disponibile tra '%d' turni\n Scegli  un altro attacco\n", INIZIO_BOMBARDAMENTO_AEREO - leggere_turno(partita));// - utilizzi
			fine_turno = 0;
		}
	}
	else
	{
		printf("Attacco non disponibile. Scegli un altro attacco\n");
		fine_turno = 0;
	}

	stampa_tabella_colpi_sferrati(attaccante, partita);

	free(coordinate_bombardamento);

  return fine_turno;
}

/*
DESCRIZIONE:
Verifica che il campo giocatori.colpo_a_largo_raggio sia >0. In caso contrario
stampare_a_video "attacco non disponibile".
Richiama calcolare_celle_adiacenti e richiama la funzione ATTACCO per ciascuna
delle 9 celle interessate. Decrementerà il valore del campo
giocatore.colpo_a_largo_raggio

INPUT:
attaccante – tipo di dato contenente i dati del primo giocatore – giocatore
difensore – tipo di dato contenente i dati del secondo giocatore – giocatore
coordinate – coordinate.x è la riga della cella, mentre coordinate.y è la
colonna della cella- record navi - record contenente i dati delle navi – record

OUTPUT:
fine_turno – indica la fine del turno – booleano – VERO: turno finito  FALSO:
turno iniziato

LAVORO:
celle_bersaglio – contiene le 9 celle che verranno colpite – record di
coordinate – dimensione=9, i suoi valori sono compresi tra 1 e 16 utilizzi -
contiene il numero di utilizzi dell’attacco - intero - >= del campo Largo Raggio
del record   Giocatore i - indice  - intero

*/

int colpo_largo_raggio(giocatore *attaccante, giocatore *difensore, coordinate *posizione_colpo, partita *partita)
{

	int fine_turno;
	celle_adiacenti *celle_bersaglio;
	int utilizzi;
	int i;

	fine_turno = 0;
	celle_bersaglio = (celle_adiacenti *)malloc(sizeof(celle_adiacenti) * DIMENSIONE_CELLE_ADIACENTI);

	if(leggere_colpo_largo_raggio(attaccante) > 0)
	{
		/*verifichiamo che non siano date in input coordinate sui bordi della tabella per evitare che
		  l’attacco colpisca celle al di fuori della tabella stessa, facilitando il giocatore*/
		if ((leggere_coordinata_x(posizione_colpo) == 0) || (leggere_coordinata_x(posizione_colpo) == DIMENSIONE_TABELLA - 1) ||
			(leggere_coordinata_y(posizione_colpo) == 0) || (leggere_coordinata_y(posizione_colpo) == DIMENSIONE_TABELLA - 1))
		{
			do
			{
				printf("Coordinate errate. Inserisci un valore di COLONNA compreso tra B e O e di RIGA compreso tra 2 e 15. \n");
				chiedere_coordinate(posizione_colpo);
			}while((leggere_coordinata_x(posizione_colpo) == 0) ||(leggere_coordinata_x(posizione_colpo) == DIMENSIONE_TABELLA - 1) ||
				   (leggere_coordinata_y(posizione_colpo) == 0) || (leggere_coordinata_y(posizione_colpo) == DIMENSIONE_TABELLA - 1));

		}
		system("@cls||clear");
		printf("\nRisultato del Colpo a largo raggio:\n");
		celle_bersaglio = calcolare_celle_adiacenti(celle_bersaglio, posizione_colpo);
		i = 0;
		while (i < DIMENSIONE_CELLE_ADIACENTI)
		{
			posizione_colpo->x = celle_bersaglio->x[i];
			posizione_colpo->y = celle_bersaglio->y[i];
		    fine_turno = attacco(attaccante, difensore, posizione_colpo);
			i++;
		}
		utilizzi = leggere_colpo_largo_raggio(attaccante);
		scrivere_colpo_largo_raggio(attaccante, utilizzi-1);
	}
	else
	{
		printf("\nAttacco non disponibile. Scegli un altro attacco\n");
		scelta_attacco(attaccante, difensore, partita, fine_turno);
	}

	stampa_tabella_colpi_sferrati(attaccante, partita);

	free(celle_bersaglio);

  return fine_turno;
}

/*
DESCRIZIONE:
Verifica che le coordinate date in input sono comprese tra "2-2" e "15-15", in caso contrario stampare a video
"coordinate errate" e richiama la funzione Richieste coordinate attacco.
Questo controllo è per evitare di usare l'attacco su celle al di fuori della tabella 16x16.
Calcola le celle di raggio 1 data una cella indicata in input, inserendole nell’array celle_adiacenti.
Nell’array celle_adiacenti inseriremo i valori:

INPUT:
celle_adiacenti - record contenente le coordinate delle celle in un’area di dimensione 3x3 – RECORD
posizione_colpo - coordinate.x è la colonna della cella, mentre coordinate.y è la riga della cella - record – valore
dei campi compresi tra 1 e 16
SALTO - valore per saltare da una riga o colonna alla successiva - costante - =3
DIMENSIONE_ CELLE_ADIACENTI - dimensione dell’array celle adiacenti - costante - = 9

OUTPUT:
celle_adicenti- record contenente le coordinate delle celle in un’area di dimensione 3x3 – RECORD

LAVORO:
x – valore delle righe dell’area considerata – intero – compreso tra +1 e -1 coordinate.x
y – valore delle colonne dell’area considera – intero – compreso tra +1 e -1 coordinate.y
i – indica la posizione nel record celle_adiacenti – intero – valore compreso tra 1 e 9
salti - numero di passaggio per scandire tutta l'area 3x3 - intero
*/

celle_adiacenti *calcolare_celle_adiacenti(celle_adiacenti *celle_adiacenti, coordinate *coordinate)
{
	int salti;
	int x;
	int y;
	int i;

	salti = SALTO;
	x = coordinate->x;
	y = coordinate->y;
	y--;
	i = 0;

	while (i < DIMENSIONE_CELLE_ADIACENTI)
	{
		while (i < salti) // scrive i valori  x-1,y-1   x-1,y   x-1,y+1 nelle posizioni  1,2,3
		{
			scrivere_valore_celle_adiacenti_x(celle_adiacenti, i, x-1);
			scrivere_valore_celle_adiacenti_y(celle_adiacenti, i, y);
			y++;
			i++;
		}
		y = coordinate->y; // Resettiamo la variabile y
		y--;
		salti += SALTO;

		while (i < salti) // scrive i valori  x,y-1   x,y  x,y+1 nelle posizioni  4,5,6
		{
			scrivere_valore_celle_adiacenti_x(celle_adiacenti, i, x);
			scrivere_valore_celle_adiacenti_y(celle_adiacenti, i, y);
			y++;
			i++;
		}
		y = coordinate->y; // Resettiamo la variabile y
		y--;
		salti += SALTO;

		while (i < salti) // scrive i valori  x+1,y-1   x+1,y   x+1,y+1 nelle posizioni  7,8,9
		{
			scrivere_valore_celle_adiacenti_x(celle_adiacenti, i, x+1);
			scrivere_valore_celle_adiacenti_y(celle_adiacenti, i, y);
			y++;
			i++;
		}
	}

  return celle_adiacenti;
}

/*
DESCRIZIONE:
Verifica che il campo giocatore.radar sia >0. In caso contrario stampare a video "attacco non disponibile".
Verifica che le coordinate date in input non siano sul bordo, così da evitare che colpisca meno celle.
Viene richiamata la funzione calcolare_celle_adiacenti e per ogni cella considerata se:
- legge ACQUA (0) in flotta difensore, scriverà 0 in colpi sferrati attaccante e stamperà a video ‘vuoto’
- se in flotta difensore legge COLPITO (-1) o AFFONDATO (-2) stamperà a video ‘nave già colpita’
- se le 2 precedenti sono false, scriverà RILEVATO nella tabella dei colpi sferrati e stamperà a video ‘nave’

RILEVATO (1) indicherà le celle in cui sappiamo che c'è una nave, ma che non abbiamo ancora colpito.
Stampare a video la tabella colpi sferrati.
Decrementerà il valore del campo giocatore.radar.


INPUT:
attaccante – tipo di dato contenente i dati del primo giocatore – giocatore
difensore – tipo di dato contenente i dati del secondo giocatore – giocatore
coordinate – coordinate.x è la riga della cella, mentre coordinate.y è la
colonna della cella- record partita – record contenente i dati della partita - RECORD
ACQUA - valore delle celle contenenti acqua - costante - = 0
COLPITO - valore delle celle in cui c’è una nave colpita - costante - = -1
AFFONDATO - valore delle celle in cui c’è una nave affondata - costante - -2
RILEVATO - valore cella nave rilevata dal radar - costante - = 1


OUTPUT:
fine_turno – indica la fine del turno – booleano – VERO: turno finito  FALSO:
turno iniziato

LAVORO:
LAVORO:
celle_bersaglio – contiene le 9 celle che verranno colpite – record di coordinate – dimensione=9, i suoi valori sono compresi tra 1 e 16
utilizzi - contiene il numero di utilizzi dell’attacco - intero - >= del campo Radar del record Giocatore
i - scandisce celle bersaglio - intero - 1<i<DIMENSIONE_ CELLE_ADIACENTI
carattere - contiene la lettera della colonna della cella interessata - carattere - compresto
tra PRIMA_LETTERA_COLONNA e ULTIMA_LETTERA_COLONNA
*/

int radar(giocatore *attaccante, giocatore *difensore, coordinate *coordinate, partita *partita)
{
	/*  Possibili valori di:
	-> colpi sferrati: CELLA_NEUTRA, RILEVATO, ACQUA, COLPITO, AFFONDATO
	-> posizione flotta: ACQUA, ID della nave integra, COLPITO, AFFONDATO
	*/

	int fine_turno;
	int i;
	celle_adiacenti *celle_bersaglio;
	int utilizzi;
	char carattere;

	celle_bersaglio = (celle_adiacenti *) malloc(sizeof(celle_adiacenti)*DIMENSIONE_CELLE_ADIACENTI);

	if (leggere_radar(attaccante) > 0)
	{
		/*
    	verifichiamo che non siano date in input
    	coordinate sui bordi della tabella per evitare
    	che l’attacco colpisca celle al di fuori della
    	tabella stessa, facilitando il giocatore
		 */
		if ((leggere_coordinata_x(coordinate) == 0) || (leggere_coordinata_x(coordinate) == DIMENSIONE_TABELLA - 1) ||
			(leggere_coordinata_y(coordinate) == 0) || (leggere_coordinata_y(coordinate) == DIMENSIONE_TABELLA - 1))
		{
			do
			{
				printf("\nCoordinate errate. Inserisci un valore di COLONNA compreso tra B e O e di RIGA compreso tra 2 e 15. \n");
				chiedere_coordinate(coordinate);
			}while((leggere_coordinata_x(coordinate) == 0) || (leggere_coordinata_x(coordinate) == DIMENSIONE_TABELLA - 1) ||
					(leggere_coordinata_y(coordinate) == 0) || (leggere_coordinata_y(coordinate) == DIMENSIONE_TABELLA - 1));
		}
		system("@cls||clear");
		printf("\nRisultato della scansione del Radar:\n");
		celle_bersaglio = calcolare_celle_adiacenti(celle_bersaglio, coordinate);
		i = 0;
		while (i < DIMENSIONE_CELLE_ADIACENTI)
		{
			if (leggere_posizione_flotta(difensore, celle_bersaglio->x[i], celle_bersaglio->y[i]) == ACQUA)		//celle mare
			{
				scrivere_colpi_sferrati(attaccante, celle_bersaglio->x[i], celle_bersaglio->y[i], ACQUA);
				carattere = PRIMA_LETTERA_COLONNA + celle_bersaglio->y[i];
				printf("\n- C'e' ACQUA in [%c - %d]\n", carattere, celle_bersaglio->x[i]);
			}
			else if (leggere_posizione_flotta(difensore, celle_bersaglio->x[i], celle_bersaglio->y[i]) == COLPITO || leggere_posizione_flotta(difensore, celle_bersaglio->x[i], celle_bersaglio->y[i]) == AFFONDATO) //celle colpite
			{
				carattere = PRIMA_LETTERA_COLONNA + celle_bersaglio->y[i];
				printf("\n- C'e' una nave GIA' COLPITA in [%c - %d]\n", carattere, celle_bersaglio->x[i]);
			}
			else		//navi integre
			{
				carattere = PRIMA_LETTERA_COLONNA + celle_bersaglio->y[i];
				scrivere_colpi_sferrati(attaccante, celle_bersaglio->x[i], celle_bersaglio->y[i], RILEVATO);
				printf("\n- LOCALIZZATA una nave in [%c - %d]\n", carattere, celle_bersaglio->x[i]);
			}
			fine_turno = 1;
			i++;
		}
		utilizzi = leggere_radar(attaccante);
		scrivere_radar(attaccante, (utilizzi-1));
		stampa_tabella_colpi_sferrati(attaccante, partita);
	}
	else
	{
		printf("Attacco non disponibile. Scegli un altro attacco\n");
	}

	free(celle_bersaglio);

  return fine_turno;
}
