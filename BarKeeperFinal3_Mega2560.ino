#include <U8g2lib.h>
// UNO!!!!!U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock/sck=*/ 13, /* data/mosi=*/ 11, /* CS/ss=*/ 10, /* reset=*/ 8); /* miso=12*/
//U8GLIB_ST7920_128X64_1X u8g(52, 51, 53);	// SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17
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

//----Einstellung der Getränkefüllung----------------------------------------------
int gMix1ml = 30; // Einstellung der ml
int gMix2ml = 30; // Einstellung der ml
int gMix3ml = 105; // Einstellung der ml
int gMix4ml = 120; // Einstellung der ml
int gMix5ml = 120; // Einstellung der ml
int gMix6ml = 200; // Einstellung der ml

//----Einstellung der Getränkebezeichnungen---------------------------------------
char *myStrings[] = {"WHISKY", "WODKA", " COLA",
                     " RUM ", " SAFT", "SERVICE"
                    };

//---------------------------------------------------------------------------------
// -------------------------Einstellung der Ports am ATMega2560                    
int gMix1 = 44;
int gMix2 = 42;
int gMix3 = 40;
int gMix4 = 38;
int gMix5 = 36;
//int gMix6 = 34;
int Gcheck = 30;
int GOK;
//--------------------------------------------------------------------------------
unsigned int menu = 0;
//--------------------------------------------------------------------------------
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 7 ,NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(6, 34 ,NEO_GRBW + NEO_KHZ800);
//--------------------------------------------------------------------------------
void setup() {
  u8g2.begin();
  delay(500);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);
  pinMode(Gcheck, INPUT);
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
  strip1.begin();
  strip.setBrightness(200); // set accordingly
  strip1.setBrightness(100); // set accordingly
  /*
  knightRider(255, 0, 0, 1, 3, 5, 50);
  knightRider(0, 255, 0, 1, 3, 5, 50);
  knightRider(0, 0, 255, 1, 3, 5, 50);
  knightRider(255, 155, 0, 1, 3, 5, 50);
  knightRider(0, 255, 255, 1, 3, 5, 50);
  knightRider(255, 0, 255, 1, 3, 5, 50);

  */
  rainbow(10);
  scale.tare();

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
    if (millis() - lastButtonPress > 100) {
      executeAction();
      updateMenu();
    }
    lastButtonPress = millis();
  }
    delay(1);
    Glastest();
}
//--------------------------------------------------------------------------------

void updateMenu() {
  
  switch (menu) {
    case 0:
      menu = 0;
    break;
    case 1:
     u8g2.clearBuffer();
     u8g2.drawFrame(0,0,128,38);
     u8g2.setFont(u8g2_font_HelvetiPixelOutline_tr);
     u8g2.drawStr( 21, 14, "Bar Keeper");
     u8g2.setFont(u8g2_font_9x15_tf);
     u8g2.drawStr( 36, 32, myStrings[0]);
     u8g2.setFont(u8g2_font_open_iconic_arrow_2x_t);
     u8g2.drawStr( 105, 35, "F");
     u8g2.setFont(u8g2_font_6x10_tf);
     u8g2.sendBuffer();
     LEDStrip();
    break;

    case 2:
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
     LEDStrip();
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
     LEDStrip();
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
     LEDStrip();
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
     u8g2.sendBuffer();
     LEDStrip();
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
      menu = 0;
    break;
  }
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
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
  }
}


//--------------------------------------------------------------------------------

void action1() {
      Glasein();
//   -------------------------------------------------------------------
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      GOK=digitalRead(Gcheck);
      if (GOK == LOW)  {// …wenn Glas OK ist dann
      strip.setPixelColor(0, strip.Color(0, 255, 0, 0));
      strip.show();
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawStr( 52, 35, "6");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 17, 50, " Bitte warten ");
      u8g2.sendBuffer();
      gewicht = ((scale.get_units()* 0.01)-21)/19.7688;//
      delay(1000);
      digitalWrite(gMix1, LOW);
      while ((((scale.get_units()* 0.01)-21)/19.7688) - gewicht < gMix1ml ) 
      {
      for (int i=0; i <= 7; i++){
      strip1.setPixelColor(i, strip.Color(255,0,0, 0));
      }
      strip1.show();
      strip.setPixelColor(0, strip.Color(255, 0, 0, 0));
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
      LEDFertig();
      Glasaus();
      }
      else
      {
      Glasfehl();
      }
        
}
//--------------------------------------------------------------------------------
void action2() {
      
      Glasein();
//   -------------------------------------------------------------------
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      GOK=digitalRead(Gcheck);
      if (GOK == LOW)  {// …wenn Glas OK ist dann
      strip.setPixelColor(0, strip.Color(0, 255, 0, 0));
      strip.show();
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawStr( 52, 35, "6");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 17, 50, " Bitte warten ");
      u8g2.sendBuffer();
      gewicht = ((scale.get_units()* 0.01)-21)/19.7688;
      delay(1000);
      digitalWrite(gMix2, LOW);
      while ((((scale.get_units()* 0.01)-21)/19.7688) - gewicht < gMix2ml ) {
      for (int i=0; i <= 7; i++){
      strip1.setPixelColor(i, strip.Color(255,0,0, 0));
      }
      strip1.show();
      strip.setPixelColor(0, strip.Color(255, 0, 0, 0));
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
      LEDFertig();
      Glasaus();
      }
      else
      {
      Glasfehl();
      }
}
//--------------------------------------------------------------------------------
void action3() {
      Glasein();
//   -------------------------------------------------------------------
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      GOK=digitalRead(Gcheck);
      if (GOK == LOW)  {// …wenn Glas OK ist dann
      strip.setPixelColor(0, strip.Color(0, 255, 0, 0));
      strip.show();
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawStr( 52, 35, "6");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 17, 50, " Bitte warten ");
      u8g2.sendBuffer();
      gewicht = ((scale.get_units()* 0.01)-21)/19.7688;
      delay(1000);
      digitalWrite(gMix3, LOW);
      while ((((scale.get_units()* 0.01)-21)/19.7688) - gewicht < gMix3ml ) {
      for (int i=0; i <= 7; i++){
      strip1.setPixelColor(i, strip.Color(255,0,0, 0));
      }
      strip1.show();
      strip.setPixelColor(0, strip.Color(255, 0, 0, 0));
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
      LEDFertig();
      Glasaus();
      }
      else
      {
      Glasfehl();
      }
}
//--------------------------------------------------------------------------------
void action4() {
      Glasein();
//   -------------------------------------------------------------------
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      GOK=digitalRead(Gcheck);
      if (GOK == LOW)  {// …wenn Glas OK ist dann
      strip.setPixelColor(0, strip.Color(0, 255, 0, 0));
      strip.show();
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawStr( 52, 35, "6");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 17, 50, " Bitte warten ");
      u8g2.sendBuffer();
      gewicht = ((scale.get_units()* 0.01)-21)/19.7688;
      delay(1000);
      digitalWrite(gMix4, LOW);
      while ((((scale.get_units()* 0.01)-21)/19.7688) - gewicht < gMix4ml ) {
      for (int i=0; i <= 7; i++){
      strip1.setPixelColor(i, strip.Color(255,0,0, 0));
      }
      strip1.show();
      strip.setPixelColor(0, strip.Color(255, 0, 0, 0));
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
      LEDFertig();
      Glasaus();
      }
      else
      {
      Glasfehl();
      } 
}
//--------------------------------------------------------------------------------
void action5() {
      Glasein();
//   -------------------------------------------------------------------
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      GOK=digitalRead(Gcheck);
      if (GOK == LOW)  {// …wenn Glas OK ist dann
      strip.setPixelColor(0, strip.Color(0, 255, 0, 0));
      strip.show();
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawStr( 52, 35, "6");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 17, 50, " Bitte warten ");
      u8g2.sendBuffer();
      gewicht = ((scale.get_units()* 0.01)-21)/19.7688;
      delay(1000);
      digitalWrite(gMix5, LOW);
      while ((((scale.get_units()* 0.01)-21)/19.7688) - gewicht < gMix5ml ) {
      for (int i=0; i <= 7; i++){
      strip1.setPixelColor(i, strip.Color(255,0,0, 0));
      }
      strip1.show();
      strip.setPixelColor(0, strip.Color(255, 0, 0, 0));
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
      LEDFertig();
      Glasaus();
      }
      else
      {
      Glasfehl();
      }
}

//--------------------------------------------------------------------------------------------------------------
void action6() {   // SERVICE REINIGUNG
      u8g2.clearBuffer();
      u8g2.drawFrame(0,0,128,38);
      u8g2.setFont(u8g2_font_HelvetiPixelOutline_tr);
      u8g2.drawStr( 21, 14, "Bar Keeper");
      u8g2.setFont(u8g2_font_9x15_tf);
      u8g2.drawStr( 34, 32, myStrings[5]);
      Glasein();
//   -------------------------------------------------------------------
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      GOK=digitalRead(Gcheck);
      if (GOK == LOW)  {// …wenn Glas OK ist dann
      strip.setPixelColor(0, strip.Color(0, 255, 0, 0));
      strip.show();
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawStr( 52, 35, "6");
      u8g2.setFont(u8g2_font_6x12_tf);
      u8g2.drawStr( 20, 50, "Servicebuttons");
      u8g2.drawStr( 40, 63, "druecken!");
      u8g2.sendBuffer();
      delay(1000);
      while ((((scale.get_units()* 0.01)-21)/19.7688) - gewicht < gMix6ml ) {
      for (int i=0; i <= 7; i++){
      strip1.setPixelColor(i, strip.Color(255,0,0, 0));
      }
      strip1.show();
      strip.setPixelColor(0, strip.Color(255, 0, 0, 0));
      strip.show();;
      }
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
      LEDFertig();
      Glasaus();
      }
      else
      {
      Glasfehl();
      }
}
//--------------------------------------------------------------------------------

void Glastest() {
      GOK=digitalRead(Gcheck);
      if (GOK == LOW)  {// …wenn Glas OK ist dann
      strip.setPixelColor(0, strip.Color(0, 255, 0, 0));
      strip.show();
      }
      else
      {
      strip.setPixelColor(0, strip.Color(0, 0, 0, 150));
      strip.show();
      }

}

void Glasein() {
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 12, 50, "Glas einstellen");
      u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(0, 100, 0, 0));
      strip.show();
      knightRider(0, 255, 0, 3, 3, 5, 80);
      delay(1000);

}

void Glasaus() {
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      u8g2.setFont(u8g2_font_open_iconic_www_4x_t);
      u8g2.drawStr( 50, 35, "I");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 15, 50, "Glas entnehmen");
      u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(0, 255, 0, 0));
      strip.show();
      knightRider(0, 255, 0, 3, 3, 3, 60);
      for (int i=0; i <= 7; i++){
      strip1.setPixelColor(i, strip.Color(0,0,255,0));
      }
      strip1.show();
      strip.setPixelColor(0, strip.Color(0, 0, 255, 0));
      strip.show();
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 0, 50, "                        ");
      u8g2.sendBuffer();
      delay(1000);
      u8g2.clearBuffer();
}

void Glasfehl() {
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_emoticons21_tr);
      u8g2.drawStr( 52, 35, "5");
      u8g2.setFont(u8g2_font_7x13_tf);
      u8g2.drawStr( 12, 50, "Glas fehlt ! ! ! ! ");
      u8g2.sendBuffer();
      strip.setPixelColor(0, strip.Color(255, 0, 0, 0));
      strip.show();
      knightRider(255, 0, 0, 3, 3, 3, 80);
}

void LEDFertig() {
      strip.setPixelColor(0, strip.Color(0, 0, 255, 0));
      strip.show();
      knightRider(0, 0, 255, 1, 3, 3, 60);
      delay(2000);
}

void LEDStrip() {
      knightRider(255, 0, 255, 1, 1, 3, 10);
      strip.setPixelColor(0, strip.Color(255, 0, 255, 0));
      strip.show();
      strip.setPixelColor(0, strip.Color(0, 0, 0, 255)); 
      strip.show();
      for (int i=0; i <= 7; i++){
      strip1.setPixelColor(i, strip.Color(0,0,255, 0));
      }
      strip1.show();
}


void knightRider(int r, int g, int b, int rounds, int width, int fade, int wait){
  int faktor = 20/(fade*2);
  int r2, g2, b2;

  for (int c = 0; c < rounds; c++) {  // legt fest wie viele Runden abgespielt werden sollen
    
    for(int i=0; i<strip1.numPixels()+width+fade; i++) {  // gesamten Strip durchlaufen VORWÄRTS
  
      for(int j=0; j < width; j++){ // hier werden die Pixel (ohne den fade) generiert
        strip1.setPixelColor(i-j, r, g, b);    
         
        for(int f = fade; f > 0; f--) {  // hier wird das fade generiert und an das Band angehängt
          r2 = (r / 20) * (f * faktor);
          g2 = (g / 20) * (f * faktor);
          b2 = (b / 20) * (f * faktor);
          strip1.setPixelColor((i-width-fade+f), r2, g2, b2);
        }
        
        strip1.setPixelColor(i-width-fade, 0, 0, 0); // löscht die Pixel nach dem Fade
      }
      strip1.show();
      delay(wait);
    }

    for(int i = strip1.numPixels(); i>0-width-fade-2; i--) {  // gesamten Strip durchlaufen RÜCKWÄRTS (rw)
       for(int j = width; j > 0; j--){ //rw: hier werden die Pixel (ohne den fade) generiert
        strip1.setPixelColor(i+j, r, g, b);    
         
        for(int f = fade; f > 0; f--) {  //rw: hier wird das fade generiert und an das Band angehängt
          r2 = (r / 20) * (f * faktor);
          g2 = (g / 20) * (f * faktor);
          b2 = (b / 20) * (f * faktor);
          strip1.setPixelColor((i+width+fade-f+1), r2, g2, b2);
        }
        
        strip1.setPixelColor(i+width+fade+1, 0, 0, 0); //rw löscht die Pixel nach dem Fade
      }
      strip1.show();
      delay(wait);
    }
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip1.numPixels(); i++) {
      strip1.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip1.show();
    delay(wait);
  }
}
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}