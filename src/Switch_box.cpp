#include "Switch_box.h"
Switch_box swb;
Switch_box::Switch_box()
{

}

void Switch_box::setpin_switch(byte white_pin,byte blue_pin,byte yellow_pin)
{
    white_switch_pin = white_pin;
    blue_switch_pin = blue_pin;
    yellow_switch_pin = yellow_pin;

    pinMode(white_pin,INPUT_PULLUP);
    pinMode(blue_pin,INPUT_PULLUP);
    pinMode(yellow_pin,INPUT_PULLUP);
    Serial.println("setpin complete!");

}

byte Switch_box::read_blue_switch()
{
    if(digitalRead(blue_switch_pin)==0)
    {
        while(digitalRead(blue_switch_pin)==0)
        {
            result_blue_switch = 0;
            backup_result_blue_switch =0;
        }
        Serial.println("Status_Blue_Switch : pass! ="+String(result_blue_switch));
        return result_blue_switch;
    }
    else
    {
        result_blue_switch = 1;
        if(backup_result_blue_switch != result_blue_switch)
        {
            backup_result_blue_switch = result_blue_switch;
           // Serial.println("Status_Blue_Switch : "+String(result_blue_switch));
        }
        return result_blue_switch;
    }
}


byte Switch_box::read_yellow_switch()
{
    if(digitalRead(yellow_switch_pin)==0)
    {
        while(digitalRead(yellow_switch_pin)==0)
        {
            result_yellow_switch = 0;
            backup_result_yellow_switch =0;
        }
        Serial.println("Status_Yellow_Switch :  pass! ="+String(result_yellow_switch));
        return result_yellow_switch;
    }
    else
    {
        result_yellow_switch = 1;
        if(backup_result_yellow_switch != result_yellow_switch)
        {
            backup_result_yellow_switch = result_yellow_switch;
         //   Serial.println("Status_Yellow_Switch : "+String(result_yellow_switch));
        }
        return result_yellow_switch;
    }
}

byte Switch_box::read_white_switch()
{
    if(digitalRead(white_switch_pin)==0)
    {
        while(digitalRead(white_switch_pin)==0)
        {
            result_white_switch = 0; 
            backup_result_white_switch =0;
        }
        Serial.println("Status_White_Switch :  pass! ="+String(result_white_switch));
        return result_white_switch;
    }
    else
    {
        result_white_switch = 1;
        if(backup_result_white_switch != result_white_switch)
        {
            backup_result_white_switch = result_white_switch;
           // Serial.println("Status_White_Switch : "+String(result_white_switch));
        }
        return result_white_switch;
    }
}

void Switch_box::read_all_switch()
{
    status_all_switch[0] = read_white_switch();
    status_all_switch[1] = read_blue_switch();
    status_all_switch[2] = read_yellow_switch();
}

void Switch_box::test_white()
{
    if(digitalRead(white_switch_pin)==1 )
    {
        Serial.println("white sw : "+String(digitalRead(white_switch_pin)));
    }
    else{
        Serial.println("white sw : "+String(digitalRead(white_switch_pin)));
    }
}
void Switch_box::on_led()
{
    pinMode(13,OUTPUT);
    pinMode(14,OUTPUT);
    pinMode(26,OUTPUT);

    digitalWrite(13,HIGH);
    digitalWrite(14,HIGH);
    digitalWrite(26,HIGH);
    Serial.println("ON led switch1");
}