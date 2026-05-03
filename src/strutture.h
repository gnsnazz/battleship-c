/*PROLOGO INTERFACCIA: Modulo che contiene tutte le strutture utili al gioco e le rispettive funzioni d’accesso*/

#ifndef STRUTTURE_H_
#define STRUTTURE_H_

//DEFINIZIONE COSTANTI
#define DIMENSIONE_TABELLA 16
#define DIMENSIONE_CELLE_ADIACENTI 9
#define DIMENSIONE_CAMPI_NAVI 15

#define DIMENSIONE_NOME 20
#define QUANTITA_BOMBARDAMENTO_AEREO 1
#define QUANTITA_RADAR 3
#define QUANTITA_COLPO_LARGO_RAGGIO 3
#define DIMENSIONE_CAMPI_NAVI 15


//navi - record contenente i dati delle navi – RECORD
typedef struct
{
	float indentificativo[DIMENSIONE_CAMPI_NAVI];
	int dimensione_nave[DIMENSIONE_CAMPI_NAVI];
	int integrita[DIMENSIONE_CAMPI_NAVI];
}navi;


//flotta - record contenente i dati della flotta- RECORD
typedef struct
{
	float posizione_flotta[DIMENSIONE_TABELLA][DIMENSIONE_TABELLA];
	int numero_navi;
	navi navi;
}flotta;


//giocatore - record contenente i dati di un giocatore – RECORD
typedef struct
{
	char nome[DIMENSIONE_NOME];
	flotta flotta;
	int colpi_sferrati[DIMENSIONE_TABELLA][DIMENSIONE_TABELLA];
	int bombardamento_aereo;
	int radar;
	int colpi_largo_raggio;
}giocatore;


//giocatori - record contenente i dati dei giocatori - RECORD
typedef struct
{
	giocatore giocatore_1;
	giocatore giocatore_2;
}giocatori;


//partita - record contenente i dati della partita – RECORD
typedef struct
{
	int numero_fase;
	int numero_turno;
  giocatori giocatori;
}partita;


//coordinate - record contenente le coordinate di una cella – RECORD
typedef struct
{
	int x;
	int y;
}coordinate;


//celle adiacenti - record contenente le coordinate delle celle in un’area di dimensione 3x3 – RECORD
typedef struct
{
	int x[DIMENSIONE_CELLE_ADIACENTI];
	int y[DIMENSIONE_CELLE_ADIACENTI];
}celle_adiacenti;


//FUNZIONI DI ACCESSO
int leggere_turno(partita *partita);
partita *scrivere_turno(partita *partita, int num);
int leggere_fase(partita *partita);
partita *scrivere_fase(partita *partita, int fase);
char* leggere_nome(giocatore *giocatore);
giocatore *scrivere_nome(giocatore *giocatore, char nome_giocatore[]);
float leggere_posizione_flotta(giocatore *giocatore, int x, int y);
giocatore *scrivere_posizione_flotta(giocatore *giocatore, int x, int y, float valore);
int leggere_colpi_sferrati(giocatore *giocatore, int x, int y);
giocatore *scrivere_colpi_sferrati(giocatore *giocatore, int x, int y, int valore);
int leggere_bombardamento_aereo(giocatore *giocatore);
giocatore *scrivere_bombardamento_aereo(giocatore *giocatore, int i);
int leggere_radar(giocatore *giocatore);
giocatore *scrivere_radar(giocatore *giocatore, int i);
int leggere_colpo_largo_raggio(giocatore *giocatore);
giocatore *scrivere_colpo_largo_raggio(giocatore *giocatore, int i);
int leggere_numero_navi(giocatore *giocatore);
giocatore *scrivere_numero_navi(giocatore *giocatore, int valore);
float leggere_identificativo_nave(giocatore *giocatore, int i);
giocatore *scrivere_identificativo_nave(giocatore *giocatore, float valore, int i);
int leggere_dimensione_nave(giocatore *giocatore, int i);
giocatore *scrivere_dimensione_nave(giocatore *giocatore, int valore, int i);
int leggere_integrita_nave(giocatore *giocatore, int i);
giocatore *scrivere_integrita_nave(giocatore *giocatore, int valore, int i);
int leggere_coordinata_x(coordinate *coordinate);
coordinate *scrivere_coordinata_x(coordinate *coordinate, int x);
int leggere_coordinata_y(coordinate *coordinate);
coordinate *scrivere_coordinata_y(coordinate *coordinate, int y);
int leggere_valore_celle_adiacenti_x(celle_adiacenti *celle_adiacenti, int i);
celle_adiacenti *scrivere_valore_celle_adiacenti_x(celle_adiacenti *celle_adiacenti, int i, int valore);
int leggere_valore_celle_adiacenti_y(celle_adiacenti *celle_adiacenti, int i);
celle_adiacenti *scrivere_valore_celle_adiacenti_y(celle_adiacenti *celle_adiacenti, int i, int valore);

#endif
