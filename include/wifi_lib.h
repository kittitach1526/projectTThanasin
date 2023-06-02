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
        char select_wifi='e';
        String get_ssid_eep();
        String get_pass_eep();
        void setEEPwifi(String ssid,String password);
        void scanWiFi();
        void Select_wifi(char data);
        void connect_wifi_by_eep();

    private :
        int count_restart =0;
        char test_string[10]="hello";
        char read_eeprom[10];

        char ssid_eeprom[20];
        char password_eeprom[20];

        String result_get_ssid_eep ="";
        String result_get_pass_eep ="";





};
extern wifi_lib w;
#endif