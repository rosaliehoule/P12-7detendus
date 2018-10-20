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
#include <LibRobus.h> // Essentielle pour utiliser RobUS

/*
 * @Nom : pid
 * @Brief : 
 * @Entré : double vitesse, double distance
 * @Sortie : void
 */
void go(double vitesse, double distance){
  
  double KPB=0.2;
  double KIB=0.02;
  double erreurTot=0;
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  
  while(ENCODER_Read(0)*0.075594573<distance*0.1)
  {
    MOTOR_SetSpeed(1,0.13+vitesse*((ENCODER_Read(0)*0.075594573)/(distance*0.1)));
    MOTOR_SetSpeed(0,0.13+vitesse*((ENCODER_Read(0)*0.075594573)/(distance*0.1)));
  }
  MOTOR_SetSpeed(0,vitesse);
  MOTOR_SetSpeed(1,vitesse);
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  
  while(distance*0.8>ENCODER_Read(0)*0.075594573&&distance*0.8>ENCODER_Read(1)*0.075594573)
  {
    double multiplicateur=1;
    double erreur=(ENCODER_Read(0)-ENCODER_Read(1))/50;
    erreurTot+=erreur;
    multiplicateur+=(KPB*erreur+KIB*erreurTot);
    MOTOR_SetSpeed(1,vitesse*multiplicateur);
    delay(50);
  }
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  while(ENCODER_Read(0)*0.075594573<distance*0.1)
  {
    MOTOR_SetSpeed(1,0.13+vitesse-vitesse*((ENCODER_Read(0)*0.075594573)/(distance*0.1)));
    MOTOR_SetSpeed(0,0.13+vitesse-vitesse*((ENCODER_Read(0)*0.075594573)/(distance*0.1)));
  }
  MOTOR_SetSpeed(0,0);
  MOTOR_SetSpeed(1,0);
}

/*
 * @Nom : 
 * @Brief :
 *  empatement = 18.8 cm
 *  3.281218894 mm/deg
 *  0.023038563 deg/pulse
 * @Entré : 
 * @Sortie : 
 */
void turn_R(double vitesse , double angle)
{
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  while(angle>ENCODER_Read(0)*0.023038563)
  {
    MOTOR_SetSpeed(0,vitesse);
    MOTOR_SetSpeed(1,0);
  }
}

/*
 * @Nom : 
 * @Brief :
 * @Entré : 
 * @Sortie : 
 */
void turn_L(double vitesse , double angle)
{
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  while(angle>ENCODER_Read(1)*0.023038563)
  {
    MOTOR_SetSpeed(1,vitesse);
    MOTOR_SetSpeed(0,0);
  }
}

/*
 * @Nom : 
 * @Brief :
 * @Entré : 
 * @Sortie : 
 */
void turn_180(double vitesse)
{
  ENCODER_Reset(1);
  ENCODER_Reset(0);
  while(87>ENCODER_Read(1)*0.023038563||-87<ENCODER_Read(0)*0.023038563)
  {
    if(87>ENCODER_Read(1)*0.023038563)
    {
      MOTOR_SetSpeed(1,vitesse);
    }
    else
      MOTOR_SetSpeed(1,0);
    if(-87<ENCODER_Read(0)*0.023038563)
    {
      MOTOR_SetSpeed(0,-vitesse);
    }
    else
      MOTOR_SetSpeed(0,0);
  }
}

/*
 * @Nom : get_line()
 * @Brief : va chercher l'état des capteurs de ligne, on dispose de 
 *          3 capteurs un à côté de l'autre, on retourne un int qui 
 *          représante un nombre binaire a 3 bites.
 * @Entré : void 
 * @Sortie : on retourne un int qui représante un nombre binaire a 
 *           3 bites, chaque bite représante un capteur, EX: 2 
 *           (010 en binaire) = la ligne est détecté au centre.
 */
int get_line()
{
  return 2; // 2 = 010
}

/*
 * @Nom : detect_line()
 * @Brief : fonction pour detecté quand on croise une ligne sur le 
 *          parcoure
 * @Entré : void
 * @Sortie : void
 */
void detect_line()
{
  if(get_line() != 0)
    move_on_line();
}

/*
 * @Nom : move_on_line()
 * @Brief : une fois un ligne détecté on bouge le robot sur la ligne
 * @Entré : void
 * @Sortie : void
 */
void move_on_line()
{
  if(get_line() != 2)
  {
    if(get_line() == 1)
      turn_L(0.3, 1);
    else 
      turn_R(0.3, 1);
  }
}

/*
 * @Nom : setup()
 * @Brief : fonction d'initialisation
 * @Entré : void
 * @Sortie : void
 */
void setup(){
  BoardInit();
}

/*
 * @Nom : 
 * @Brief :
 * @Entré : 
 * @Sortie : 
 */
void loop() {

  // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels
  delay(100);// Delais pour décharger le CPU
}