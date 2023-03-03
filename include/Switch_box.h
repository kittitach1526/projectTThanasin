#ifndef Switch_box_H
#define Switch_box_H
#include <Arduino.h>
class Switch_box
{
    public:
        Switch_box();
        void setpin_switch(byte white_pin,byte blue_pin,byte yellow_pin);
        void read_all_switch();

        byte white_switch_pin;
        byte blue_switch_pin;
        byte yellow_switch_pin;

        byte read_white_switch();
        byte read_blue_switch();
        byte read_yellow_switch();

        void test_white();
        void on_led();

        byte result_yellow_switch;
        byte result_blue_switch;
        byte result_white_switch;

        byte backup_result_blue_switch=0;
        byte backup_result_white_switch=0;
        byte backup_result_yellow_switch=0;

        byte status_all_switch[];


    private:

};
extern Switch_box swb;
#endif