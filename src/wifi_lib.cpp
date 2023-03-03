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
            ssid.toCharArray(ssid_eeprom,20);
            writeString(ssid_eeprom,addresss_ssid_eeprom);
            Serial.println("\nset ssid = "+data_ssid[0]);
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
            password.toCharArray(password_eeprom,20);
            writeString(password_eeprom,address_password_eeprom);
        }
    }
    test_readeeprom_ssid = readStringFromFlash(addresss_ssid_eeprom);
    Serial.println("Read Flash ssid : "+test_readeeprom_ssid);
    test_readeeprom_password = readStringFromFlash(address_password_eeprom);
    Serial.println("Read Flash password :"+test_readeeprom_password);
    Serial.println("Select funtion complete !");
}

void wifi_lib::BeginEEP()
{
    EEPROM.begin(100);
}

void wifi_lib::writeString(const char* toStore, int startAddr)
{
    int i = 0;
    Serial.println(LENGTH(toStore));
    for (; i < LENGTH(toStore); i++) {
    EEPROM.write(startAddr + i, toStore[i]);
    Serial.print(toStore[i]);
    delay(100);
    EEPROM.commit();

    }
    Serial.println();
    EEPROM.write(startAddr + i, '\0');
    EEPROM.commit();
}

String wifi_lib::readStringFromFlash1(int startAddr,int length) 
{
    char in[128];
    char curIn;
    int i = 0;
    curIn = EEPROM.read(startAddr);
    for (; i < 128; i++) {
        curIn = EEPROM.read(startAddr + i);
        Serial.print(curIn);
        in[i] = curIn;
        if (curIn=='\0') break;
    }
    Serial.println();
    return String(in);
}

String wifi_lib::readStringFromFlash(int startAddr) 
{
    char in[128];
    char curIn;
    int i = 0;
    curIn = EEPROM.read(startAddr);
    for (; i < 128; i++) {
        curIn = EEPROM.read(startAddr + i);
        in[i] = curIn;
    }
    return String(in);
}

void wifi_lib::chech_eeprom_wifi()
{
    Serial.println("YOYOYO");
    writeString("Helld World", addresss_ssid_eeprom);
    test_readeeprom_ssid = readStringFromFlash1(addresss_ssid_eeprom,20);
    test_readeeprom_password = readStringFromFlash(address_password_eeprom);
    Serial.println("Check ssid = "+test_readeeprom_ssid);
    Serial.println("Check password = "+test_readeeprom_password);

    return;
    /*
    if(test_readeeprom_password == "")
    {
        Serial.println("No password on eeprom ! ");
    }
    if(test_readeeprom_ssid =="")
    {
        Serial.println("No ssid on eeprom ! ");
    }*/
    if((test_readeeprom_ssid  == "")||(test_readeeprom_password ==""))
    {
        searchWiFi();
    }
    else {
        int state_wifi = 0;
        if (state_wifi == 0)
        {
            Serial.println("Next ? 1(yes)/2(no want to clear wifi)");
            int data = 0;
            while(data == 0)
            {
                if(Serial.available()>0)
                {
                    data = Serial.read();
                }
            }
            switch(data)
            {
                case 1:
                    Serial.println("Next >>>> yes connect");
                    state_wifi =1;
                    break;
                case 2:
                    Serial.println("Next >>>> no Clear Wifi");
                    searchWiFi();
                    state_wifi =1;
                    break;
            }
        }
    }
}