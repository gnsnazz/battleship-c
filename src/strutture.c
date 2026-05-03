/*PROLOGO IMPLEMENTAZIONE:
GRUPPO6 = Dinatale_Marco + Elmadhi_Nazim + Epifania_Cristiano + Ferrulli_Alessandro + Illuzzi_Gaetano ;
rev 1.0 - 22/06/22
*/

#include "strutture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int leggere_turno(partita *partita)
{
	int valore;
	valore = partita->numero_turno;
  return valore;
}

partita *scrivere_turno(partita *partita, int num)
{
	partita->numero_turno = num;
  return partita;
}

int leggere_fase(partita *partita)
{
	int fase;
	fase = partita->numero_fase;
  return fase;
}

partita *scrivere_fase(partita *partita, int fase)
{
	partita->numero_fase = fase;
  return partita;
}

char *leggere_nome(giocatore *giocatore)
{
	char *nome_giocatore;
	int dim_nome;
	dim_nome = strlen(giocatore->nome);
	nome_giocatore = (char *) malloc(sizeof(char) *dim_nome+1);
	strcpy(nome_giocatore, giocatore->nome);
  return nome_giocatore;
}


giocatore *scrivere_nome(giocatore *giocatore, char nome_giocatore[])
{
	strcpy(giocatore->nome, nome_giocatore);
  return giocatore;
}

float leggere_posizione_flotta(giocatore *giocatore, int x, int y)
{
	float valore;
	valore = giocatore->flotta.posizione_flotta[x][y];
  return valore;
}

giocatore *scrivere_posizione_flotta(giocatore *giocatore, int x, int y, float valore)
{
	giocatore->flotta.posizione_flotta[x][y] = valore;
  return giocatore;
}

int leggere_colpi_sferrati(giocatore *giocatore, int x, int y)
{
	int valore;
	valore = giocatore->colpi_sferrati[x][y];
  return valore;
}

giocatore *scrivere_colpi_sferrati(giocatore *giocatore, int x, int y, int valore)
{
	giocatore->colpi_sferrati[x][y] = valore;
  return giocatore;
}

int leggere_bombardamento_aereo(giocatore *giocatore)
{
	int valore;
	valore = giocatore->bombardamento_aereo;
  return valore;
}

giocatore *scrivere_bombardamento_aereo(giocatore *giocatore, int valore)
{
	giocatore->bombardamento_aereo = valore;
  return giocatore;
}

int leggere_radar(giocatore *giocatore)
{
	int valore;
	valore = giocatore->radar;
  return valore;
}

giocatore *scrivere_radar(giocatore *giocatore, int valore)
{
	giocatore->radar = valore;
  return giocatore;
}

int leggere_colpo_largo_raggio(giocatore *giocatore)
{
	int valore;
	valore = giocatore->colpi_largo_raggio;
  return valore;
}

giocatore *scrivere_colpo_largo_raggio(giocatore *giocatore, int valore)
{
	giocatore->colpi_largo_raggio = valore;
  return giocatore;
}

int leggere_numero_navi(giocatore *giocatore)
{
	int valore;
	valore = giocatore->flotta.numero_navi;
  return valore;
}

giocatore *scrivere_numero_navi(giocatore *giocatore, int valore)
{
	giocatore->flotta.numero_navi = valore;
  return giocatore;
}

float leggere_identificativo_nave(giocatore *giocatore, int i)
{
	float valore;
	valore = giocatore->flotta.navi.indentificativo[i];
  return valore;
}

giocatore *scrivere_identificativo_nave(giocatore *giocatore, float valore, int i)
{
	giocatore->flotta.navi.indentificativo[i] = valore;
	valore++;
  return giocatore;
}

int leggere_dimensione_nave(giocatore *giocatore, int i)
{
	int valore;
	valore = giocatore->flotta.navi.dimensione_nave[i];
  return valore;
}

giocatore *scrivere_dimensione_nave(giocatore *giocatore, int valore, int i)
{
	giocatore->flotta.navi.dimensione_nave[i] = valore;
  return giocatore;
}

int leggere_integrita_nave(giocatore *giocatore, int i)
{
	int valore;
	valore = giocatore->flotta.navi.integrita[i];
  return valore;
}

giocatore *scrivere_integrita_nave(giocatore *giocatore, int valore, int i)
{
	giocatore->flotta.navi.integrita[i] = valore;
  return giocatore;
}


int leggere_coordinata_x(coordinate *coordinate) {
	int x;
	x = coordinate->x;
  return x;
}

coordinate *scrivere_coordinata_x(coordinate *coordinate, int x)
{
	coordinate->x = x;
  return coordinate;
}

int leggere_coordinata_y(coordinate *coordinate)
{
	int y;
	y = coordinate->y;
  return y;
}

coordinate *scrivere_coordinata_y(coordinate *coordinate, int y)
{
	coordinate->y = y;
  return coordinate;
}

int leggere_valore_celle_adiacenti_x(celle_adiacenti *celle_adiacenti, int i)
{
	int valore;
	valore = celle_adiacenti->x[i];
  return valore;
}

celle_adiacenti *scrivere_valore_celle_adiacenti_x(celle_adiacenti *celle_adiacenti, int i, int valore)
{
	celle_adiacenti->x[i] = valore;
  return celle_adiacenti;
}

int leggere_valore_celle_adiacenti_y(celle_adiacenti *celle_adiacenti, int i)
{
	int valore;
	valore = celle_adiacenti->y[i];
  return valore;
}

celle_adiacenti *scrivere_valore_celle_adiacenti_y(celle_adiacenti *celle_adiacenti, int i, int valore)
{
	celle_adiacenti->y[i] = valore;
  return celle_adiacenti;
}
