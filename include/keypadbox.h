#ifndef keypadbox_H
#define keypadbox_H
#include <Arduino.h>
const byte ROWS = 4;
const byte COLS = 4;
class keypadbox
{
    public:
        void keypad();
        void beginkeypad();
        char readkeypad();
        String msg="";
        void test();


    private:



};
extern keypadbox kp;
#endif 