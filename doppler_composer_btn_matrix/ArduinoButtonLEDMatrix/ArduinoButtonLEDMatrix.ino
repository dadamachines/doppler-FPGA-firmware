#include <Adafruit_NeoPixel_ZeroDMA.h>
#include "IceComposer.h"

#define PIN        A3
#define NUM_PIXELS 252

Adafruit_NeoPixel_ZeroDMA strip(NUM_PIXELS, PIN, NEO_GRB);
IceComposer fpga;


void setup() {
  strip.begin();
  strip.setBrightness(25);
  strip.show();


  fpga.upload();
  delay(100);
  // start SPI runtime Link to FPGA
  fpga.initSPI();


  Serial.begin(9600);
  Serial.println("\ndebugger");
}

static uint16_t nr=0;
static uint16_t btArray[12];


bool isButtonPressed(uint16_t bt_nr){
  uint16_t i = bt_nr/16;
  uint16_t rest = bt_nr % 16;
  if(i<12)
    return !bitRead(btArray[i],rest);

   return false;
}



void loop() {

    for(int row = 0 ; row < 12 ; row++){
       btArray[row] = fpga.sendSPI16(~ ( 0x0001 << row)  );
       //Serial.print(btArray[row],HEX);
    }
    //Serial.println(" ---");

    nr++;
    if(nr>strip.numPixels())
      nr=0;
  
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      if(isButtonPressed(i))
        strip.setPixelColor(i, 0x00ff00);
      else if(i==nr) 
        strip.setPixelColor(i, 0xff0000);
      else
        strip.setPixelColor(i, 0x000000);
    }

    strip.show();

    delay(12);

}


