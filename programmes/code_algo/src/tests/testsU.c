/**
 * @file testsU.c
 * @brief Tests unitaires pour le projet de navigation urbaine.
 * * Ce fichier utilise la bibliothèque CUnit pour valider le comportement des TAD 
 * Direction, Case, Ville et Chemin.
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include "direction.h"
#include "case.h"
#include "ville.h"
#include "chemin.h"

/** @brief Initialisation de la suite de tests (ne fait rien ici). */
int init_suite_success() { 
  return 0; 
}

/** @brief Nettoyage après la suite de tests (ne fait rien ici). */
int clean_suite_success() { 
  return 0; 
}

/* --- Tests de TAD Direction --- */

/** @brief Vérifie que l'inversion des points cardinaux fonctionne (ex: NORD -> SUD). */
void test_Direction_opposee() {
    CU_ASSERT_EQUAL(directionOpposee(NORD), SUD);
    CU_ASSERT_EQUAL(directionOpposee(SUD), NORD);
    CU_ASSERT_EQUAL(directionOpposee(EST), OUEST);
    CU_ASSERT_EQUAL(directionOpposee(OUEST), EST);
}

/* --- Tests du TAD C_Case --- */

/** @brief Vérifie qu'une case neuve possède bien son numéro et aucun voisin. */
void test_Case_creation_valeurs_defaut() {
    C_Case c = C_creerCase(10, false);
    
    CU_ASSERT_EQUAL(C_obtenirNumeroCase(c), 10);
    CU_ASSERT_FALSE(C_estObligatoire(c));
    CU_ASSERT_EQUAL(C_obtenirVoisin(c, NORD), 0);
    CU_ASSERT_EQUAL(C_obtenirVoisin(c, SUD), 0);
    CU_ASSERT_EQUAL(C_obtenirVoisin(c, EST), 0);
    CU_ASSERT_EQUAL(C_obtenirVoisin(c, OUEST), 0);
}

/** @brief Vérifie le changement d'état "obligatoire" d'une case. */
void test_Case_modification_obligatoire() {
    C_Case c = C_creerCase(1, false);
    C_fixerObligatoire(&c, true);
    CU_ASSERT_TRUE(C_estObligatoire(c));
    
    C_fixerObligatoire(&c, false);
    CU_ASSERT_FALSE(C_estObligatoire(c));
}

/** @brief Vérifie qu'on peut lier une case à une autre via une direction. */
void test_Case_adjacence() {
    C_Case c = C_creerCase(5, false);
    C_fixerCaseAdj(&c, NORD, 8);

    CU_ASSERT_EQUAL(C_obtenirVoisin(c, NORD), 8);
    CU_ASSERT_EQUAL(C_obtenirVoisin(c, SUD), 0); 
    CU_ASSERT_EQUAL(C_obtenirVoisin(c, EST), 0);
    CU_ASSERT_EQUAL(C_obtenirVoisin(c, OUEST), 0);
}

/* --- Tests de V_Ville --- */

/** @brief Vérifie l'allocation d'une ville et le calcul correct du nombre de cases. */
void test_Ville_creation() {
    unsigned int largeur = 3;
    V_Ville* v = V_creerVille(largeur);
    
    CU_ASSERT_PTR_NOT_NULL(v);
    CU_ASSERT_EQUAL(V_obtenirLargeur(v), largeur);
    CU_ASSERT_EQUAL(V_obtenirNbCases(v), largeur * largeur);
    
    CU_ASSERT_EQUAL(V_obtenirNumCaseDepart(v), 1);
    CU_ASSERT_EQUAL(V_obtenirDirDepart(v), NORD);
    
    V_liberer(v);
}

/** @brief Vérifie qu'on récupère bien la bonne case via son index. */
void test_Ville_acces_cases() {
    V_Ville* v = V_creerVille(3); 
    C_Case* c1 = V_obtenirCase(v, 1);
    CU_ASSERT_PTR_NOT_NULL(c1);
    CU_ASSERT_EQUAL(C_obtenirNumeroCase(*c1), 1);
    
    C_Case* c9 = V_obtenirCase(v, 9);
    CU_ASSERT_PTR_NOT_NULL(c9);
    CU_ASSERT_EQUAL(C_obtenirNumeroCase(*c9), 9);
    
    V_liberer(v);
}

/** @brief Vérifie la modification du point de départ du robot. */
void test_Ville_fixer_depart(void) {
    V_Ville* v = V_creerVille(3);
    V_fixerDepart(v, 5, EST);
    
    CU_ASSERT_EQUAL(V_obtenirNumCaseDepart(v), 5);
    CU_ASSERT_EQUAL(V_obtenirDirDepart(v), EST);
    
    V_liberer(v);
}

/** @brief Vérifie que le compteur de cases obligatoires fonctionne. */
void test_Ville_compter_obligatoires() {
    V_Ville* v = V_creerVille(3);
    CU_ASSERT_EQUAL(V_nbCasesObligatoire(v), 0);
    
    C_Case* c1 = V_obtenirCase(v, 1);
    C_fixerObligatoire(c1, true);
    
    C_Case* c2 = V_obtenirCase(v, 2);
    C_fixerObligatoire(c2, true);
    
    CU_ASSERT_EQUAL(V_nbCasesObligatoire(v), 2);
    
    V_liberer(v);
}

/* --- Tests du TAD CH_Chemin --- */

/** @brief Vérifie l'état initial d'un nouveau chemin vide. */
void test_Chemin_creation() {
    Ch_Chemin *c = Ch_creerChemin();

    CU_ASSERT_PTR_NOT_NULL(c);
    CU_ASSERT_EQUAL(Ch_nbrCases(c), 0);
    CU_ASSERT_EQUAL(Ch_obtenirDirDepart(c), NORD);

    Ch_liberer(c);
}

/** * @brief Scénario complexe : vérifie que l'algorithme trouve le chemin optimal.
 * Test sur une boucle 2x2 avec passage obligatoire par la case la plus éloignée.
 */
void test_Chemin_algo_boucle_carre() {
    V_Ville *v = V_creerVille(2);
    V_fixerDepart(v, 1, EST);

    C_Case *c1 = V_obtenirCase(v, 1);
    C_Case *c2 = V_obtenirCase(v, 2);
    C_Case *c3 = V_obtenirCase(v, 3);
    C_Case *c4 = V_obtenirCase(v, 4);

    C_fixerCaseAdj(c1, EST, 2);   // 1 -> 2
    C_fixerCaseAdj(c2, SUD, 4);   // 2 -> 4
    C_fixerCaseAdj(c4, OUEST, 3); // 4 -> 3
    C_fixerCaseAdj(c3, NORD, 1);  // 3 -> 1

    C_fixerObligatoire(c4, true);

    Ch_Chemin *resultat = Ch_genererCheminOptimal(v);

    CU_ASSERT_PTR_NOT_NULL(resultat);
    CU_ASSERT_EQUAL(Ch_nbrCases(resultat), 4);

    if (Ch_nbrCases(resultat) == 4) {
        CU_ASSERT_EQUAL(C_obtenirNumeroCase(*Ch_obtenirCaseAuChemin(resultat, 0)), 1);
        CU_ASSERT_EQUAL(C_obtenirNumeroCase(*Ch_obtenirCaseAuChemin(resultat, 1)), 2);
        CU_ASSERT_EQUAL(C_obtenirNumeroCase(*Ch_obtenirCaseAuChemin(resultat, 2)), 4);
        CU_ASSERT_EQUAL(C_obtenirNumeroCase(*Ch_obtenirCaseAuChemin(resultat, 3)), 3);
        CU_ASSERT_EQUAL(C_obtenirNumeroCase(*Ch_obtenirCaseAuChemin(resultat, 4)), 1);
    }

    Ch_liberer(resultat);
    V_liberer(v);
}

/** * @brief Point d'entrée principal des tests unitaires.
 * Initialise le registre, crée les suites, les lance et affiche les résultats.
 */
int main(){
  CU_pSuite pSuiteDirection = NULL;
  CU_pSuite pSuiteCase = NULL;
  CU_pSuite pSuiteVille = NULL;
  CU_pSuite pSuiteChemin = NULL; 

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* --- Configuration Suite Direction --- */
  pSuiteDirection = CU_add_suite("Tests TAD Direction", init_suite_success, clean_suite_success);
  if (NULL == pSuiteDirection) { CU_cleanup_registry(); return CU_get_error(); }
  if ((NULL == CU_add_test(pSuiteDirection, "Direction Opposee", test_Direction_opposee)))
     { CU_cleanup_registry(); return CU_get_error(); }

  /* --- Configuration Suite Case --- */
  pSuiteCase = CU_add_suite("Tests de C_Case", init_suite_success, clean_suite_success);
  if (NULL == pSuiteCase) { CU_cleanup_registry(); return CU_get_error(); }
  if (
      (NULL == CU_add_test(pSuiteCase, "Creation Case", test_Case_creation_valeurs_defaut)) ||
      (NULL == CU_add_test(pSuiteCase, "Modification Status Obligatoire", test_Case_modification_obligatoire)) ||
      (NULL == CU_add_test(pSuiteCase, "Gestion Adjacence", test_Case_adjacence))
     ) { CU_cleanup_registry(); return CU_get_error(); }

  /* --- Configuration Suite Ville --- */
  pSuiteVille = CU_add_suite("Tests TAD Ville", init_suite_success, clean_suite_success);
  if (NULL == pSuiteVille) { CU_cleanup_registry(); return CU_get_error(); }
  if (
      (NULL == CU_add_test(pSuiteVille, "Creation Ville", test_Ville_creation)) ||
      (NULL == CU_add_test(pSuiteVille, "Acces aux Cases", test_Ville_acces_cases)) ||
      (NULL == CU_add_test(pSuiteVille, "Configuration depart", test_Ville_fixer_depart)) ||
      (NULL == CU_add_test(pSuiteVille, "Compte cases obligatoires", test_Ville_compter_obligatoires))
     ) { CU_cleanup_registry(); return CU_get_error(); }

  /* --- Configuration Suite Chemin --- */
  pSuiteChemin = CU_add_suite("Tests TAD Chemin", init_suite_success, clean_suite_success);
  if (NULL == pSuiteChemin) { CU_cleanup_registry(); return CU_get_error(); }
  if (
      (NULL == CU_add_test(pSuiteChemin, "Creation Chemin Vide", test_Chemin_creation)) ||
      (NULL == CU_add_test(pSuiteChemin, "Algo Force Brute (Scenario Simple)", test_Chemin_algo_boucle_carre))
     ) { CU_cleanup_registry(); return CU_get_error(); }
  
  /* Lancement et affichage */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  
  printf("\n");
  CU_basic_show_failures(CU_get_failure_list());
  printf("\n\n");

  CU_cleanup_registry();
  return CU_get_error();
}
