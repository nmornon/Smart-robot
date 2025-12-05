# 🤖 PI SMART ROBOT (IT13)

### [cite_start]Projet d'Intégration (PI) 2025-2026 - INSA Rouen [cite: 1, 10]

---

## [cite_start] Objectif du Projet [cite: 3]

[cite_start]L'objectif principal de ce projet est la conception, la réalisation et la programmation d'un **robot mobile** capable de naviguer de manière autonome dans un environnement simulé (une ville composée de rues modélisées par des lignes noires)[cite: 4, 5].

Le robot doit :
1.  [cite_start]**Partir** d'un point initial (pastille verte)[cite: 7].
2.  [cite_start]**Passer** par tous les points de passage obligatoires (pastilles bleues)[cite: 6].
3.  [cite_start]**Revenir** à son point de départ[cite: 4].

[cite_start]Le critère de performance est le **temps le plus court** pour réaliser l'intégralité du trajet[cite: 4, 171].

---

## Modélisation et Description de la Ville

[cite_start]La ville est modélisée par une grille de cases formant un carré[cite: 12].



[cite_start]Le problème est décrit à l'aide d'un **flux texte** structuré qui définit[cite: 28, 39]:
* [cite_start]La largeur $l$ de la ville en nombre de cases[cite: 29].
* [cite_start]La case de départ et son orientation initiale (N, E, S, O)[cite: 31, 32, 33, 34].
* [cite_start]Les passages entre les cases (ex: `1-2`)[cite: 35, 36].
* [cite_start]Les numéros des cases contenant les points de passage obligatoires (pastilles bleues)[cite: 37].

## Architecture Logicielle et Contrôle [cite: 126]

L'exécution du projet repose sur une architecture en deux programmes communicants, orchestrés par un script `bash`[cite: 126, 127].

| Composant | Rôle | Description |
| :--- | :--- | :--- |
| **Script `bash`** | Orchestrateur | Lance les deux programmes, crée le pipeline de communication et affiche le temps d'exécution[cite: 124, 128]. |
| **Programme 1** | Algorithme / Pathfinder | Lit la description de la ville et **produit sur sa sortie standard les ordres** que devra suivre le robot (séquence AV, TG, TD)[cite: 126]. |
| **Programme 2** | Contrôleur / Driver | **Lit les ordres depuis son entrée standard**, les interprète, et pilote les composants du robot (moteurs, capteurs)[cite: 127]. |

### Les Ordres de Contrôle [cite: 77]
Le robot est guidé à l'aide de trois ordres :
* `AV` : **Avancer** jusqu'au prochain croisement[cite: 78].
* `TG` : **Tourner à Gauche** (n'avance pas)[cite: 79].
* `TD` : **Tourner à Droite** (n'avance pas)[cite: 80].

---

## Composants Matériels (Partie Électronique)

Le robot sera équipé des composants suivants[cite: 108, 109, 110, 111, 112, 113, 114, 115]:
* **Contrôle/Alimentation :** Châssis, Contrôleur L293D, Raspberry Pi, Interrupteur on/off.
* **Déplacement :** 2 moteurs + roues + supports.
* **Capteurs :** 1 Capteur couleur, 3 Capteurs détecteurs de ligne.
* **Interface :** Buzzers, LED, Écran LCD (pour afficher les manœuvres en continu [cite: 117] et les couleurs détectées en émettant un bip [cite: 118]).
* **Batteries :** 1 batterie USB-C pour la Raspberry Pi, 2 batteries NIMH 3,7V + support.

Il est crucial de déterminer le **positionnement optimal** de ces composants pour assurer les meilleures performances[cite: 119].

---

## Utilisation et Démonstration

Le jour de la démonstration[cite: 121]:
1.  **Transfert du Fichier :** Copier le fichier de description de la ville sur le robot (utilisation de `scp`)[cite: 123].
2.  **Connexion :** Se connecter en `SSH` sur le robot[cite: 124].
3.  **Lancement :** Lancer le script `bash` en lui passant le nom du fichier de description en paramètre[cite: 124, 125].

```bash
# Exemple de lancement :
ssh pi@<adresse_ip_robot>
./run.sh mon_fichier_ville.txt