#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <softPwm.h>

#define IN1 6 //GPIO 6
#define	IN2  5 // GPIO 5
#define	IN3 4   // GPIO 4 
#define	IN4 18    // GPIO 18
#define	EN1 24  //GPIO 24 
#define	EN2 25    //GPIO 25
#define CAPTEUR_PIN1 13  //GPIO 13
#define CAPTEUR_PIN1 14 //GPIO 14 




void setup(){
	wiringPiSetupGpio();
	pinMode(IN1,OUTPUT);
	pinMode(IN2,OUTPUT);
	pinMode(IN3,OUTPUT);
	pinMode(IN4,OUTPUT);
	pinMode(EN1,OUTPUT);
	pinMode(EN2,OUTPUT);
    pinMode(CAPTEUR_PIN1, INPUT); 
    pinMode(CAPTEUR_PIN2, INPUT);
    pinMode(CAPTEUR_PIN3, INPUT);  
}
void Gauche(){
	digitalWrite(IN1,1);
	digitalWrite(IN2,0);
	digitalWrite(IN3,1);
	digitalWrite(IN4,0);
	digitalWrite(EN1,1);
	digitalWrite(EN2,1);
	printf("Gauche\n");
}

void Droite(){
	
	digitalWrite(IN1,0);
	digitalWrite(IN2,1);
	digitalWrite(IN3,0);
	digitalWrite(IN4,1);
	digitalWrite(EN1,1);
	digitalWrite(EN2,1);
	printf("Droite\n");


	
}


void Avance(){
	digitalWrite(IN1,0);
	digitalWrite(IN2,1);
	digitalWrite(IN3,1);
	digitalWrite(IN4,0);
	digitalWrite(EN1,1);
	digitalWrite(EN2,1);
	printf("Horaire\n");
}

void Arret(){
	digitalWrite(IN1,0);
	digitalWrite(IN2,0);
	digitalWrite(IN3,0);
	digitalWrite(IN4,0);
	digitalWrite(EN1,1);
	digitalWrite(EN2,1);
	printf("Arret\n");
}

void capteur(){

    

    
    int valeur = digitalRead(CAPTEUR_PIN1);

    if (valeur == 0) {
        Arret();
        
    } else {
        Avance();
   
    }
    int valeur = digitalRead(CAPTEUR_PIN2);

    if (valeur == 0) {
        Arret();
        
    } else {
        Droite();
        delay(200);
        Avance();
        
    }
    int valeur = digitalRead(CAPTEUR_PIN3);

    if (valeur == 0) {
        Arret();
        
    } else {
        Gauche();
        delay(200);
        Avance();
        
    }
    
}


int main(int argc, char **argv)
{ 
    setup();
    while(1){
		capteur();
		
}	return 0;
}
