#ifndef display_box_H
#define display_box_H
#include <Arduino.h>
class display_box
{
    public:
        display_box();
        void intit_display();
        void show(int line,char *data_to_show);
        void clear();
        void drawStr(byte x,byte y,String data);

    private:


};
extern display_box oled;
#endif