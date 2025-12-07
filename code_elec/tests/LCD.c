#include <stdio.h>
#include <stdlib.h>
#include <wiring¶i.h>
#include <pcf8574.h>
#include <lcd.h>

#define AF_BASE 100
#define  AF_RS (AF_BASE+0)
#define  AF_E (AF_BASE+2)
#define  AF_DB4 (AF_BASE+4)
#define  AF_DB5 (AF_BASE+5)
#define  AF_DB6 (AF_BASE+6)
#define  AF_DB7 (AF_BASE+7)
#define  AF_RW (AF_BASE+1)
#define  AF_LED (AF_BASE+3)

int IHM_initialiserLcd()
{
    
    pcf8574Setup(AF_BASE,0x27); //mettre l’adresse I2C
    
    int handle = lcdInit(2, 16, 4, AF_RS, AF_E, AF_DB4, AF_DB5, AF_DB6, AF_DB7, 0, 0, 0, 0);
   // 2lignes , 16 colonnes, mode 4 bits , le reste c’est les pins du WiringPI qui correspond aux broches du LCD
   
   if(handle < 0)
    {
        fprintf(stderr, "Erreur : initialisation du LCD\n");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < 8; i++) {   //on parcourt les 8 broches virtuelles 
	pinMode(AF_BASE+i,OUTPUT); //chaque broche est mise en sortie
	}
    digitalWrite(AF_LED,1);   //allume la broche du LED sur le PCF8574
    digitalWrite(AF_RW,0); //mode écriture
    lcdClear(handle); //efface tout l'écran 
    lcdPosition(handle, 0, 0); //deplacer le curseur en 0,0
    return handle;
}

void IHM_afficherCouleur(int handle, const char* couleur)
{

    lcdClear(handle); //efface
    
    lcdPosition(handle, 0, 0); //position 0,0
    lcdPuts(handle, "Couleur detectee:"); 

    lcdPosition(handle, 0, 1); // position deuxième ligne
    lcdPuts(handle, couleur); //affiche la couleur
}

const char* detecterCouleur(int r, int g, int b)
{
    if(r > 200 && g < 100 && b > 200) return "Rose";
    if(r > 200 && g > 200 && b < 100) return "Jaune";
    if(r > g && r > b) return "Rouge";
    if(g > r && g > b) return "Vert";
    if(b > r && b > g) return "Bleu";
    if(r < 50 && g < 50 && b < 50) return "Noir";
    if(r > 200 && g > 200 && b > 200) return "Blanc";
    return "Indetermine"
}

int main()
{
	int lcdHandle = IHM_initialiserLcd();


	int r = 250, g = 100, b = 200; // exemple mais on lira la couleur 	du capteur 
	const char* couleur = detecterCouleur(r, g, b);
	//si on detecte noir faut pas l’afficher je pense 

	// Afficher sur le LCD
	IHM_afficherCouleur(lcdHandle, couleur);
	return 0;
}




