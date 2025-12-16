#include "pastille_detect.h"

volatile bool pastilleDetectee=false;
volatile bool threadEnCours=true;
pthread_mutex_t mutex_pastille;
int lcd_handle_global=-1;
char derniereCouleur[20]="";

void initialiser_variables_globales(){
	pthread_mutex_init(&mutex_pastille,NULL);
}

void* thread_detection_pastille(){
	int capteur=initCapteur();
	int r,g,b;
	const char* couleur;
	
	printf("Thread de détection de pastille a démarré\n");
	
	while(threadEnCours){
	
		lireCouleur(capteur,&r,&g,&b);
		couleur=detecterCouleur(r,g,b);
		
		if (strcmp(couleur,"Rouge")==0||strcmp(couleur,"Vert")==0){
		
			pthread_mutex_lock(&mutex_pastille);
			if (!pastilleDetectee){
				pastilleDetectee=true;
                                strcpy(derniereCouleur,couleur);
				printf("Pastille %s détectée\n",couleur);
				
				if (lcd_handle_global !=-1){
					AfficherCouleur(lcd_handle_global,couleur);
				}
			}
			
			pthread_mutex_unlock(&mutex_pastille);
			delay(500);
		} else {
		
			pthread_mutex_lock(&mutex_pastille);
			if (pastilleDetectee) {
				pastilleDetectee=false;
				bip();
			}
			
			pthread_mutex_unlock(&mutex_pastille);
			}
			
		delay(100);
		}
		
		printf("Thread de détection de pastille terminée\n");
		return NULL;
}
