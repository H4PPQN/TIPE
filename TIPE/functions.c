#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "metro_v.h"
#include "functions.h"

void update_station(graphe* g) {

    for (int i = 0; i < NB_STATIONS_METRO; i++) {
        assert(((g->stations[i])->current_people + (g->stations[i])->in) < (g->stations[i])->capacity);
 
        (g->stations[i])->current_people += (g->stations[i])->in;


    }
}





void update_rame(graphe* g) {

    for (int i = 0; i < NB_RAMES_METRO; i++) {

        int id_dep = (g->rames[i])->depart;
        int id_arr = (g->rames[i])->arrivee;
        int dist = g->longueur[id_arr][id_dep];
        station *stat = g->stations[i];
        if ((g->rames[i])->localisation + UPDATE_INTERV >= dist) {
            int stat_arr = (g->stations[id_arr + 1])->id;
            (g->rames[i])->depart = (g->stations[id_arr])->id;
            (g->rames[i])->arrivee = stat_arr;
            (g->rames[i])->localisation = 0;
            (g->rames[i])->current_people += stat->montee[id_arr + 1] - ((g->rames[i])->destinations[id_arr]); //updating current_people (subtract people who got out and add those get in) 
            (g->stations[i])->current_people -= stat->montee[id_arr + 1]; //soustraire ceux qui descendent (on ajoute rien car les personnes qui rentrent sont gerees par update_station)
            stat->montee[id_arr + 1] = 0; //remise a zero du nombre de personnes qui souhaitaient monter dans la rame

            (g->rames[i])->destinations[id_arr] = 0; //remise a zero des gens qui avaient pour destination

        }
        else {
            (g->rames[i])->localisation += (g->rames[i])->vitesse*UPDATE_INTERV;
        }


    }
}





void reroute(graphe* g, station* from, station* to, station* affected_station) {

    int pathLength;
    int* path = dijkstra(g, from, to, &pathLength);

    int aff_station_id = affected_station->id;

    for (int i = 0; i < NB_STATIONS_METRO; i++) { //mise a jour des tab_montees des stations du nouveau chemin
        int ppl_to_reroute = (g->stations[i])->montee[aff_station_id];
        (g->stations[i])->montee[aff_station_id] = 0;
        for (int j = 1; j < pathLength - 1; j++) {
            (g->stations[path[j - 1]])->montee[path[j]] += ppl_to_reroute;
        }


    }


    for (int i = 0; i < NB_RAMES_METRO; i++) { //mise a jour des tab_montees des stations des anciens chemins
        int ppl_to_reroute = (g->stations[i])->montee[aff_station_id];
        int pathCount;
        int length;
        Path* allPaths = findAllPathsWrapper(g, from->id, to->id, &pathCount);
        freePaths(allPaths, pathCount);
        linked_stations(g, from->id, to->id, pathCount, &length);

        for (int j = 0; j < length; j++) {




       }

    }
}