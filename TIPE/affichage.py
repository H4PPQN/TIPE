import pygame
import json
import os
import time
from math import sqrt

# Définition des couleurs
couleur = [(255, 206, 0), (0, 100, 176), (159, 152, 37), (152, 212, 226), (192, 65, 145), (242, 142, 66), (131, 196, 145),
           (243, 164, 186), (131, 196, 145), (206, 173, 210), (213, 201, 0), (227, 179, 42), (141, 94, 42), (0, 129, 79), 
           (52, 212, 226), (102, 36, 131)]
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

pygame.init()
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 800

file = "TIPE/reseau.json"
# Récupération de l'heure de modification du fichier
last_modif = os.path.getmtime(file)

def load_data():
    # Chargement du fichier JSON
    f = open(file)
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
    if os.path.getmtime(file) > last_modif:
        time.sleep(0.1)
        data = load_data()
        last_modif = os.path.getmtime(file)

    # Affichage des lignes
    for i, ligne in enumerate(data["lignes"]):
        for k in range(len(ligne["stations"]) - 1):
            pygame.draw.line(screen, couleur[i], data["stations"][ligne["stations"][k]]["position"], data["stations"][ligne["stations"][k+1]]["position"], 5)

    # Affichage des stations
    for station in data["stations"]:
        gradient = station["current_people"]/station["capacity"]
        pygame.draw.circle(screen, (255*gradient, 255-255*gradient, 0), [station["position"][0], station["position"][1]], 4)

    # Affichage des rames
    for rame in data["rames"]:
        id_depart = rame["depart"]
        depart = data["stations"][id_depart]

        id_arrivee = rame["arrivee"]
        arrivee = data["stations"][id_arrivee]

        id_ligne = rame["ligne"]
        ligne = data["lignes"][id_ligne]

        tab_stations = data["lignes"][id_ligne]["stations"]

        x =  depart["position"][0] + (arrivee["position"][0] - depart["position"][0]) * rame["localisation"]/data["graphe"]["longueur"][id_depart][id_arrivee]

        y =  depart["position"][1] + (arrivee["position"][1] - depart["position"][1]) * rame["localisation"]/data["graphe"]["longueur"][id_depart][id_arrivee]

        pygame.draw.rect(screen, (0,0,0), pygame.Rect(x, y, 5, 3.5))

    pygame.display.flip()

# Fermeture de la fenêtre pygame
pygame.quit()