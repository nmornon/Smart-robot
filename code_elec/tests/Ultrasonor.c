#include <wiringPi.h>
#include <stdio.h>

// Choisir les GPIO en numérotation BCM
#define TRIG 1   // GPIO1 (équivalent MicroPython GP1)
#define ECHO 0   // GPIO0 (équivalent MicroPython GP0)

int main(void)
{
    if (wiringPiSetupGpio() == -1) {
        printf("Erreur d'initialisation WiringPi.\n");
        return 1;
    }

    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    // Assurer TRIG à LOW
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);

    while (1) {
        // Envoi du pulse 10µs
        digitalWrite(TRIG, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIG, LOW);

        // Attendre début du signal echo = HIGH
        while (digitalRead(ECHO) == LOW);

        long start = micros();//le temps de depart

        // Attendre fin du signal echo = LOW
        while (digitalRead(ECHO) == HIGH);

        long end = micros();

        long duration = end - start;

        // Distance en cm (vitesse du son = 343m/s)
        double distance = (duration * 0.0343) / 2.0;

        printf("Distance: %.2f cm\n", distance);

        delay(1000);  // 1 seconde
    }

    return 0;
}
