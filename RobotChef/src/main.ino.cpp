# 1 "c:\\users\\adam\\appdata\\local\\temp\\tmp_yzkzy"
#include <Arduino.h>
# 1 "C:/Users/Adam/P12-7detendus/RobotChef/src/main.ino"
# 25 "C:/Users/Adam/P12-7detendus/RobotChef/src/main.ino"
#include <librairie_bras.h>

#include <classControl.h>



classControl classcontrol;
# 47 "C:/Users/Adam/P12-7detendus/RobotChef/src/main.ino"
void setup();
void loop();
#line 47 "C:/Users/Adam/P12-7detendus/RobotChef/src/main.ino"
void setup()

{

  Serial.begin(9600);

  BoardInit();

  DisplayInit();

  calsscontrol.refresh_LCD();

}
# 75 "C:/Users/Adam/P12-7detendus/RobotChef/src/main.ino"
void loop()

{

  classcontrol.gestion_manette();

  delay(100);

}