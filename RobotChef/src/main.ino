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
#include <librairie_bras.h>


//--- LISTE DES #DEFINES---//

//--- LISTES DES VAR GLOBAL ---// 
int etat_Affich = 0;
char menu[4][20] = {"Burger", "Bacon Burger", "Cheese Burger", "Setup"};

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
  refresh_LCD();
}

/*
 * @Nom : loop()
 * @Brief : Boucle principal, le Main de l'Arduino
 * @Entré : void
 * @Sortie : void
 */
void loop() 
{
  int remote = get_ir();

  //gestion de déplacement dans le menu
  if(remote == 1)
  {
    etat_Affich++;
    if(etat_Affich == 4)
      etat_Affich = 0;
    refresh_LCD();
  }
  else if(remote == 2)
  {
    etat_Affich--;
    if(etat_Affich == -1)
      etat_Affich = 3;
    refresh_LCD();
  }
  else if(remote == 0)
  {
    menu_enter();
    refresh_LCD();
  }

  delay(100);// Delais pour décharger le CPU
}

/// --- AFFICHAGE & MANETTE ---///

/*
 * @Nom : get_ir
 * @Brief : trete les donnes recu par le capteur infrarouge et retourne la commande
 * @Entré : void
 * @Sortie : un char qui décrie la commande recu
 */
int get_ir()
{ 
  int retour = -1;
  uint32_t remote = REMOTE_read();

  if(remote == 0x6604CFC6) //haut
    retour = 1;
  else if(remote == 0x6604CFFA) //bas
    retour = 2;
  else if(remote == 0x6604CFD6) //gauche
    retour = 3;
  else if(remote == 0x6604CFE6) //droite
    retour = 4;
  else if(remote == 0x6604CFF6) //enter
    retour = 0;

  return retour;
}

/*
 * @Nom : 
 * @Brief :
 * @Entré : 
 * @Sortie : 
 */
void refresh_LCD()
{
  DISPLAY_Clear();
  DISPLAY_SetCursor(0,0);
  Serial.print("\n\r");
  Serial.print(menu[etat_Affich]);
}

/// --- BURGER --- ///

/*
 * @Nom : menu_enter
 * @Brief : 
 * @Entré : 
 * @Sortie : 
 */
void menu_enter()
{
  if(etat_Affich == 0)
    burger1();  
  if(etat_Affich == 1)
    burger2();  
  if(etat_Affich == 2)
    burger3();  
}

/*
 * @Nom : 
 * @Brief :
 * @Entré : 
 * @Sortie : 
 */
void burger1()
{
  Serial.print("\n\r");
  Serial.print("creation du burger1");
}

/*
 * @Nom : 
 * @Brief :
 * @Entré : 
 * @Sortie : 
 */
void burger2()
{
  Serial.print("\n\r");
  Serial.print("creation du burger2");
}

/*
 * @Nom : 
 * @Brief :
 * @Entré : 
 * @Sortie : 
 */
void burger3()
{
  Serial.print("\n\r");
  Serial.print("creation du burger3");
}

/// --- MOUVEMENT --- ///


/*
 * @Nom : move
 * @Brief : fonction qui utilise un pid pour déplacé le robot
 * @Entré : double vitesse, double distance
 * @Sortie : void
 */
void move(double vitesse)
{
  double KPB=0.2;
  double multiplicateur=1;
  double erreur=(ENCODER_Read(0)-ENCODER_Read(1))/50;
  multiplicateur+=(KPB*erreur);
  MOTOR_SetSpeed(1,vitesse*multiplicateur);
  MOTOR_SetSpeed(0,vitesse);
  delay(50);
}

void moveBack(double vitesse, double distance)
{
  
  double KPB=0.2;
  double KIB=0.02;
  double erreurTot=0;
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  
  if (vitesse > 0)
  {
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
  else
  {
    while(ENCODER_Read(0)*0.075594573>-distance*0.1)
    {
      MOTOR_SetSpeed(1,-0.13+vitesse*((ENCODER_Read(0)*0.075594573)/(-distance*0.1)));
      MOTOR_SetSpeed(0,-0.13+vitesse*((ENCODER_Read(0)*0.075594573)/(-distance*0.1)));
    }
    MOTOR_SetSpeed(0,vitesse);
    MOTOR_SetSpeed(1,vitesse);
    ENCODER_Reset(0);
    ENCODER_Reset(1);
    
    while(-distance*0.8<ENCODER_Read(0)*0.075594573&&-distance*0.8<ENCODER_Read(1)*0.075594573)
    {
      double multiplicateur=1;
      double erreur=-1*(ENCODER_Read(0)-ENCODER_Read(1))/50;

      erreurTot+=erreur;
      multiplicateur+=(KPB*erreur+KIB*erreurTot);
      MOTOR_SetSpeed(1,vitesse*multiplicateur);
      delay(50);
    }
    ENCODER_Reset(0);
    ENCODER_Reset(1);
    while(ENCODER_Read(0)*0.075594573>-distance*0.1)
    {
      MOTOR_SetSpeed(1,(-0.13+vitesse-vitesse*((ENCODER_Read(0)*0.075594573)/(-distance*0.1))));
      MOTOR_SetSpeed(0,(-0.13+vitesse-vitesse*((ENCODER_Read(0)*0.075594573)/(-distance*0.1))));
    }
    MOTOR_SetSpeed(0,0);
    MOTOR_SetSpeed(1,0);
  }
}

/*  
 * Pour les deux fonctions suivantes:
 *  empatement = 18.8 cm
 *  3.281218894 mm/deg
 *  0.023038563 deg/pulse
 *
 * @Nom : turn_R()
 * @Brief : on déplace le robot vers la droite
 * @Entré : double vitesse , double angle
 * @Sortie : void
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
 * @Nom : turn_L()
 * @Brief : on déplace le robot vers la gauche
 * @Entré : double vitesse , double angle
 * @Sortie : void
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
 * @Nom : turn_180()
 * @Brief : on fait faire un 180 au robot
 * @Entré : double vitesse
 * @Sortie : void
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

int get_distance(int pin)
{
  int adc = analogRead(pin);

  //on transforme la valeur de l'adc (de 0 a 1023) en volt (de 0 a 5)
  float analog = adc * (5.0 / 1023.0);
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
  int adc = analogRead(A4);
  int output = 0;

  //on transforme la valeur de l'adc (de 0 a 1023) en volt (de 0 a 5)
  float analog = adc * (5.0 / 1023.0);

  /* on doit convertire notre valeur de tention 
   * en int (pour pouvoir l'analyser comme un byte),
   * la valeur du 1er bit est 0.7v, le 2eim 1.4v 
   * et le 3eim 2.7v.
   */

  //3eim bit
  if (analog - 2.7 >= 0)
  {
    output += 4;
    analog -= 2.7;
  }

  //2eim bit
  if(analog - 1.4 >= 0)
  {
    output += 2;
    analog -= 1.4;
  }

  //1er bit
  if(analog - 0.7 >= -0.5)
  {
    output += 1;
    analog -= 0.7;
  }

  Serial.print("\n\r Valeur retourne par get_line() : ");
  Serial.print(output);

  return output;
}

/*
 * @Nom : detect_line()
 * @Brief : fonction pour detecté quand on croise une ligne sur le 
 *          parcoure
 * @Entré : void
 * @Sortie : void
 */
bool detect_line()
{
  if(get_line() != 0)
    return true;
  else
    return false;
}

/*
 * @Nom : move_on_line()
 * @Brief : une fois un ligne détecté on bouge le robot sur la ligne
 * @Entré : void
 * @Sortie : void
 */
void move_on_line()
{
  if(get_line() != 2)  {
    if(get_line() == 1)
      turn_L(0.3, 1);
    else 
      turn_R(0.3, 1);
  }

}

/*
 * @Nom : setup()
 * @Brief : fonction d'initialisation, appeler avant la fonction loop()
 * @Entré : void
 * @Sortie : void
 */
void setup(){
  Serial.begin(9600);
  BoardInit();
}

/*
 * @Nom : loop()
 * @Brief : Boucle principal, le Main de l'Arduino
 * @Entré : void
 * @Sortie : void
 */
void loop() {
  pince(true);
  delay(500);
  pince(false);
  delay(500);
  flip_bras(true);
  delay(500);
}