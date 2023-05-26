#define NB_STATIONS_METRO 305
#define NB_LIGNES_METRO 14
#define NB_RAMES_METRO 20
#define UPDATE_INTERV 0.5

typedef struct Station
{
	int id;
	char nom[50];
	int* correspondances[NB_LIGNES_METRO];   //Tableau des ids des lignes accessibles depuis la station
	unsigned int capacity;                   //Nombre de personne maximum pouvant se trouver dans la station sans risques
	unsigned int current_people;             //Nombre de personnes pr�sentes actuellement dans la station
	unsigned int in;
	int *destinations[NB_STATIONS_METRO];   //Nombre de personnes sortants de la sation � chaque actualisation
} station;

typedef struct Ligne
{
	int id;
	char nom[50];
	int* tab_station[NB_STATIONS_METRO];    //Tableau des ids des stations pr�sentes sur la ligne dans l'ordre
} ligne;

typedef struct Rame
{
	int id;
	int* depart;                         //Station de d�part du tron�on actuel
	int* arrivee;                        //Station d'arriv�e du tron�on actuel
	int localisation;                        //Portion du tron�on parcouru (nombre d'actualisation depuis que la rame est sur le tron�on)
	int current_people;
	int *destinations[NB_STATIONS_METRO];
} rame;

typedef struct Graphe
{
	station* stations[NB_STATIONS_METRO];    //Tableau de toutes les stations
	ligne* lignes[NB_LIGNES_METRO];          //Tableau de toutes les lignes
	rame* rames[NB_RAMES_METRO];             //Tableau de toutes les rames
	int longueur[NB_STATIONS_METRO][NB_STATIONS_METRO];
	int vitesse[NB_STATIONS_METRO][NB_STATIONS_METRO];
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

//fonctions d'affichage
void afficher_rames(graphe* g);
void afficher_graphe(graphe* g);
