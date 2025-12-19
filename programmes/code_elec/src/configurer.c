#include "configurer.h"

void configurerRobot(){

        if (wiringPiSetupGpio() == -1){
                printf("Erreur à l'initialisation\n");
        }

        pinMode(PIN_CAPT_AV_D, INPUT);
        pinMode(PIN_CAPT_AV_G, INPUT);
        pinMode(PIN_CAPT_AR_D, INPUT);
        pinMode(PIN_CAPT_AR_G, INPUT);
        pinMode(PIN_CAPT_AV_M,INPUT);
        pinMode(EN2, PWM_OUTPUT);
        pinMode(EN1, PWM_OUTPUT);
        pinMode(IN1, OUTPUT);
        pinMode(IN2, OUTPUT);
        pinMode(IN3, OUTPUT);
        pinMode(IN4, OUTPUT);

        pwmWrite(EN2, 0);
        pwmWrite(EN1, 0);

        digitalWrite(IN1, 1);  
        digitalWrite(IN2, 0);  
        digitalWrite(IN3, 1);  
        digitalWrite(IN4, 0);  

}

