#define NB_STATIONS_METRO 305
#define NB_LIGNES_METRO 14
#define NB_RAMES_METRO 20
#define UPDATE_INTERV 30

typedef struct Station
{
	int id;
	char nom[50];
	int *correspondances;  					//Tableau des ids des lignes accessibles depuis la station
	int capacity;                   		//Nombre de personne maximum pouvant se trouver dans la station sans risques
	int current_people;             		//Nombre de personnes pr�sentes actuellement dans la station
	int in;									//Nombre de personnes rentrant dans la stations à chaque actualisation
	int *destinations;   					//Tableau des destinations des personnes destination[i]: nombre de personne voulant aller à la stations i+1
} station;

typedef struct Ligne
{
	int id;
	char nom[10];
	int tab_stat_len;
	int *tab_station;    					//Tableau des ids des stations pr�sentes sur la ligne dans l'ordre de passage
} ligne;

typedef struct Rame
{
	int id;
	int ligne_id;
	int capacity;							//Capacité de la rame
	int depart;                           	//Id de la station de d�part
	int arrivee;							//Id de la station d'arrivée
	float localisation;                     //Portion du tron�on parcouru (nombre d'actualisation depuis que la rame est sur le tron�on)
	int current_people;						//nombre de personnes dans la rame
	int *distribution;						//Tableau des destinations des personnes dans la rame
} rame;

typedef struct Graphe
{
	station *stations[NB_STATIONS_METRO];    //Tableau de toutes les stations
	ligne *lignes[NB_LIGNES_METRO];          //Tableau de toutes les lignes
	rame *rames[NB_RAMES_METRO];             //Tableau de toutes les rames
	int longueur[NB_STATIONS_METRO][NB_STATIONS_METRO];
	float vitesse[NB_STATIONS_METRO][NB_STATIONS_METRO];
	int *next_station[NB_STATIONS_METRO][NB_STATIONS_METRO];
} graphe;

//constructeurs
station* creer_station(int id, char* nom);
ligne* creer_ligne(int id, char* nom);
rame* creer_rame(int id);
graphe* creer_graphe_vide();

//fonction pour faire �voluer le graphe dans le temps
void maj_station(graphe* g);
void maj_rame(graphe* g);
void maj(graphe* g);


void ajouter_station(graphe* g, station* s);                                                        //ajoute une station au graphe
void ajouter_ligne(graphe* g, ligne* l);                                                            //ajoute une ligne au graphe
void ajouter_rame(graphe* g, rame* r);                                                              //ajoute une rame au graphe
void ajouter_connection(graphe* g, station* station_1, station* station_2, ligne* l, int temps);    //ajouter une connexion dans la matrice d'adjacence entre deux station sur une ligne particuli�re

//fonctions de chargement et enregistrement
graphe *upload();
void register(graphe* g);