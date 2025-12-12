#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include "direction.h"
#include "case.h"
#include "ville.h"

int init_suite_success(void) { 
  return 0; 
}

int clean_suite_success(void) { 
  return 0; 
}

/* Tests de TAD Direction*/

void test_Direction_opposee(void) {
    CU_ASSERT_EQUAL(directionOpposee(NORD), SUD);
    CU_ASSERT_EQUAL(directionOpposee(SUD), NORD);
    CU_ASSERT_EQUAL(directionOpposee(EST), OUEST);
    CU_ASSERT_EQUAL(directionOpposee(OUEST), EST);
}

/*Tests du TAD C_Case */

void test_Case_creation_valeurs_defaut(void) {
    C_Case c = C_creerCase(10, false);
    
    CU_ASSERT_EQUAL(C_obtenirNumeroCase(c), 10);
    CU_ASSERT_FALSE(C_estObligatoire(c));
    //Ici on vérifie que tous les voisins sont bien initialisés à 0
    CU_ASSERT_EQUAL(C_obtenirVoisin(c, NORD), 0);
    CU_ASSERT_EQUAL(C_obtenirVoisin(c, SUD), 0);
    CU_ASSERT_EQUAL(C_obtenirVoisin(c, EST), 0);
    CU_ASSERT_EQUAL(C_obtenirVoisin(c, OUEST), 0);
}

void test_Case_modification_obligatoire(void) {
    C_Case c = C_creerCase(1, false);
    C_fixerObligatoire(&c, true);
    CU_ASSERT_TRUE(C_estObligatoire(c));
    
    C_fixerObligatoire(&c, false);
    CU_ASSERT_FALSE(C_estObligatoire(c));
}

void test_Case_adjacence(void) {
    C_Case c = C_creerCase(5, false);
    // On relie la case 5 avec la 8 au NORD
    C_fixerCaseAdj(&c, NORD, 8);

    CU_ASSERT_EQUAL(C_obtenirVoisin(c, NORD), 8);
    // Les autres directions doivent restées sans voisins donc 0
    CU_ASSERT_EQUAL(C_obtenirVoisin(c, SUD), 0); 
    CU_ASSERT_EQUAL(C_obtenirVoisin(c, EST), 0);
    CU_ASSERT_EQUAL(C_obtenirVoisin(c, OUEST), 0);
}

/* Tests de V_Ville*/

void test_Ville_creation(void) {
    unsigned int largeur = 3;
    V_Ville* v = V_creerVille(largeur);
    
    CU_ASSERT_PTR_NOT_NULL(v);
    CU_ASSERT_EQUAL(V_obtenirLargeur(v), largeur);
    CU_ASSERT_EQUAL(V_obtenirNbCases(v), largeur * largeur);
    
    /* Vérification de l'initialisation par défaut définie dans ville.c */
    CU_ASSERT_EQUAL(V_obtenirNumCaseDepart(v), 1);
    CU_ASSERT_EQUAL(V_obtenirDirDepart(v), NORD);
    
    V_liberer(v);
}

void test_Ville_acces_cases(void) {
    V_Ville* v = V_creerVille(3); // on crée 3x3 cases 
    C_Case* c1 = V_obtenirCase(v, 1);
    CU_ASSERT_PTR_NOT_NULL(c1);
    CU_ASSERT_EQUAL(C_obtenirNumeroCase(*c1), 1);
    
    C_Case* c9 = V_obtenirCase(v, 9);
    CU_ASSERT_PTR_NOT_NULL(c9);
    CU_ASSERT_EQUAL(C_obtenirNumeroCase(*c9), 9);
    
    V_liberer(v);
}

void test_Ville_fixer_depart(void) {
    V_Ville* v = V_creerVille(3);
    
    //Changement du départ avec la case 5 a l'EST
    V_fixerDepart(v, 5, EST);
    
    CU_ASSERT_EQUAL(V_obtenirNumCaseDepart(v), 5);
    CU_ASSERT_EQUAL(V_obtenirDirDepart(v), EST);
    
    V_liberer(v);
}

void test_Ville_compter_obligatoires(void) {
    V_Ville* v = V_creerVille(3);
    
    // Par défaut il n'y a pas de cases obligatoires a l'initilisation
    CU_ASSERT_EQUAL(V_nbCasesObligatoire(v), 0);
    
    // on rend les cases 1 et 2 obligatoires et on reteste
    C_Case* c1 = V_obtenirCase(v, 1);
    C_fixerObligatoire(c1, true);
    
    C_Case* c2 = V_obtenirCase(v, 2);
    C_fixerObligatoire(c2, true);
    
    CU_ASSERT_EQUAL(V_nbCasesObligatoire(v), 2);
    
    V_liberer(v);
}


int main(int argc, char** argv){
  CU_pSuite pSuiteDirection = NULL;
  CU_pSuite pSuiteCase = NULL;
  CU_pSuite pSuiteVille = NULL;

  /* initialisation du registre de tests */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* ajout de la suite sur Directions */
  pSuiteDirection = CU_add_suite("Tests TAD Direction", init_suite_success, clean_suite_success);
  if (NULL == pSuiteDirection) { 
    CU_cleanup_registry(); 
    return CU_get_error(); 
  }
  
  if ((NULL == CU_add_test(pSuiteDirection, "Direction Opposee", test_Direction_opposee)))
     { CU_cleanup_registry(); return CU_get_error(); }


  /* ajout de la suite sur C_Case */
  pSuiteCase = CU_add_suite("Tests de C_Case", init_suite_success, clean_suite_success);
  if (NULL == pSuiteCase) { 
    CU_cleanup_registry(); 
    return CU_get_error(); 
  }
  
  if (
      (NULL == CU_add_test(pSuiteCase, "Creation Case", test_Case_creation_valeurs_defaut)) ||
      (NULL == CU_add_test(pSuiteCase, "Modification Status Obligatoire", test_Case_modification_obligatoire)) ||
      (NULL == CU_add_test(pSuiteCase, "Gestion Adjacence", test_Case_adjacence))
     )
     { CU_cleanup_registry(); return CU_get_error(); }


  /* ajout de la suite sur V_Ville */
  pSuiteVille = CU_add_suite("Tests TAD Ville", init_suite_success, clean_suite_success);
  if (NULL == pSuiteVille) { 
    CU_cleanup_registry(); 
    return CU_get_error(); 
  }

  if (
      (NULL == CU_add_test(pSuiteVille, "Creation Ville", test_Ville_creation)) ||
      (NULL == CU_add_test(pSuiteVille, "Acces aux Cases grâce au numéro", test_Ville_acces_cases)) ||
      (NULL == CU_add_test(pSuiteVille, "Configuration case de départ", test_Ville_fixer_depart)) ||
      (NULL == CU_add_test(pSuiteVille, "Nombre de cases obligatoires", test_Ville_compter_obligatoires))
     )
     { CU_cleanup_registry(); return CU_get_error(); }

  
  /* Lancement des tests */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  printf("\n");
  CU_basic_show_failures(CU_get_failure_list());
  printf("\n\n");

  /* Nettoyage du registre */
  CU_cleanup_registry();
  return CU_get_error();
}