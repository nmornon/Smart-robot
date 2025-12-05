#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <softPwm.h>

#define IN1 6 //GPIO 6
#define	IN2  5 // GPIO 5
#define	IN3 4   // GPIO 4 
#define	IN4 18    // GPIO 18
#define	EN1 12  //GPIO 24 
#define	EN2 13    //GPIO 25
#define CAPTEUR_PIN1 24  //GPIO 13
#define CAPTEUR_PIN2 25 //GPIO 14 
#define CAPTEUR_PIN3 15 //GPIO 15 a verifier 



void setup(){
	wiringPiSetupGpio();
	pinMode(IN1,OUTPUT);
	pinMode(IN2,OUTPUT);
	pinMode(IN3,OUTPUT);
	pinMode(IN4,OUTPUT);
	pinMode(EN1,PWM_OUTPUT);
	pinMode(EN2,PWM_OUTPUT);
    pinMode(CAPTEUR_PIN1, INPUT); 
    pinMode(CAPTEUR_PIN2, INPUT);
    pinMode(CAPTEUR_PIN3, INPUT);  
}

void setSpeed(int speed) {  // 0-100 en pourcentage
    speed = speed * 1024 / 100;
    pwmWrite(EN1, speed);
    pwmWrite(EN2, speed);
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

    

    
    int valeur1 = digitalRead(CAPTEUR_PIN1);
    int valeur2 = digitalRead(CAPTEUR_PIN2);
    int valeur3 = digitalRead(CAPTEUR_PIN3);

    if (valeur1 == 0 && valeur2 == 0 && valeur3 ==0) {
        Arret();
        delay(200);
        
        
    } else if (valeur1 == 1 && valeur2 == 0 && valeur3 == 0) {
        Avance();
   
    
    

    } else if (valeur1 == 0 && valeur2 == 1 && valeur3 == 0) {

        setSpeed(speed);//quand en detecte a gauche en ralenti la vitesse a 50% puis en tourne

        Droite();

        delay(200);
        setSpeed(speed1);// ici en remet la vitesse initial et en continu a la vitesse intial
        Avance();
        
    } else if (valeur1 == 0 && valeur2 == 0 && valeur3 == 1) {

        setSpeed(speed);
        delay(200)


        Gauche();
        delay(200);
        setSpeed(speed1);
        Avance();
        
    } else if (valeur1 == 1 && valeur2 == 1 && valeur3 == 1) {
        Avance();
        
    } else if (valeur1 == 1 && valeur2 == 1 && valeur3 == 1)) {
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
