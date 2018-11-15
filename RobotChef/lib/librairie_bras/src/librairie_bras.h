/*
 * @Fichier : 
 * @Auteur :
 * @Date :
 * @Bref : 
 * @Environnement :
 * @Compilateur :
 * @Matériel :
 * @Revision :
 */

//--- LISTE DES PROTOTYPES ---//
#ifndef LIBRAIRIE_BRAS_H
#define LIBRAIRIE_BRAS_H

#include<LibRobus.h>

/*
 * @Nom : 
 * @Brief :
 * @Entré : bool p, 1: position normal, 0: position renversé
 * @Sortie : 
 */
void flip_bras(bool p);


/*
 * @Nom : 
 * @Brief :
 * @Entré : bool p, 1: ouvert, 0: fermé
 * @Sortie : 
 */
void pince(bool p);

void flip_bras(bool p)
{
    SERVO_Enable(0);
    if(p)
    {
        SERVO_SetAngle(0,0);
    }
    else
    {
        SERVO_SetAngle(0,180);
    }   
}
void pince(bool p)
{
    SERVO_Enable(1);
    if(p)
    {
      SERVO_SetAngle(1,90);  
    }
    else
    {
        SERVO_SetAngle(1,0);
    }
    
}

#endif