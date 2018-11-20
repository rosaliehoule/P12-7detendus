#include <LibRobus.h>

#define calib true

#define capt_1 A9
#define capt_2 A11
#define capt_3 A12

/*calibration des capteurs
 *	    blanc 	noir
 *   1	400     200
 *   2	360     200	
 *   3	170     100
 */

class mouvement
{
    public:
        int threshold_1 = 200;
        int threshold_2 = 200;
        int threshold_3 = 130;

        float moteur_g = 0.1;
        float moteur_d = 0.1;

        bool flag = false;
        int station = 0;

        void m_mouvement();
        int read();
        void avance();
        void alignement_d();
        void alignement_g();
        void detect_station();
        void turn_station();
        void calibration();
};

void mouvement::m_mouvement()
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
        detect_station();
    }
}

int mouvement::read()
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

void mouvement::avance()
{
    moteur_d = 0.1;
    moteur_g = 0.1;
}

void mouvement::alignement_d()
{
    moteur_d = 0.1;
    moteur_g = 0.13;
}

void mouvement::alignement_g()
{
    moteur_d = 0.13;
    moteur_g = 0.1;
}

void mouvement::detect_station()
{
    station++;
    
    //Serial.print("\n\r");
    //Serial.print(station);

    if (station == 1)
    {
        turn_station();
        avance();
    }
    else if (station == 2)
    {
        MOTOR_SetSpeed(0, 0);
        MOTOR_SetSpeed(1, 0);
        while(true){}
    }
}

void mouvement::turn_station()
{
    MOTOR_SetSpeed(0, 0.1);
    MOTOR_SetSpeed(1, 0.1);
    delay(350);
    MOTOR_SetSpeed(0, 0);
    MOTOR_SetSpeed(1, 0.1);
    while(read() != 7){}
}

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

    delay(15000);
}