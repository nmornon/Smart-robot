#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include "lecture_fichier.h"
#include "lcd_bip.h"
#include "rgb_sensor.h"
#include <stdbool.h> 
#include "commande_final.h"
#include "configurer.h"
#include <pthread.h>
#include "pastille_detect.h"

// gcc -o robot main.c lcd_bip.c rgb_sensor.c lecture_fichier.c commande_final.c configurer.c pastille_detect.c -lwiringPi -lpthread -lwiringPiDev -lm

int main()
{
    pthread_t thread_pastille;
    
    configurerRobot();
    initialiser_variables_globales();
    init_Bip();
    lcd_handle_global=InitialiserLcd();
    int lcd=lcd_handle_global;
    
    Instruction instruc[MAX];
    unsigned int nbreInstruc=0;
    lcdClear(lcd);
    lcdPuts(lcd,"INIT OK");
    delay(1000);
    
    if (pthread_create(&thread_pastille,NULL,thread_detection_pastille,NULL)!=0){
    	fprintf(stderr,"erreur de création du thread\n");
    	return 1;
    }
    
    lire_fichier(instruc,&nbreInstruc);
    
    deplacer(instruc,nbreInstruc,lcd);   
    
    pthread_mutex_lock(&mutex_pastille);
    threadEnCours=false;
    pthread_mutex_unlock(&mutex_pastille);
    pthread_join(thread_pastille,NULL);
    
    arreter();
    
    pthread_mutex_destroy(&mutex_pastille);
    return 0;
}

	
