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
#define NBR_INGREDIENT 1
#define Pain 2
#define Fromage 3
#define Salade 4
#define Boulette 3
#define Poele 6
#define Drop 7

//CLASS DEFINITION
class classControl
{
    public:
        //--- LISTES DES VAR GLOBAL ---// 
        bool is_menu_setup = false;//true: menu princ false: menu setup

        //index et structure du menu principal
        int index_menu = 1;
        char menu_main[6][20] = {"", "PATE DE CRABE", "COMBO CROUSTILLANT", "CRABE DELUXE", "Setup", ""};

        //index et structure du menu principal
        int index_setup = 1;
        char menu_setup[6][20] = {"", "Calibration", "Afficher valeur M.", "Debuging", "Quitter", ""};

        //valeur de threshold de pour les detecteurs de ligne
        int threshold_1 = eeprom_read_byte((uint8_t *)1) * 5;
        int threshold_2 = eeprom_read_byte((uint8_t *)2) * 5;
        int threshold_3 = eeprom_read_byte((uint8_t *)3) * 5;

        //valeur pour les vitesses de moteurs
        //la vitesse des moteurs est modifier en 
        //modifiant ces valeurs
        float moteur_g = 0.1;
        float moteur_d = 0.1;

        //variable pour la gestion des stations
        bool flag = false;
        bool fini = false;
        int station = -1;

        /// --- DÉPLACEMENT --- ///

        /*
        * @Nom : mouvement()
        * @Brief : fonction principal pour le déplacement du robot
        * @Entré : void
        * @Sortie : void
        */
        void mouvement(int bonneStation);

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
        bool detect_station(int bonneStation);

        /*
        * @Nom : turn_station()
        * @Brief : appele quand on detecte un station et qu'on veux tourne
        * a 90 degre pour aller rejoindre la station
        * @Entré : void
        * @Sortie : void
        */
        void turn_Sort_station(bool direction);

        /*
        * @Nom : turn_station()
        * @Brief : appele quand on detecte un station et qu'on veux tourne
        * a 90 degre pour aller rejoindre la station
        * @Entré : void
        * @Sortie : void
        */
        void turn_station(bool direction);
        /*
        * @Nom : mouvement_Station()
        * @Brief : suit la ligne jusqu'a la prochaine ligne perpendiculaire
        * @Entré : void
        * @Sortie : void
        */
        void mouvement_Station();
       
        /*
        * @Nom : mouvement_Fin()
        * @Brief : suit la ligne jusqu'a ce qu'elle n'existe plus
        * @Entré : void
        * @Sortie : void
        */
        void mouvement_Fin();
        
        /*
        * @Nom : demiTour()
        * @Brief : Fait un demi-tour 
        * @Entré : void
        * @Sortie : void
        */
        void demiTour(bool direction); 
        
        /*
        * @Nom : quartTour(bool)
        * @Brief : fait un quart de tour du sens voulu 
        * @Entré : indique la direction a tourner
        * @Sortie : void
        */
        void quartTour(bool direction);
       
        /*
        * @Nom : prendreIngredient()
        * @Brief : Prend les ingredients 
        * @Entré : void
        * @Sortie : void
        */
        void prendreIngredient();
        /*
        * @Nom : lacherIngredient()
        * @Brief : Laisse tomber l'ingredient 
        * @Entré : void
        * @Sortie : void
        */
        void lacherIngredient();
        
        /*
        * @Nom : retourner()
        * @Brief : retourne à sa position initial
        * @Entré : void
        * @Sortie : void
        */
        void retourner();
        
        /*@Nom : allerPorter(bool)
        * @Brief : envoi les ingredients a la drop 
        * @Entré : indique la direction qu'il doit aller
        * @Sortie : void
        */
        void allerPorter(bool direction);
        
        /*
        * @Nom : bouletteStation()
        * @Brief : Handle la boulette de son arrivé au poele a la drop
        * @Entré : void
        * @Sortie : void
        */
        void bouletteStation();

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
    else if(index_setup == 3 && is_menu_setup)
    {
        while(true)
        {
            DISPLAY_Clear();
            DISPLAY_SetCursor(0,0);
            DISPLAY_Printf((String) read());
            delay(500);
        }
    }
    else if(index_setup == 4 && is_menu_setup)
    {
        index_setup = 1;
        is_menu_setup = !is_menu_setup;
        refresh_LCD();
    }
}

void classControl::print_values()
{
    DISPLAY_Clear();
    DISPLAY_SetCursor(0,0);
    DISPLAY_Printf("Cap1:");
    DISPLAY_Printf((String) (eeprom_read_byte((uint8_t *)1) * 5));
    DISPLAY_SetCursor(1,0);
    DISPLAY_Printf("Cap2:");
    DISPLAY_Printf((String) (eeprom_read_byte((uint8_t *)2) * 5));
    DISPLAY_SetCursor(2,0);
    DISPLAY_Printf("Cap3:");
    DISPLAY_Printf((String) (eeprom_read_byte((uint8_t *)3) * 5));
    while(get_ir() != 0){}
    refresh_LCD();
}

void classControl::calibration()
{
    DISPLAY_Clear();
    DISPLAY_SetCursor(0,0);
    DISPLAY_Printf("Calib. du noir");

    while(get_ir() != 0){}
    DISPLAY_Clear();
    DISPLAY_SetCursor(0,0);

    int a1 = analogRead(capt_1);
    int b1 = analogRead(capt_2);
    int c1 = analogRead(capt_3);

    DISPLAY_Printf("Cap1:");
    DISPLAY_Printf((String) a1);
    DISPLAY_SetCursor(1,0);
    DISPLAY_Printf("Cap2:");
    DISPLAY_Printf((String) b1);
    DISPLAY_SetCursor(2,0);
    DISPLAY_Printf("Cap3:");
    DISPLAY_Printf((String) c1);

    while(get_ir() != 0){}
    DISPLAY_Clear();
    DISPLAY_SetCursor(0,0);

    DISPLAY_Printf("Calib. du blanc");

    while(get_ir() != 0){}
    DISPLAY_Clear();
    DISPLAY_SetCursor(0,0);

    int a2 = analogRead(capt_1);
    int b2 = analogRead(capt_2);
    int c2 = analogRead(capt_3);

    DISPLAY_Printf("Cap1:");
    DISPLAY_Printf((String) a2);
    DISPLAY_SetCursor(1,0);
    DISPLAY_Printf("Cap2:");
    DISPLAY_Printf((String) b2);
    DISPLAY_SetCursor(2,0);
    DISPLAY_Printf("Cap3:");
    DISPLAY_Printf((String) c2);

    while(get_ir() != 0){}
    DISPLAY_Clear();
    DISPLAY_SetCursor(0,0);

    int a = a1 + a2;
    a = a / 2;
    int b = b1 + b2;
    b = b / 2;
    int c = c1 + c2;
    c = c / 2;

    DISPLAY_Printf("Thr1:");
    DISPLAY_Printf((String) a);
    DISPLAY_SetCursor(1,0);
    DISPLAY_Printf("Thr2:");
    DISPLAY_Printf((String) b);
    DISPLAY_SetCursor(2,0);
    DISPLAY_Printf("Thr3:");
    DISPLAY_Printf((String) c);

    while(get_ir() != 0){}
    DISPLAY_Clear();
    DISPLAY_SetCursor(0,0);

    eeprom_write_byte((uint8_t *)1, a / 5);
    eeprom_write_byte((uint8_t *)2, b / 5);
    eeprom_write_byte((uint8_t *)3, c / 5);

    threshold_1 = eeprom_read_byte((uint8_t *)1) * 5;
    threshold_2 = eeprom_read_byte((uint8_t *)2) * 5;
    threshold_3 = eeprom_read_byte((uint8_t *)3) * 5;

    DISPLAY_Printf("Calib. effectue");

    delay(1500);
    refresh_LCD();
}

void classControl::burger1()
{
    mouvement(Pain);
    fini=false;
    mouvement(Boulette);
    fini=false;
    mouvement(Pain);
    fini=false;
}

void classControl::burger2()
{
    mouvement(Pain);
    fini=false;
    mouvement(Boulette);
    fini=false;
    mouvement(Pain);
    fini=false;
}

void classControl::burger3()
{
   mouvement(Pain);
    fini=false;
    mouvement(Boulette);
    fini=false;
    mouvement(Boulette);
    fini=false;
    mouvement(Pain);
    fini=false;
}

void classControl::mouvement(int bonneStation)
{
    while(!fini)
    {
         //diagnostique
        MOTOR_SetSpeed(0, moteur_g);
        MOTOR_SetSpeed(1, moteur_d);
        int capteurs = read();

        if(capteurs == 2)//Est centre
        {
            flag = false;
            avance();
        }
        else if (capteurs == 6||capteurs==4)//Est décalé vers la gauche
        {
            flag = false;
            alignement_d();
        }
        else if (capteurs == 3||capteurs==1)//Est décalé vers la droite
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
                    if(bonneStation<5&&bonneStation!=Boulette)         //Ingredients
                    {
                        prendreIngredient();
                        allerPorter(direction);
                    }
                    else if(bonneStation==Boulette)         //Boulette
                    {
                        prendreIngredient();
                        demiTour(true);
                        mouvement_Station();
                        turn_Sort_station(direction);
                        mouvement(Poele);
                    }
                    else if (bonneStation==Poele) //Poele
                    {
                        bouletteStation();
                    }
                    else if(bonneStation==Drop)  //Drop
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

void classControl::avance()
{
    moteur_d = 0.2;
    moteur_g = 0.2;
}

void classControl::alignement_d()
{
    moteur_d = 0.13;
    moteur_g = 0.2;
}

void classControl::alignement_g()
{
    moteur_d = 0.2;
    moteur_g = 0.13;
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

bool classControl::detect_station(int bonneStation)
{
    station++;
    if (station == bonneStation)
    //regarde s'il est a la station voulu
    {
        return true;
    }
    else
    {
        return false;
    }
}

void classControl::turn_station(bool direction)
{
    if(direction)
    {
        moteur_g=0;
        moteur_d=0.2;
    }
    else
    {
        moteur_g=0.2;
        moteur_d=0;
    }

    //avance un peu
    MOTOR_SetSpeed(0, 0.2);
    MOTOR_SetSpeed(1, 0.2);
    delay(250);
    //tourne pour ne plus voir la ligne
    MOTOR_SetSpeed(0, moteur_g);
    MOTOR_SetSpeed(1, moteur_d);
    delay(350);
    //tourne jusqu'a la prochaine ligne
    while(read() != 7){}
}

void classControl::turn_Sort_station(bool direction)
{
    //avance un peu
    MOTOR_SetSpeed(0, 0.2);
    MOTOR_SetSpeed(1, 0.2);
    while(read()!=0){}
    
    while(read()!=7){}
    delay(150);
    //tourne d'un quart de tour
    quartTour(direction);
}

void classControl::prendreIngredient()
{
    pince(false);
    delay(500);
}

void classControl::lacherIngredient()
{
    pince(true);//ouvre
    delay(500);
    flip_bras(false);//vire le bras
    delay(800);
    flip_bras(true);//retourne le bras a sa position normal
    delay(500);
}

void classControl::retourner()
{
    demiTour(true);
    mouvement_Station();
    turn_Sort_station(true);
    mouvement_Fin();//Retourne sur la ligne principal
    demiTour(true);
    //réinitialise les variables pour la prochaine commande
    fini =true; 
    station = -1;

}

void classControl::allerPorter(bool direction)
{
    demiTour(true);
    mouvement_Station();
    turn_Sort_station(direction);
    mouvement(Drop);//Avance a la chute
}

void classControl::demiTour(bool direction)
{
    MOTOR_SetSpeed(direction,-0.15);
    MOTOR_SetSpeed(!direction,-0.15);
    delay(750);
    ENCODER_Reset(!direction);
    ENCODER_Reset(direction);
  while(89>ENCODER_Read(!direction)*0.023038563||-89<ENCODER_Read(direction)*0.023038563)
  {
    if(89>ENCODER_Read(!direction)*0.023038563)//tourne le moteur 1 tant qu'il ne fait pas 90 degree
    {
      MOTOR_SetSpeed(!direction,0.15);
    }
    else
      MOTOR_SetSpeed(!direction,0);
    if(-89<ENCODER_Read(direction)*0.023038563)//tourne le moteur 0 tant qu'il ne fait pas 90 degree
    {
      MOTOR_SetSpeed(direction,-0.1495);
    }
    else
      MOTOR_SetSpeed(direction,0);
  }
  MOTOR_SetSpeed(direction,0);
  MOTOR_SetSpeed(!direction,0);
}

void classControl::quartTour(bool direction)
{
    ENCODER_Reset(direction);
    ENCODER_Reset(!direction);
  while(42>ENCODER_Read(direction)*0.023038563||-42<ENCODER_Read(!direction)*0.023038563)
  {
    if(42>ENCODER_Read(direction)*0.023038563)//tourne le moteur tant qu'il ne fait pas 45 degree
    {
      MOTOR_SetSpeed(direction,0.15);
    }
    else
      MOTOR_SetSpeed(direction,0);
    if(-42<ENCODER_Read(!direction)*0.023038563)//tourne le moteur tant qu'il ne fait pas 45 degree
    {
      MOTOR_SetSpeed(!direction,-0.1495);
    }
    else
      MOTOR_SetSpeed(!direction,0);
  }
}

void classControl::mouvement_Fin()
{
    mouvement_Station();
     bool Arrive=false;
    while(Arrive==false)
    {
        MOTOR_SetSpeed(0, moteur_g);
        MOTOR_SetSpeed(1, moteur_d);
        int capteurs = read();

        if(capteurs == 2)//Est centre
        {
            flag = false;
            avance();
        }
        else if (capteurs == 6||capteurs==4)//Est décalé vers la gauche
        {
            flag = false;
            alignement_d();
        }
        else if (capteurs == 3||capteurs==1)//Est décalé vers la droite
        {
            flag = false;
            alignement_g();
        }
        else if (capteurs == 7 && flag == false)//Est à la ligne
        {
            station--;
            if(station==-1)
            {
                MOTOR_SetSpeed(0, 0.15);
                MOTOR_SetSpeed(1, 0.15);
                delay(2000);
                Arrive=true;
            }
            flag =true;
        }
    }
}

void classControl::mouvement_Station()
{
    //Avance jusqu'a ne plus voir de ligne
    while(read()==7)
    {
        MOTOR_SetSpeed(0, 0.1);
        MOTOR_SetSpeed(1, 0.1);
    }
    delay(200);
    //Avance à la prochaine ligne
    bool Arrive(false);
    while(Arrive==false)
    {
        MOTOR_SetSpeed(0, moteur_g);
        MOTOR_SetSpeed(1, moteur_d);
        int capteurs = read();

        if(capteurs == 2)//Est centre
        {
            flag = false;
            avance();
        }
        else if (capteurs == 6||capteurs==4)//Est décalé vers la gauche
        {
            flag = false;
            alignement_d();
        }
        else if (capteurs == 3||capteurs==1)//Est décalé vers la droite
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

void classControl::bouletteStation()
{
    pince(true);//ouvre
    delay(500);
    flip_bras(false);//flip le bras
    MOTOR_SetSpeed(1,-0.15);//recule pendant 1.5 sec
    MOTOR_SetSpeed(0,-0.15);
    delay(1500);
    MOTOR_SetSpeed(1,0);//arrete
    MOTOR_SetSpeed(0,0);
    flip_bras(true);//retourne son bras inferieur a la position normal
    delay(5000); //Attend 5 secondes
    mouvement_Station();//revient à la ligne
    delay(500);
    flip_bras(false);//flip le bras
    delay(500);
    MOTOR_SetSpeed(1,-0.15);//recule pendant 1.5 sec
    MOTOR_SetSpeed(0,-0.15);
    delay(1500);
    MOTOR_SetSpeed(1,0);//arrete
    MOTOR_SetSpeed(0,0);
    flip_bras(true);//retourne son bras inferieur a la position normal
    delay(5000);   //Attend 5 secondes
    mouvement_Station();
    prendreIngredient();
    demiTour(false);  //Retourne
    MOTOR_SetSpeed(0,0.15);
    MOTOR_SetSpeed(1,0.15);
    while(read()==7)
    delay(100);
    while(read()!=7){}
    while(read()==7)
    delay(100);
    while(read()!=7){}//bouge a la ligne de fin de la poele
    while(read()==7)
    delay(100);
    while(read()!=7){}
    mouvement_Station();//bouge a la drop
    lacherIngredient();
    retourner();
}