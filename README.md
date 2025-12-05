# 🤖 PI SMART ROBOT

### Projet d'Intégration (PI) 2025-2026 - INSA Rouen

---

## Objectif du Projet

L'objectif principal de ce projet est la conception, la réalisation et la programmation d'un **robot mobile** capable de naviguer de manière autonome dans un environnement simulé (une ville composée de rues modélisées par des lignes noires).

Le robot doit :
1.  **Partir** d'un point initial (pastille verte).
2.  **Passer** par tous les points de passage obligatoires (pastilles bleues).
3.  **Revenir** à son point de départ.

Le critère de performance est le **temps le plus court** pour réaliser l'intégralité du trajet.

---

## Modélisation et Description de la Ville

La ville est modélisée par une grille de cases formant un carré.


Le problème est décrit à l'aide d'un **flux texte** structuré qui définit:
* La largeur $l$ de la ville en nombre de cases
* [cite_start]La case de départ et son orientation initiale (N, E, S, O)
* [cite_start]Les passages entre les cases (ex: `1-2`)
* [cite_start]Les numéros des cases contenant les points de passage obligatoires (pastilles bleues)

## Architecture Logicielle et Contrôle

L'exécution du projet repose sur une architecture en deux programmes communicants, orchestrés par un script `bash`[cite: 126, 127].

| Composant | Rôle | Description |
| :--- | :--- | :--- |
| **Script `bash`** | Orchestrateur | Lance les deux programmes, crée le pipeline de communication et affiche le temps d'exécution |
| **Programme 1** | Algorithme / Pathfinder | Lit la description de la ville et **produit sur sa sortie standard les ordres** que devra suivre le robot (séquence AV, TG, TD) |
| **Programme 2** | Contrôleur / Driver | **Lit les ordres depuis son entrée standard**, les interprète, et pilote les composants du robot (moteurs, capteurs) |

### Les Ordres de Contrôle 
Le robot est guidé à l'aide de trois ordres :
* `AV` : **Avancer** jusqu'au prochain croisement
* `TG` : **Tourner à Gauche** (n'avance pas)
* `TD` : **Tourner à Droite** (n'avance pas)

---

## Composants Matériels (Partie Électronique)

Le robot est équipé des composants suivants:
* **Contrôle/Alimentation :** Châssis, Contrôleur L293D, Raspberry Pi, Interrupteur on/off.
* **Déplacement :** 2 moteurs + roues + supports.
* **Capteurs :** 1 Capteur couleur, 3 Capteurs détecteurs de ligne.
* **Interface :** Buzzers, LED, Écran LCD (pour afficher les manœuvres en continu et les couleurs détectées en émettant un bip).
* **Batteries :** 1 batterie USB-C pour la Raspberry Pi, 2 batteries NIMH 3,7V + support.

---

## Utilisation et Démonstration

Le jour de la démonstration:
1.  **Transfert du Fichier :** Copier le fichier de description de la ville sur le robot
2.  **Connexion :** Se connecter en `SSH` sur le robot
3.  **Lancement :** Lancer le script `bash` en lui passant le nom du fichier de description en paramètre

```bash
# Exemple de lancement :
ssh pi@<adresse_ip_robot>
./run.sh mon_fichier_ville.txt