#include <stdio.h>
#include <wiringPi.h>

#define CAPTEUR_PIN 27 

int main(int argc, char **argv)
{
    //Permet d'utiliser les numéros de GPIO
    wiringPiSetupGpio(); 
    
    pinMode(CAPTEUR_PIN, INPUT); 

    while (1){
        int valeur = digitalRead(CAPTEUR_PIN);

        if (valeur == 0) {
            // Blanc
            printf("Détection : BLANC (0)\n");
        } else {
            Noir
            printf("Détection : NOIR (1)\n");
        }

        delay(500); // Pause de 500ms pour avoir le temps de lire
    }
    return 0;
}