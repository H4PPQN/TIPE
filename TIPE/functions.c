#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "metro.h"
#include "functions.h"
#include <stdbool.h>


station* create_station(int id, char* nom, int* correspondances, unsigned int capacity) {

    station* new_station = malloc(sizeof(station));
    new_station->id = id;
    new_station->nom = nom;
    new_station->correspondances = correspondances;
    new_station->capacity= capacity;
    new_station->current_people= 0;
    new_station->in = 0;

    new_station->destinations = NULL;
    return new_station;
}

rame* create_rame(int id, int depart, int* destinations) {

    rame *new_rame = malloc(sizeof(rame));

    new_rame->id = id;
    new_rame->depart = depart;
    new_rame->arrivee = depart + 1;
    new_rame->localisation= 0;

    new_rame->current_people = 0;
    new_rame->distribution = calloc(NB_STATIONS_METRO,sizeof(int));


    return new_rame;

}


graphe* create_graph(station *stations,rame* rames, int** longueurs) {

    graphe* new_graph = malloc(sizeof(graphe));
    new_graph->longueurs = longueurs;
    new_graph->rames = rames;
    new_graph->stations = stations;
    // creer la matrice vitesse
    double** vitesse = (double**)malloc(NB_STATIONS_METRO * sizeof(double*));
    for (int i = 0; i < NB_STATIONS_METRO; i++) {
        vitesse[i] = (double*)malloc(NB_STATIONS_METRO * sizeof(double));
    }

    for (int i = 0; i < NB_STATIONS_METRO; i++) {
        for (int j = 0; j < NB_STATIONS_METRO; j++) {
            vitesse[i][j] = 0;
        }
    }


    new_graph->vitesse = vitesse;


    return new_graph;
}

void update_stations(graphe* g) {

    for (int i = 0; i < NB_STATIONS_METRO; i++) {
        assert(((g->stations[i])->current_people + (g->stations[i])->in) < (g->stations[i])->capacity);
 
        (g->stations[i]).current_people += (g->stations[i]).in;



    }
}

void update_rames(graphe* g) {//all good

    for (int i = 0; i < NB_RAMES_METRO; i++) {

        int id_dep = (g->rames[i]).depart;
        int id_arr = (g->rames[i]).arrivee;
        int dist = g->longueurs[id_arr][id_dep];
        int tmp = 0;
        int nombre_a_faire_monter = 0;
        for (int j = 0; j < (g->ligne[(g->rame[i])->ligne_id])->tab_stat_len; j++) {
            if ((g->ligne[(g->rame[i])->ligne_id])->tab_station[j] == (g->rame[i]).id) {

                tmp = 1;
            }
            if (tmp == 1) {//une fois on arrive a la station courante dans le tab des stations de la ligne

                nombre_a_faire_monter += ((g->stations[id_arr])->destinations[j] ) % (g->rame[i]->capacity); //histoire de pas depasser la capacite de la rame
                (g->station[id_arr])->destination[j] -= ((g->stations[id_arr])->destinations[j]) % (g->rame[i]->capacity);

            }




        }
 
        station stat = g->stations[i];
        if ((g->rames[i]).localisation + UPDATE_INTERV >= dist) {
            int stat_arr = (g->stations[id_arr + 1]).id;
            (g->rames[i]).depart = (g->stations[id_arr]).id;
            (g->rames[i]).arrivee = stat_arr;
            (g->rames[i]).localisation = 0;

            (g->rames[i]).current_people += - (g->rame[i])->distribution[id_arr] + nombre_a_faire_monter;

            (g->station[id_arr])->destination[id_arr + 1] -= nombre_a_faire_monter;
            

            

        }
        else {
            (g->rames[i]).localisation += g->vitesse[id_dep][id_arr] * UPDATE_INTERV;
        }


    }
}

void maj(graphe* g) {

    update_stations(g);
    update_rames(g);
    //mise a jour des vitesses --> PROBLEME
    
    

}

bool isAffStat_inPath(Path* allPaths, station* affected_station, int pathCount) {//verifie si le chemin contient la station affectee

    for (int i = 0; i < pathCount; i++) {
        for (int j = 0; j < allPaths[i].length; j++) {

            if (allPaths[i].nodes[j] == affected_station->id) {

                return true;

            }
            else { return false; }
        }
    }
};

//void reroute(graphe * g, station * from, station * to, station * affected_station) {//recalculer pour chaque personne.
//        
//
//        int pathLength;
//        int* shortest_path = dijkstra(g->longueurs, from->id, to->id, &pathLength); //path: tableau qui contient le chemin optimal (chemin avec les IDs des stations etla station affectee aura un coeff tres eleve)
//
//        int aff_station_id = affected_station->id;
//
//        //mise a jour des tab_montees des stations du nouveau chemin
//        int ppl_to_reroute = from->montee[aff_station_id]; //personnes qui souhaitaient monter pour aller a la stat_aff
//        from->montee[aff_station_id] = 0;
//        for (int j = 1; j < pathLength; j++) { //rajouter les personnes a transferer dans les stations du nouveau chemin
//            (g->stations[shortest_path[j - 1]]).montee[shortest_path[j]] += ppl_to_reroute;
//        }
//        
//
//        //mise a jour des tab_montees des stations des anciens chemins
//
//        int pathCount;
//
//
//        Path* allPaths = findAllPathsWrapper(g->longueurs, from->id, to->id, &pathCount); //tous les chemins possibles 
//
//        for (int j = 0; j < pathCount; j++) {
//
//            if (allPaths[j].nodes != shortest_path && isAffStat_inPath(allPaths, affected_station, pathCount)) {
//
//
//                for (int k = 0; k < allPaths[j].length; k++) {
//
//                    if ((g->stations[allPaths[j].nodes[k]]).montee[to->id] != 0) {
//                        for (int m = 1; m < allPaths[j].length; m++) {
//                            if ((g->stations[allPaths[j].nodes[k]]).montee[allPaths[j].nodes[m]] != 0) {
//                                (g->stations[allPaths[j].nodes[k]]).montee[allPaths[j].nodes[m]] -= (g->stations[allPaths[j].nodes[k]]).montee[to->id];
//                            }
//
//                        }
//                        
//                    }
//
//                    
//                }
//
//
//            }
//        }
//    }
