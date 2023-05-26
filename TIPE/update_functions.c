#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "metro_v.h"


void update_station(graphe* g, int pctge_in) {

    for (int i = 0; i < NB_STATIONS_METRO; i++) {
        assert((g->stations[i])->in * (1 + pctge_in) < (g->stations[i])->capacity);
        (g->stations[i])->in = ((g->stations[i])->in) * (1 + pctge_in);
        (g->stations[i])->current_people += (g->stations[i])->in;


    }
}





void update_rame(graphe* g) {

    for (int i = 0; i < NB_RAMES_METRO; i++) {

        int id_dep = (g->rames[i])->depart;
        int id_arr = (g->rames[i])->arrivee;
        int dist = g->longueur[id_arr][id_dep];
        int people_getting_out = ((g->rames[i])->current_people) * ((g->rames[i])->destinations[id_arr]);
        if ((g->rames[i])->localisation + UPDATE_INTERV >= dist) {
            int stat_arr = (g->stations[id_arr + 1])->id;
            (g->rames[i])->depart = (g->stations[id_arr])->id;
            (g->rames[i])->arrivee = stat_arr;
            (g->rames[i])->localisation = 0;
            (g->rames[i])->current_people -= people_getting_out; //updating current_people (subtract people who got out) 
            (g->rames[i])->destinations[id_arr] = 0; //updating the pctg of people heading to station[i]

        }
        else {
            (g->rames[i])->localisation += UPDATE_INTERV;
        }


    }
}