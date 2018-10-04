/*
Projet: Le nom du script
Equipe: Votre numero d'equipe
Auteurs: Les membres auteurs du script
Description: Breve description du script
Date: Derniere date de modification
*/

/* ****************************************************************************
Inclure les librairies de functions que vous voulez utiliser
**************************************************************************** */
#include <Arduino.h>
#include <LibRobus.h> // Essentielle pour utiliser RobUS

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 13

uint8_t moteur1 = 0;
uint8_t moteur2 = 1;

/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
// L'ensemble des fonctions y ont acces



/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */
void Avance()
{
  MOTOR_SetSpeed(moteur1,0.5);
  MOTOR_SetSpeed(moteur2,0.5);
}

void PID(float vitesse, float distance)
{
  float KP = 0.165;
  float KI = 0.001; 
  float erreur_tot = 0;
  float vitesse_debut = 0; 

  ENCODER_ReadReset(0);
  ENCODER_ReadReset(1);

  MOTOR_SetSpeed(moteur1,vitesse);
  MOTOR_SetSpeed(moteur2,vitesse);

  while(vitesse_debut<vitesse)
  {
    vitesse_debut = vitesse_debut + (vitesse/6000);
  }
 
   while (distance > ENCODER_Read(0)*(0.00755957323) && distance > ENCODER_Read(1)*(0.00755957323))
   {
     float multiplicateur = 1;
     float erreur = ((ENCODER_Read(0)-ENCODER_Read(1))/50);

     erreur_tot = erreur_tot + erreur;

     multiplicateur = multiplicateur + KP*erreur + KI*erreur_tot;

    MOTOR_SetSpeed(1,vitesse*multiplicateur);

    delay(50);
   }
}

/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les varibbles globales

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  BoardInit();
}


/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop() 
{while(ROBUS_IsBumper(3)==0)
{}
 PID(0.5, 250);
 MOTOR_SetSpeed(0,0);
 MOTOR_SetSpeed(1,0);

 delay(10);
}