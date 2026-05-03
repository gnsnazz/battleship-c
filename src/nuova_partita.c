/*PROLOGO IMPLEMENTAZIONE:
GRUPPO6 = Dinatale_Marco + Elmadhi_Nazim + Epifania_Cristiano + Ferrulli_Alessandro + Illuzzi_Gaetano ;
rev 1.0 - 22/06/22
*/

//MODULI DA INCLUDERE
#include "nuova_partita.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
 DESCRIZIONE:
Imposta la strutture Partita e richiama Gestione Turno

INPUT:
partita – record contenente i dati della partita - record

OUTPUT:
partita – record contenente i dati della partita - record
*/

partita *nuova_partita(partita *partita)
{
	scrivere_fase(partita, 1);
	scrivere_turno(partita, 1);
	inizializzare_giocatori(&partita->giocatori, partita);
	gestione_turno(partita);

  return partita;
}

/*
DESCRIZIONE: effettua il set-up del record giocatore ad inizio partita

INPUT
giocatori – contiene i record giocatore_1 e giocatore_2 – record
partita – record contenente i dati della partita - record
QUANTITA_BOMBARDAMENTO_AEREO - numero degli utilizzi dell’attacco bomardamento aeireo - costante- =  1
QUANTITA_RADAR - numero degli utilizzi dell’attacco radar - costante- = 3
QUANTITA_COLPO_LARGO_RAGGIO - numero degli utilizzi dell’attacco a largo raggio - costante- = 3
DIMENSIONE_CAMPI_NAVI - numero totale di navi - costante - =15
DIMENSIONE_NOME - dimensione della stringa contenente il nome - costante - =20

OUTPUT
giocatori – contiene i dati dei giocatori – record

LAVORO
nome - nome del giocatore - stringa - dimensione = DIMENSIONE_NOME
*/

giocatori *inizializzare_giocatori(giocatori *giocatori, partita *partita)
{
	system("@cls||clear");

	char nome[DIMENSIONE_NOME];

	// inizializziamo il Giocatore 1

	do
	{
		printf("\nGIOCATORE 1 inserisci il tuo nome: ");
		scanf("%s", nome);
		if (strlen(nome) > DIMENSIONE_NOME)
		{
			printf("\nIl tuo nome e' troppo lungo! (Max %d)\n", DIMENSIONE_NOME);
		}
	}while(strlen(nome) > DIMENSIONE_NOME);

	scrivere_nome(&giocatori->giocatore_1, nome);
	inizializzare_tabelle(&giocatori->giocatore_1);
	scrivere_bombardamento_aereo(&giocatori->giocatore_1, QUANTITA_BOMBARDAMENTO_AEREO);
  	scrivere_radar(&giocatori->giocatore_1, QUANTITA_RADAR);
 	scrivere_colpo_largo_raggio(&giocatori->giocatore_1, QUANTITA_COLPO_LARGO_RAGGIO);
  	scrivere_numero_navi(&giocatori->giocatore_1, DIMENSIONE_CAMPI_NAVI);
  	inizializzare_navi(&giocatori->giocatore_1);
  	printf("\n%s! disponi la tua flotta \n", leggere_nome(&giocatori->giocatore_1));
  	disporre_flotta(&giocatori->giocatore_1, partita);


  	system("@cls||clear");
	// inizializziamo il Giocatore 2
  	do
  	{
  		printf("\nGIOCATORE 2 inserisci il tuo nome: ");
  		scanf("%s", nome);
  		if (strlen(nome) > DIMENSIONE_NOME)
  		{
  			printf("\nIl tuo nome e' troppo lungo! (Max %d)\n", DIMENSIONE_NOME);
  		}
  	}while(strlen(nome) > DIMENSIONE_NOME);

  	scrivere_nome(&giocatori->giocatore_2, nome);
  	inizializzare_tabelle(&giocatori->giocatore_2);
  	scrivere_bombardamento_aereo(&giocatori->giocatore_2, QUANTITA_BOMBARDAMENTO_AEREO);
  	scrivere_radar(&giocatori->giocatore_2, QUANTITA_RADAR);
  	scrivere_colpo_largo_raggio(&giocatori->giocatore_2, QUANTITA_COLPO_LARGO_RAGGIO);
  	scrivere_numero_navi(&giocatori->giocatore_2, DIMENSIONE_CAMPI_NAVI);
  	inizializzare_navi(&giocatori->giocatore_2);
  	printf("\n%s! disponi la tua flotta \n", leggere_nome(&giocatori->giocatore_2));
  	disporre_flotta(&giocatori->giocatore_2, partita);

  return giocatori;
}

/*
DESCRIZIONE: sfrutta il numero e la dimensione delle navi dati in input per poter inizializzare la struttura dati navi all’inizio di una nuova partita

INPUT
giocatore- record contenente i dati del giocatore - RECORD // può essere 1 o 2
DIMENSIONE_CAMPI_NAVI - dimensione del record navi - costante -  15
NUMERO_NAVI_5- numero delle navi di dimensione 5 - costante - =1
NUMERO_NAVI_4 - numero delle navi di dimensione 4 - costante - =2
NUMERO_NAVI_3 - numero delle navi di dimensione 3 - costante - = 3
NUMERO_NAVI_2 - numero delle navi di dimensione 2 - costante - =4
NUMERO_NAVI_1 - numero delle navi di dimensione 1 - costante - =5
DIMENSIONE_NAVI_5 – numero delle celle occupate dalle navi da 5 - costante - = 5
DIMENSIONE_NAVI_4 – numero delle celle occupate dalle navi da 4 - costante - = 4
DIMENSIONE_NAVI_3 – numero delle celle occupate dalle navi da 3 - costante - = 3
DIMENSIONE_NAVI_2 – numero delle celle occupate dalle navi da 2 - costante - = 2
DIMENSIONE_NAVI_1 – numero delle celle occupate dalle navi da 1 - costante - = 1

OUTPUT
giocatore- record contenente i dati del giocatore - RECORD // può essere 1 o 2

LAVORO
i – contatore che scandisce la posizione nel record navi – intero – compreso tra 1 e 15
j – indica il numero di nave considerata – intero - da 1 a 5
*/

giocatore *inizializzare_navi(giocatore *giocatore)
{
	int i;
	int j;

	i = 0;
	j = 0;

	while(i < DIMENSIONE_CAMPI_NAVI) //controllo sul numero finale delle navi(15)
	{
		while (j < NUMERO_NAVI_1)
		{
			identificare_navi(giocatore, DIMENSIONE_NAVI_1, i, j);
			i++;
			j++;
		}

		j = 0;
		while (j < NUMERO_NAVI_2)
		{
			identificare_navi(giocatore, DIMENSIONE_NAVI_2, i, j);
			i++;
			j++;
		}

		j = 0;
		while (j < NUMERO_NAVI_3)
		{
			identificare_navi(giocatore, DIMENSIONE_NAVI_3, i, j);
			i++;
			j++;
		}

		j = 0;
		while (j < NUMERO_NAVI_4)
		{
			identificare_navi(giocatore, DIMENSIONE_NAVI_4, i, j);
			i++;
			j++;
		}

		j = 0;
		while (j < NUMERO_NAVI_5)
		{
			identificare_navi(giocatore, DIMENSIONE_NAVI_5, i, j);
			i++;
			j++;
		}
	}

  return giocatore;
}

/*
DESCRIZIONE:
compila i campi identificativo, dimensione_nave e integrità per l’inizializzazione di una posizione nella struttura dati navi

INPUT
giocatore- record contenente i dati del giocatore - RECORD // puo' essere 1 o 2
dimensione_navi – numero delle celle occupate da ogni nave –  intero – compreso tra 1 e 5
i – posizione nel record navi – intero – compreso tra 1 e DIMENSIONE_CAMPI_NAVI
j – indica il numero di nave considerata – intero - da 1 a 5

OUTPUT
giocatore- record contenente i dati del giocatore - RECORD // puo' essere 1 o 2

LAVORO
identificativo_calcolato – contiene l'id della nave considerata, intero=dimensione  decimale=numero di nave – float - da 1.1 a 5.1
*/

giocatore *identificare_navi(giocatore *giocatore, int dimensione_navi, int i, int j)
{
	float identificativo_calcolato;

	j++;

	identificativo_calcolato = dimensione_navi + (j * pow(10, -1));		// il numero di nave e' il decimale
	scrivere_identificativo_nave(giocatore, identificativo_calcolato, i);
	scrivere_dimensione_nave(giocatore, dimensione_navi, i);
	scrivere_integrita_nave(giocatore, dimensione_navi, i);
	printf("int: %d", leggere_integrita_nave(giocatore, i));

  return giocatore;
}

/*
DESCRIZIONE: indica le navi da posizionare (tot 15) in ordine di dimensione e numero, e prende in input la prima ed ultima cella di ognuna.
Scrivera' nel record flotta, nel campo posizione flotta l'ID della nave in tutte le celle occupate dalla nave stessa.
Controllera' che non ci siano sovrapposizioni di navi, che le celle siano adiacenti e che ci sia una cella di distanziamento tra ogni nave.
Ogni nave avra' lo stato = FALSO e l'integrita'=0. Ogni nave avra' nel campo dimensione la sua dimensione.

INPUT:
giocatore- record contenente i dati del giocatore - RECORD // puo' essere 1 o 2
partita – record contenente i dati della partita - record
DIMENSIONE_CAMPI_NAVI – quantità totale delle navi – intero costante – =15
OUTPUT:
giocatore- record contenente i dati del giocatore - RECORD // può essere 1 o 2

LAVORO:
i – contatore che indica il numero delle navi posizionabili rimanente – intero - >0
k – contatore dell'array celle_nave - intero - >0
cella_iniziale – coordinate della prima cella della nave - coordinate
cella_finale - coordinate dell'ultima cella della nave - coordinate
controllo – indica se la nave e' disposta correttamente – intero
celle_nave -contiene le coordinate delle celle della nave, coordinate.x è la riga della cella, mentre coordinate.y è la colonna della cella- di tipo celle adiacenti - i valori dei campi sono compresi tra 1 e 16 è di dimensione  dimensione_nave
*/

giocatore *disporre_flotta(giocatore *giocatore, partita *partita)
{
	int i;
	int k;
	coordinate *cella_iniziale;
	int dim_nave;
	coordinate *cella_finale;
	float controllo;
	celle_adiacenti *celle_nave;
	coordinate *posizione;

	posizione = (coordinate *)malloc(sizeof(coordinate));
	cella_iniziale = (coordinate*) malloc(sizeof(coordinate));
	cella_finale = (coordinate*) malloc(sizeof(coordinate));

	system("@cls||clear");
	printf("\nLe navi da posizionare sono: 1 nave da 5 caselle, 2 navi da 4 caselle, 3 navi da 3 caselle, 4 navi da 2 caselle, 5 navi da 1 casella\n");

	controllo = 0;
	i = 0;

	while(i < DIMENSIONE_CAMPI_NAVI)
	{
		printf("\nInserire nave %.1f di dimensione %d", leggere_identificativo_nave(giocatore, i), leggere_dimensione_nave(giocatore, i));
		celle_nave = (celle_adiacenti*) malloc(sizeof(celle_adiacenti)*leggere_dimensione_nave(giocatore, i));
		stampa_tabella_posizione_flotta(giocatore, partita);

		if(leggere_dimensione_nave(giocatore, i) == 1) // allocare a celle_nave spazio con dimensione dimensione_nave
		{
			do	//controlli nave da 1
			{
				printf("\nInserire coordinate della cella in cui c'e' la nave");

				chiedere_coordinate(cella_iniziale);

				celle_nave->x[0] = cella_iniziale->x;
				celle_nave->y[0] = cella_iniziale->y;
				dim_nave = leggere_dimensione_nave(giocatore, i);
				controllo = verificare_celle_libere(giocatore, celle_nave, dim_nave);

			}while(controllo != 0);

		}
		else	//controlli nave di dimensione da 2 a 5
		{
			do		// controllo spazi liberi intorno alla nave
			{
				do		// controllo dimensione nave + nave in diagonale
				{
					controllo = 1;
					printf("\nInserire coordinate della cella in cui inizia la nave");
					cella_iniziale = chiedere_coordinate(cella_iniziale);
					printf("\nInserire coordinate della cella finale della nave");
					cella_finale = chiedere_coordinate(cella_finale);

					controllo = verificare_dimensione(cella_iniziale, cella_finale, leggere_dimensione_nave(giocatore, i));

					if(controllo == 0)
					{
						printf("\nLa dimensione della nave non corrisponde alla distanza delle celle inserite. Inserire nuove coordinate|");
					}
					else if(controllo == -1)
					{
						printf("\nNon puoi inserire una nave in diagonale. Inserire nuove coordinate!");
					}
				}while(controllo != 1);
				//calcoliamo le celle della nave partendo dalla prima e l'ultima
				celle_nave = calcolare_celle_navi(celle_nave, cella_iniziale, cella_finale, leggere_dimensione_nave(giocatore, i));

				controllo = verificare_celle_libere(giocatore, celle_nave, leggere_dimensione_nave(giocatore, i));

				if(controllo != 0)
				{
					printf("\nNon hai rispettato la distanza di 1 casella con le altre navi. Inserire nuove coordinate|");
				}

			}while(controllo != 0);
			//controllo spazi liberi intorno alla nave, non è 1 perché 0 è il risultato ottimale di verificare_celle_libere
		}

		k = 0;		// scriviamo sulla tabella gli ID della nave nelle celle che occupa
		while(k < leggere_dimensione_nave(giocatore, i)){
			scrivere_posizione_flotta(giocatore, celle_nave->x[k], celle_nave->y[k], leggere_identificativo_nave(giocatore, i));
			k++;
		}
		i++;
		system("@cls||clear");
	}

	free(celle_nave);
	free(posizione);
	free(cella_iniziale);
	free(cella_finale);

  return giocatore;
}

/*
DESCRIZIONE: date in input le coordinate della prima e dell’ultima cella, da in output un array contenente le coordinate di tutte le celle della nave

INPUT
celle_nave - contiene le coordinate delle celle della nave, coordinate.x e' la riga della cella, mentre coordinate.y è la colonna della cella - di tipo celle adiacenti - i valori dei campi sono compresi tra 1 e 16 è di dimensione  dimensione_nave
cella_iniziale – coordinate della prima cella della nave - coordinate
cella_finale - coordinate dell’ultima cella della nave - coordinate
dimensione_nave - dimensione della nave di cui calcolare le celle - intero

OUTPUT
celle_nave - contiene le coordinate delle celle della nave, coordinate.x e' la riga della cella, mentre coordinate.y e' la colonna della cella- array di coordinate - i valori dei campi sono compresi tra 1 e 16 è di dimensione  dimensione_nave
LAVORO
x – indica le possibili righe delle celle da considerare – intero – compreso tra 1 e 16
y - indica le possibili colonne delle celle da considerare – intero – compreso tra 1 e 16
i - contatore per scorrere l’array celle_nave - intero - compreso tra 1 e dimensione nave
*/

celle_adiacenti *calcolare_celle_navi(celle_adiacenti *celle_nave,coordinate *cella_iniziale, coordinate *cella_finale, int dimensione_nave)
{
	int x;
	int y;
	int i;

	i = 0;

	if (cella_iniziale->x == cella_finale->x)		// nave in orizzontale
	{
		if (cella_iniziale->y < cella_finale->y)		// determiniamo se la coordinata di cella_iniziale viene prima di quella di cella_finale
		{
			//assegniamo ad y quella che è la coordinata minore cioè quella di cella iniziale
			y = cella_iniziale->y;
			while (y <= cella_finale->y)	//cicla dalla prima all’ultima
			{
				celle_nave->x[i] = cella_iniziale->x;
				celle_nave->y[i] = y;
				y++;
				i++;
			}
		}
		else
		{
			//assegniamo ad y quella che è la coordinata minore cioè quella di cella finale
			y = cella_finale->y;
			while (y <= cella_iniziale->y)
			{
				celle_nave->x[i] = cella_iniziale->x;
				celle_nave->y[i] = y;
				y++;
				i++;
			}
		}
	}
	else	// i due campi y sono uguali (nave in verticale)
	{
		if (cella_iniziale->x < cella_finale->x)
		{
			x = cella_iniziale->x;		//coordinata minore
			while (x <= cella_finale->x)
			{
				celle_nave->y[i] = cella_iniziale->y;
				celle_nave->x[i] = x;
				x++;
				i++;
			}
		}
		else
		{
			x = cella_finale->x;	//coordinata minore
			while (x <= cella_iniziale->x)
			{
				celle_nave->y[i]= cella_iniziale->y;
				celle_nave->x[i] = x;
				x++;
				i++;
			}
		}
	}

  return celle_nave;
}

/*
DESCRIZIONE: dati in input le celle in cui si trova la nave, determina se queste e quelle a loro adiacenti sono libere.
Verifica che il valore delle celle considerate sia sempre e solo 0 (mare), in caso contrario non sono libere.
Per rendere il risultato veritiero sono escluse le celle calcolate ma al di fuori della tabella.

INPUT
giocatore- record contenente i dati del giocatore - RECORD // può essere 1 o 2
celle_nave -contiene le coordinate delle celle della nave, coordinate.x e' la riga della cella, mentre coordinate.y e' la colonna della cella-  di tipo celle adiacenti - i valori dei campi sono compresi tra 1 e 16 è di dimensione  dimensione_nave
dimensione_nave – dimensione della nave da analizzare – intero – valore compreso tra 1 e 5
DIMENSIONE_CELLE_ADIACENTI – dimensione dell’array celle adiacenti - =9
DIMENSIONE_TABELLA - dimensione delle tabelle di gioco - costante -  =16

OUTPUT
controllo_celle  – indica se le celle della nave o quelle che le stanno attorno sono occupate (tutte celle contenenti 0  – decimale – se =0 tutte le celle sono libere 	// è un controllo, ma non è booleano perchè deriva dal risultato di una somma

LAVORO
celle_circostanti -contiene le coordinate delle celle intorno a quella da analizzare, coordinate.x e' la riga della cella, mentre coordinate.y e' la colonna della cella - di tipo celle adiacenti - i valori dei campi sono compresi tra 1 e DIMENSIONE_ TABELLA, e' di dimensione  DIMENSIONE_CELLE_ADIACENTI
i – indice dell’ l’array celle nave – intero -  <= dimensione_nave
j – indice dell’ l’array celle nave – intero -  <= dimensione_nave
x - valore delle righe di una delle celle adiacenti - intero
y - valore delle righe di una delle celle adiacenti - intero
posizione - coordinate contenute in una delle posizioni di celle_nave - coordinate
*/

float verificare_celle_libere(giocatore *giocatore, celle_adiacenti *celle_nave, int dimensione_nave)
{
	float controllo_celle;
	int i;
	int j;
	int x;
	int y;
	coordinate *posizione;
	celle_adiacenti *celle_adc;

	posizione = (coordinate *) malloc(sizeof(coordinate));
	celle_adc = (celle_adiacenti *) malloc(sizeof(celle_adiacenti));

	controllo_celle = 0;
	i = 0;

	while ((i < dimensione_nave) && (controllo_celle == 0))
	{
		// consideriamo una delle celle della nave
		posizione->x = leggere_valore_celle_adiacenti_x(celle_nave, i);
		posizione->y = leggere_valore_celle_adiacenti_y(celle_nave, i);
		// calcoliamo le celle intorno alla singola cella considerata
		celle_adc = calcolare_celle_adiacenti(celle_adc, posizione);
		j = 0;
		while ((j < DIMENSIONE_CELLE_ADIACENTI) && (controllo_celle == 0))
		{
			// se una cella contiene un valore diverso da 0 finisce il controllo
			x = leggere_valore_celle_adiacenti_x(celle_adc, j);
			y = leggere_valore_celle_adiacenti_y(celle_adc, j);

			if ((x >= 0) && (x < DIMENSIONE_TABELLA) && (y >= 0) && (y < DIMENSIONE_TABELLA))
			{
				//consideriamo nel controllo solo le coordinate che rientrano nella griglia
				controllo_celle = leggere_posizione_flotta(giocatore, x, y);	// gli assegniamo il valore di una delle celle che dovrebbero essere libere (0= mare)
			}
			j++;
		}
		i++;
	}

	free(celle_adc);
	free(posizione);

  return controllo_celle;
}

/*
DESCRIZIONE: determina se la dimensione della nave data in input e' uguale a quella che il giocatore può disporre in questo momento

INPUT:
cella_iniziale – coordinate della prima cella della nave - coordinate
cella_finale - coordinate dell’ultima cella della nave - coordinate
dimensione – dimensione della nave – intero – compreso tra 1 e 5

OUTPUT:
risultato – indica se la distanza tra le celle e' uguale alla dimensione della naveo se e' in orizzontale o verticale – intero - 0=dimensione errata, 1=disposta bene  -1= nave in diagonale

LAVORO:
j – variabile che assume il valore assoluto della sottrazione tra le coordinate
*/

int verificare_dimensione(coordinate *cella_iniziale, coordinate *cella_finale, int dimensione)
{
	int risultato;
	int j;

	risultato = 0;  //nave dell dimensione sbagliata

	//evita che la nave sia in diagonale
	if((cella_iniziale->x == cella_finale->x) || (cella_iniziale->y == cella_finale->y))
	{
		if (cella_iniziale->x == cella_finale->x)	//nave in orizzontale
		{
			j = (abs(cella_iniziale->y - cella_finale->y))+ 1;
			if (j == dimensione)
			{
				risultato = 1;  //dimensione giusta
			}
		}
		else	//nave in verticale
		{
			j = (abs(cella_iniziale->x - cella_finale->x)) + 1;
			if (j == dimensione)
			{
				risultato = 1;  //dimensione giusta
			}
		}
	}
	else
	{
		risultato = -1;  //la nave e' in diagonale
	}

  return risultato;
}

/*
DESCRIZIONE: funzione che assegna il valore 0 ad ogni cella delle tabelle posizione flotta e colpi sferrati di un solo giocatore

INPUT:
giocatore- record contenente i dati del giocatore - RECORD // puo' essere 1 o 2
ACQUA - valore delle celle contenenti acqua - costante - = 0
CELLA_NEUTRA - valore cella neutra in colpi sferrati - costante -  = 2
DIMENSIONE_ TABELLA - dimensione delle tabelle colpi sferrati e posizione flotta - costante -  =16

OUTPUT:
giocatore- record contenente i dati del giocatore - RECORD // puo' essere 1 o 2

LAVORO:
i - contatore per scorrere le righe della tabella- intero- 1<=i<=DIMENSIONE_ TABELLA
j – contatore per scorrere le colonne della tabella - intero- 0<=i<=DIMENSIONE_ TABELLA
*/

giocatore *inizializzare_tabelle(giocatore *giocatore)
{
	int i;
	int j;

	i = 0;

	while (i < DIMENSIONE_TABELLA)
	{
		j = 0;
		while (j < DIMENSIONE_TABELLA)
		{
			scrivere_posizione_flotta(giocatore, i, j, ACQUA);
			scrivere_colpi_sferrati(giocatore, i, j, CELLA_NEUTRA);
			j++;
		}
		i++;
	}

  return giocatore;
}
