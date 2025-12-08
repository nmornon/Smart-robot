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

// ------------------- CAPTEURS HAUT (3 capteurs) -------------------
#define CAPTEUR_HG 17   // Haut Gauche
#define CAPTEUR_HM 27   // Haut Milieu
#define CAPTEUR_HD 22   // Haut Droite

// ------------------- CAPTEURS BAS LATERAUX (2 capteurs) -------------------
#define CAPTEUR_BG 24   // Bas Gauche
#define CAPTEUR_BD 26   // Bas Droite


// ------------------- SETUP -------------------
void setup() {

    wiringPiSetupGpio();

    pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT);
    pinMode(IN3,OUTPUT);
    pinMode(IN4,OUTPUT);

    pinMode(EN1,PWM_OUTPUT);
    pinMode(EN2,PWM_OUTPUT);

    // Capteurs haut
    pinMode(CAPTEUR_HG, INPUT);
    pinMode(CAPTEUR_HM, INPUT);
    pinMode(CAPTEUR_HD, INPUT);

    // Capteurs bas
    pinMode(CAPTEUR_BG, INPUT); 
    pinMode(CAPTEUR_BD, INPUT);
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

    // Capteurs haut
    int HG = digitalRead(CAPTEUR_HG);
    int HM = digitalRead(CAPTEUR_HM);
    int HD = digitalRead(CAPTEUR_HD);

    // Capteurs bas
    int BG = digitalRead(CAPTEUR_BG);
    int BD = digitalRead(CAPTEUR_BD);

    int slow = 50;
    int normal = 100;


    // -------------------------------------------------
    // 1) PERTE TOTALE (aucun capteur ne voit la ligne)
    // -------------------------------------------------
    if (!HG && !HM && !HD && !BG && !BD) {
        Arret();
        return;
           // -------------------------------------------------
    // 2) DECISIONS PRINCIPALES (capteurs BAS)
    // -------------------------------------------------

    // tourner à gauche
    }else if(BG == 1 && BD == 0) {
        setSpeed(slow);
        Gauche();
        delay(120);
        setSpeed(normal);
        return;
          // tourner à droite
    }else if(BD == 1 && BG == 0) {
        setSpeed(slow);
        Droite();
        delay(120);
        setSpeed(normal);
        return;
    }


 


  
   


    // -------------------------------------------------
    // 3) CORRECTIONS FINES (capteurs du HAUT)
    // -------------------------------------------------

    // robot dévie à gauche → corriger à droite
   else if (HG == 1 && HD == 0) {
        setSpeed(slow);
        Droite();
        delay(50);
        setSpeed(normal);
        Avance();
        return;
    }

    // robot dévie à droite → corriger à gauche
   else if (HD == 1 && HG == 0) {
        setSpeed(slow);
        Gauche();
        delay(50);
        setSpeed(normal);
        Avance();
        return;
    }

    // ligne détectée au milieu = tout droit
   else if (HM == 1) {
        Avance();
        return;
    }

    // -------------------------------------------------
    // 4) PAR DÉFAUT : AVANCER
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
