
#define NB_STATIONS_METRO 305
#define NB_LIGNES_METRO 14
#define NB_RAMES_METRO 20
#define UPDATE_INTERV 0.5
#define Fick_const 10
#define omega 5

typedef struct Station
{
	int id;
	char *nom;

	int* correspondances;   //Tableau des ids des lignes accessibles depuis la station 
	unsigned int capacity;                   //Nombre de personne maximum pouvant se trouver dans la station sans risques
	unsigned int current_people;             //Nombre de personnes pr�sentes actuellement dans la station
	unsigned int in;
	int *montee;   /* (taille  : [NB_STATIONS_METRO])Nombre de personnes souhaitant aller a chaque station->montee[0, 0, 0, 30, 16, 4, 3, 0, ..., 0] exemple tableau station 2
										(30 personnes souhaitent descendre a la stat 3 ou plus loins,...,4 personnes souhaitent descendre a la stat 5 ou plus loins)*/
} station;

typedef struct Ligne
{
	int id;
	char nom[50];
	int nb_stations;
	int* tab_station[NB_STATIONS_METRO];    //Tableau des ids des stations pr�sentes sur la ligne dans l'ordre
} ligne;

typedef struct Rame
{
	int id;
	int depart;                         //Station de d�part du tron�on actuel
	int arrivee;                        //Station d'arriv�e du tron�on actuel
	double localisation;                        //Portion du tron�on parcouru (nombre d'actualisation depuis que la rame est sur le tron�on)
	//double vitesse;
	int current_people;
	int *destinations; //(taille: [NB_STATIONS_METRO])nombre des gens et leur destination en fonction de la ligne
} rame;

typedef struct Graphe
{
	station* stations;    //(taille: [NB_STATIONS_METRO])Tableau de toutes les stations
	/*ligne* lignes[NB_LIGNES_METRO]; */         //Tableau de toutes les lignes
	rame* rames;             //(taille : [NB_RAMES_METRO])Tableau de toutes les rames
	int** longueurs;							//taille : [NB_STATIONS_METRO][NB_STATIONS_METRO]
	double **vitesse;					    	//taille : [NB_STATIONS_METRO][NB_STATIONS_METRO]
} graphe;

//constructeurs
station* station_create(int id, char* nom, int*correspondance,unsigned int capacity);
ligne* creer_ligne(int id, char* nom);
rame* create_rame(int id);
graphe* create_graph();

//fonction pour faire �voluer le graphe dans le temps
void update_station(graphe* g);
void update_rame(graphe* g);
void maj(graphe* g);


void ajouter_station(graphe* g, station* s);                                                        //ajoute une station au graphe
void ajouter_ligne(graphe* g, ligne* l);                                                            //ajoute une ligne au graphe
void ajouter_rame(graphe* g, rame* r);                                                              //ajoute une rame au graphe
void ajouter_connection(graphe* g, station* station_1, station* station_2, ligne* l, int temps);    //ajouter une connexion dans la matrice d'adjacence entre deux station sur une ligne particuli�re

//fonctions d'affichage
void afficher_rames(graphe* g);
void afficher_graphe(graphe* g);
