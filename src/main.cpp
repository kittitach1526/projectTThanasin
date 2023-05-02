#include <Arduino.h>
#include "wifi_lib.h"
#include "Switch_box.h"
#include "display_box.h"
#include <Wire.h>
#include "rfid_state.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "keypadbox.h"

byte state=0;
String getdataJsonTouch(String key_search);
String getdataJsonGetDataTouch(String key_search);
void checkState();


#include <Wire.h>
HTTPClient http;
typedef struct mc
{
  String rfid = "";
  String mc_number = "mc200";
}mc;

typedef struct dataStaff
{
  String id_staff ="";
  String name_first = "";
  String name_last = "";
  String role ="";
  String id_task ="";
  String id_job ="";
  String item_no = "";
  String operation ="";
  String op_color ="";
  String op_side ="";
  String op_name ="";
  String qty_oder ="";
  String qty_comp = "";
  String qty_opcn ="";
  String multiplior ="";
  String qty_shif ="";
}dataStaff;

String serverUrl ="https://bunnam.com/projects/majorette_pp/update/quit_v3.php?id_mc=02-02&id_rfid=0004953220&id_activity=4539&activity_type=1&no_send=1&no_pulse1=300&no_pulse2=1&no_pulse3=100&multiplier=1";

String Nodered_2 = "http://20.231.75.176:1880/touch?id_mc=mc200&rfid=1165304621";

void setup() {
  Wire.begin();
  Serial.begin(9600);
  kp.beginkeypad();
  //swb.setpin_switch(25,27,12);//w,b,y
  oled.intit_display();
  oled.clear();
  oled.show(1," Code by Glenda 0.8");
  delay(1000);
  oled.clear();
  Serial.println("\nVersion : 0.8  check rfid + wifi +state 0 ");
  w.BeginEEP();
  w.check_eeprom_wifi();
  //swb.on_led();
  rf_st.Init_rfid();
  Serial.println("All Setup Complete!"); 
  state =0;
}
/*-----------------------------------------------------------------------------------------------------------*/
dataStaff staff;
mc mc01;

/*-----------------------------------------------------------------------------------------------------------*/
void loop() { 
  
  //char data = kp.readkeypad();
  //Serial.println(data);
  //kp.test();
  //String keydata = getdataJson("rfid");
  //Serial.println("rfid : "+keydata);
  //delay(1000);
  if (state == 0)
  {
    oled.clear();
    Serial.println("Now State 0 ");
    oled.showString(1,"Now state 0 ");
    delay(2000);
    oled.clear();
    oled.showString(1,"tap keycard ..");
    while(rf_st.result_rfid =="")
    {
      rf_st.read_rfid();
    }
    Serial.println("RFID : "+rf_st.result_rfid);
    oled.clear();
    String data_to_show = "RFID : "+rf_st.result_rfid;
    oled.showString(1,data_to_show);
    delay(5000);
    oled.clear();
    state = 1 ;
    Serial.println(" Go to > State 1 ");
    oled.showString(1,"Go to > State 1 ");
    delay(1000);
    oled.clear();
  }
  if(state == 1 )
  {

  }

}
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
String getdataJson(String key_search)
{
  //http.begin(serverUrl);
  http.begin(Nodered_2);
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
