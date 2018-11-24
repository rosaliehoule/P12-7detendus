/*
 * @Fichier : classControl.h
 * @Auteur : Adam Martineau
 * @Date : 1/dec/2018
 * @Bref : librairie pour controler et intéragire avec le robot
 * @Environnement : PlatformIO (visual studio code)
 * @Compilateur : c++
 * @Matériel : arduino mega 
 * @Revision : v2
 */

//INCLUDES
#include <LibRobus.h>
#include <avr/eeprom.h>

//DEFINES
#define capt_1 A9
#define capt_2 A11
#define capt_3 A12

//CLASS DEFINITION
class classControl
{
    public:
        //--- LISTES DES VAR GLOBAL ---// 
        bool is_menu_setup = false;//true: menu princ false: menu setup

        //index et structure du menu principal
        int index_menu = 1;
        char menu_main[6][20] = {"", "Burger", "Bacon Burger", "Cheese Burger", "Setup", ""};

        //index et structure du menu principal
        int index_setup = 1;
        char menu_setup[6][20] = {"", "Calibration", "Afficher valeur M.", "Credit", "Quiter", ""};

        //valeur de threshold de pour les detecteurs de ligne
        int threshold_1 = eeprom_read_byte((uint8_t *)1);
        int threshold_2 = eeprom_read_byte((uint8_t *)2);
        int threshold_3 = eeprom_read_byte((uint8_t *)3);

        //valeur pour les vitesses de moteurs
        //la vitesse des moteurs est modifier en 
        //modifiant ces valeurs
        float moteur_g = 0.1;
        float moteur_d = 0.1;

        //variable pour la gestion des stations
        bool flag = false;
        int station = 0;

        /// --- DÉPLACEMENT --- ///

        /*
        * @Nom : mouvement()
        * @Brief : fonction principal pour le déplacement du robot
        * @Entré : void
        * @Sortie : void
        */
        void mouvement();

        /*
        * @Nom : read()
        * @Brief : lit le capteur de ligne
        * @Entré : void
        * @Sortie : retourn une valeur binaire (de 000 a 111) le bit 001 corespond
        * au capteur a droite, 010 lui au centre et 100 lui a gauche. Donc une ligne 
        * perpandiculaire serais une valeur de 7 (111)
        */
        int read();

        /*
        * @Nom : avance()
        * @Brief : fait avence les deux moteurs à la meme vitesse
        * @Entré : void
        * @Sortie : void
        */
        void avance();

        /*
        * @Nom : alignement_d()
        * @Brief : fait avence le moteur de gauche plus rapidement pour 
        * retourne vers la droite
        * @Entré : void
        * @Sortie : void
        */
        void alignement_d();

        /*
        * @Nom : alignement_g
        * @Brief : fait avence le moteur de droite plus rapidement pour 
        * retourne vers la gauche
        * @Entré : void
        * @Sortie : void
        */
        void alignement_g();

        /*
        * @Nom : detect_station()
        * @Brief : fonction appele quand on detecte un station (ligne 
        * perpendiculaire) et fait les action aproprie
        * @Entré : void
        * @Sortie : void
        */
        void detect_station();

        /*
        * @Nom : turn_station()
        * @Brief : appele quand on detecte un station et qu'on veux tourne
        * a 90 degre pour aller rejoindre la station
        * @Entré : void
        * @Sortie : void
        */
        void turn_station();

        /// --- GESTION DE LA MANETTE ---///

        /*
        * @Nom : gestion_
        * @Brief :
        * @Entré : 
        * @Sortie : 
        */
        void gestion_manette();
        
        /*
        * @Nom : get_ir
        * @Brief : trete les donnes recu par le capteur infrarouge et retourne la commande
        * @Entré : void
        * @Sortie : un char qui décrie la commande recu
        */
        int get_ir();
        
        /// --- LCD REFRESH --- ///

        /*
        * @Nom : get_ir()
        * @Brief : fonction qui apelle soit la fonction la fonction 
        * refresh main ou refresh setup dépendant on est dans quelle menu
        * @Entré : void
        * @Sortie : void
        */
        void refresh_LCD();

        /*
        * @Nom : refresh_main()
        * @Brief : refresh l'affichage du menu quand on est dans le 
        * menu principal 
        * @Entré : void
        * @Sortie : void
        */
        void refresh_main();

        /*
        * @Nom : refresh_setup()
        * @Brief : refresh l'affichage du menu setup quand on est dans le 
        * menu principal 
        * @Entré : void
        * @Sortie : void
        */
        void refresh_setup();

        /// --- GESTION DES OPTION DE MENU --- ///

        /*
        * @Nom : menu_enter()
        * @Brief : fonction appele quand on detecte un «enter» pour le menu
        * @Entré : void
        * @Sortie : void
        */
        void menu_enter();

        /// --- ASSEMBLAGE DES BURGERS --- ///

        /*
        * @Nom : burger1()
        * @Brief : assemblage du burger 1
        * @Entré : void
        * @Sortie : void
        */
        void burger1();

        /*
        * @Nom : burger2()
        * @Brief : assemblage du burger 2
        * @Entré : void
        * @Sortie : void
        */
        void burger2();

        /*
        * @Nom : burger3()
        * @Brief : assemblage du burger 3
        * @Entré : void
        * @Sortie : void
        */
        void burger3();

        /// --- CALIBRATION --- ///

        /*
        * @Nom : calibration()
        * @Brief : fonction pour calibre les detecteur de ligne
        * @Entré : void
        * @Sortie : void
        */
        void calibration();

        /*
        * @Nom : print_values()
        * @Brief : print les valeur mediane de calibration enregistre dans 
        * la EEPROM
        * @Entré : void
        * @Sortie : void
        */
        void print_values();
};

//FONCTIONS DEFINITION
void classControl::gestion_manette()
{
    int remote = get_ir();

  //gestion de déplacement dans le menu
  if(remote == 2)
  {
    if (!is_menu_setup)
    {
        index_menu++;
        if(index_menu == 5)
        {
            index_menu = 1;
        }
    }
    else
    {
        index_setup++;
        if(index_setup == 5)
        {
            index_setup = 1;
        }
    }
    refresh_LCD();
  }
  else if(remote == 1)
  {
    if (!is_menu_setup)
    {
        index_menu--;
        if(index_menu == 0)
        {
            index_menu = 4;
        }
    }
    else
    {
        index_setup--;
        if(index_setup == 5)
        {
            index_setup = 5;
        }
    }
    refresh_LCD();
  }
  else if(remote == 0 || remote == 4)
  {
    menu_enter();
  }
}

int classControl::get_ir()
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

void classControl::refresh_LCD()
{
    if (!is_menu_setup)
        refresh_main();
    else
        refresh_setup();
}
void classControl::refresh_main()
{
    DISPLAY_Clear();
    DISPLAY_SetCursor(0,0);
    DISPLAY_Printf("  ");
    DISPLAY_Printf(menu_main[index_menu - 1]);
    DISPLAY_SetCursor(1,0);
    DISPLAY_Printf(">>");
    DISPLAY_Printf(menu_main[index_menu]);
    DISPLAY_SetCursor(2,0);
    DISPLAY_Printf("  ");
    DISPLAY_Printf(menu_main[index_menu + 1]);
}

void classControl::refresh_setup()
{
    DISPLAY_Clear();
    DISPLAY_SetCursor(0,0);
    DISPLAY_Printf("  ");
    DISPLAY_Printf(menu_setup[index_setup - 1]);
    DISPLAY_SetCursor(1,0);
    DISPLAY_Printf(">>");
    DISPLAY_Printf(menu_setup[index_setup]);
    DISPLAY_SetCursor(2,0);
    DISPLAY_Printf("  ");
    DISPLAY_Printf(menu_setup[index_setup + 1]);
}

void classControl::menu_enter()
{
    if(index_menu == 1 && !is_menu_setup)
        burger1();  

    else if(index_menu == 2 && !is_menu_setup)
        burger2();  

    else if(index_menu == 3 && !is_menu_setup)
        burger3();  

    else if(index_menu == 4 && !is_menu_setup)
    {
        index_menu = 1;
        is_menu_setup = !is_menu_setup;
        refresh_LCD();
    }
    else if(index_setup == 1 && is_menu_setup)
    {
        calibration();
    }
    else if(index_setup == 2 && is_menu_setup)
    {
        print_values();
    }
    else if(index_setup == 4 && is_menu_setup)
    {
        index_setup = 1;
        is_menu_setup = !is_menu_setup;
        refresh_LCD();
    }
}

void classControl::burger1()
{

}

void classControl::burger2()
{

}

void classControl::burger3()
{

}

void classControl::mouvement()
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

int classControl::read()
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

void classControl::avance()
{
    moteur_d = 0.1;
    moteur_g = 0.1;
}

void classControl::alignement_d()
{
    moteur_d = 0.1;
    moteur_g = 0.13;
}

void classControl::alignement_g()
{
    moteur_d = 0.13;
    moteur_g = 0.1;
}

void classControl::detect_station()
{
    station++;

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

void classControl::turn_station()
{
    MOTOR_SetSpeed(0, 0.1);
    MOTOR_SetSpeed(1, 0.1);
    delay(350);
    MOTOR_SetSpeed(0, 0);
    MOTOR_SetSpeed(1, 0.1);
    while(read() != 7){}
}

void classControl::calibration()
{
    DISPLAY_Clear();
    DISPLAY_SetCursor(0,0);
    DISPLAY_Printf("Calib. du noir");
    while(get_ir() != 0){}

    int a1 = analogRead(capt_1);
    int b1 = analogRead(capt_2);
    int c1 = analogRead(capt_3);

    DISPLAY_Clear();
    DISPLAY_SetCursor(0,0);
    DISPLAY_Printf("Calib. du blanc");
    while(get_ir() != 0){}

    int a2 = analogRead(capt_1);
    int b2 = analogRead(capt_2);
    int c2 = analogRead(capt_3);

    eeprom_write_byte((uint8_t *)1,(a1 + a2)/2);
    eeprom_write_byte((uint8_t *)2,(b1 + b2)/2);
    eeprom_write_byte((uint8_t *)3,(c1 + c2)/2);

    threshold_1 = eeprom_read_byte((uint8_t *)1);
    threshold_2 = eeprom_read_byte((uint8_t *)2);
    threshold_3 = eeprom_read_byte((uint8_t *)3);

    DISPLAY_Clear();
    DISPLAY_SetCursor(0,0);
    DISPLAY_Printf("Calib. effectue");

    delay(1500);
    refresh_LCD();
}

void classControl::print_values()
{
    DISPLAY_Clear();
    DISPLAY_SetCursor(0,0);
    DISPLAY_Printf((String) eeprom_read_byte((uint8_t *)1));
    DISPLAY_SetCursor(1,0);
    DISPLAY_Printf((String) eeprom_read_byte((uint8_t *)2));
    DISPLAY_SetCursor(2,0);
    DISPLAY_Printf((String) eeprom_read_byte((uint8_t *)3));
    while(get_ir() != 0){}
    refresh_LCD();
}