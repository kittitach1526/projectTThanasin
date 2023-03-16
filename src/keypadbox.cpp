#include "keypadbox.h"
keypadbox kp;
#include <Keypad_I2C.h>
#include <Keypad.h>
#define I2CADDR 0x20
char keys[ROWS][COLS] = {
    {'D','C','B','A'},
    {'#','9','6','3'},
    {'0','8','5','2'},
    {'*','7','4','1'}
};

byte rowPins[ROWS] = {0, 1, 2, 3};
byte colPins[COLS] = {4, 5, 6, 7};

Keypad_I2C customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574 );

void keypadbox::keypad()
{

}

void keypadbox::beginkeypad()
{
    customKeypad.begin( );
}

String keypadbox::readkeypad()
{
    char customKey = customKeypad.getKey();
    //oled.drawStr(0,0,msg);
    if (customKey != NO_KEY)
    {
        Serial.println(customKey);
        msg += customKey;
        Serial.println(msg);
        //oled.drawStr(0,0,msg);
    }
}