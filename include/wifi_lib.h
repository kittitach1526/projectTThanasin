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



    private :



};
extern wifi_lib w;
#endif