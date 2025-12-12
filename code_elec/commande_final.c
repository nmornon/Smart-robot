// gcc -o test1 test1.c lcd_bip.c rgb_sensor.c lecture_fichier.c commande_final.c -lwiringPi -lpthread -lwiringPiDev -lm

#include "commande_final.h"

bool detecter_pastille(){

return((!digitalRead(PIN_CAPT_AV_D))&(!digitalRead(PIN_CAPT_AV_G))&(!digitalRead(PIN_CAPT_AV_M)));
}

bool detecter_Intersec() {

        bool gauche = digitalRead(PIN_CAPT_AR_G);  // Pin arrière gauche
        bool droit = digitalRead(PIN_CAPT_AR_D);   // Pin arrière droite

        // Intersection = au moins un capteur arrière voit du noir
        return droit || gauche;
}


void arreter() {
        // Arrête les 2 moteurs en mettant PWM à 0
        pwmWrite(EN2, 0);  // Moteur droit stoppé
        pwmWrite(EN1, 0);  // Moteur gauche stoppé
}

void diriger(Instruction dir) {
        switch (dir) {
                case ARRET:
                        pwmWrite(EN2, 0); 
                        pwmWrite(EN1, 0);
                        break;
                case AV: 
                        pwmWrite(EN2, VITESSE); 
                        pwmWrite(EN1, VITESSE);
                        digitalWrite(IN1, 1);        
                        digitalWrite(IN2, 0);        
                        digitalWrite(IN3, 1);        
                        digitalWrite(IN4, 0);        
                        break;
                case TG: 
                        digitalWrite(IN1, 1);        
                        digitalWrite(IN2, 0);        
                        digitalWrite(IN3, 0);        
                        digitalWrite(IN4, 1);        
                        pwmWrite(EN2, VITESSE); 
                        pwmWrite(EN1, VITESSE-DELTA_V);
                        break;
                case TD:
                        digitalWrite(IN1, 0);        
                        digitalWrite(IN2, 1);        
                        digitalWrite(IN3, 1);       
                        digitalWrite(IN4, 0);        
                        pwmWrite(EN2, VITESSE-DELTA_V); 
                        pwmWrite(EN1, VITESSE);
                        break;    
        }
    
}
void recadrer(Instruction dir) {
        if (dir==TG){
                pwmWrite(EN2, VITESSE+2*DELTA_V);  
                pwmWrite(EN1, VITESSE-2*DELTA_V);
        } else if (dir==TD){
                pwmWrite(EN2, VITESSE-2*DELTA_V);
                pwmWrite(EN1, VITESSE+2*DELTA_V);
        }
}

void avancer(int lcd, int capteur_rgb) {
    diriger(AV);
    delay(300);
    while ((!detecter_Intersec())&&(!detecter_pastille())) {
        if (digitalRead(PIN_CAPT_AV_D) && (!digitalRead(PIN_CAPT_AV_M))) {
            recadrer(TD);
        } else if (digitalRead(PIN_CAPT_AV_G) && (!digitalRead(PIN_CAPT_AV_M))) {
            recadrer(TG);
                } else {
                 diriger(AV);
         }
    }
    
    if (detecter_pastille()) {
        arreter(); // S'assurer que le robot est bien arrêté sur la pastille
        bip();
        int r, g, b;
        lireCouleur(capteur_rgb, &r, &g, &b);
        const char* couleur = detecterCouleur(r, g, b);
        
        IHM_afficherCouleur(lcd, couleur);
        bip(); // Faire un bruit pour indiquer la lecture

        delay(3000); // Laisse le temps de voir la couleur affichée (3 secondes)
        lcdClear(lcd);
   
}
}

void tournerDroite() {

        diriger(TG);
        usleep(TEMPS_TOURNER);

        while (1) {
                if (digitalRead(PIN_CAPT_AV_M)){ 
                        break;
                }
        }
}
void tournerGauche() {
        diriger(TD);
        usleep(TEMPS_TOURNER);

        while (1){
                if (digitalRead(PIN_CAPT_AV_M)){  
                        break;
                }
        }
}


