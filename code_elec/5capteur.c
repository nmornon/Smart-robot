#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <softPwm.h>

// ------------------- MOTEURS -------------------
#define IN1 6  
#define IN2 5  
#define IN3 4   
#define IN4 18    
#define EN1 12  
#define EN2 13    

// ------------------- CAPTEURS BAS (déjà existants) -------------------
#define CAPTEUR_BG 24   // Bas Gauche
#define CAPTEUR_BM 25   // Bas Milieu
#define CAPTEUR_BD 26   // Bas Droite

// ------------------- CAPTEURS HAUT (NOUVEAUX) -------------------
#define CAPTEUR_HG 17   // Haut Gauche
#define CAPTEUR_HM 27   // Haut Milieu
#define CAPTEUR_HD 22   // Haut Droite


// ------------------- SETUP -------------------
void setup() {

    wiringPiSetupGpio();

    pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT);
    pinMode(IN3,OUTPUT);
    pinMode(IN4,OUTPUT);

    pinMode(EN1,PWM_OUTPUT);
    pinMode(EN2,PWM_OUTPUT);

    // Capteurs bas
    pinMode(CAPTEUR_BG, INPUT); 
    pinMode(CAPTEUR_BM, INPUT);
    pinMode(CAPTEUR_BD, INPUT);

    // Capteurs haut
    pinMode(CAPTEUR_HG, INPUT);
    pinMode(CAPTEUR_HM, INPUT);
    pinMode(CAPTEUR_HD, INPUT);
}


// ------------------- PWM SPEED -------------------
void setSpeed(int speed) {  
    speed = speed * 1024 / 100;
    pwmWrite(EN1, speed);
    pwmWrite(EN2, speed);
}


// ------------------- MOUVEMENTS -------------------
void Gauche() {
    digitalWrite(IN1,1);
    digitalWrite(IN2,0);
    digitalWrite(IN3,1);
    digitalWrite(IN4,0);
    printf("Gauche\n");
}

void Droite() {
    digitalWrite(IN1,0);
    digitalWrite(IN2,1);
    digitalWrite(IN3,0);
    digitalWrite(IN4,1);
    printf("Droite\n");
}

void Avance() {
    digitalWrite(IN1,0);
    digitalWrite(IN2,1);
    digitalWrite(IN3,1);
    digitalWrite(IN4,0);
    printf("Avance\n");
}

void Arret() {
    digitalWrite(IN1,0);
    digitalWrite(IN2,0);
    digitalWrite(IN3,0);
    digitalWrite(IN4,0);
    printf("Stop\n");
}


// ------------------- LOGIQUE CAPTEURS -------------------
void capteur() {

    // Capteurs bas
    int BG = digitalRead(CAPTEUR_BG);
    int BM = digitalRead(CAPTEUR_BM);
    int BD = digitalRead(CAPTEUR_BD);

    // Capteurs haut
    int HG = digitalRead(CAPTEUR_HG);
    int HM = digitalRead(CAPTEUR_HM);
    int HD = digitalRead(CAPTEUR_HD);

    int slow = 50;
    int normal = 100;


    // -------------------------------------------------
    // 1) PERTE TOTALE (aucun capteur ne voit la ligne)
    // -------------------------------------------------
    if (!BG && !BM && !BD && !HG && !HM && !HD) {
        Arret();
        return;
    }


    // -------------------------------------------------
    // 2) DECISIONS PRINCIPALES (capteurs BAS)
    // -------------------------------------------------

    // tourner à gauche
    if (BG == 1 && BD == 0) {
        setSpeed(slow);
        Gauche();
        delay(120);
        setSpeed(normal);
        return;
    }

    // tourner à droite
    if (BD == 1 && BG == 0) {
        setSpeed(slow);
        Droite();
        delay(120);
        setSpeed(normal);
        return;
    }


    // -------------------------------------------------
    // 3) CORRECTIONS FINES (capteurs du haut)
    // -------------------------------------------------

    // Correction vers la droite
    if (HG == 1 && HD == 0) {
        setSpeed(slow);
        Droite();
        delay(50);
        setSpeed(normal);
        Avance();
        return;
    }

    // Correction vers la gauche
    if (HD == 1 && HG == 0) {
        setSpeed(slow);
        Gauche();
        delay(50);
        setSpeed(normal);
        Avance();
        return;
    }

    // Capteur haut milieu détecte → ligne droite
    if (HM == 1) {
        Avance();
        return;
    }

    // -------------------------------------------------
    // 4) AVANCER PAR DEFAUT
    // -------------------------------------------------
    Avance();
}



// ------------------- PROGRAMME PRINCIPAL -------------------
int main(int argc, char **argv) { 

    setup();

    while (1) {
        capteur();
    }

    return 0;
}
