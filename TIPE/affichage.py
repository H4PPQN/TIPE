import pygame
import json
import os
import time
from math import sqrt

# Définition des couleurs
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE =(0, 0, 255)

couleur = [RED, GREEN, BLUE]

pygame.init()
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600

# Récupération de l'heure de modification du fichier
last_modif = os.path.getmtime("reseau.json")

def load_data():
    # Chargement du fichier JSON
    f = open("reseau.json")
    data = json.load(f)
    return data

data = load_data()

# Création de la fenêtre
screen = pygame.display.set_mode([SCREEN_WIDTH, SCREEN_HEIGHT])
pygame.display.set_caption("Réseau de transport")

done = False

while not done:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True

    # Effacement de l'écran
    screen.fill(WHITE)

    # Rechargement des données si le fichier a été modifié
    if os.path.getmtime("reseau.json") > last_modif:
        time.sleep(0.1)
        data = load_data()
        last_modif = os.path.getmtime("reseau.json")

    # Affichage des lignes
    for i, ligne in enumerate(data["lignes"]):
        for k in range(len(ligne["stations"]) - 1):
            pygame.draw.line(screen, couleur[i], data["stations"][ligne["stations"][k]]["position"], data["stations"][ligne["stations"][k+1]]["position"], 5)

    # Affichage des stations
    for station in data["stations"]:
        gradient = station["current_people"]/station["capacity"]
        pygame.draw.circle(screen, (255*gradient, 255-255*gradient, 0), [station["position"][0], station["position"][1]], 10)

    # Affichage des rames
    for rame in data["rames"]:
        id_depart = rame["depart"]
        depart = data["stations"][id_depart]

        id_ligne = rame["ligne"]
        ligne = data["lignes"][id_ligne]

        tab_stations = data["lignes"][id_ligne]["stations"]

        id_arrivee = tab_stations[tab_stations.index(id_depart) + 1]
        arrivee = data["stations"][id_arrivee]

        x =  depart["position"][0] + (arrivee["position"][0] - depart["position"][0]) * rame["position"]/data["adjacences"][id_depart][id_arrivee]

        y =  depart["position"][1] + (arrivee["position"][1] - depart["position"][1]) * rame["position"]/data["adjacences"][id_depart][id_arrivee]

        pygame.draw.rect(screen, (0,0,0), pygame.Rect(x, y-5, 15, 10))

    pygame.display.flip()

# Fermeture de la fenêtre pygame
pygame.quit()