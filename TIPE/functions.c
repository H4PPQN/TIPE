#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "metro_v.h"
#include "functions.h"
#include <stdbool.h>

bool isStat_inLine(station* station, ligne* ligne) {
    bool resp = false;
    for (int i = 0; i < ligne->tab_stat_len; i++) {

        if (ligne->tab_station[i] == station) {

            resp = true;
        }

        return resp;
    }

}
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
    new_graph->longueur = longueurs;
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

void maj_station(graphe* g) {

    for (int i = 0; i < NB_STATIONS_METRO; i++) {
        assert(((g->stations[i])->current_people + (g->stations[i])->in) < (g->stations[i])->capacity);
 
        (g->stations[i])->current_people += (g->stations[i])->in;



    }
}

void maj_rame(graphe *g) {//all good

    for (int i = 0; i < NB_RAMES_METRO; i++) {
        rame* rame_courante = g->rames[i];
        int id_dep = (g->rames[i])->depart;
        int id_arr = (g->rames[i])->arrivee;
        int dist = g->longueur[id_arr][id_dep];
        int tmp = 0; 
        int nombre_a_faire_monter = 0;
        
        for (int j = 0; j < NB_STATIONS_METRO; j++) {
            if ((g->stations[id_arr])->destinations[j] != 0) {

                if ((g->next_station[id_arr][j]) = id_arr + 1 && isStat_inLine(g->stations[id_arr + 1], g->lignes[(g->rames[i])->ligne_id]) == true){//il faut s'assurer que la station suivante est dans la ligne de la rame
                    nombre_a_faire_monter = (nombre_a_faire_monter + (g->stations[id_arr])->destinations[j]) % (g->stations[id_arr])->capacity; //calcul du nombre de personne a faire monter (le modulo sert a ne pas depasser la capacite de la rame)
                    (g->stations[id_arr])->destinations[j] -= ((g->stations[id_arr])->destinations[j]) % (g->stations[id_arr])->capacity;//on soustrait le nombre des personnes qui sont monte dans la rame
                }
            }
            if (isStat_inLine((g->next_station[id_arr][j]), g->lignes[(g->rames[i])->ligne_id] == false)) {
                int p_qui_changent_de_ligne = rame_courante->distribution[j] % (g->stations[id_arr])->capacity;
                rame_courante->current_people -= rame_courante->distribution[j]; //ceux qui doivent changer de ligne vont devoir descendre
                (g->stations[id_arr])->current_people += p_qui_changent_de_ligne; //modulo : ceux en plus vont quitter la station...
                ((g->stations[id_arr])->destinations[j]) += p_qui_changent_de_ligne;
            }
        }
 
        if (rame_courante->localisation + UPDATE_INTERV >= dist) {
            int stat_arr = (g->stations[id_arr + 1])->id;
            rame_courante->depart = (g->stations[id_arr])->id;
            rame_courante->arrivee = stat_arr;
            rame_courante->localisation = 0;
            
            rame_courante->current_people += - (g->rames[i])->distribution[id_arr] + nombre_a_faire_monter;

            (g->rames[i])->distribution[id_arr] = 0; //Tout ceux qui voulaient descendre pourront descendre
           
            

            

        }
        else {
            (g->rames[i])->localisation += g->vitesse[id_dep][id_arr] * UPDATE_INTERV;
        }


    }
}

void maj(graphe* g) {

    update_stations(g);
    update_rames(g);

    //mise a jour des vitesses 

    
    for (int i = 0; i < NB_STATIONS_METRO; i++) {
        int ppl_in_i = (g->stations[i])->current_people;
        int cap_stat_i = (g->stations[i])->capacity;
        for (int j = 0; j < NB_STATIONS_METRO; j++) {
            int ppl_in_j = (g->stations[j])->current_people;
            int cap_stat_j = (g->stations[j])->capacity;
            g->vitesse[i][j] = -(FICK_CONST * (ppl_in_j - ppl_in_i) / CAPACITE_RAME) - (OMEGA * (ppl_in_i + ppl_in_j) / (cap_stat_i + cap_stat_j));


        }


    }
    




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
