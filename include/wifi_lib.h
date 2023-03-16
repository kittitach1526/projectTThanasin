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
        String data_ssid[20];
        void select_ssid();
        char read_ssid_eeprom[20];
        char read_password_eeprom[20];
        void BeginEEP();
        String test_readeeprom_ssid="";
        String test_readeeprom_password ="";
        byte addresss_ssid_eeprom = 0;
        byte address_password_eeprom = 50;
        void check_eeprom_wifi();
        void clearEEPROM();

    private :
        
        char test_string[10]="hello";
        char read_eeprom[10];

        char ssid_eeprom[20];
        char password_eeprom[20];






};
extern wifi_lib w;
#endif