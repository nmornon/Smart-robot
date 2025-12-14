#ifndef PASTILLE_DETECT_H
#define PASTILLE_DETECT_H

#include <pthread.h>
#include <stdbool.h>
#include <wiringPi.h>
#include <stdio.h>
#include "rgb_sensor.h"
#include "lcd_bip.h"
#include "configurer.h"

// Variables partagées
extern volatile bool pastilleDetectee;
extern volatile bool threadEnCours;
extern pthread_mutex_t mutex_pastille;

// Handle de l'écran LCD pour l'affichage dans le thread
extern int lcd_handle_global;

// Prototypes
void* thread_detection_pastille(void* arg);
void initialiser_variables_globales();

#endif
