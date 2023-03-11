#ifndef http_box_H
#define http_box_H
#include <Arduino.h>
class http_box
{
    public:
        http_box();
        String server_url = "";
        String server_path = "";
        void post(String name_index,String data);
        String recive();
        String payload = "";
        String sensorReadings;
        float sensorReadingsArr[3];
        String readJson();
        



    private:
        String httpGETRequest(const char* serverName);


};
extern http_box http_b;
#endif