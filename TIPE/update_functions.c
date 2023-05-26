#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "metro.h"


void maj_station(graphe* g, int pctge_in) {

    for (int i = 0; i < NB_STATIONS_METRO; i++) {
        assert((g->stations[i])->in * (1 + pctge_in) < (g->stations[i])->capacity);
        (g->stations[i])->in = ((g->stations[i])->in) * (1 + pctge_in);
        (g->stations[i])->current_people += (g->stations[i])->in;


    }
}





void maj_rame(graphe* g) {

    for (int i = 0; i < NB_RAMES_METRO; i++) {

        int id_dep = ((g->rames[i])->depart)->id;
        int id_arr = ((g->rames[i])->arrivee)->id;
        int dist = g->adjacences[id_arr][id_dep];
        if ((g->rames[i])->localisation + UPDATE_INTERV > dist) {
            station* stat_arr = g->stations[(((g->rames[i])->arrivee)->id) + 1];
            (g->rames[i])->depart = (g->rames[i])->arrivee;
            (g->rames[i])->arrivee = stat_arr;
            (g->rames[i])->localisation = 0;

        }
        else {
            (g->rames[i])->localisation = (g->rames[i])->localisation + UPDATE_INTERV;
        }


    }
