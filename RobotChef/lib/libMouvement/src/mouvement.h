#include <LibRobus.h>


#define calib true

#define capt_1 A9
#define capt_2 A11
#define capt_3 A12
#define NBR_INGREDIENT 1
#define Pain 1
#define Fromage 2
#define Salade 3
#define Sauce 4
#define Tomate 5
#define Boulette 6

/*calibration des capteurs
 *	    blanc 	noir
 *   1	400     200
 *   2	360     200	
 *   3	170     100
 */
/*
    Stations:
    1 Pain
    2 Fromage
    3 Salade
    4 Sauce
    5 Tomate
    6 Boulette
*/

class mouvement
{
    public:
        int threshold_1 = 200;
        int threshold_2 = 200;
        int threshold_3 = 130;
        classControl lcd;

        bool fini =false;

        float moteur_g = vitesseLent;
        float moteur_d = vitesseLent;

        float vitesseRapide = 0.13;
        float vitesseLent = 0.1;

        bool flag = false;
        int station = 0;

        void calibration();
        int read();

        void burger_1();
        void burger_2();
        void burger_3();

        void m_mouvement(int bonneStation);
        void avance();
        void alignement_d();
        void alignement_g();
        void mouvement_Station();
        void mouvement_Fin();
        
        bool detect_station(int bonneStation);
        void turn_station(bool direction);
        void demiTour();
        
        void prendreIngredient();
        void lacherIngredient();
        void retourner();
        void allerPorter();
};

/*
* @Nom : burger1
* @Brief : fait le burger 1
* @Entré : 
* @Sortie : 
*/
void mouvement::burger_1()
{
    fini=false;
    m_mouvement(Pain);
    fini=false;
}

/*
* @Nom : burger2
* @Brief : fait le burger 2
* @Entré : 
* @Sortie : 
*/
void mouvement::burger_2()
{
    fini=false;
    m_mouvement(Pain);
    fini=false;
    m_mouvement(Boulette);
    fini=false;
    m_mouvement(Fromage);
    fini=false;
    m_mouvement(Pain);
    fini=false;
}

/*
* @Nom : burger 3
* @Brief : fait le burger 3
* @Entré : 
* @Sortie : 
*/
void mouvement::burger_3()
{
    fini=false;
    m_mouvement(Pain);
    fini=false;
    m_mouvement(Boulette);
    fini=false;
    m_mouvement(Fromage);
    fini=false;
    m_mouvement(Tomate);
    fini=false;
    m_mouvement(Sauce);
    fini=false;
    m_mouvement(Pain);
    fini=false;
}

/*
* @Nom : m_mouvement
* @Brief : se dirige ver une station et fait les manipulations necessaires
* @Entré : le numéro de la station
* @Sortie : 
*/
void mouvement::m_mouvement(int bonneStation)
{
    while(!fini)
    {
         //diagnostique
        MOTOR_SetSpeed(0, moteur_g);
        MOTOR_SetSpeed(1, moteur_d);

        int capteurs = read();

        if(capteurs == 2)
        {
            flag = false;
            avance();
        }
        else if (capteurs == 4)
        {
            flag = false;
            alignement_d();
        }
        else if (capteurs == 1)
        {
            flag = false;
            alignement_g();
        }
        else if (capteurs == 7 && flag == false)
        {
            flag = true;
            if(detect_station(bonneStation)==true)
            {
                turn_station(true);
                mouvement_Station();
                if(bonneStation<NBR_INGREDIENT)
                {
                    prendreIngredient();
                    allerPorter();
                }
                else if (bonneStation==NBR_INGREDIENT)
                {
                    prendreIngredient();
                    demiTour();
                    mouvement_Station();
                    turn_station(true);
                    MOTOR_SetSpeed(0,0.1);
                    MOTOR_SetSpeed(1,0.1);
                    delay(300);
                    m_mouvement(NBR_INGREDIENT+1);
                }
                else if (bonneStation==NBR_INGREDIENT+1)
                {
                    lacherIngredient();
                    delay(5000);
                    prendreIngredient();
                    lacherIngredient();
                    delay(5000);
                    prendreIngredient();
                    allerPorter();
                }
                else
                {
                    lacherIngredient();
                    retourner();
                }
            }
        }
    }   
}
/*
* @Nom : read
* @Brief : lit les capteurs de luminosités
* @Entré : 
* @Sortie : valeur des trois capteurs
            +1 pour gauche
            +2 pour milieu
            +4 pour droit
*/
int mouvement::read()
{
    int retourn = 0;
    
    if (analogRead(capt_3) <= threshold_3)
            retourn += 1;
    if (analogRead(capt_2) <= threshold_2)
        retourn += 2;
    if (analogRead(capt_1) <= threshold_1)
        retourn += 4;
    Serial.print("\n\r");
    Serial.print(retourn);
    return retourn;
}

/*
* @Nom : avance
* @Brief : avance en ligne droite
* @Entré : 
* @Sortie : 
*/
void mouvement::avance()
{
    moteur_d = vitesseRapide;
    moteur_g = vitesseRapide;
}

/*
* @Nom : alignement_d
* @Brief : tourne vers la droite
* @Entré : 
* @Sortie : 
*/
void mouvement::alignement_d()
{
    moteur_d = vitesseRapide;
    moteur_g = vitesseRapide;
}

/*
* @Nom : alignement_g
* @Brief : tourne vers la gauche
* @Entré : 
* @Sortie : 
*/
void mouvement::alignement_g()
{
    moteur_d = vitesseRapide;
    moteur_g = vitesseLent;
}

/*
* @Nom : detect_station
* @Brief : augmente la station présente de 1
* @Entré : station désiré
* @Sortie : à atteint la station désiré
*/
bool mouvement::detect_station(int bonneStation)
{
    station++;
    
    //Serial.print("\n\r");
    //Serial.print(station);

    if (station == bonneStation)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
* @Nom : turn_station
* @Brief : tourne jusqu'à tmeps de voir une autre ligne
* @Entré : direction (1:gauche, 2:droite)
* @Sortie : 
*/
void mouvement::turn_station(bool direction)
{
    int moteurGauche;
    int moteurDroit;
    if(direction)
    {
        moteurGauche=0;
        moteurDroit=vitesseLent;
    }
    else
    {
        moteurGauche=vitesseLent;
        moteurDroit=0;
    }
    MOTOR_SetSpeed(0, vitesseLent);
    MOTOR_SetSpeed(1, vitesseLent);
    delay(350);
    MOTOR_SetSpeed(0, moteurGauche);
    MOTOR_SetSpeed(1, moteurDroit);
    while(read() != 7){}
}
/*
* @Nom : mouvement_Station
* @Brief : bouge jusqu'au bout de la station
* @Entré : 
* @Sortie : 
*/
void mouvement::mouvement_Station()
{
    bool Arrive(true);
    while(Arrive==false)
    {
        MOTOR_SetSpeed(0, moteur_g);
        MOTOR_SetSpeed(1, moteur_d);

        int capteurs = read();

        if(capteurs == 2)
        {
            flag = false;
            avance();
        }
        else if (capteurs == 4)
        {
            flag = false;
            alignement_d();
        }
        else if (capteurs == 1)
        {
            flag = false;
            alignement_g();
        }
        else if (capteurs == 7 && flag == false)
        {
            MOTOR_SetSpeed(0,0);
            MOTOR_SetSpeed(1,0);
            Arrive=true;
        }
    }
}

/*
* @Nom : calibration
* @Brief : calibre les capteurs de luminosité
* @Entré : 
* @Sortie : 
*/
void mouvement::calibration()
{
    Serial.print("\n\r");

    Serial.print("Robot sur blanc");
    delay(10000);

    int a1 = analogRead(capt_1);
    int b1 = analogRead(capt_2);
    int c1 = analogRead(capt_3);

    Serial.print("\n\r");
    Serial.print("Robot sur noir");
    delay(10000);

    int a2 = analogRead(capt_1);
    int b2 = analogRead(capt_2);
    int c2 = analogRead(capt_3);

    threshold_1 = (a1 + a2)/2;
    threshold_2 = (b1 + b2)/2;
    threshold_3 = (c1 + c2)/2;

    Serial.print("\n\r");
    Serial.print("Calibration fini");

    delay(5000);
}

/*
* @Nom : prendre ingrédient
* @Brief : prend un ingrédient
* @Entré : 
* @Sortie : 
*/
void mouvement::prendreIngredient()
{
    pince(false);
    delay(500);
}

/*
* @Nom : lacherIngredient
* @Brief : lache l'ingrédient
* @Entré : 
* @Sortie : 
*/
void mouvement::lacherIngredient()
{
    pince(true);
    delay(500);
    flip_bras(false);
    delay(500);
    flip_bras(true);
    delay(500);
}

/*
* @Nom : retourner
* @Brief : sort de la chute et retourne à la station de départ
* @Entré : 
* @Sortie : 
*/
void mouvement::retourner()
{
    demiTour();
    mouvement_Station();
    turn_station(false);
    fini =true;
    station = 0;
}

/*
* @Nom : allerPorter
* @Brief : Sort de la station et va à la chute
* @Entré : 
* @Sortie : 
*/
void mouvement::allerPorter()
{
    demiTour();
    mouvement_Station();
    turn_station(true);
    m_mouvement(NBR_INGREDIENT+2);

}

/*
* @Nom : demiTour
* @Brief : Fait un demi-tour
* @Entré : 
* @Sortie : 
*/
void mouvement::demiTour()
{
    MOTOR_SetSpeed(0,-vitesseLent);
    MOTOR_SetSpeed(1,-vitesseLent);
    delay(500);
    MOTOR_SetSpeed(1,vitesseLent);
    while(read()!=0)
    {}
    while(read()!=2)
    {}
    MOTOR_SetSpeed(0,0);
    MOTOR_SetSpeed(1,0);
}

/*
* @Nom : mouvement_Fin
* @Brief : retourne au départ
* @Entré : 
* @Sortie : 
*/
void mouvement::mouvement_Fin()
{
    bool Arrive(true);
    while(Arrive==false)
    {
        MOTOR_SetSpeed(0, moteur_g);
        MOTOR_SetSpeed(1, moteur_d);

        int capteurs = read();

        if(capteurs == 2)
        {
            avance();
        }
        else if (capteurs == 4)
        {
            alignement_d();
        }
        else if (capteurs == 1)
        {
            alignement_g();
        }
        else if (capteurs == 0)
        {
            MOTOR_SetSpeed(0,0);
            MOTOR_SetSpeed(1,0);
            Arrive=true;
            demiTour();
        }
    }
}
