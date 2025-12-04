#include <stdio.h>
#include <unistd.h>
#include "lcd.h"
#include "rgb_sensor.h"

int main()
{
    int lcd = IHM_initialiserLcd();
    int capteur = initCapteur();
    if(capteur < 0) return 1;

    while(1)
    {
        int r, g, b;
        lireCouleur(fd, &r, &g, &b);

        const char* couleur = detecterCouleur(r, g, b);

        // n'affiche pas noir ou blanc
        if(couleur != "Noir" && couleur != "Blanc") {
            IHM_afficherCouleur(lcd, couleur);
        }

        usleep(200000); // 200ms
    }

    return 0;
}

