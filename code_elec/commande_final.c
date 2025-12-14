#include "commande_final.h"

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
                        digitalWrite(IN1, 1);        
                        digitalWrite(IN2, 0);        
                        digitalWrite(IN3, 1);        
                        digitalWrite(IN4, 0);        
                        break;
                case TG: 
                        digitalWrite(IN1, 1);        
                        digitalWrite(IN2, 0);        
                        digitalWrite(IN3, 0);        
                        digitalWrite(IN4, 1);        
                        pwmWrite(EN2, VITESSE); 
                        pwmWrite(EN1, VITESSE-DELTA_V);
                        break;
                case TD:
                        digitalWrite(IN1, 0);        
                        digitalWrite(IN2, 1);        
                        digitalWrite(IN3, 1);       
                        digitalWrite(IN4, 0);        
                        pwmWrite(EN2, VITESSE-DELTA_V); 
                        pwmWrite(EN1, VITESSE);
                        break;    
        }
    
}
void recadrer(Instruction dir) {
        if (dir==TG){
                pwmWrite(EN2, VITESSE+2*DELTA_V);  
                pwmWrite(EN1, VITESSE-2*DELTA_V);
        } else if (dir==TD){
                pwmWrite(EN2, VITESSE-2*DELTA_V);
                pwmWrite(EN1, VITESSE+2*DELTA_V);
        }
}

void avancer() {
    diriger(AV);
    delay(300);
    while ((!detecter_Intersec())) {
        if (digitalRead(PIN_CAPT_AV_D) && (!digitalRead(PIN_CAPT_AV_M))) {
            recadrer(TD);
        } else if (digitalRead(PIN_CAPT_AV_G) && (!digitalRead(PIN_CAPT_AV_M))) {
            recadrer(TG);
                } else {
                 diriger(AV);
         }
         
         pthread_mutex_lock(&mutex_pastille);
         bool pastille=pastilleDetectee;
         pthread_mutex_unlock(&mutex_pastille);
         usleep(10000);//pour ne pas saturer le processeur
    }
   
}

void tournerDroite() {

        diriger(TG);
        usleep(TEMPS_TOURNER);

        while (1) {
                if (digitalRead(PIN_CAPT_AV_G)){ 
                        break;
                }
        }
}
void tournerGauche() {
        diriger(TD);
        usleep(TEMPS_TOURNER);

        while (1){
                if (digitalRead(PIN_CAPT_AV_D)){  
                        break;
                }
        }
}

void deplacer(Instruction* listeInstructions,int nb_instruc,int lcd){
	for (int i = 0; i < nb_instruc; i++){
                printf("%s\n",Instruction_en_chaine(listeInstructions[i]));
                pthread_mutex_lock(&mutex_pastille);
                
                if (pastilleDetectee){
                	printf("pastille detectée pendant la commande précédente");
                	pastilleDetectee=false;
                }
                pthread_mutex_unlock(&mutex_pastille);
		afficher_instruction(lcd,listeInstructions[i]);
		switch (listeInstructions[i]) {
			case AV: 
				avancer();
				break;
			case TG: 
				tournerGauche();
				break;
			case TD:
				tournerDroite();
				break;
			default:
				printf("non reconnue\n");
				break;
		}
	}
}

