#include <ESP8266WiFi.h>
#include <time.h>
#include "FastLED.h"

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    4
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    96
#define BRIGHTNESS  255
#define NIGHT_MODE        1     //Set night mode where 0 is off and 1 is on (Night mode turns the clock off at night)
#define WEEKEND_MODE      0     //Set weekend mode where 0 is off and 1 is on (Weekend mode turns the clock off on the weekends)
#define NIGHT_OFF_TIME    22    //Time that clock turns off when night mode is active
#define NIGHT_ON_TIME     7     //Time that clock turns on when night mode is active
int NIGHT_CHK = 0;              //Night model toggle
int WEEKEND_CHK = 0;            //Weekend mode toggle

CRGB leds[NUM_LEDS];

//Digits color values in RGB
int r=255;
int g=255;
int b=255;

const char* ESP_HOST_NAME = "esp-" + ESP.getFlashChipId();
//Your Wifi info
const char* ssid    = "SSID";
const char* password = "PASSWORD";

//Your time zone
int timezone = -8 * 3600; //UTC offset * 3600
int DST = 0;  //Default to DST is in effect
int CHK_DST = 0;                //Flip flop check to see if DST has changed and if so, force time update
   
WiFiClient wifiClient;

void connectWifi() 
{
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  delay(500);
  connectWifi();
  Serial.println();
  Serial.println("\n\nNext Loop-Step: " + String(millis()) + ":");
  configTime(timezone, DST*(3600), "pool.ntp.org","time.nist.gov");
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip)
    .setDither(BRIGHTNESS < 255);
  FastLED.setBrightness(BRIGHTNESS);
}

void timeupdate(int timezone, int DST) {
  configTime(timezone, DST*(3600), "pool.ntp.org","time.nist.gov");
}

void loop()
{
    time_t now = time(nullptr);
    struct tm* p_tm = localtime(&now);
    Serial.print("-------------------------------------------------\n");
    Serial.print("Date & Time : ");
    Serial.print(p_tm->tm_mday);
    Serial.print("/");
    Serial.print(p_tm->tm_mon + 1);
    Serial.print("/");
    Serial.print(p_tm->tm_year + 1900);
    Serial.print(" DST ");
    Serial.print(DST);
    Serial.print(" ");
    Serial.print(CHK_DST);
    Serial.print(" ");
    int month=p_tm->tm_mon;
    int day=p_tm->tm_mday;
    int hour=p_tm->tm_hour;
    int minute=p_tm->tm_min;
    int weekday=p_tm->tm_wday; //day of the week, range 0 to 6

if (month > 3 && month < 11)
    {
     DST = 1;
    }
else if (month == 3)
    {
     if (day > 14)
         {
          DST = 1;
         } 
     else if (day < 8)
         {
          DST = 0; 
         }
     else if (day == 8)
           {
            if (weekday == 1)
              {
                if (hour > 1)
                 {
                  DST = 1;
                 }
              }
           }   
     else if (day == 9)
           {
            if (weekday == 1)
              {
                if (hour > 1)
                 {
                  DST = 1;
                 }
              }
           }   
      else if (day == 10)
           {
            if (weekday == 1)
              {
                if (hour > 1)
                 {
                  DST = 1;
                 }
              }
           }   
      else if (day == 11)
           {
            if (weekday == 1)
              {
                if (hour > 1)
                 {
                  DST = 1;
                 }
              }
           }   
      else if (day == 12)
           {
            if (weekday == 1)
              {
                if (hour > 1)
                 {
                  DST = 1;
                 }
              }
           }   
      else if (day == 13)
           {
            if (weekday == 1)
              {
                if (hour > 1)
                 {
                  DST = 1;
                 }
              }
           }  
      else if (day == 14)
           {
            if (weekday == 1)
              {
                if (hour > 1)
                 {
                  DST = 1;
                 }                 
              }
           }   
       else
           {
            DST = 0;
           }
    } 
else if (month == 11)
    {
     if (day > 7)
         {
          DST = 0;
         } 
     else if (day == 1)
           {
            if (weekday == 1)
              {
                if (hour > 1)
                 {
                  DST = 0;
                 }
              }
           }   
     else if (day == 2)
           {
            if (weekday == 1)
              {
                if (hour > 1)
                 {
                  DST = 0;
                 }
              }
           }   
      else if (day == 3)
           {
            if (weekday == 1)
              {
                if (hour > 1)
                 {
                  DST = 0;
                 }
              }
           }   
      else if (day == 4)
           {
            if (weekday == 1)
              {
                if (hour > 1)
                 {
                  DST = 0;
                 }
              }
           }   
      else if (day == 5)
           {
            if (weekday == 1)
              {
                if (hour > 1)
                 {
                  DST = 0;
                 }
              }
           }   
      else if (day == 6)
           {
            if (weekday == 1)
              {
                if (hour > 1)
                 {
                  DST = 0;
                 }
              }
           }  
      else if (day == 7)
           {
            if (weekday == 1)
              {
                if (hour > 1)
                 {
                  DST = 0;
                 }                 
              }
           }   
       else
           {
            DST = 1;
           }
    }
    
    if (DST != CHK_DST)
    {
      CHK_DST = DST;
      timeupdate(timezone, DST);
    }

    if (NIGHT_MODE==1)
    {
      if (hour==NIGHT_OFF_TIME && NIGHT_CHK==0)
      {
        NIGHT_CHK = 1;
      }
      if (hour==NIGHT_ON_TIME && NIGHT_CHK==1)
      {
        NIGHT_CHK = 0;
      }
    }

    if (WEEKEND_MODE == 1)
    {
      if (weekday == 0 || weekday == 6)
      {
        WEEKEND_CHK = 1;
      }
      if (weekday != 0 && weekday != 6)
      {
        WEEKEND_CHK = 0;
      }
    }

    if (NIGHT_CHK == 1 || WEEKEND_CHK == 1)
    {
      FastLED.clear();  // clear all pixel data
      FastLED.show();
    }

    if (NIGHT_CHK == 0 && WEEKEND_CHK == 0)
    {
    if(hour>12)
    {
      hour=hour-12;
    }
    Serial.print(hour);
    Serial.print(":");
    Serial.print(minute);
    Serial.print(":");
    Serial.println(p_tm->tm_sec);
    pride();
    if(hour==0||hour==12)
    {
      hour12();
    }
    if(hour==1)
    {
      hour1();
    }
    if(hour==2)
    {
      hour2();
    }
    if(hour==3)
    {
      hour3();
    }
    if(hour==4)
    {
      hour4();
    }
    if(hour==5)
    {
      hour5();
    }
    if(hour==6)
    {
      hour6();
    }
    if(hour==7)
    {
      hour7();
    }
    if(hour==8)
    {
      hour8();
    }
    if(hour==9)
    {
      hour9();
    }
    if(hour==10)
    {
      hour10();
    }
    if(hour==11)
    {
      hour11();
    }

    if(minute==0)
    {
      min0();
    }
    if(minute==1)
    {
      min1();
    }
    if(minute==2)
    {
      min2();
    }
    if(minute==3)
    {
      min3();
    }
    if(minute==4)
    {
      min4();
    }
    if(minute==5)
    {
      min5();
    }
    if(minute==6)
    {
      min6();
    }
    if(minute==7)
    {
      min7();
    }
    if(minute==8)
    {
      min8();
    }
    if(minute==9)
    {
      min9();
    }
    if(minute==10)
    {
      min10();
    }
    if(minute==11)
    {
      min11();
    }
    if(minute==12)
    {
      min12();
    }
    if(minute==13)
    {
      min13();
    }
    if(minute==14)
    {
      min14();
    }
    if(minute==15)
    {
      min15();
    }
    if(minute==16)
    {
      min16();
    }
    if(minute==17)
    {
      min17();
    }
    if(minute==18)
    {
      min18();
    }
    if(minute==19)
    {
      min19();
    }
    if(minute==20)
    {
      min20();
    }
    if(minute==21)
    {
      min21();
    }
    if(minute==22)
    {
      min22();
    }
    if(minute==23)
    {
      min23();
    }
    if(minute==24)
    {
      min24();
    }
    if(minute==25)
    {
      min25();
    }
    if(minute==26)
    {
      min26();
    }
    if(minute==27)
    {
      min27();
    }
    if(minute==28)
    {
      min28();
    }
    if(minute==29)
    {
      min29();
    }
    if(minute==30)
    {
      min30();
    }
    if(minute==31)
    {
      min31();
    }
    if(minute==32)
    {
      min32();
    }
    if(minute==33)
    {
      min33();
    }
    if(minute==34)
    {
      min34();
    }
    if(minute==35)
    {
      min35();
    }
    if(minute==36)
    {
      min36();
    }
    if(minute==37)
    {
      min37();
    }
    if(minute==38)
    {
      min38();
    }
    if(minute==39)
    {
      min39();
    }
    if(minute==40)
    {
      min40();
    }
    if(minute==41)
    {
      min41();
    }
    if(minute==42)
    {
      min42();
    }
    if(minute==43)
    {
      min43();
    }
    if(minute==44)
    {
      min44();
    }
    if(minute==45)
    {
      min45();
    }
    if(minute==46)
    {
      min46();
    }
    if(minute==47)
    {
      min47();
    }
    if(minute==48)
    {
      min48();
    }
    if(minute==49)
    {
      min49();
    }
    if(minute==50)
    {
      min50();
    }
    if(minute==51)
    {
      min51();
    }
    if(minute==52)
    {
      min52();
    }
    if(minute==53)
    {
      min53();
    }
    if(minute==54)
    {
      min54();
    }
    if(minute==55)
    {
      min55();
    }
    if(minute==56)
    {
      min56();
    }
    if(minute==57)
    {
      min57();
    }
    if(minute==58)
    {
      min58();
    }
    if(minute==59)
    {
      min59();
    }
    if(minute==60)
    {
      min60();
    }
    FastLED.show();
    FastLED.clear();
    FastLED.show();  
    }
}

void pride() 
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
 
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;
  
  for( uint16_t i = 0 ; i < NUM_LEDS; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    CRGB newcolor = CHSV( hue8, sat8, bri8);
    
    uint16_t pixelnumber = i;
    pixelnumber = (NUM_LEDS-1) - pixelnumber;
    
    nblend( leds[pixelnumber], newcolor, 64);
  }
}

/*------------------------------------Hour LEDs------------------------------------*/
void hour12()
{
    leds[2] = CRGB(r,g,b);
    leds[4] = CRGB(r,g,b);
    leds[5] = CRGB(r,g,b);
    leds[7] = CRGB(r,g,b);
    leds[10] = CRGB(r,g,b);
    leds[14] = CRGB(r,g,b);
    leds[16] = CRGB(r,g,b);
    leds[17] = CRGB(r,g,b);
    leds[23] = CRGB(r,g,b);
    leds[25] = CRGB(r,g,b);
    leds[30] = CRGB(r,g,b);
    leds[32] = CRGB(r,g,b);
    leds[33] = CRGB(r,g,b);
}
void hour1()
{
    leds[3] = CRGB(r,g,b);
    leds[9] = CRGB(r,g,b);
    leds[15] = CRGB(r,g,b);
    leds[24] = CRGB(r,g,b);
    leds[31] = CRGB(r,g,b);
}
void hour2()
{
    leds[0] = CRGB(r,g,b);
    leds[1] = CRGB(r,g,b);
    leds[4] = CRGB(r,g,b);
    leds[8] = CRGB(r,g,b);
    leds[9] = CRGB(r,g,b);
    leds[15] = CRGB(r,g,b);
    leds[23] = CRGB(r,g,b);
    leds[24] = CRGB(r,g,b);
}
void hour3()
{
    leds[0] = CRGB(r,g,b);
    leds[1] = CRGB(r,g,b);
    leds[4] = CRGB(r,g,b);
    leds[8] = CRGB(r,g,b);
    leds[9] = CRGB(r,g,b);
    leds[16] = CRGB(r,g,b);
    leds[23] = CRGB(r,g,b);
    leds[24] = CRGB(r,g,b);
}
void hour4()
{
    leds[3] = CRGB(r,g,b);
    leds[4] = CRGB(r,g,b);
    leds[8] = CRGB(r,g,b);
    leds[9] = CRGB(r,g,b);
    leds[16] = CRGB(r,g,b);
    leds[23] = CRGB(r,g,b);
}
void hour5()
{
    leds[0] = CRGB(r,g,b);
    leds[1] = CRGB(r,g,b);
    leds[3] = CRGB(r,g,b);
    leds[8] = CRGB(r,g,b);
    leds[9] = CRGB(r,g,b);
    leds[16] = CRGB(r,g,b);
    leds[23] = CRGB(r,g,b);
    leds[24] = CRGB(r,g,b);
}
void hour6()
{
    leds[0] = CRGB(r,g,b);
    leds[1] = CRGB(r,g,b);
    leds[3] = CRGB(r,g,b);
    leds[8] = CRGB(r,g,b);
    leds[9] = CRGB(r,g,b);
    leds[15] = CRGB(r,g,b);
    leds[16] = CRGB(r,g,b);
    leds[23] = CRGB(r,g,b);
    leds[24] = CRGB(r,g,b);
}
void hour7()
{
    leds[0] = CRGB(r,g,b);
    leds[1] = CRGB(r,g,b);
    leds[3] = CRGB(r,g,b);
    leds[4] = CRGB(r,g,b);
    leds[8] = CRGB(r,g,b);
    leds[16] = CRGB(r,g,b);
    leds[23] = CRGB(r,g,b);
}
void hour8()
{
    leds[0] = CRGB(r,g,b);
    leds[1] = CRGB(r,g,b);
    leds[3] = CRGB(r,g,b);
    leds[4] = CRGB(r,g,b);
    leds[8] = CRGB(r,g,b);
    leds[9] = CRGB(r,g,b);
    leds[15] = CRGB(r,g,b);
    leds[16] = CRGB(r,g,b);
    leds[23] = CRGB(r,g,b);
    leds[24] = CRGB(r,g,b);
}
void hour9()
{
    leds[0] = CRGB(r,g,b);
    leds[1] = CRGB(r,g,b);
    leds[3] = CRGB(r,g,b);
    leds[4] = CRGB(r,g,b);
    leds[8] = CRGB(r,g,b);
    leds[9] = CRGB(r,g,b);
    leds[16] = CRGB(r,g,b);
    leds[23] = CRGB(r,g,b);
    leds[24] = CRGB(r,g,b);
}
void hour10()
{
    leds[2] = CRGB(r,g,b);
    leds[4] = CRGB(r,g,b);
    leds[5] = CRGB(r,g,b);
    leds[7] = CRGB(r,g,b);
    leds[8] = CRGB(r,g,b);
    leds[10] = CRGB(r,g,b);
    leds[14] = CRGB(r,g,b);
    leds[22] = CRGB(r,g,b);
    leds[23] = CRGB(r,g,b);
    leds[25] = CRGB(r,g,b);
    leds[30] = CRGB(r,g,b);
    leds[32] = CRGB(r,g,b);
    leds[33] = CRGB(r,g,b);
}
void hour11()
{
    leds[2] = CRGB(r,g,b);
    leds[4] = CRGB(r,g,b);  
    leds[8] = CRGB(r,g,b);
    leds[10] = CRGB(r,g,b);
    leds[14] = CRGB(r,g,b);
    leds[16] = CRGB(r,g,b);
    leds[23] = CRGB(r,g,b);
    leds[25] = CRGB(r,g,b);
    leds[30] = CRGB(r,g,b);
    leds[32] = CRGB(r,g,b);
}

/*----------------------------Minutes LEDs----------------------------*/
void min0()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min1()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min2()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min3()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min4()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min5()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min6()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min7()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min8()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min9()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min10()
{
    leds[62] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min11()
{
    leds[62] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
}
void min12()
{
    leds[62] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min13()
{
    leds[62] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min14()
{
    leds[62] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min15()
{
    leds[62] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min16()
{
    leds[62] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min17()
{
    leds[62] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min18()
{
    leds[62] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min19()
{
    leds[62] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min20()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min21()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min22()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min23()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min24()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min25()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min26()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min27()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min28()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min29()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min30()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min31()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min32()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min33()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min34()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min35()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min36()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min37()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min38()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min39()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min40()
{
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min41()
{
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min42()
{
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min43()
{
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min44()
{
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min45()
{
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min46()
{
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min47()
{
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min48()
{
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min49()
{
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[72] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min50()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min51()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min52()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min53()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min54()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min55()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min56()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min57()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min58()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min59()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[80] = CRGB(r,g,b);
    leds[81] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
void min60()
{
    leds[62] = CRGB(r,g,b);
    leds[63] = CRGB(r,g,b);
    leds[64] = CRGB(r,g,b);
    leds[65] = CRGB(r,g,b);
    leds[70] = CRGB(r,g,b);
    leds[71] = CRGB(r,g,b);
    leds[73] = CRGB(r,g,b);
    leds[78] = CRGB(r,g,b);
    leds[79] = CRGB(r,g,b);
    leds[85] = CRGB(r,g,b);
    leds[86] = CRGB(r,g,b);
    leds[87] = CRGB(r,g,b);
    leds[88] = CRGB(r,g,b);
    leds[90] = CRGB(r,g,b);
    leds[91] = CRGB(r,g,b);
    leds[92] = CRGB(r,g,b);
    leds[93] = CRGB(r,g,b);
}
