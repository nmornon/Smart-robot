#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* INCLUDES DU PROJET */
#include "case.h"
#include "direction.h"
#include "ville.h"
#include "chemin.h"


/* TESTS CAS */


void test_case_creation(void)
{
    C_Case c = C_creerCase(5, false);

    assert(C_obtenirNumeroCase(c) == 5);
    assert(C_estObligatoire(c) == false);

    for (int d = 0; d < 4; d++) {
        assert(C_obtenirVoisin(c, (Direction)d) == 0);
    }

    printf("test_case_creation OK\n");
}

void test_case_obligatoire(void)
{
    C_Case c = C_creerCase(1, false);
    C_fixerObligatoire(&c, true);

    assert(C_estObligatoire(c) == true);

    printf("test_case_obligatoire OK\n");
}

void test_case_voisins(void)
{
    C_Case c = C_creerCase(1, false);

    C_fixerCaseAdj(&c, NORD, 2);
    C_fixerCaseAdj(&c, EST, 3);

    assert(C_obtenirVoisin(c, NORD) == 2);
    assert(C_obtenirVoisin(c, EST) == 3);
    assert(C_obtenirVoisin(c, SUD) == 0);

    printf("test_case_voisins OK\n");
}


/* TESTS DIRECTION*/


void test_directionOpposee(void)
{
    assert(directionOpposee(NORD) == SUD);
    assert(directionOpposee(SUD) == NORD);
    assert(directionOpposee(EST) == OUEST);
    assert(directionOpposee(OUEST) == EST);

    printf("test_directionOpposee OK\n");
}


/* TESTS VILLE */


void test_ville_creation(void)
{
    V_Ville *v = V_creerVille(3);

    assert(v != NULL);
    assert(V_obtenirLargeur(v) == 3);
    assert(V_obtenirNbCases(v) == 9);

    V_liberer(v);
    printf("test_ville_creation OK\n");
}

void test_ville_cases(void)
{
    V_Ville *v = V_creerVille(2); /* 4 cases */

    C_Case *c1 = V_obtenirCase(v, 1);
    C_Case *c4 = V_obtenirCase(v, 4);

    assert(c1 != NULL);
    assert(c4 != NULL);
    assert(C_obtenirNumeroCase(*c1) == 1);
    assert(C_obtenirNumeroCase(*c4) == 4);

    V_liberer(v);
    printf("test_ville_cases OK\n");
}

void test_ville_depart(void)
{
    V_Ville *v = V_creerVille(2);

    V_fixerDepart(v, 3, OUEST);

    assert(V_obtenirNumCaseDepart(v) == 3);
    assert(V_obtenirDirDepart(v) == OUEST);

    V_liberer(v);
    printf("test_ville_depart OK\n");
}

void test_ville_cases_obligatoires(void)
{
    V_Ville *v = V_creerVille(2);

    C_fixerObligatoire(V_obtenirCase(v, 1), true);
    C_fixerObligatoire(V_obtenirCase(v, 4), true);

    assert(V_nbCasesObligatoire(v) == 2);

    V_liberer(v);
    printf("test_ville_cases_obligatoires OK\n");
}


/* TESTS CHEMIN */


void test_chemin_basique(void)
{
    Ch_Chemin *c = Ch_creerChemin();

    assert(c != NULL);
    assert(Ch_nbrCases(c) == 0);
    assert(Ch_obtenirDirDepart(c) == NORD);

    Ch_liberer(c);
    printf("test_chemin_basique OK\n");
}

void test_chemin_acces_cases(void)
{
    Ch_Chemin *c = Ch_creerChemin();

    c->nb_cases = 2;
    c->tab_cases = malloc(3 * sizeof(C_Case));

    c->tab_cases[0] = C_creerCase(1, false);
    c->tab_cases[1] = C_creerCase(2, false);
    c->tab_cases[2] = C_creerCase(3, false);

    assert(Ch_obtenirCaseAuChemin(c, 0)->numero_case == 1);
    assert(Ch_obtenirCaseAuChemin(c, 2)->numero_case == 3);
    assert(Ch_obtenirCaseAuChemin(c, 5) == NULL);

    Ch_liberer(c);
    printf("test_chemin_acces_cases OK\n");
}


/*MAIN */


int main(void)
{
    printf("  LANCEMENT DES TESTS UNITAIRES\n");
   

    /* CASE */
    test_case_creation();
    test_case_obligatoire();
    test_case_voisins();

    /* DIRECTION */
    test_directionOpposee();

    /* VILLE */
    test_ville_creation();
    test_ville_cases();
    test_ville_depart();
    test_ville_cases_obligatoires();

    /* CHEMIN */
    test_chemin_basique();
    test_chemin_acces_cases();

    printf("  ✅ TOUS LES TESTS ONT RÉUSSI\n");

    return 0;
}
