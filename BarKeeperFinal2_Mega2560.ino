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
int gMix1ml = 42; // Einstellung der ml
int gMix2ml = 42; // Einstellung der ml
int gMix3ml = 42; // Einstellung der ml
int gMix4ml = 120; // Einstellung der ml
int gMix5ml = 120; // Einstellung der ml
int gMix6ml = 200; // Einstellung der ml

char *myStrings[] = {"WHISKY", "WODKA", "FEIGE",
                     " COLA", " SAFT", "SERVICE"
                    };
int gMix1 = 44;
int gMix2 = 42;
int gMix3 = 40;
int gMix4 = 38;
int gMix5 = 36;
int gMix6 = 34;
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
  delay(150);
  strip.setPixelColor(0, strip.Color(0,255, 0, 0));        //  Set pixel's color (in RAM)
  strip.show();
  delay(150);
  strip.setPixelColor(0, strip.Color(0,0,255, 0));        //  Set pixel's color (in RAM)
  strip.show();
  delay(150);
  strip.setPixelColor(0, strip.Color(0,0, 0, 255));        //  Set pixel's color (in RAM)
  strip.show();
  delay(150);
  strip.setPixelColor(0, strip.Color(255,0, 255, 0));        //  Set pixel's color (in RAM)
  strip.show();
  delay(150);
  strip.setPixelColor(0, strip.Color(255,255, 0, 0));        //  Set pixel's color (in RAM)
  strip.show();
  delay(150);
  strip.setPixelColor(0, strip.Color(0,255,255, 0));        //  Set pixel's color (in RAM)
  strip.show();
  delay(150);
  strip.setPixelColor(0, strip.Color(0,0, 0, 0));        //  Set pixel's color (in RAM)
  strip.show();
  

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
     u8g2.drawFrame(0,0,128,38);
     u8g2.setFont(u8g2_font_HelvetiPixelOutline_tr);
     u8g2.drawStr( 21, 14, "Bar Keeper");
     //u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     //u8g2.drawStr( 5, 35, "F");
     u8g2.setFont(u8g2_font_9x15_tf);
     u8g2.drawStr( 36, 32, myStrings[0]);
     u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     u8g2.drawStr( 105, 35, "F");
     u8g2.setFont(u8g2_font_6x10_tf);
     u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(255, 0, 255, 0));
      strip.show();
      delay(200);
      strip.setPixelColor(0, strip.Color(0, 0, 0, 255)); 
      strip.show();

      break;
    case 2:
     //printlcd();
      u8g2.clearBuffer();
     u8g2.drawFrame(0,0,128,38);
     u8g2.setFont(u8g2_font_HelvetiPixelOutline_tr);
     u8g2.drawStr( 21, 14, "Bar Keeper"); 
     u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     u8g2.drawStr( 5, 35, "E");
     u8g2.setFont(u8g2_font_9x15_tf);
     u8g2.drawStr( 41, 32, myStrings[1]);
     u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     u8g2.drawStr( 105, 35, "F");
     u8g2.sendBuffer(); 
      strip.setPixelColor(0, strip.Color(255, 0, 255, 0));
      strip.show();
      delay(200);
      strip.setPixelColor(0, strip.Color(0, 0, 0, 255)); 
      strip.show();
      break;
    case 3:
      u8g2.clearBuffer();
      u8g2.drawFrame(0,0,128,38);
     u8g2.setFont(u8g2_font_HelvetiPixelOutline_tr);
     u8g2.drawStr( 21, 14, "Bar Keeper");
     u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     u8g2.drawStr( 5, 35, "E");
     u8g2.setFont(u8g2_font_9x15_tf);
     u8g2.drawStr( 41, 32, myStrings[2]);
     u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     u8g2.drawStr( 105, 35, "F");
     u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(255, 0, 255, 0));
      strip.show();
      delay(200);
      strip.setPixelColor(0, strip.Color(0, 0, 0, 255)); 
      strip.show();
      break;
    case 4:
      u8g2.clearBuffer();
      u8g2.drawFrame(0,0,128,38);
     u8g2.setFont(u8g2_font_HelvetiPixelOutline_tr);
     u8g2.drawStr( 21, 14, "Bar Keeper");
     u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     u8g2.drawStr( 5, 35, "E");
     u8g2.setFont(u8g2_font_9x15_tf);
     u8g2.drawStr( 36, 32, myStrings[3]);
     u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     u8g2.drawStr( 105, 35, "F");
     u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(255, 0, 255, 0));
      strip.show();
      delay(200);
      strip.setPixelColor(0, strip.Color(0, 0, 0, 255)); 
      strip.show();
      break;
    case 5:
      u8g2.clearBuffer();
      u8g2.drawFrame(0,0,128,38);
     u8g2.setFont(u8g2_font_HelvetiPixelOutline_tr);
     u8g2.drawStr( 21, 14, "Bar Keeper");
     u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     u8g2.drawStr( 5, 35, "E");
     u8g2.setFont(u8g2_font_9x15_tf);
     u8g2.drawStr( 36, 32, myStrings[4]);
     //u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     //u8g2.drawStr( 105, 35, "E");
     u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(255, 0, 255, 0));
      strip.show();
      delay(200);
      strip.setPixelColor(0, strip.Color(0, 0, 0, 255)); 
      strip.show();
      break;
    case 6:
      u8g2.clearBuffer();
      u8g2.drawFrame(0,0,128,38);
     u8g2.setFont(u8g2_font_HelvetiPixelOutline_tr);
     u8g2.drawStr( 21, 14, "Bar Keeper");
     u8g2.setFont(u8g2_font_9x15_tf);
     u8g2.drawStr( 34, 32, myStrings[5]);
     u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
     u8g2.drawStr( 55, 58, "\x0e5");
     u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(255, 0, 0, 0));
      strip.show();
      delay(100);
      strip.setPixelColor(0, strip.Color(0, 0, 255, 0)); 
      strip.show();
      delay(100);
      strip.setPixelColor(0, strip.Color(255, 0, 0, 0));
      strip.show();
      delay(100);
      strip.setPixelColor(0, strip.Color(0, 0, 255, 0)); 
      strip.show();
      delay(100);
      strip.setPixelColor(0, strip.Color(255, 0, 0, 0));
      strip.show();
      delay(100);
      strip.setPixelColor(0, strip.Color(0, 0, 255, 0)); 
      strip.show();
      delay(100);
      strip.setPixelColor(0, strip.Color(255, 0, 0, 0));
      strip.show();
      delay(100);
      strip.setPixelColor(0, strip.Color(0, 0, 255, 0)); 
      strip.show();
      delay(100);
      strip.setPixelColor(0, strip.Color(255, 0, 0, 0));
      strip.show();
      delay(100);
      strip.setPixelColor(0, strip.Color(0, 0, 255, 0)); 
      strip.show();
      delay(100);
      strip.setPixelColor(0, strip.Color(0, 0, 0, 0)); 
      strip.show();
      break;
    case 7:
      menu = 6;
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
      action6();
      break;  
    case 7:
      
      break;
  }
}
//--------------------------------------------------------------------------------
void action1() {
      
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
      while ((((scale.get_units()* 0.01)-21)/19.7688) - gewicht < gMix1ml )//while ((scale.read()*0.001+0.8) - gewicht < wiml) 
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
      while ((((scale.get_units()* 0.01)-21)/19.7688) - gewicht < gMix2ml ) {
      
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
      while ((((scale.get_units()* 0.01)-21)/19.7688) - gewicht < gMix3ml ) {
      
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
      while ((((scale.get_units()* 0.01)-21)/19.7688) - gewicht < gMix4ml ) {
      
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
      while ((((scale.get_units()* 0.01)-21)/19.7688) - gewicht < gMix5ml ) {
      
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

//--------------------------------------------------------------------------------------------------------------
void action6() {   // SERVICE REINIGUNG
      u8g2.clearBuffer();
      u8g2.drawFrame(0,0,128,38);
      u8g2.setFont(u8g2_font_HelvetiPixelOutline_tr);
      u8g2.drawStr( 21, 14, "Bar Keeper");
      u8g2.setFont(u8g2_font_9x15_tf);
      u8g2.drawStr( 34, 32, myStrings[5]);
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 12, 50, "Glas einstellen");
      u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(0, 255, 0, 0));
      strip.show();
      delay(5000);
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawStr( 52, 35, "6");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 17, 50, " Bitte warten ");
      u8g2.sendBuffer();
      //gewicht = ((scale.get_units()* 0.01)-21)/19.7688;
      delay(1000);
      
      //while ((((scale.get_units()* 0.01)-21)/19.7688) - gewicht < gMix6ml ) {
      
      strip.setPixelColor(0, strip.Color(255, 0, 0, 0));        //  Set pixel's color (in RAM)
      strip.show();
      //}
      strip.setPixelColor(0, strip.Color(255, 0, 0, 0));        //  Set pixel's color (in RAM)
      strip.show();
      digitalWrite(gMix1, LOW);
      delay(1000);
      digitalWrite(gMix1, HIGH);
      delay(1000);
      digitalWrite(gMix2, LOW);
      delay(1000);
      digitalWrite(gMix2, HIGH);
      delay(1000);
      digitalWrite(gMix3, LOW);
      delay(1000);
      digitalWrite(gMix3, HIGH);
      delay(1000);
      digitalWrite(gMix4, LOW);
      delay(1000);
      digitalWrite(gMix4, HIGH);
      delay(1000);
      digitalWrite(gMix5, LOW);
      delay(1000);
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
