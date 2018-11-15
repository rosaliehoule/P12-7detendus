// classControl.cpp

#include <LibRobus.h>

class classControl
{
    public:
        //--- LISTES DES VAR GLOBAL ---// 
        int etat_Affich = 0;
        char menu[4][20] = {"Burger", "Bacon Burger", "Cheese Burger", "Setup"};
    
        /// --- AFFICHAGE & MANETTE ---///
        void gestion_manette();
        /*
        * @Nom : get_ir
        * @Brief : trete les donnes recu par le capteur infrarouge et retourne la commande
        * @Entré : void
        * @Sortie : un char qui décrie la commande recu
        */
        int get_ir();

        /*
        * @Nom : 
        * @Brief :
        * @Entré : 
        * @Sortie : 
        */
        void refresh_LCD();

        /// --- BURGERS --- ///
        /*
        * @Nom : menu_enter
        * @Brief : 
        * @Entré : 
        * @Sortie : 
        */
        void menu_enter();

        /*
        * @Nom : 
        * @Brief :
        * @Entré : 
        * @Sortie : 
        */
        void burger1();

        /*
        * @Nom : 
        * @Brief :
        * @Entré : 
        * @Sortie : 
        */
        void burger2();

        /*
        * @Nom : 
        * @Brief :
        * @Entré : 
        * @Sortie : 
        */
        void burger3();
};

/// --- AFFICHAGE & MANETTE ---///
void classControl::gestion_manette()
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
}

/*
* @Nom : get_ir
* @Brief : trete les donnes recu par le capteur infrarouge et retourne la commande
* @Entré : void
* @Sortie : un char qui décrie la commande recu
*/
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

/*
* @Nom : 
* @Brief :
* @Entré : 
* @Sortie : 
*/
void classControl::refresh_LCD()
{
    DISPLAY_Clear();
    DISPLAY_SetCursor(0,0);
    DISPLAY_Printf(menu[etat_Affich]);
}

/// --- BURGERS --- ///
/*
* @Nom : menu_enter
* @Brief : 
* @Entré : 
* @Sortie : 
*/
void classControl::menu_enter()
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
void classControl::burger1()
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
void classControl::burger2()
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
void classControl::burger3()
{
    Serial.print("\n\r");
    Serial.print("creation du burger3");
}