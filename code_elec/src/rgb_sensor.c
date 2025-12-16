#include "rgb_sensor.h"

int lire_registre_16_bits(int capteur, int adresse_registre){

	int poids_faible=wiringPiI2CReadReg8(capteur,COMMAND_BIT|adresse_registre);
	int poids_fort=wiringPiI2CReadReg8(capteur,COMMAND_BIT|(adresse_registre+1));
	
	return (poids_fort<<8) | poids_faible;
}


int initCapteur(){

	int capteur=wiringPiI2CSetup(TCS3472_ADDR);
	
	if(capteur<0){
	
		printf("Erreur I2C capteur\n");
		return -1;
	}
	
	wiringPiI2CWriteReg8(capteur,COMMAND_BIT|ENABLE_REG,0x03);
	wiringPiI2CWriteReg8(capteur,COMMAND_BIT|ATIME_REG,0xF6);
	wiringPiI2CWriteReg8(capteur,COMMAND_BIT|CONTROL_REG,0x01);
	
	return capteur;
}

void lireCouleur(int capteur, int *r, int *g, int *b){

	int c=lire_registre_16_bits(capteur,Clear);
	*r=lire_registre_16_bits(capteur,Red);
	*g=lire_registre_16_bits(capteur,Green);
	*b=lire_registre_16_bits(capteur,Blue);
	
	if (c==0) c=1;
	
	*r=(*r*255)/c;
	*g=(*g*255)/c;
	*b=(*b*255)/c;
}

const char* detecterCouleur(int r, int g, int b){

	if (r<g && b<=130){
		return "Vert";
	}
	
	if (r>=170 && g<=130 && b<=135){
		return "Rouge";
	}
	
	return "Indetermine";
}
