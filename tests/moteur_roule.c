#include <wiringPi.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

// gcc -o robot moteur_roule.c -lwiringPi -lm 

#define PIN_CAPT_AV_D 19    // Capteur AVANT DROIT
#define PIN_CAPT_AV_G 26    // Capteur AVANT GAUCHE
#define PIN_CAPT_AV_M 17  // Capteur AVANT MILIEU
#define PIN_CAPT_AR_D 23    // Capteur ARRIERE DROIT
#define PIN_CAPT_AR_G 21    // Capteur ARRIERE GAUCHE

#define EN2 25        // PWM Vitesse moteur DROIT
#define EN1 24        // PWM Vitesse moteur GAUCHE

#define IN1 6              // Direction moteur gauche
#define IN2 5              // Direction moteur gauche
#define IN3 4               // Direction moteur droit
#define IN4 18               // Direction moteur droit

#define VITESSE 500         // Vitesse de base PWM (0-1023 car 2¹⁰=1024) 
#define DELTA_V 150         // Correction vitesse pour suivi ligne
#define TEMPS_TOURNER 200000    // A adpater car je me rends pas compte de comment il tourne

typedef enum{
	ARRET,
	AV,
	TG,
	TD} Instruction;

bool detecter_Intersec() {

	bool gauche = digitalRead(PIN_CAPT_AR_G);  // Pin arrière gauche
	bool droit = digitalRead(PIN_CAPT_AR_D);   // Pin arrière droite
	
	// Intersection = au moins un capteur arrière voit du noir
	return droit || gauche;
}


void arreter() {
	// Arrête les 2 moteurs en mettant PWM à 0
	pwmWrite(EN2, 0);  // Moteur droit stoppé
	pwmWrite(EN1, 0);  // Moteur gauche stoppé
}


void diriger(Instruction dir) {
	switch (dir) {
		case ARRET:
			pwmWrite(EN2, 0); 
			pwmWrite(EN1, 0);
			break;
		case AV: 
			pwmWrite(EN2, VITESSE); 
			pwmWrite(EN1, VITESSE);
			digitalWrite(IN1, 0);        //1
			digitalWrite(IN2, 1);	     //0
			digitalWrite(IN3, 1);        //0
			digitalWrite(IN4, 0);        //1
			break;
		case TG: 
			digitalWrite(IN1, 0);        //1
			digitalWrite(IN2, 1);        //0
			digitalWrite(IN3, 0);        //1
			digitalWrite(IN4, 1);        //0
			pwmWrite(EN2, VITESSE); 
			pwmWrite(EN1, VITESSE-DELTA_V);
			break;
		case TD:
			digitalWrite(IN1, 0);        //0
			digitalWrite(IN2, 1);        //1
			digitalWrite(IN3, 0);        //0
			digitalWrite(IN4, 1);        //1
			pwmWrite(EN2, VITESSE-DELTA_V); 
			pwmWrite(EN1, VITESSE);
			break;    
	}
    
}

void recadrer(Instruction dir) {
	if (dir==TG){
		pwmWrite(EN2, VITESSE+2*DELTA_V);  //il faudra adapter les delta j'ai fait au hasard 
		pwmWrite(EN1, VITESSE-2*DELTA_V);
	} else if (dir==TD){
		pwmWrite(EN2, VITESSE-2*DELTA_V);
		pwmWrite(EN1, VITESSE+2*DELTA_V);
	}
}

void avancer() {
    diriger(AV);
    delay(300);
    while (!detecter_Intersec()) {
        if (digitalRead(PIN_CAPT_AV_D) && (!digitalRead(PIN_CAPT_AV_M))) {
            recadrer(TD);
        } else if (digitalRead(PIN_CAPT_AV_G) && (!digitalRead(PIN_CAPT_AV_M))) {
            recadrer(TG);
        	} else {
           	 diriger(AV);
       	 }
    }
    
}

void tournerGauche() {
	
	diriger(TG);
	usleep(TEMPS_TOURNER);

	while (1) {
		if (digitalRead(PIN_CAPT_AV_G)){  //j'ai mis gauche car je pense que si je met milieu il tournera de trop
			break;
		}
	}
}
void tournerDroite() {
	diriger(TD);
	usleep(TEMPS_TOURNER);

	while (1){
		if (digitalRead(PIN_CAPT_AV_D)){   //tester avec PIN_CAPT_AV_M si ça marche pas 
			break;
		}
	}
}

void configurerRobot(){

	if (wiringPiSetupGpio() == -1){
        	printf("Erreur à l'initialisation\n");
    	}
    	 
    	pinMode(PIN_CAPT_AV_D, INPUT);
    	pinMode(PIN_CAPT_AV_G, INPUT);
    	pinMode(PIN_CAPT_AR_D, INPUT);
    	pinMode(PIN_CAPT_AR_G, INPUT);
    	pinMode(EN2, PWM_OUTPUT);
  	pinMode(EN1, PWM_OUTPUT);
   	pinMode(IN1, OUTPUT);
  	pinMode(IN2, OUTPUT);
  	pinMode(IN3, OUTPUT);
  	pinMode(IN4, OUTPUT);

    	pwmWrite(EN2, 0);
    	pwmWrite(EN1, 0);

    	digitalWrite(IN1, 0);  //1
    	digitalWrite(IN2, 1);  //0
    	digitalWrite(IN3, 1);  //0
    	digitalWrite(IN4, 0);  //1

}
	
	
	
int main() {

    configurerRobot();
    printf("robot pret");
    delay(2000);

    printf("debut test\n");
    
    
    avancer(); 
    printf("il va tourner à droite\n");
    
    tournerDroite(); 
    printf("il va avancer\n ");
    
    avancer(); 
    printf("il va tourner à gauche\n");
    
    tournerGauche(); 
    printf("il va avancer\n");
    
    avancer();
    
    printf("fin test \n");
    arreter();
    return 0;
}

