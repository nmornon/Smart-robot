#ifndef RGB_SENSOR_H
#define RGB_SENSOR_H

int initCapteur();
void lireCouleur(int fd, int *r, int *g, int *b);
const char* detecterCouleur(int r, int g, int b);

#endif

