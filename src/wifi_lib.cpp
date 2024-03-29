#include "wifi_lib.h"
#include "WiFi.h"
#include <EEPROM.h>
#include "display_box.h"
#include "keypadbox.h"
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
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void wifi_lib::connect_wifi_by_eep()
{
    w.ssid = get_ssid_eep();
    w.password = get_pass_eep(); 
    Serial.println("ssid connect eep :"+w.ssid);
    Serial.println("password connect eep :"+w.password);
    WiFi.begin(w.ssid.c_str(),w.password.c_str());
    while (WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
            count_restart +=1;
            Serial.print(".");
            if(count_restart > 15 )
            {
                Serial.println("restart !");
                ESP.restart(); 
            }
        }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void wifi_lib::searchWiFi()
{
    //Serial.begin(115200);
   // WiFi.mode(WIFI_STA);
   // WiFi.mode(WIFI_MODE_APSTA);
    WiFi.disconnect();
    delay(100);
    Serial.println("Setup done");
    Serial.println("scan start");
    //oled.show(1," Scan WiFi ...");
    int n = WiFi.scanNetworks();
    //oled.clear();
    Serial.println(" scan done");
    //oled.show(1," Scan done");
    delay(1000);
    //oled.clear();

    if (n == 0) {
    Serial.println("no networks found");
    } 
    else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < 5; ++i) {
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
    Serial.println("Search wifi complete !");
    //select_ssid();
}

void wifi_lib::scanWiFi()
{
    searchWiFi();
    oled.clear();
    for (int i=0;i<4;i++){
        Serial.println(String(i+1)+"."+data_ssid[i]);
        String result_to_show = String(i+1)+"."+data_ssid[i];
        oled.showString(i+1,result_to_show);
    }
}

void wifi_lib::Select_wifi(char data)
{
        switch (data)
            {
            case '1':
                ssid= data_ssid[0];
                EEPROM.writeString(0,ssid);
                EEPROM.commit();
                Serial.println("\nset ssid = "+ssid);
                break;
            case '2':
                ssid= data_ssid[1];
                EEPROM.writeString(0,ssid);
                EEPROM.commit();
                Serial.println("\nset ssid = "+ssid);
                break;
            case '3':
                ssid= data_ssid[2];
                EEPROM.writeString(0,ssid);
                EEPROM.commit();
                Serial.println("\nset ssid = "+ssid);
                break;
            case '4':
                ssid= data_ssid[3];
                EEPROM.writeString(0,ssid);
                EEPROM.commit();
                Serial.println("\nset ssid = "+ssid);
                break;
            }
}

void wifi_lib::select_ssid()
{
    
    for (int i=0;i<5;i++){
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
            case '2':
                ssid= data_ssid[1];
                EEPROM.writeString(0,ssid);
                EEPROM.commit();
                Serial.println("\nset ssid = "+ssid);
                break;
            case '3':
                ssid= data_ssid[2];
                EEPROM.writeString(0,ssid);
                EEPROM.commit();
                Serial.println("\nset ssid = "+ssid);
                break;
            case '4':
                ssid= data_ssid[3];
                EEPROM.writeString(0,ssid);
                EEPROM.commit();
                Serial.println("\nset ssid = "+ssid);
                break;
            case '5':
                ssid= data_ssid[4];
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
    //oled.show(1," check eeprom..");
    EEPROM.begin(64);
    delay(1000);
    Serial.println("Begin EEP complete");
    //oled.clear();
}

void wifi_lib::check_eeprom_wifi()
{
    oled.clear();
    oled.show(1," Check WiFi ...");
    delay(1000);
    test_readeeprom_ssid = EEPROM.readString(0);
    test_readeeprom_password = EEPROM.readString(32);
    //EEPROM.get(0,test_readeeprom_ssid);
    //EEPROM.get(32,test_readeeprom_password);
    Serial.println(" Check ssid = "+test_readeeprom_ssid);
    Serial.println(" Check password = "+test_readeeprom_password);
    oled.clear();
    oled.showString(1," ssid : "+test_readeeprom_ssid);
    oled.showString(2," pass : "+test_readeeprom_password);
    //delay(1000);

    if((test_readeeprom_ssid  == "")||(test_readeeprom_password ==""))
    {
        searchWiFi();
        connect_wifi();
    }
    else {
        int state_wifi = 0;
        if (state_wifi == 0)
        {
            //oled.clear();
            oled.showString(3,"1.connect this wifi");
            oled.showString(4,"2.change wifi");
            Serial.print("Next ? 1(yes)/2(no want to clear wifi) : ");
            Serial.print("select : ");
            Serial.println(select_wifi);
            while(select_wifi == 'e')
            {
                select_wifi = kp.readkeypad();
            }
            Serial.print("\nSelect wifi : ");
            Serial.println(select_wifi);
            switch(select_wifi)
            {
                case '1':
                    oled.clear();
                    oled.showString(1," ok connect wifi..");
                    Serial.println("Next >>>> yes connect");
                    ssid = test_readeeprom_ssid;
                    password = test_readeeprom_password;
                    connect_wifi();
                    oled.clear();
                    oled.showString(1,"Connect complete!");
                    delay(1000);
                    oled.clear();
                    state_wifi =1;
                    break;
                case '2':
                    Serial.println("Next >>>> no Clear Wifi");
                    oled.clear();
                    oled.showString(1," ok clear EEPROM");
                    clearEEPROM();
                    searchWiFi();
                    connect_wifi();
                    state_wifi =1;
                    delay(1000);
                    oled.clear();
                    break;
                default:
                    select_wifi ='e';
                    oled.clear();
                    oled.showString(1,"Try Again !!");
                    delay(2000);
                    oled.clear();
                    oled.showString(3,"1.connect this wifi");
                    oled.showString(4,"2.change wifi");
                    Serial.println("Try Again!! ");
            }

            //int data = 0;
            /*
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
            }*/
        }
    }
}

void wifi_lib::clearEEPROM()
{
    for (int i = 0; i < EEPROM.length(); i++) {
        EEPROM.write(i, 0xFF);
    }

  // Commit ข้อมูลเพื่อเขียนข้อมูลลงใน EEPROM
    EEPROM.commit();
    Serial.println("Claer EEPROM Complete !");
}

String wifi_lib::get_ssid_eep()
{
    result_get_ssid_eep = EEPROM.readString(0);
    Serial.println("result_ssid_eep : "+result_get_ssid_eep);
    return result_get_ssid_eep;
}
String wifi_lib::get_pass_eep()
{
    result_get_pass_eep = EEPROM.readString(32);
    Serial.println("result_pass_eep : "+result_get_pass_eep );
    return result_get_pass_eep;
}

void wifi_lib::setEEPwifi(String ssid,String passwrod)
{
    EEPROM.writeString(0,ssid);
    EEPROM.commit();
    EEPROM.writeString(32,password);
    EEPROM.commit();
    Serial.println("setEEP complete!");
}