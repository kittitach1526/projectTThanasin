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
String getdataJson();
String getValue(String data, char separator, int index);
void api_contact();

String mc_number = "mc200";

#include <Wire.h>


typedef struct dataStaff
{
  String id_staff ="";//
  String id_mc ="";//
  String name_first = ""; //
  String name_last = ""; //
  int role ="";
  int id_task ="";
  int id_job ="";
  String item_no = "";//
  int operation ="";
  int op_color ="";
  String op_side ="";//
  String op_name ="";//
  int qty_oder ="";
  int qty_comp = "";
  int qty_opcn ="";
  int multiplior ="";
  int qty_shif ="";
}dataStaff;

String serverUrl ="https://bunnam.com/projects/majorette_pp/update/quit_v3.php?id_mc=02-02&id_rfid=0004953220&id_activity=4539&activity_type=1&no_send=1&no_pulse1=300&no_pulse2=1&no_pulse3=100&multiplier=1";
HTTPClient http;
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
  Serial.println("\nVersion : 0.8  check rfid + wifi + api  ");
  w.BeginEEP();
  w.check_eeprom_wifi();
  //swb.on_led();
  rf_st.Init_rfid();
  Serial.println("All Setup Complete!"); 
  //getdataJson(); // test json funtion 
  //api_contact();
  state =0;
  

}
/*-----------------------------------------------------------------------------------------------------------*/
dataStaff staff;

/*-----------------------------------------------------------------------------------------------------------*/
void loop() { 

  if (state == 0)
  {
    oled.clear();
    Serial.println("Now State 0 ");
    oled.showString(1,"Now state 0 ");
    delay(2000);
    oled.clear();
    Serial.println("tap keycard ..");
    oled.showString(1,"tap keycard ..");
    while(rf_st.result_rfid =="")
    {
      rf_st.read_rfid();
    }
    Serial.println("RFID : "+rf_st.result_rfid);

    oled.clear();
    String data_to_show = "RFID : "+rf_st.result_rfid;
    oled.showString(1,data_to_show);
    delay(2000);
    oled.clear();
    Serial.println(" Go to > State 1 ");
    oled.showString(1,"Go to > State 1 ");
    delay(1000);
    oled.clear();
    state = 1 ;
    
  }
  if(state == 1)
  {
    api_contact();
    state =2;
    Serial.println(" Go to > State 2 ");
    oled.showString(1,"Go to > State 2 ");
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

void api_contact()
{
  String test_server = "http://20.231.75.176:1880/touch?id_mc="+mc_number+"&rfid="+rf_st.result_rfid;
  http.begin(test_server);
  int httpCode = http.GET();

  // Check HTTP status code
  if (httpCode > 0) {
    Serial.printf("HTTP status code: %d\n", httpCode);

    // Check if response is available
    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
      String payload = http.getString();
      payload = getValue(payload,'[',1);
      payload = getValue(payload,']',0);
      Serial.println(payload);
      DynamicJsonDocument doc(2048);
      deserializeJson(doc, payload);
      int getdata = doc["job_id"];
      Serial.println("Value frome key : "+String(getdata));
    }
  } else {
    Serial.println("Error in HTTP request");
  }
}