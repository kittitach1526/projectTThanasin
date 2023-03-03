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



};
extern wifi_lib w;
#endif