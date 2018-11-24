#include <LibRobus.h>


#define calib true

#define capt_1 A9
#define capt_2 A11
#define capt_3 A12
#define NBR_INGREDIENT 1
#define Pain 0
#define Boulette 1
#define Fromage 2
#define Salade 3
#define Tomate 4
#define Sauce 5

/*  Stations:
    0 Pain
    1 Boulette
    2 Fromage
    3 Salade
    4 Tomate
    5 Sauce
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

        float vitesseRapide = 0.26;
        float vitesseLent = 0.15;

        bool flag = false;
        int station = -1;

        void calibration();
        int Read();

        void burger_1();
        void burger_2();
        void burger_3();

        void m_mouvement(int bonneStation);
        void avance();
        void alignement_d();
        void alignement_g();
        void mouvement_Station();
        void mouvement_Fin();
        
        bool detect_station(int bonneArret);
        void turn_Sort_station(bool direction);
        void turn_station(bool direction);
        void demiTour();
        
        void prendreIngredient();
        void lacherIngredient();
        void retourner();
        void allerPorter(bool direction);
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
        int capteurs = Read();

        if(capteurs == 2)//Est centre
        {
            flag = false;
            avance();
        }
        else if (capteurs == 4)//Est décalé vers la gauche
        {
            flag = false;
            alignement_d();
        }
        else if (capteurs == 1)//Est décalé vers la droite
        {
            flag = false;
            alignement_g();
        }
        else if (capteurs == 7 && flag == false)//Est à la ligne
        {
        {
            bool direction= bonneStation%2==0;
            flag = true;
            if(detect_station(floor((bonneStation)/2))==true)// le calcul traduit la station en nombre de ligne perpendiculaire
            {
                turn_station(direction);
                mouvement_Station();
                if(bonneStation<=NBR_INGREDIENT)         //Ingredient
                {
                    prendreIngredient();
                    allerPorter(direction);
                }
                /*else if (bonneStation==NBR_INGREDIENT) //Boulette
                {
                    prendreIngredient();
                    demiTour();
                    mouvement_Station();
                    turn_Sort_station(true);
                    MOTOR_SetSpeed(0,0.1);
                    MOTOR_SetSpeed(1,0.1);
                    delay(300);
                    m_mouvement(NBR_INGREDIENT+1);
                }
                else if (bonneStation==NBR_INGREDIENT+1) //Poele
                {
                    lacherIngredient();
                    delay(5000);
                    prendreIngredient();
                    lacherIngredient();
                    delay(5000);
                    prendreIngredient();
                    allerPorter(direction);
                }*/
                else                                     //Drop
                {
                    lacherIngredient();
                    retourner();
                }
            }
            else
            {
                avance();
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
int mouvement::Read()
{
    int retourn = 0;
    
    if (analogRead(capt_3) <= threshold_3)
        retourn += 1;
    if (analogRead(capt_2) <= threshold_2)
        retourn += 2;
    if (analogRead(capt_1) <= threshold_1)
        retourn += 4;

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
    Serial.print("\n\r");
    Serial.print("Avance");
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
    moteur_d = vitesseLent;
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
bool mouvement::detect_station(int bonneArret)
{
    //Augmente la station presente
    station++;
    if (station == bonneArret)
    //regarde s'il est a la station voulu
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
* @Nom : turn_Sort_station
* @Brief : tourne jusqu'à temps de voir une autre ligne
* @Entré : direction (1:gauche, 2:droite)
* @Sortie : 
*/
void mouvement::turn_Sort_station(bool direction)
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

    //avance un peu
    MOTOR_SetSpeed(0, vitesseLent);
    MOTOR_SetSpeed(1, vitesseLent);
    delay(350);
    //tourne pour ne plus voir la ligne
    MOTOR_SetSpeed(0, moteurGauche);
    MOTOR_SetSpeed(1, moteurDroit);
    delay(350);
    //tourne jusqu'a la prochaine ligne
    while(Read() != 2){}
}
/*
* @Nom : turn_station
* @Brief : tourne jusqu'à temps de voir une autre ligne
* @Entré : direction (1:gauche, 2:droite)
* @Sortie : 
*/
void mouvement::turn_station(bool direction)
{
    int moteurGauche;
    int moteurDroit;
    //regarde la direction a tourner
    if(direction)
    {
        moteurGauche=0;
        moteurDroit=vitesseLent;
        Serial.print("\n\r");
        Serial.print("Tourne Fini 1");
    }
    else
    {
        moteurGauche=vitesseLent;
        moteurDroit=0;
    }

    //avance un peu
    MOTOR_SetSpeed(0, vitesseLent);
    MOTOR_SetSpeed(1, vitesseLent);
    delay(350);
    //tourne pour ne plus voir la ligne
    MOTOR_SetSpeed(0, moteurGauche);
    MOTOR_SetSpeed(1, moteurDroit);
    delay(350);
    //tourne jusqu'a la prochaine ligne
    while(Read() != 7){}
}
/*
* @Nom : mouvement_Station
* @Brief : bouge jusqu'au bout de la station
* @Entré : 
* @Sortie : 
*/
void mouvement::mouvement_Station()
{
    //Avance jusqu'a ne plus voir de ligne
    while(Read()==7)
    {
        MOTOR_SetSpeed(0, vitesseLent);
        MOTOR_SetSpeed(1, vitesseLent);
    }
    //Avance à la prochaine ligne
    bool Arrive(true);
    while(Arrive==false)
    {
        MOTOR_SetSpeed(0, moteur_g);
        MOTOR_SetSpeed(1, moteur_d);
        int capteurs = Read();

        if(capteurs == 2)//Est centre
        {
            flag = false;
            avance();
        }
        else if (capteurs == 4)//Est décalé vers la gauche
        {
            flag = false;
            alignement_d();
        }
        else if (capteurs == 1)//Est décalé vers la droite
        {
            flag = false;
            alignement_g();
        }
        else if (capteurs == 7 && flag == false)//Est à la ligne
        {
            //Arrete
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
    pince(true);//ouvre
    delay(500);
    flip_bras(false);//vire le bras
    delay(500);
    flip_bras(true);//retourne le bras a sa position normal
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
    turn_Sort_station(false);//Retourne sur la ligne principal
    //réinitialise les variables pour la prochaine commande
    fini =true; 
    station = -1;
}

/*
* @Nom : allerPorter
* @Brief : Sort de la station et va à la chute
* @Entré : 
* @Sortie : 
*/
void mouvement::allerPorter(bool direction)
{
    demiTour();
    mouvement_Station();
    turn_Sort_station(direction);
    m_mouvement(NBR_INGREDIENT+2);//Avance a la chute
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
    while(Read()!=0)//Tourne jusqu'a ne plus voir de ligne
    {}
    while(Read()!=2)//Tourne jusqu'a voir une ligne centre
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

        int capteurs = Read();

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