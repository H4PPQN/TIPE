#define NB_STATIONS_METRO 305
#define NB_LIGNES_METRO 14
#define NB_RAMES_METRO 20

typedef struct Ligne ligne;

typedef struct Station
{
	int id;
	char nom[50];
	ligne* correspondances[NB_LIGNES_METRO]; //Tableau des lignes accessibles depuis la station
	unsigned int capacity;                   //Nombre de personne maximum pouvant se trouver dans la station sans risques
	unsigned int current_people;             //Nombre de personnes présentes actuellement dans la station
	unsigned int in;                         //Nombre de personnes entrant dans la station à chaque actualisation
	unsigned int out;                        //Nombre de personnes sortants de la sation à chaque actualisation
} station;

typedef struct Ligne
{
	int id;
	char nom[50];
	station* tab_station[NB_STATIONS_METRO]; //Tableau des stations présentes sur la ligne
} ligne;

typedef struct Rame
{
	int id;
	station* depart;                         //Station de départ du tronçon actuel
	station* arrivee;                        //Station d'arrivée du tronçon actuel
	int localisation;                        //Portion du tronçon parcouru (nombre d'actualisation depuis que la rame est sur le tronçon)
} rame;

typedef struct Graphe
{
	station* stations[NB_STATIONS_METRO];    //Tableau de toutes les stations
	ligne* lignes[NB_LIGNES_METRO];          //Tableau de toutes les lignes
	rame* rames[NB_RAMES_METRO];             //Tableau de toutes les rames
	int adjacences[NB_STATIONS_METRO][NB_STATIONS_METRO]; //Matrices d'ajacence du graphe pondéré par le temps entre deux stations directement voisine
} graphe;

//constructeurs
station* creer_station(int id, char* nom);
ligne* creer_ligne(int id, char* nom);
rame* creer_rame(int id);
graphe* creer_graphe_vide();

//fonction pour faire évoluer le graphe dans le temps
void maj_station(graphe* g);
void maj_rame(graphe* g);
void maj(graphe* g);


void ajouter_station(graphe* g, station* s);                                                        //ajoute une station au graphe
void ajouter_ligne(graphe* g, ligne* l);                                                            //ajoute une ligne au graphe
void ajouter_rame(graphe* g, rame* r);                                                              //ajoute une rame au graphe
void ajouter_connection(graphe* g, station* station_1, station* station_2, ligne* l, int temps);    //ajouter une connexion dans la matrice d'adjacence entre deux station sur une ligne particulière

//fonctions d'affichage
void afficher_rames(graphe* g);
void afficher_graphe(graphe* g);
