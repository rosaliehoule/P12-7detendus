/*
Projet: Parcours
Equipe: P12
Auteurs: Félix TG 
Description: Fait le parcours
Date: 2018-09-27
*/

/* ****************************************************************************
Inclure les librairies de functions que vous voulez utiliser
**************************************************************************** */

#include <LibRobus.h> // Essentielle pour utiliser RobUS



/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
// L'ensemble des fonctions y ont acces



/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */
void pid(double vitesse, double distance){
  //12B
  double KPB=0.2;
  double KIB=0.02;
  double erreurTot=0;
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  /*while(i<vitesse)
  {
    MOTOR_SetSpeed(0,i);
    MOTOR_SetSpeed(1,i);
    i+=vitesse/3000;
  }*/
  while(ENCODER_Read(0)*0.075594573<distance*0.1)
  {
    MOTOR_SetSpeed(1,0.13+vitesse*((ENCODER_Read(0)*0.075594573)/(distance*0.1)));
    MOTOR_SetSpeed(0,0.13+vitesse*((ENCODER_Read(0)*0.075594573)/(distance*0.1)));
  }
  MOTOR_SetSpeed(0,vitesse);
  MOTOR_SetSpeed(1,vitesse);
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  //(77*pi mm/3200 pulse)=0.075594573mm/pulse
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
void pid2(double vitesse, double distance){
  //12B
  double KPB=0.2;
  double KIB=0.02;
  double erreurTot=0;
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  /*while(i<vitesse)
  {
    MOTOR_SetSpeed(0,i);
    MOTOR_SetSpeed(1,i);
    i+=vitesse/3000;
  }*/
  while(ENCODER_Read(0)*0.075594573<distance*0.1)
  {
    MOTOR_SetSpeed(1,0.20+vitesse*((ENCODER_Read(0)*0.075594573)/(distance*0.1)));
    MOTOR_SetSpeed(0,0.2+vitesse*((ENCODER_Read(0)*0.075594573)/(distance*0.1)));
  }
  MOTOR_SetSpeed(0,vitesse);
  MOTOR_SetSpeed(1,vitesse);
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  //(77*pi mm/3200 pulse)=0.075594573mm/pulse
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
    MOTOR_SetSpeed(1,0.20+vitesse-vitesse*((ENCODER_Read(0)*0.075594573)/(distance*0.1)));
    MOTOR_SetSpeed(0,0.20+vitesse-vitesse*((ENCODER_Read(0)*0.075594573)/(distance*0.1)));
  }
  MOTOR_SetSpeed(0,0);
  MOTOR_SetSpeed(1,0);
}
//empatement = 18.8 cm
//3.281218894 mm/deg
//0.023038563 deg/pulse
void tournerDroite(double vitesse , double angle)
{
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  while(angle>ENCODER_Read(0)*0.023038563)
  {
    MOTOR_SetSpeed(0,vitesse);
    MOTOR_SetSpeed(1,0);
  }
}
void demiTour(double vitesse)
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
void tournerGauche(double vitesse , double angle)
{
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  while(angle>ENCODER_Read(1)*0.023038563)
  {
    MOTOR_SetSpeed(1,vitesse);
    MOTOR_SetSpeed(0,0);
  }
}
/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les varibbles globales

void setup(){
  BoardInit();
}


/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop() {
  while(ROBUS_IsBumper(2)==0)
  {}
  
  MOTOR_SetSpeed(0,0.3);
}