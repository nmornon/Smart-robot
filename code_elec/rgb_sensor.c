#include <stdio.h>
#include <wiringPiI2C.h>
#include <unistd.h>
#include "rgb_sensor.h"

#define TCS3472_ADDR 0x29 //adresse I2C du capteur

// adreese des registres du capteur 
#define COMMAND_BIT 0x80 //sert à indiquer que l'on veut accéder au registre du capteur
#define ENABLE_REG  0x00 //sert à activer le capteur (bit 0 met le capteur sous tension) (bit 1 active les mesures de couleur)
#define ATIME_REG   0x01 //sert à dire combien de temps le capteur collecte la lumière
#define CONTROL_REG 0x0F //régle la sensibilité du capteur

#define Clear 0x14 //adresse ou le capteur stocke les mesures de clear
#define Red 0x16
#define Green 0x18
#define Blue 0x1A

// fonction pour lire un registre 1- bits
int read16(int capteur, int adresse_registre) {
    int low = wiringPiI2CReadReg8(capteur, COMMAND_BIT | adresse_registre); //ici on lit l'octet de poids faible de la valeur de 16 bits
    int high = wiringPiI2CReadReg8(capteur, COMMAND_BIT | (adresse_registre + 1)); //ici on lit l'octet de poids fort de la valeur de 16 bits
    return (high << 8) | low; //combine les deux octects avec un OU
}

int initCapteur()
{
    int capteur= wiringPiI2CSetup(TCS3472_ADDR); //initialiser la communication I2C avec le capteur TCS3472
    
    if(capteur < 0) {  //verifie si l'initalisation à échoué 
        printf("Erreur I2C\n");
        return -1;
    }

    wiringPiI2CWriteReg8(capteur, COMMAND_BIT | ENABLE_REG, 0x03); //active le capteur 
    wiringPiI2CWriteReg8(capteur, COMMAND_BIT | ATIME_REG, 0xF6); //configure le temps d'integration
    wiringPiI2CWriteReg8(capteur, COMMAND_BIT | CONTROL_REG, 0x01); // configure la sensibilité au capteur

    return capteur;
}

void lireCouleur(int capteur, int *r, int *g, int *b)
{
    int c = read16(capteur, Clear); //lecture luminosité totale 
    *r = read16(capteur, Red);      //lecture valeur rouge
    *g = read16(capteur, Green);  //lecture valeur verte
    *b = read16(capteur, Blue);   //lecture valeur bleu

    if(c == 0) c = 1; //pour éviter la division par 0
    
    //normalise les couleurs de 0 à 255
    *r = (*r * 255) / c; 
    *g = (*g * 255) / c;
    *b = (*b * 255) / c;
}

const char* detecterCouleur(int r, int g, int b)
{
    if(r < 50 && g < 50 && b < 50) return "Noir";       // ignore
    if(r > 200 && g > 200 && b > 200) return "Blanc";   // ignore
    if(r > 200 && g < 100 && b > 200) return "Rose";
    if(r > 200 && g > 200 && b < 100) return "Jaune";
    if(r > g && r > b) return "Rouge";
    if(g > r && g > b) return "Vert";
    if(b > r && b > g) return "Bleu";
    return "Indetermine";
}

