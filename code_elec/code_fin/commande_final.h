#ifndef COMMANDE_FINAL_H
#define COMMANDE_FINAL_H

#include <stdbool.h>
#include <wiringPi.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include "lcd_bip.h"
#include "rgb_sensor.h"
#include <string.h>
#include "configurer.h"

bool detecter_pastille();
bool detecter_Intersec();
void arreter();
void diriger(Instruction dir);
void recadrer(Instruction dir);
void avancer();
void tournerGauche();
void tournerDroite();

#endif
