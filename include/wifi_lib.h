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
        char read_ssid_eeprom[20];
        char read_password_eeprom[20];
        void BeginEEP();
        void writeString(const char* toStore, int startAddr);
        String readStringFromFlash(int startAddr);
        String readStringFromFlash1(int startAddr,int length);
        String test_readeeprom_ssid="";
        String test_readeeprom_password ="";
        byte addresss_ssid_eeprom = 0;
        byte address_password_eeprom = 20;
        void chech_eeprom_wifi();
        void clearEEPROM();

    private :
        
        char test_string[10]="hello";
        char read_eeprom[10];

        char ssid_eeprom[20];
        char password_eeprom[20];






};
extern wifi_lib w;
#endif