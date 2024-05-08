#include <U8g2lib.h>
// UNO!!!!!U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock/sck=*/ 13, /* data/mosi=*/ 11, /* CS/ss=*/ 10, /* reset=*/ 8); /* miso=12*/
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 52, /* data=*/ 51, /* CS=*/ 53, /* reset=*/ 52 );
//--------------------------------------------------------------------------------
#include "HX711.h"
const int LOADCELL_DOUT_PIN = 5;
const int LOADCELL_SCK_PIN = 6;
HX711 scale;
long gewicht;
//--------------------------------------------------------------------------------
#define CLK 2
#define DT 3
#define SW 4
int currentStateCLK;
int lastStateCLK;
unsigned long lastButtonPress = 0;
//--------------------------------------------------------------------------------
#define gMix1 WHISKY
#define gMix2 WODKA
#define gMix3 FEIGE
#define gMix4 COLA
#define gMix5 SAFT
#define gMix6 WASSER
#define gServ1 SERVICE
#define gServ2 CHECK1
#define gServ3 CHECK2
int gMix1 = A0;
int gMix2 = A1;
int gMix3 = A2;
int gMix4 = A3;
int gMix5 = A4;
//--------------------------------------------------------------------------------
unsigned int menu = 0;
//--------------------------------------------------------------------------------
#include <Adafruit_NeoPixel.h>
#define PIN 7
#define STRIPSIZE 1
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIPSIZE, PIN, NEO_GRBW + NEO_KHZ800);
//--------------------------------------------------------------------------------
void setup() {
  //Serial.begin(9600);
  //u8g.begin();
  u8g2.begin();
  delay(500);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);
  pinMode(gMix1, OUTPUT); 
  pinMode(gMix2, OUTPUT);
  pinMode(gMix3, OUTPUT); 
  pinMode(gMix4, OUTPUT);
  pinMode(gMix5, OUTPUT);
  digitalWrite(gMix1,HIGH);
  digitalWrite(gMix2,HIGH);
  digitalWrite(gMix3,HIGH);
  digitalWrite(gMix4,HIGH); 
  digitalWrite(gMix5,HIGH);
  menu = 0;
  updateMenu();
  strip.begin();
  strip.setBrightness(150); // set accordingly
  strip.setPixelColor(0, strip.Color(255,0, 0, 0));        //  Set pixel's color (in RAM)
  strip.show();
  delay(500);
  strip.setPixelColor(0, strip.Color(0,255, 0, 0));        //  Set pixel's color (in RAM)
  strip.show();
  delay(500);
  strip.setPixelColor(0, strip.Color(0,0,255, 0));        //  Set pixel's color (in RAM)
  strip.show();
  delay(500);
  strip.setPixelColor(0, strip.Color(0,0, 0, 255));        //  Set pixel's color (in RAM)
  strip.show();
  delay(500);
  

}
//--------------------------------------------------------------------------------
void loop() {
  currentStateCLK = digitalRead(CLK);
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1) {
    if (digitalRead(DT) != currentStateCLK) {
      menu --;
      updateMenu();
    } else {
      menu ++;
      updateMenu();
    }
  }
  lastStateCLK = currentStateCLK;

  int btnState = digitalRead(SW);
  if (btnState == LOW) {
    if (millis() - lastButtonPress > 50) {
      executeAction();
      updateMenu();
    }
    lastButtonPress = millis();
  }
    delay(1);
}
//--------------------------------------------------------------------------------
void updateMenu() {
  
  switch (menu) {
    case 0:
      menu = 0;
      break;
    case 1:
      //printlcd();
     u8g2.clearBuffer();
     u8g2.setFont(u8g2_font_HelvetiPixelOutline_tr);
     u8g2.drawStr( 21, 12, "Bar Keeper");
     u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     u8g2.drawStr( 5, 35, "F");
     u8g2.setFont(u8g2_font_9x15_tf);
     u8g2.drawStr( 36, 32, "WHISKY");
     u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     u8g2.drawStr( 105, 35, "F");
     u8g2.setFont(u8g2_font_6x10_tf);
     u8g2.sendBuffer();


      break;
    case 2:
     //printlcd();
      u8g2.clearBuffer();
     u8g2.setFont(u8g2_font_HelvetiPixelOutline_tr);
     u8g2.drawStr( 21, 12, "Bar Keeper"); 
     u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     u8g2.drawStr( 5, 35, "E");
     u8g2.setFont(u8g2_font_9x15_tf);
     u8g2.drawStr( 41, 32, "WODKA");
     u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     u8g2.drawStr( 105, 35, "F");
     u8g2.sendBuffer(); 

      break;
    case 3:
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_HelvetiPixelOutline_tr);
     u8g2.drawStr( 21, 12, "Bar Keeper");
     u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     u8g2.drawStr( 5, 35, "E");
     u8g2.setFont(u8g2_font_9x15_tf);
     u8g2.drawStr( 41, 32, "FEIGE");
     u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     u8g2.drawStr( 105, 35, "F");
     u8g2.sendBuffer();

      break;
    case 4:
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_HelvetiPixelOutline_tr);
     u8g2.drawStr( 21, 12, "Bar Keeper");
     u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     u8g2.drawStr( 5, 35, "E");
     u8g2.setFont(u8g2_font_9x15_tf);
     u8g2.drawStr( 36, 32, " COLA");
     u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     u8g2.drawStr( 105, 35, "F");
     u8g2.sendBuffer();

      break;
    case 5:
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_HelvetiPixelOutline_tr);
     u8g2.drawStr( 21, 12, "Bar Keeper");
     u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     u8g2.drawStr( 5, 35, "E");
     u8g2.setFont(u8g2_font_9x15_tf);
     u8g2.drawStr( 36, 32, " SAFT");
     u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     u8g2.drawStr( 105, 35, "E");
     u8g2.sendBuffer();

      break;

    case 6:
      menu = 5;
      break;
  }
}
//--------------------------------------------------------------------------------
void executeAction() {
  switch (menu) {
    case 1:
        action1();
        break;
    case 2:
      action2();
      break;
    case 3:
      action3();
      break;
    case 4:
      action4();
      break;
    case 5:
      action5();
      break;
    case 6:
      
      break;
  }
}
//--------------------------------------------------------------------------------
void action1() {
      int wiml = 45; // Einstellung der ml
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 12, 50, "Glas einstellen");
      u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(0, 100, 0, 0));
      strip.show();
      delay(8000);
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawStr( 52, 35, "6");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 17, 50, " Bitte warten ");
      u8g2.sendBuffer();
      gewicht = ((scale.get_units()* 0.01)-21)/19.7688;//scale.read()*-0.001;
      delay(1000);
      digitalWrite(gMix1, LOW);
      while ((((scale.get_units()* 0.01)-21)/19.7688) - gewicht < wiml )//while ((scale.read()*0.001+0.8) - gewicht < wiml) 
      {
      
      strip.setPixelColor(0, strip.Color(255, 0, 0, 0));        //  Set pixel's color (in RAM)
      strip.show();
      }
      digitalWrite(gMix1, HIGH);
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawStr( 52, 35, "1");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 17, 50, " F E R T I G ");
      u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(0, 0, 255, 0));        //  Set pixel's color (in RAM)
      strip.show();
      delay(3000);
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      u8g2.setFont(u8g2_font_open_iconic_www_4x_t);
      u8g2.drawStr( 50, 35, "I");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 15, 50, "Glas entnehmen");
      u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(0, 255, 0, 0));        //  Set pixel's color (in RAM)
      strip.show();
      delay(5000);
      strip.setPixelColor(0, strip.Color(0, 0, 0, 250));        //  Set pixel's color (in RAM)
      strip.show();
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      delay(1000);
      u8g2.clearBuffer();
}
//--------------------------------------------------------------------------------
void action2() {
      int woml = 44; // Einstellung der ml
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 12, 50, "Glas einstellen");
      u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(0, 255, 0, 0));
      strip.show();
      delay(8000);
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawStr( 52, 35, "6");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 17, 50, " Bitte warten ");
      u8g2.sendBuffer();
      gewicht = ((scale.get_units()* 0.01)-21)/19.7688;
      delay(1000);
      digitalWrite(gMix2, LOW);
      while ((((scale.get_units()* 0.01)-21)/19.7688) - gewicht < woml ) {
      
      strip.setPixelColor(0, strip.Color(255, 0, 0, 0));        //  Set pixel's color (in RAM)
      strip.show();
      }
      digitalWrite(gMix2, HIGH);
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawStr( 52, 35, "1");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 17, 50, " F E R T I G ");
      u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(0, 0, 255, 0));        //  Set pixel's color (in RAM)
      strip.show();
      delay(3000);
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      u8g2.setFont(u8g2_font_open_iconic_www_4x_t);
      u8g2.drawStr( 50, 35, "I");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 15, 50, "Glas entnehmen");
      u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(0, 255, 0, 0));        //  Set pixel's color (in RAM)
      strip.show();
      delay(5000);
      strip.setPixelColor(0, strip.Color(0, 0, 0, 255));        //  Set pixel's color (in RAM)
      strip.show();
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      delay(1000);
      u8g2.clearBuffer();
}
//--------------------------------------------------------------------------------
void action3() {
      int coml = 110; // Einstellung der ml
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 12, 50, "Glas einstellen");
      u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(0, 255, 0, 0));
      strip.show();
      delay(8000);
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawStr( 52, 35, "6");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 17, 50, " Bitte warten ");
      u8g2.sendBuffer();
      gewicht = ((scale.get_units()* 0.01)-21)/19.7688;
      delay(1000);
      digitalWrite(gMix3, LOW);
      while ((((scale.get_units()* 0.01)-21)/19.7688) - gewicht < coml ) {
      
      strip.setPixelColor(0, strip.Color(255, 0, 0, 0));        //  Set pixel's color (in RAM)
      strip.show();
      }
      digitalWrite(gMix3, HIGH);
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawStr( 52, 35, "1");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 17, 50, " F E R T I G ");
      u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(0, 0, 255, 0));        //  Set pixel's color (in RAM)
      strip.show();
      delay(3000);
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      u8g2.setFont(u8g2_font_open_iconic_www_4x_t);
      u8g2.drawStr( 50, 35, "I");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 15, 50, "Glas entnehmen");
      u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(0, 255, 0, 0));        //  Set pixel's color (in RAM)
      strip.show();
      delay(5000);
      strip.setPixelColor(0, strip.Color(0, 0, 0, 255));        //  Set pixel's color (in RAM)
      strip.show();
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      delay(1000);
      u8g2.clearBuffer();
}
//--------------------------------------------------------------------------------
void action4() {
      int spml = 165; // Einstellung der ml
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 12, 50, "Glas einstellen");
      u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(0, 255, 0, 0));
      strip.show();
      delay(8000);
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawStr( 52, 35, "6");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 17, 50, " Bitte warten ");
      u8g2.sendBuffer();
      gewicht = ((scale.get_units()* 0.01)-21)/19.7688;
      delay(1000);
      digitalWrite(gMix4, LOW);
      while ((((scale.get_units()* 0.01)-21)/19.7688) - gewicht < spml ) {
      
      strip.setPixelColor(0, strip.Color(255, 0, 0, 0));        //  Set pixel's color (in RAM)
      strip.show();
      }
      digitalWrite(gMix4, HIGH);
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawStr( 52, 35, "1");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 17, 50, " F E R T I G ");
      u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(0, 0, 255, 0));        //  Set pixel's color (in RAM)
      strip.show();
      delay(3000);
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      u8g2.setFont(u8g2_font_open_iconic_www_4x_t);
      u8g2.drawStr( 50, 35, "I");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 15, 50, "Glas entnehmen");
      u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(0, 255, 0, 0));        //  Set pixel's color (in RAM)
      strip.show();
      delay(5000);
      strip.setPixelColor(0, strip.Color(0, 0, 0, 255));        //  Set pixel's color (in RAM)
      strip.show();
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      delay(1000);
      u8g2.clearBuffer(); 
}
//--------------------------------------------------------------------------------
void action5() {
      int biml = 165; // Einstellung der ml
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 12, 50, "Glas einstellen");
      u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(0, 255, 0, 0));
      strip.show();
      delay(8000);
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawStr( 52, 35, "6");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 17, 50, " Bitte warten ");
      u8g2.sendBuffer();
      gewicht = ((scale.get_units()* 0.01)-21)/19.7688;
      delay(1000);
      digitalWrite(gMix5, LOW);
      while ((((scale.get_units()* 0.01)-21)/19.7688) - gewicht < biml ) {
      
      strip.setPixelColor(0, strip.Color(255, 0, 0, 0));        //  Set pixel's color (in RAM)
      strip.show();
      }
      digitalWrite(gMix5, HIGH);
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawStr( 52, 35, "1");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 17, 50, " F E R T I G ");
      u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(0, 0, 255, 0));        //  Set pixel's color (in RAM)
      strip.show();
      delay(3000);
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      u8g2.setFont(u8g2_font_open_iconic_www_4x_t);
      u8g2.drawStr( 50, 35, "I");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 15, 50, "Glas entnehmen");
      u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(0, 255, 0, 0));        //  Set pixel's color (in RAM)
      strip.show();
      delay(5000);
      strip.setPixelColor(0, strip.Color(0, 0, 0, 255));        //  Set pixel's color (in RAM)
      strip.show();
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      delay(1000);
      u8g2.clearBuffer();
}
//--------------------------------------------------------------------------------
