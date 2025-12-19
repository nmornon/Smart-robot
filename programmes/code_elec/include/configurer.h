#ifndef CONFIGURER_H
#define CONFIGURER_H

#include <wiringPi.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>


#define PIN_CAPT_AV_D 22    // Capteur AVANT DROIT
#define PIN_CAPT_AV_G 20    // Capteur AVANT GAUCHE
#define PIN_CAPT_AV_M 19  // Capteur AVANT MILIEU
#define PIN_CAPT_AR_D 24    // Capteur ARRIERE DROIT
#define PIN_CAPT_AR_G 17    // Capteur ARRIERE GAUCHE

#define EN2 12        // PWM Vitesse moteur DROIT
#define EN1 13        // PWM Vitesse moteur GAUCHE

#define IN1 26             // Direction moteur gauche
#define IN2 21             // Direction moteur gauche
#define IN3 27              // Direction moteur droit
#define IN4 23               // Direction moteur droit

#define VITESSE 500         // Vitesse de base PWM (0-1023 car 2¹⁰=1024) 
#define DELTA_V 150         // Correction vitesse pour suivi ligne
#define TEMPS_TOURNER 200000    // A adpater car je me rends pas compte de comment il tourne

typedef enum{
        ARRET,
        AV,
        TG,
        TD} Instruction;

void configurerRobot();

#endif
