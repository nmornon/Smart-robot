#ifndef LCD_BIP_H
#define LCD_BIP_H

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <pcf8574.h>
#include <lcd.h>
#include "configurer.h"
#include "pastille_detect.h"

#define AF_BASE 100
#define  AF_RS (AF_BASE+0)
#define  AF_E (AF_BASE+2)
#define  AF_DB4 (AF_BASE+4)
#define  AF_DB5 (AF_BASE+5)
#define  AF_DB6 (AF_BASE+6)
#define  AF_DB7 (AF_BASE+7)
#define  AF_RW (AF_BASE+1)
#define  AF_LED (AF_BASE+3)
#define PIN_BUZZER 16

int InitialiserLcd();
void AfficherCouleur(int handle, const char* couleur);
void init_Bip();
void bip();
const char* Instruction_en_chaine(Instruction instruc);
void afficher_instruction(int lcd, Instruction instruc);

#endif

