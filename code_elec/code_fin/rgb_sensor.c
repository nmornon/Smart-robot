#include "rgb_sensor.h"

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
    if(r > g && r > b) return "Rouge";
    if(g > r && g > b) return "Vert";
    return "Indetermine";
}

