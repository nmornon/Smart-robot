#ifndef RGB_SENSOR_H
#define RGB_SENSOR_H

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


int initCapteur();
void lireCouleur(int fd, int *r, int *g, int *b);
const char* detecterCouleur(int r, int g, int b);

#endif

