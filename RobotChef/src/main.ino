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
#include <mouvement.h>
#include<LibRobus.h>

classControl classcontrol;
mouvement move;

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
  classcontrol.refresh_LCD();

  pince(true);
  flip_bras(true);

  delay(10000);
  move.calibration();
}

/*
 * @Nom : loop()
 * @Brief : Boucle principal, le Main de l'Arduino
 * @Entré : void
 * @Sortie : void
 */
void loop() 
{
  move.calibration();
  int burgerChoisi;
  burgerChoisi = classcontrol.gestion_manette();
  switch(burgerChoisi)
  {
    case 1:
      move.burger1();
      break;
    case 2:
      move.burger2();
      break;
    case 3:
      move.burger3();
      break;
    default:
      break;
  }
  delay(25);// Delais pour décharger le CPU
}