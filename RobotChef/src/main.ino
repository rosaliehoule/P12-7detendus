/*
 * @Fichier : main.ino
 * @Auteur : Adam Martineau, Félix Thibault-Giguère 
 * @Date : 20/oct/2018
 * @Bref : Attaquant pour le défi de l'octogone
 * @Environnement : Visual Studio Code, PlatformIO
 * @Compilateur : C++
 * @Matériel : Arduino mega 2560
 * @Revision : 1
 */

//--- LISTE DES #INCLUDES ---//
#include <librairie_bras.h>
#include <classControl.h>

classControl classcontrol;

/*
 * @Nom : setup()
 * @Brief : fonction d'initialisation, appeler avant la fonction loop()
 * @Entré : void
 * @Sortie : void
 */
void setup()
{
  Serial.begin(9600);
  BoardInit();
  DisplayInit();
  calsscontrol.refresh_LCD();
}

/*
 * @Nom : loop()
 * @Brief : Boucle principal, le Main de l'Arduino
 * @Entré : void
 * @Sortie : void
 */
void loop() 
{
  classcontrol.gestion_manette();
  delay(100);// Delais pour décharger le CPU
}