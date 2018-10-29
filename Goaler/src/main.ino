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
 * @Nom : move
 * @Brief : fonction qui utilise un pid pour déplacé le robot
 * @Entré : double vitesse, double distance
 * @Sortie : void
 */
float siffletValue = 0;
float ambiantValue = 0;
int siffletPin = A0;
int ambiantPin = A1;
int captG = A2;
int captM = A3;
int captD = A4; 
float noirValue = 50;

void move(double vitesse, double distance){
  
  double KPB=0.3;
  double KIB=0.02;
  double KPB_back = 0.1;
  double KIB_back = 0.02;
  double erreurTot=0;
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  
  if (vitesse > 0)
  {
    while(ENCODER_Read(0)*0.075594573<distance*0.1)
      { 
        double multiplicateur=1;
        double erreur=(ENCODER_Read(0)-ENCODER_Read(1))/50;
        if (ROBUS_IsBumper(1) == true)
        {
          MOTOR_SetSpeed(0, 0);
          MOTOR_SetSpeed(1, 0);
        }
        else
        {
          erreurTot+=erreur;
          multiplicateur+=(KPB*erreur+KIB*erreurTot);
          MOTOR_SetSpeed(1,0.13+vitesse*((ENCODER_Read(0)*0.075594573)/(distance*0.1))*multiplicateur);
          MOTOR_SetSpeed(0,0.13+vitesse*((ENCODER_Read(0)*0.075594573)/(distance*0.1)));
        }
        delay(50);
      }

      MOTOR_SetSpeed(0,vitesse);
      MOTOR_SetSpeed(1,vitesse);
      ENCODER_Reset(0);
      ENCODER_Reset(1);
      erreurTot=0;
      
      while(distance*0.8>ENCODER_Read(0)*0.075594573&&distance*0.8>ENCODER_Read(1)*0.075594573)
      {
        double multiplicateur=1;
        double erreur=(ENCODER_Read(0)-ENCODER_Read(1))/50;

        if (ROBUS_IsBumper(1) == true)
        {
          MOTOR_SetSpeed(0, 0);
          MOTOR_SetSpeed(1, 0);
        }
        else
        {
          erreurTot+=erreur;
          multiplicateur+=(KPB*erreur+KIB*erreurTot);
          MOTOR_SetSpeed(0, vitesse);
          MOTOR_SetSpeed(1,vitesse*multiplicateur);
        }

        delay(50);
      }
      erreurTot=0;
      ENCODER_Reset(0);
      ENCODER_Reset(1);
      while(ENCODER_Read(0)*0.075594573<distance*0.1)
      {
        double multiplicateur=1;
        double erreur=(ENCODER_Read(0)-ENCODER_Read(1))/50;
        if (ROBUS_IsBumper(1) == true)
        {
          MOTOR_SetSpeed(0, 0);
          MOTOR_SetSpeed(1, 0);
        }
        else
        {
          erreurTot+=erreur;
          multiplicateur+=(KPB*erreur+KIB*erreurTot);
          MOTOR_SetSpeed(1,0.13+vitesse-vitesse*((ENCODER_Read(0)*0.075594573)/(distance*0.1))*multiplicateur);
          MOTOR_SetSpeed(0,0.13+vitesse-vitesse*((ENCODER_Read(0)*0.075594573)/(distance*0.1)));          
        }
        delay(50);
      }
      erreurTot=0;
      ENCODER_Reset(1);
      ENCODER_Reset(0);
      MOTOR_SetSpeed(0,0);
      MOTOR_SetSpeed(1,0);
    }
else
{
    ENCODER_Reset(0);
    ENCODER_Reset(1);
    while(ENCODER_Read(0)*0.075594573>-distance*0.1)
      {
        double multiplicateur=1;
        double erreur=(ENCODER_Read(0)-ENCODER_Read(1))/50;
        if (ROBUS_IsBumper(1) == true)
        {
          MOTOR_SetSpeed(0, 0);
          MOTOR_SetSpeed(1, 0);
        }        
        else
        {
          erreurTot+=erreur;
          multiplicateur+=(KPB*erreur+KIB*erreurTot);
          MOTOR_SetSpeed(1,-0.13+(vitesse*((ENCODER_Read(0)*0.075594573)/(-distance*0.1))*multiplicateur));
          MOTOR_SetSpeed(0,-0.13+vitesse*((ENCODER_Read(0)*0.075594573)/(-distance*0.1)));
        }
        delay(50);
      }
      erreurTot=0;
      MOTOR_SetSpeed(0,vitesse);
      MOTOR_SetSpeed(1,vitesse);
      ENCODER_Reset(0);
      ENCODER_Reset(1);
      
      while(-distance*0.8<ENCODER_Read(0)*0.075594573&&-distance*0.8<ENCODER_Read(1)*0.075594573)
      {
        double multiplicateur=1;
        double erreur=-1*(ENCODER_Read(0)-ENCODER_Read(1))/50;

        if (ROBUS_IsBumper(1) == true)
        {
          MOTOR_SetSpeed(0, 0);
          MOTOR_SetSpeed(1, 0);
        }
        else
        {
          erreurTot+=erreur;
          multiplicateur+=(KPB_back*erreur+KIB_back*erreurTot);
          MOTOR_SetSpeed(0, vitesse);
          MOTOR_SetSpeed(1,vitesse*multiplicateur);
        }

        delay(50);
      }
      erreurTot=0;
      ENCODER_Reset(0);
      ENCODER_Reset(1);
      while(ENCODER_Read(0)*0.075594573>-distance*0.1)
      {
        double multiplicateur=1;
        double erreur=-1*(ENCODER_Read(0)-ENCODER_Read(1))/50;
        if (ROBUS_IsBumper(1) == true)
        {
          MOTOR_SetSpeed(0, 0);
          MOTOR_SetSpeed(1, 0);
        }
        else
        {
          erreurTot+=erreur;
          multiplicateur+=(KPB_back*erreur+KIB_back*erreurTot);
          MOTOR_SetSpeed(1,(-0.13+vitesse-vitesse*((ENCODER_Read(0)*0.075594573)/(-distance*0.1)))*multiplicateur);
          MOTOR_SetSpeed(0,(-0.13+vitesse-vitesse*((ENCODER_Read(0)*0.075594573)/(-distance*0.1))));
        }
        delay(50);
      }
      erreurTot=0;
      ENCODER_Reset(0);
      ENCODER_Reset(1);
      MOTOR_SetSpeed(0,0);
      MOTOR_SetSpeed(1,0);
  }
}

void suivre_ligne()
{
  float vitesse_grande = 0.5; 
  float vitesse_petite = 0.1; 
while(1)
{

   while (analogRead(captM) > noirValue)
  {
    digitalWrite(13, LOW);
    siffletValue = getAnalogValue(A0);
    ambiantValue = getAnalogValue(A1);
    if (  logiqueSifflet(siffletValue, ambiantValue))
    {
      MOTOR_SetSpeed(0, 0);
      MOTOR_SetSpeed(1, 0);
      delay(10000);
    }
    else if (ROBUS_IsBumper(1))
    {
      MOTOR_SetSpeed(0,0);
      MOTOR_SetSpeed(1,0);
    }
    else
    {
       if (ROBUS_IsBumper(2) || ROBUS_IsBumper(3))
        {
          vitesse_grande = vitesse_grande*(-1);
          vitesse_petite = vitesse_petite*(-1);
          while (ROBUS_IsBumper(2) || ROBUS_IsBumper(3))
         {
           MOTOR_SetSpeed(0, vitesse_petite);
           MOTOR_SetSpeed(1, vitesse_grande);
         } 
        }
        else
        {
          MOTOR_SetSpeed(0, vitesse_petite);
          MOTOR_SetSpeed(1, vitesse_grande);
        }
        
    }
  }

  while (analogRead(captG) > noirValue)
  { 
    digitalWrite(13, LOW);
    siffletValue = getAnalogValue(A0);
    ambiantValue = getAnalogValue(A1);
    if (  logiqueSifflet(siffletValue, ambiantValue))
    {
      MOTOR_SetSpeed(0, 0);
      MOTOR_SetSpeed(1, 0);
      delay(10000);

    }
    else if (ROBUS_IsBumper(1))
    {
      MOTOR_SetSpeed(0,0);
      MOTOR_SetSpeed(1,0);
    }
    else
    {
      if (ROBUS_IsBumper(2) || ROBUS_IsBumper(3))
      {
        vitesse_grande = vitesse_grande*(-1);
        vitesse_petite = vitesse_petite*(-1);
        while(ROBUS_IsBumper(2) || ROBUS_IsBumper(3))
        {
          MOTOR_SetSpeed(0, vitesse_petite);
          MOTOR_SetSpeed(1, vitesse_grande);
        }
      }
    }
  }

  while (analogRead(captM) < noirValue)
  {
    
    siffletValue = getAnalogValue(A0);
    ambiantValue = getAnalogValue(A1);
    if (  logiqueSifflet(siffletValue, ambiantValue) == true)
    {
      MOTOR_SetSpeed(0, 0);
      MOTOR_SetSpeed(1, 0);
      delay(10000);
    }
    else if (ROBUS_IsBumper(1))
    {
      MOTOR_SetSpeed(0,0);
      MOTOR_SetSpeed(1,0);
    }
    else
    { 
      digitalWrite(13, HIGH);
      if (ROBUS_IsBumper(2) || ROBUS_IsBumper(3))
      {
        vitesse_grande = vitesse_grande*(-1);
        vitesse_petite = vitesse_petite*(-1);
        while(ROBUS_IsBumper(2) || ROBUS_IsBumper(3))
        {
          MOTOR_SetSpeed(1, vitesse_petite);
          MOTOR_SetSpeed(0, vitesse_grande);
        }
      }
      MOTOR_SetSpeed(0, vitesse_grande);
      MOTOR_SetSpeed(1, vitesse_petite);
    }
  }

  while (analogRead(captD) < noirValue)
  {
    digitalWrite(13, HIGH);
    siffletValue = getAnalogValue(A0);
    ambiantValue = getAnalogValue(A1);
    if (  logiqueSifflet(siffletValue, ambiantValue) == true)
    {
      MOTOR_SetSpeed(0, 0);
      MOTOR_SetSpeed(1, 0);
      delay(10000);
    }
    else if (ROBUS_IsBumper(1))
    {
      MOTOR_SetSpeed(0,0);
      MOTOR_SetSpeed(1,0);
    }
    else
    {
      if (ROBUS_IsBumper(2) || ROBUS_IsBumper(3))
      {
        vitesse_grande = vitesse_grande*(-1);
        vitesse_petite = vitesse_petite*(-1);
        while(ROBUS_IsBumper(2) || ROBUS_IsBumper(3))
        {
          MOTOR_SetSpeed(1, vitesse_petite);
          MOTOR_SetSpeed(0, vitesse_grande);
        }
      }  
    }
  }
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
  if(analog - 0.7 >= -0.05)
  {
    output += 1;
    analog -= 0.7;
  }

  //DEBUG PRINT
  Serial.print("\n\r");
  Serial.print("analogue ");
  Serial.print(analog);
  Serial.print("\n\r");
  Serial.print("output");
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
 * @Nom : acceleration()
 * @Brief : fonction d'acceleration du robot
 * @Entré : void
 * @Sortie : void
 */
void acceleration(float vitesse)
{
  if( vitesse > 0)
  {
    for (int i = 15; i < vitesse/100; i++)
    {
      MOTOR_SetSpeed(0, i);
      MOTOR_SetSpeed(1, i);
      delay(25);
    }
  }
  else if( vitesse < 0)
  {
    for (int i = -15; i > vitesse/100; i--)
    {
      MOTOR_SetSpeed(0, i);
      MOTOR_SetSpeed(1, i);
      delay(25);
    }
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
  
  pinMode(13, OUTPUT); //DEL integree dans le arduino
  pinMode(A1, INPUT); //pin du bruit ambiant
  pinMode(A0, INPUT); //pin du sifflet+-
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  
  BoardInit();
}

/*
 * @Nom : getAnalogValue()
 * @Brief : Retourne la valeur analog de la pin
 * @Entré : float analog
 * @Sortie : float
 */
float getAnalogValue(int pinAnalog)
{
  float x = analogRead(pinAnalog);
  return x;
}

/*
 * @Nom : logiqueSifflet()
 * @Brief : Retourne 0 ou 1
 * @Entré : float Sifflet float ambiant
 * @Sortie : bool
 */
bool logiqueSifflet(float siffletValue, float ambiantValue)
{
  if (siffletValue > ambiantValue)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/*
 * @Nom : loop()
 * @Brief : Boucle principal, le Main de l'Arduino
 * @Entré : void
 * @Sortie : void
 */
void loop() {
  suivre_ligne();
  // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels
  delay(100);// Delais pour décharger le CPU
}