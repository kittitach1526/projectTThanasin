#include "wifi_lib.h"
#include "WiFi.h"
#include <EEPROM.h>

wifi_lib w;

#define LENGTH(x) (strlen(x) + 1)

wifi_lib::wifi_lib()
{

}

void wifi_lib::connect_wifi()
{
    Serial.println("Connecting to "+ssid+" now !");
    //BeginEEP();
    WiFi.begin(w.ssid.c_str(),w.password.c_str());
    while (WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
            Serial.print(".");
        }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: "+String(WiFi.localIP()));


}
void wifi_lib::searchWiFi()
{
    //Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    Serial.println("Setup done");
    Serial.println("scan start");

    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0) {
    Serial.println("no networks found");
    } 
    else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
        //Serial.print(i + 1);
        //Serial.print(": ");
        //Serial.print(WiFi.SSID(i));
        data_ssid[i]=WiFi.SSID(i);
        //Serial.print(" (");
        //Serial.print(WiFi.RSSI(i));
        //Serial.print(")");
        //Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
        delay(10);
    }
}
    Serial.println("");
    select_ssid();
}

void wifi_lib::select_ssid()
{
    
    for (int i=0;i<=5;i++){
        Serial.println(String(i+1)+"."+data_ssid[i]);
    }
    Serial.print("Select Wifi 1-5 : ");
    while(ssid ==""){
        
        if(Serial.available()>0)
        {
            char data = Serial.read();
            switch (data)
            {
            case '1':
            ssid= data_ssid[0];
            EEPROM.writeString(0,ssid);
            EEPROM.commit();
            Serial.println("\nset ssid = "+ssid);
                break;
            }
        }
        
    }
    Serial.print("Enter Password : ");
    while(password == "")
    {
        if(Serial.available()>0)
        {
            String data = Serial.readString();
            Serial.println("\npassword : "+data);
            password = data;
            EEPROM.writeString(32,password);
            EEPROM.commit();
        }
    }
    delay(1000);
    test_readeeprom_ssid = EEPROM.readString(0);
    Serial.println("Read Flash ssid : "+test_readeeprom_ssid);
    test_readeeprom_password = EEPROM.readString(32);
    Serial.println("Read Flash password :"+test_readeeprom_password);
    Serial.println("Select funtion complete !");
}

void wifi_lib::BeginEEP()
{
    EEPROM.begin(64);
}

void wifi_lib::check_eeprom_wifi()
{
    test_readeeprom_ssid = EEPROM.readString(0);
    test_readeeprom_password = EEPROM.readString(32);

    Serial.println("Check ssid = "+test_readeeprom_ssid);
    Serial.println("Check password = "+test_readeeprom_password);
    if((test_readeeprom_ssid  == "")||(test_readeeprom_password ==""))
    {
        searchWiFi();
    }
    else {
        int state_wifi = 0;
        if (state_wifi == 0)
        {
            Serial.print("Next ? 1(yes)/2(no want to clear wifi) : ");
            int data = 0;
            while(data == 0)
            {
                if(Serial.available()>0)
                {
                    String Read = Serial.readString();
                    data = Read.toInt();
                    Serial.println("data : "+String(data));
                }
            }
            switch(data)
            {
                case 1:
                    Serial.println("Next >>>> yes connect");
                    ssid = test_readeeprom_ssid;
                    password = test_readeeprom_password;
                    connect_wifi();
                    state_wifi =1;
                    break;
                case 2:
                    Serial.println("Next >>>> no Clear Wifi");
                    clearEEPROM();
                    searchWiFi();
                    connect_wifi();
                    state_wifi =1;
                    break;
            }
        }
    }
}

void wifi_lib::clearEEPROM()
{
    for (int i = 0; i < EEPROM.length(); i++) {
        EEPROM.write(i, 0xFF);
    }

  // Commit ?????????????????????????????????????????????????????????????????????????????? EEPROM
    EEPROM.commit();
    Serial.println("Claer EEPROM Complete !");
}