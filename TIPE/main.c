
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "metro_v.h"
#include "functions.h"



int main()
{
    int longueurs[SIZE][SIZE] = {
        {0, 3, 3, 0, 0, 0,  0, 0, 0},
        {3, 0, 0, 4, 4, 0,  0, 2, 0},
        {0, 0, 0, 0, 0, 0,  0, 0, 0},
        {0, 4, 0, 0, 0, 0, 10, 0, 0},
        {0, 4, 0, 0, 0, 4,  4, 0, 0},
        {0, 0, 0, 0, 4, 0,  3, 0, 2},
        {0, 0, 0,10, 4, 3,  0, 0, 0},
        {0, 2, 0, 0, 0, 0,  0, 0, 2},
        {0, 0, 0, 0, 0, 2,  0, 2, 0},
    };

    int longeurs_mod[SIZE][SIZE] = {//supprimer la station 6

        {0, 3, 3, 0, 0, 0,  0, 0, 0},
        {3, 0, 0, 4, 4, 0,  0, 2, 0},
        {0, 0, 0, 0, 0, 0,  0, 0, 0},
        {0, 4, 0, 0, 0, 0, 10, 0, 0},
        {0, 4, 0, 0, 0, 0,  4, 0, 0},
        {0, 0, 0, 0, 0, 0,  0, 0, 0},
        {0, 0, 0,10, 4, 0,  0, 0, 0},
        {0, 2, 0, 0, 0, 0,  0, 0, 2},
        {0, 0, 0, 0, 0, 0,  0, 2, 0},


    };

    int* correspondances = NULL;
    unsigned int capacity = 100;
    station* station_1 = create_station(1, "1", correspondances, capacity);
    station* station_2 = create_station(2, "2", correspondances, capacity);
    station* station_3 = create_station(3, "3", correspondances, capacity);
    station* station_4 = create_station(4, "4", correspondances, capacity);
    station* station_5 = create_station(5, "5", correspondances, capacity);
    station* station_6 = create_station(6, "6", correspondances, capacity);
    station* station_7 = create_station(7, "7", correspondances, capacity);
    station* station_8 = create_station(8, "8", correspondances, capacity);
    station* station_9 = create_station(9, "9", correspondances, capacity);


    int montee_1[NB_STATIONS_METRO] = {0, 88, 6, 12,21, 19, 9,30 ,20};
    int montee_2[NB_STATIONS_METRO] = { 0, 0, 0, 12, 21, 19,9,30, 20 };
    int montee_3[NB_STATIONS_METRO] = { 0, 0, 0, 0, 0, 0, 0 };
    int montee_4[NB_STATIONS_METRO] = { 0, 0, 0, 0, 0, 0, 3, 0,0 };
    int montee_5[NB_STATIONS_METRO] = { 0, 0, 0, 0, 0, 4, 2, 0,0 };
    int montee_6[NB_STATIONS_METRO] = { 0, 0, 0, 0, 0, 0, 4, 0,0 };
    int montee_7[NB_STATIONS_METRO] = { 0, 0, 0, 0, 0, 0, 0, 0,0 };
    int montee_8[NB_STATIONS_METRO] = { 0, 0, 0, 0, 0, 15, 4, 0, 20 };
    int montee_9[NB_STATIONS_METRO] = { 0, 0, 0, 0, 0, 19, 4, 0, 0 };


   
    
    station_1->montee = montee_1;
    station_2->montee = montee_2;
    station_3->montee = montee_3;
    station_4->montee = montee_4;
    station_5->montee = montee_5;
    station_8->montee = montee_6;
    station_9->montee = montee_7;
    station_6->montee = montee_8;
    station_7->montee = montee_9;


   

    station stations[9] = { *station_1,*station_2,*station_3,*station_4,*station_5,*station_6,*station_7,*station_8,*station_9 };

   
    rame* rames = NULL;
    graphe* g = create_graph(stations, rames, longueurs);

    station *from = station_1;
    station *to = station_7;
    station* affected_station = station_6;
  
    

    reroute(g, from, to, affected_station);
    

    for (int i = 0; i < NB_STATIONS_METRO; i++) {
        printf("[");
        for (int j = 0; j < NB_STATIONS_METRO; j++) {

            printf("%d,", (g->stations[i]).montee[j]);

        }
        printf("]\n");


    }
 
    
    /*

    int src = 1;
    int dest = 3;


    int pathLength;
   
    int* path = dijkstra(longueurs, src, dest, &pathLength);

    printf("Shortest Path from %d to %d: ", src, dest);
    for (int i = 0; i < pathLength; i++)
    {
        printf("%d ", path[i]);
    }
    printf("\n");

    free(path);


    int pathCount;
    Path* allPaths = findAllPathsWrapper(longueurs, src, dest, &pathCount);

    printf("All Paths from %d to %d:\n", src, dest);
    for (int i = 0; i < pathCount; i++)
    {
        for (int j = 0; j < allPaths[i].length; j++)
        {
            printf("%d ", allPaths[i].nodes[j]);
        }
        printf("\n");
    }

    printf("\nTotal Paths: %d\n", pathCount);
    

    */


    return;
}
