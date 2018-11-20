# 1 "c:\\users\\adam\\appdata\\local\\temp\\tmpafb3y_"
#include <Arduino.h>
# 1 "C:/Users/Adam/P12-7detendus/RobotChef/src/main.ino"
# 25 "C:/Users/Adam/P12-7detendus/RobotChef/src/main.ino"
#include <librairie_bras.h>

#include <classControl.h>

#include <mouvement.h>



classControl classcontrol;

mouvement move;
# 51 "C:/Users/Adam/P12-7detendus/RobotChef/src/main.ino"
void setup();
void loop();
#line 51 "C:/Users/Adam/P12-7detendus/RobotChef/src/main.ino"
void setup()

{

  Serial.begin(9600);

  BoardInit();

  DisplayInit();

  classcontrol.refresh_LCD();



  pince(true);

  flip_bras(true);



  delay(5000);

  move.calibration();

}
# 91 "C:/Users/Adam/P12-7detendus/RobotChef/src/main.ino"
void loop()

{

  move.m_mouvement();

  classcontrol.gestion_manette();

  delay(25);

}