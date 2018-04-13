

#include <Arduino.h>
#include <U8g2lib.h>

#include <SimpleDHT.h>
// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: D2

int pinDHT11 = 2;
SimpleDHT11 dht11;

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


void setup(void) 
{
  u8g2.begin();
  u8g2.setFlipMode(0);
}

//Humidity
uint8_t  H = 62;
uint8_t  T = 21;
// y  is draw line
uint8_t yy = 0;

void read_data(void)
{
    int err = SimpleDHTErrSuccess; 
    if ((err = dht11.read(pinDHT11, &T, &H, NULL)) != SimpleDHTErrSuccess) {
      H =0;
      T =0;
    }
}

uint8_t xx =0;
void draw(void)
{
    u8g2.setFontDirection(0);
    u8g2.setFont(u8g2_font_5x8_mf);
    u8g2.drawStr(0,8,"Make By Gavim");
    if(xx == 40)
      u8g2.drawStr(0,8,"Make By Gavim      *.*");
    if(xx == 80)
      u8g2.drawStr(0,8,"Make By Gavim         @v@");      
    //-----------------------------------
    u8g2.setFont(u8g2_font_inb27_mf);
    u8g2.setCursor(20, 43);    
    u8g2.print(T);
    //--------------------------------
    u8g2.setFont(u8g2_font_helvB12_tf );
    u8g2.setCursor(70, 30);
    u8g2.print("oC");    
    //--------------------------------
    u8g2.setFont(u8g2_font_5x8_mf);
    u8g2.drawStr(20,55,"Now Humidity"); 
    //-------------------------------   
    u8g2.setFont(u8g2_font_helvB12_tf );
    u8g2.setCursor(90, 54);
    u8g2.print(H);  
    u8g2.print("%"); 
    //------------------------------
    u8g2.setFont(u8g2_font_5x8_mf);
   
    if(xx>120)
      xx =0;
    u8g2.drawStr(xx,63,"=="); 
}

void drawPage(void)
{
    u8g2.firstPage();
    do {
      draw();
    } while ( u8g2.nextPage() );  
}


void loop(void) {
    xx=xx+2;
    read_data();
    drawPage();
    delay(2000);
}

