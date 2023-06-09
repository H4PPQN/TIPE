#include "metro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

station *creer_station(int id, char *nom)
{
  station *s = (station*)malloc(sizeof(station));
  s->id = id;
  strcpy(s->nom, nom);
  for(int i = 0; i < NB_LIGNES_METRO; i++)
    s->correspondances[i] = NULL;
  return s;
}

ligne *creer_ligne(int id, char *nom)
{
  ligne *l = (ligne*)malloc(sizeof(ligne));
  l->id = id;
  strcpy(l->nom, nom);
  for(int i = 0; i < NB_STATIONS_METRO; i++)
    l->tab_station[i] = NULL;
  return l;
}

graphe *creer_graphe_vide()
{
  graphe *g = (graphe*)malloc(sizeof(graphe));
  for(int i = 0; i < NB_STATIONS_METRO; i++)
    g->stations[i] = NULL;
  for(int i = 0; i < NB_LIGNES_METRO; i++)
    g->lignes[i] = NULL;
  for(int i = 0; i < NB_STATIONS_METRO; i++)
    {
      for(int j = 0; j < NB_STATIONS_METRO; j++)
	g->adjacences[i][j] = 0;
    }
  return g;
}