#include <Arduino.h>
#include "wifi_lib.h"
#include "Switch_box.h"
#include "display_box.h"
#include <Wire.h>
#include "rfid_state.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
//#include <rdm6300.h>
//#define RDM6300_RX_PIN  16
//Rdm6300 rdm6300;
String msg = " Code :";
byte state=0;
String getdataJson(String key_search);
#include <Keypad_I2C.h>
#include <Keypad.h>
#include <Wire.h>
HTTPClient http;
#define I2CADDR 0x20

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
    {'D','C','B','A'},
    {'#','9','6','3'},
    {'0','8','5','2'},
    {'*','7','4','1'}
};

byte rowPins[ROWS] = {0, 1, 2, 3};
byte colPins[COLS] = {4, 5, 6, 7};

Keypad_I2C customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574 );
/*
  w = wifi_lib.h
  http_b = htttp_box.h
  key = keypad_box.h
  swb = switch_box.h
  blue switch pin = 27;
  yellow switch pin = 12;
  white switch pin = 25;
  oled = display_box.h
*/
String serverUrl ="https://bunnam.com/projects/majorette_pp/update/quit_v3.php?id_mc=02-02&id_rfid=0004953220&id_activity=4539&activity_type=1&no_send=1&no_pulse1=300&no_pulse2=1&no_pulse3=100&multiplier=1";

void setup() {
  Wire.begin();
  Serial.begin(9600);
  //w.ssid = "Best&Man_2.4G-wlan";
  //w.password ="best5261";
  //w.connect_wifi();
  //w.ssid = "Best&Man_2.4G-wlan";
  //w.password = "best5261";
  //customKeypad.begin( );
  //swb.setpin_switch(25,27,12);//w,b,y
  //oled.intit_display();
  Serial.println("\nVersion : 0.6 state ");
  //test-3-
  w.BeginEEP();
  //w.clearEEPROM();
  w.check_eeprom_wifi();
  //w.searchWiFi();
  //swb.on_led();
  //rf_st.Init_rfid();
  //w.searchWiFi();
  //w.connect_wifi();
  //oled.show(1," Code by Glenda");
  //rdm6300.begin(RDM6300_RX_PIN);
  //rf_st.Init_rfid();
  Serial.println("All Setup Complete!"); 
  state =0;
}

void loop() { 
  
  String keydata = getdataJson("code");
  Serial.println("code : "+keydata);

  delay(5000);
}

String getdataJson(String key_search)
{
  http.begin(serverUrl);
  int httpResponseCode = http.GET();

  if (httpResponseCode == 200) {
    String payload = http.getString();
    Serial.print("Json : ");
    Serial.println(payload);

    // Parse JSON object
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return "error";
      //return;
    }
    // Extract values
    //const char* title = doc["title"];
    //bool completed = doc["completed"];
    String getdata = doc[key_search];
    Serial.println("Value frome key : "+getdata);
    return getdata;
  } 
  else {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}

  //rf_st.read_rfid();
  //Serial.print("RFID : ");
  //Serial.println(rf_st.result_rfid);
  //delay(500);


  /*
  if(state == 0)
  {
    while (Serial.available()<= 0 )
    {
        Serial.println(" Enter RFID : ");
        delay(5000);
    }
    if(Serial.available() > 0)
    {
      String data_serial = Serial.readString();
      Serial.println("RFID : "+data_serial);
      //http_b.post("update-sensor","temperature="+data_serial);//test
      state =1;
    }
    //http_b.post("update-sensor","temperature=20");
    //delay(1000);
    //state =1;
  }
  if(state == 1 )
  {
    String response = http_b.recive();
    //response.trim();
    Serial.println(response);
  }
  /*
  if(state ==3 )
  {
    Serial.println("working on state 1");
    oled.show(1," เลือกระบบการทำงาน");
    oled.show(2," สีฟ้า  = BF");
    oled.show(3," สีส้ม = RW");
    oled.show(4," สีขาว = DT");
    state =4 ;
  }
  if(state ==4 )
  {
    swb.read_all_switch();
    if(swb.result_blue_switch == 0)
      {
        Serial.println("go to bf state !");
        oled.clear();
        oled.show(1,"now is BF state");
        state =5 ;
      }
    if(swb.result_white_switch == 0)
      {
        Serial.println("go to dt state !");
        oled.clear();
        oled.show(1,"now is DT state");
        oled.show(2," Code : ");
        oled.clear();
        state = 6;
      }
    if(swb.backup_result_yellow_switch == 0)
    {
      Serial.println("go to rw state !");
      oled.clear();
      oled.show(1,"now is RW state");
      state == 7;
    }
  }
  if(state ==4 )
  {

  }
  if(state == 7)
  {
    char customKey = customKeypad.getKey();
    oled.drawStr(0,0,msg);
    if (customKey != NO_KEY)
    {
      Serial.println(customKey);
      msg += customKey;
      Serial.println(msg);
      oled.drawStr(0,0,msg);
    }
  }*/



