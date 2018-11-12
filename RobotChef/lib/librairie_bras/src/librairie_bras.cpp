#include<LibRobus.h>

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