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
void process_count_empty_time();
void api_contact();

String mc_number = "mc200";

#include <Wire.h>
unsigned long m=0;

int hour=0;
int minute=0;
int sec=0;
unsigned long count_for_show= 0;
unsigned long count_for_connect_wifi= 0;
String result_time="";
int count_state_1 = 0;
int count_millis_state1 =0;

typedef struct dataStaff
{
  String id_staff ="";//
  String id_mc ="";//
  String name_first = ""; //
  String name_last = ""; //
  int role =0;
  int id_task =0;
  int id_job =0;
  String item_no = "";//
  int operation =0;
  int op_color =0;
  String op_side ="";//
  String op_name ="";//
  int qty_oder =0;
  int qty_comp = 0;
  int qty_open =0;
  int multiplior =0;
  int qty_shif =0;
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
  oled.show(1," Code by Glenda 0.9x");
  delay(1000);
  oled.clear();
  Serial.println("\nVersion : 0.10x  check rfid + wifi + api  ");
  w.BeginEEP();
  //w.clearEEPROM();
  //w.setEEPwifi("","");// adess[0],[32]
  //w.check_eeprom_wifi();
  //swb.on_led();
  rf_st.Init_rfid();
  Serial.println("All Setup Complete!"); 
  state =0;
}
/*-----------------------------------------------------------------------------------------------------------*/
dataStaff staff;
/*-----------------------------------------------------------------------------------------------------------*/
void loop() { 
  if (state == 0)
  {
    Serial.println("Now State 0 ");
    oled.clear();
    oled.showString(1,"Majorette(Thailand)Co,LTD");
    oled.showString(2,"-----------------------------------------");
    oled.showString(3,"Connect to WiFi / Press A");
    String ssid = w.get_ssid_eep();
    String reslut_show_state0 = "SSID: "+ssid;
    oled.showString(4,reslut_show_state0);
    count_for_connect_wifi= millis();
    state = 1;
  }
/*-----------------------------------------------------*/
  if(state ==1 )
  {
    String ssid = w.get_ssid_eep();
    //Serial.println("ssid_state1 : "+ssid);
    if(ssid == "")
    {
      Serial.println("Don't have ssid .");
      oled.clear();
      oled.showString(1,"Scan WiFi ...");
      w.scanWiFi();
      state =2 ;
    }
    else
    {
      
      if(millis()-count_for_connect_wifi>5000)
      {
        Serial.println("connect to  : "+ssid);
        state =4 ;
      }
      char data = kp.readkeypad();
      if(data != 'e')
      {
        Serial.println(data);
        if(data == 'A')
        {
          oled.clear();
          oled.showString(1,"Scan WiFi ...");
          w.clearEEPROM();
          Serial.println("Have ssid and press A button reset wifi");
          w.scanWiFi();
          //oled.clear();
          state =2;
        }
      }
    }
  }
/*-----------------------------------------------------*/
  if(state ==2 )
  {
    char data = kp.readkeypad();
    if(data != 'e')
    {
      Serial.println(data);
      w.Select_wifi(data);
      oled.clear();
      oled.show(2,"ใส่รหัสผ่าน WiFi");
      oled.showString(2,"password : _"+w.password);
      state =3;
    }
  }
/*-----------------------------------------------------*/
if(state == 3)
{
  char data = kp.readkeypad();
    if(data != 'e')
    {
      if(data != '*')
      {
        oled.clear();
        w.password += data;
        Serial.println("keypad password : "+w.password);
        oled.show(2,"ใส่รหัสผ่าน WiFi");
        oled.showString(2,"password : "+w.password+"_");
      }
      else
      {
        Serial.println("keypad = '*'");
        if(w.password == "001")
        {
          w.ssid = "makoto";
          w.password = "naekimakoto";
          w.setEEPwifi(w.ssid,w.password);
          Serial.println("Use set by Glenda ! ");
          Serial.println("go to state 4 !");
          state =4;
        }
        else
        {
          Serial.println("set password = "+w.password);
          w.setEEPwifi(w.ssid,w.password);
          state =4 ;
        }
      }
    }
    if(Serial.available()>0)
    {
      w.password = Serial.readString();
      Serial.println("keyboard : "+w.password);
      w.setEEPwifi(w.ssid,w.password);
      state = 4;
    }
}
/*-----------------------------------------------------*/
  if(state == 4)
  {
    w.connect_wifi_by_eep();
    Serial.println("go to state 5 !");
    m=millis();
    state =5 ;
  }
/*-----------------------------------------------------*/
  
  if(state == 5)
  {
    if(millis()-m > 1000)
    {
      process_count_empty_time();
      oled.clear();
      oled.show(1,"        (P) mc/no.02-03");
      oled.show(2,"      โปรดทำการสแกนบัตร");
      String result_to_showe = "             "+result_time;
      oled.showString(2,result_to_showe);
      m = millis();
    }
    rf_st.read_rfid();
    if(rf_st.result_rfid != "")
    {
      Serial.print("RFID Length : ");
      Serial.println(rf_st.result_rfid.length());
      Serial.println("RFID Num :"+rf_st.result_rfid);
      state =6;
    }
  }
  if(state == 6)
  {
    api_contact();
    state =7;
  }

/*
  if (state == 300)
  {
    process_count_empty_time();
    
  }*/
  /*
  if(state == 1)
  {
    Serial.println("Now state 2 ");
    oled.clear();
    oled.show(1,"        (P) mc/no.02-03");
    oled.show(2,"      โปรดทำการสแกนบัตร");
    oled.showString(3,"Best");
    state = 3;
  }*/
}














/*--------------------------------------------------------------------------------------------------------------------------------------------*/

void process_count_empty_time()
{
  if(millis()-count_for_show > 1000)
    {
      sec +=1;
      // สร้าง String เก็บเวลา
      if(sec > 59)
      {
        minute++;
        sec =0;
      }
      if(minute > 59)
      {
        hour++;
        minute =0;
      }


      if (hour < 10) {
        result_time = "0"+String(hour) + ":";
      }
      //result_time = String(hour) + ":";
      if(hour > 10){
        result_time = String(hour) + ":";
      }

      if (minute < 10) {
        result_time += "0";
      }
      result_time += String(minute) + ":";

      if (sec < 10) {
        result_time += "0";
      }
      result_time += String(sec);
      Serial.println(result_time);
      count_for_show = millis();
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
      Serial.println();
      DynamicJsonDocument doc(2048);
      deserializeJson(doc, payload);

      staff.id_job = doc["job_id"];
      Serial.println("job_id : "+String(staff.id_job));

      String data_id_mc = doc["id_mc"];
      staff.id_mc = data_id_mc;
      Serial.println("id_mc : "+String(staff.id_mc));

      String data_id_staff = doc["id_staff"];
      staff.id_staff = data_id_staff;
      Serial.println("id_staff : "+String(staff.id_staff));

      staff.id_task=doc["id_task"];
      Serial.println("id_task : "+String(staff.id_task));

      String data_item_no = doc["item_no"];
      staff.item_no = data_item_no;
      Serial.println("item_no : "+String(staff.item_no));

      String data_name_first = doc["nameStaff"];
      staff.name_first = data_name_first;
      Serial.println("name_first : "+String(staff.name_first));

      String data_lastname = doc["lastnameStaff"];
      staff.name_last = data_lastname;
      Serial.println("name_last : "+String(staff.name_last));

      staff.op_color =doc["op_color"];
      Serial.println("op_color : "+String(staff.op_color));

      String data_op_name = doc["op_name"];
      staff.op_name = data_op_name;
      Serial.println("op_name : "+String(staff.op_name));

      String data_op_side = doc["op_side"];
      staff.op_side = data_op_side;
      Serial.println("op_side : "+String(staff.op_side));

      staff.qty_comp = doc["qty_complete"];
      Serial.println("qty_comp : "+String(staff.qty_comp));

      staff.qty_oder = doc["qty_order"];
      Serial.println("qty_order : "+String(staff.qty_oder));

      staff.qty_open = doc["qty_open"];
      Serial.println("qty_open : "+String(staff.qty_open));

      Serial.println();
    }
  } else {
    Serial.println("Error in HTTP request");
  }
}