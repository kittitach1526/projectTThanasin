#ifndef wifi_lib_H
#define wifi_lib_H

#include <Arduino.h>

class wifi_lib
{
    public :
        wifi_lib();
        void connect_wifi();
        String ssid ="";
        String password ="";
        void searchWiFi();
        String data_ssid[10];
        void select_ssid();

    private :
        void BeginEEP();
        char test_string[10]="hello";
        char read_eeprom[10];



};
extern wifi_lib w;
#endif