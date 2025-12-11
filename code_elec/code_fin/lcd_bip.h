#ifndef LCD_BIP_H
#define LCD_BIP_H

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <pcf8574.h>
#include <lcd.h>

#define AF_BASE 100
#define  AF_RS (AF_BASE+0)
#define  AF_E (AF_BASE+2)
#define  AF_DB4 (AF_BASE+4)
#define  AF_DB5 (AF_BASE+5)
#define  AF_DB6 (AF_BASE+6)
#define  AF_DB7 (AF_BASE+7)
#define  AF_RW (AF_BASE+1)
#define  AF_LED (AF_BASE+3)
#define PIN_BUZZER 4

int IHM_initialiserLcd();
void IHM_afficherCouleur(int handle, const char* couleur);
void init_Bip();
void bip();

#endif

