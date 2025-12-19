# 🤖 PI SMART ROBOT

### Projet Intégratif - Groupe 6 - 2025-2026 - INSA Rouen

![Image schema électrique](https://gitlab.insa-rouen.fr/pi-smartrobot/25-26-pi-smartrobot-26/-/raw/main/rapport/schema/shema_elec_16_12_2025.png)

---

## Objectif du Projet

L'objectif principal de ce projet est la conception, la réalisation et la programmation d'un **robot mobile** capable de naviguer de manière autonome dans un environnement simulé (une ville composée de rues modélisées par des lignes noires).

Le robot doit :
1.  **Partir** d'un point initial (pastille verte).
2.  **Passer** par tous les points de passage obligatoires (pastilles bleues).
3.  **Revenir** à son point de départ.

Le critère de performance est le **temps le plus court** pour réaliser l'intégralité du trajet.

---

## Structure du projet
```
25-26-PI-SMART-ROBOT/
├── programmes/
│   ├── code_algo/
│   │   ├── src/
│   │   │    ├── tests/
│   │   │    ├── chemin_force_brute/
│   │   │    ├── chemin_bfs/
│   │   │    └── .../
│   │   ├── include/
│   │   ├── bin/
│   │   ├── lib/
│   │   └── makefile
│   └──  code_elec/
│       ├── src/
│       ├── include/
│       ├── bin/
│       ├── doc/
│       ├── makefile
│       └── Doxyfile
├── rapport/
│       ├── analyse_descendente/
│       ├── schema/
│       ├── sections/
│       ├── images/
│       └── main.tex
├── pipeline.sh
└── README.md
```

## Modélisation et Description de la Ville

La ville est modélisée par une grille de cases formant un carré.


Le problème est décrit à l'aide d'un **flux texte structuré** qui définit:
* La largeur $l$ de la ville en nombre de cases
* La case de départ et son orientation initiale (N, E, S, O)
* Les passages entre les cases (ex: `1-2`)
* Les numéros des cases contenant les points de passage obligatoires (pastilles bleues)

## Architecture Logicielle et Contrôle

L'exécution du projet repose sur une architecture en deux programmes communicants, orchestrés par un script `bash`.

| Composant | Rôle | Description |
| :--- | :--- | :--- |
| **Script `bash`** | Orchestrateur | Lance les deux programmes, crée le pipeline de communication et affiche le temps d'exécution |
| **Programme 1** | Algorithme / Pathfinder | Lit la description de la ville et **produit sur sa sortie standard les ordres** que devra suivre le robot (séquence AV, TG, TD) |
| **Programme 2** | Contrôleur / Driver | **Lit les ordres depuis son entrée standard**, les interprète, et pilote les composants du robot (moteurs, capteurs) |

### Les Ordres de Contrôle 
Le robot est guidé à l'aide d'ordres tels que :
* `AV` : **Avancer** jusqu'au prochain croisement
* `TG` : **Tourner à Gauche**
* `TD` : **Tourner à Droite**

---

## Composants Matériels (Partie Électronique)

Le robot est équipé des composants suivants:
* **Contrôle/Alimentation :** Châssis, Contrôleur L293D, Raspberry Pi, Interrupteur on/off.
* **Déplacement :** 2 moteurs + roues + supports.
* **Capteurs :** 1 Capteur couleur, 3 Capteurs détecteurs de ligne.
* **Interface :** Buzzers, LED, Écran LCD (pour afficher les manœuvres en continu et les couleurs détectées en émettant un bip).
* **Batteries :** 1 batterie USB-C pour la Raspberry Pi 4, 2 batteries NIMH 3,7V + support.

---

## Utilisation et Démonstration

Le jour de la démonstration:
1.  **Connexion :** Se connecter en `SSH` sur le robot
2.  **Transfert du Fichier :** Copier le fichier de description de la ville sur le robot
3.  **Lancement :** Lancer le script `bash` en lui passant le nom du fichier de description en paramètre

```bash
# Exemple de lancement :
scp <fichier_ville> pi@<adresse_ip_robot>:<adresse_destination>
ssh pi@<adresse_ip_robot>
./pipeline.sh fichier_ville.txt
```

---

## Algorithme

Pour changer l'algorithme de résolution de la ville il suffit d'ouvrir le fichier `makefile` situé dans le dossier `./programmes/code_algo`.
La variable `algorithme` peut prendre les valeurs `chemin_bfs` ou `chemin_force_brute`.

---

## Tests unitaires et documentation des algorithmes

Pour accéder aux tests unitaires et à la documentation des algorithmes il faut se déplacer dans le dossier `./programmes/code_algo` et taper une des commandes suivantes au choix : 
```bash
make #Pour compiler normalement les algorithmes
make tests #Pour compiler les tests
make doc #Pour générer la doc
make clean #Pour supprimer l'excés
```
