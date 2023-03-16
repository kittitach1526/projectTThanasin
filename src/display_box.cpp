#include "display_box.h"
display_box oled;
#include "dw_font.h"
#include <SH1106Wire.h>
#define LINE1       8
#define LINE2       23
#define LINE3       38
#define LINE4       53
#define LINE5       68
#define TAB0        0
#define TAB5        5
#define TAB10       10
#define TAB15       15
#define TAB20       20
#define TAB40       40
SH1106Wire display(0x3c, 21, 22);                     // ADDRESS, SDA, SCL
extern dw_font_info_t font_th_sarabun_new_regular14;  // font TH
dw_font_t myfont;

display_box::display_box()
{

}
void draw_pixel(int16_t x, int16_t y) {
    display.setColor(WHITE);
    display.setPixel(x, y);
}
void clear_pixel(int16_t x, int16_t y) {
    display.setColor(BLACK);
    display.setPixel(x, y);
}
void display_box::intit_display()
{
    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    dw_font_init(&myfont, 128, 64, draw_pixel, clear_pixel);
    dw_font_setfont(&myfont, &font_th_sarabun_new_regular14);
    //show(1," Code by Glenda");
    delay(1000);
    clear();

}

void display_box::show(int line,char *data_to_show)
{
    //dw_font_goto(&myfont, TAB0, LINE1);
    //dw_font_print(&myfont, "Majorette (Thailand) Co.,LTD");

    if(line == 1)
    {
        //display.clear();
        dw_font_goto(&myfont, TAB0, LINE1);
        dw_font_print(&myfont, data_to_show);
       // display.display();
    }
    if(line == 2 )
    {
        //display.clear();
        dw_font_goto(&myfont, TAB0, LINE2);
        dw_font_print(&myfont, data_to_show);
       // display.display();
    }
    if(line == 3 )
    {
        //display.clear();
        dw_font_goto(&myfont, TAB0, LINE3);
        dw_font_print(&myfont, data_to_show);
       // display.display();
    }
    if(line == 4 )
    {
        //display.clear();
        dw_font_goto(&myfont, TAB0, LINE4);
        dw_font_print(&myfont, data_to_show);
        //display.display();
    }
    if(line == 5 )
    {
        display.clear();
        dw_font_goto(&myfont, TAB0, LINE5);
        dw_font_print(&myfont, data_to_show);
        //display.display();
    }
    display.display();
}

void display_box::clear()
{
    display.resetDisplay();
}

void display_box::drawStr(byte x,byte y,String data)
{
    display.drawString(x, y, data);
    display.display();
}

void display_box::showString(int line,String data_display)
{
    if(line == 1)
    {
        display.drawString(TAB0,LINE1,data_display);
    }
    if(line == 2)
    {
        display.drawString(TAB0,LINE2,data_display);
    }
    if(line == 3)
    {
        display.drawString(TAB0,LINE3,data_display);
    }
    if(line == 4)
    {
        display.drawString(TAB0,LINE4,data_display);
    }
    if(line == 5)
    {
        display.drawString(TAB0,LINE5,data_display);
    }
    display.display();
}