#include "htttp_box.h"
#include <HTTPClient.h>
#include <Arduino_JSON.h>
http_box http_b;
HTTPClient http;
http_box::http_box()
{

}

void http_box::post(String name_index,String data)
{
    
    server_path = server_url+name_index+"?"+data;
    server_path.trim();
    http.begin(server_path.c_str());
    Serial.println("Send : "+server_path);
    http.end();

}

String http_box::recive()
{
    int httpResponseCode = http.GET();   
    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
        Serial.println(payload);
        return payload;
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        //return String(httpResponseCode);
    }
      // Free resources
    http.end();
}

String http_box::httpGETRequest(const char* serverName) {
    WiFiClient client;
    HTTPClient http;
        
    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName);
    
    // If you need Node-RED/server authentication, insert user and password below
    //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
    
    // Send HTTP POST request
    int httpResponseCode = http.GET();
    
    String payload = "{}"; 
    
    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();

    return payload;
}