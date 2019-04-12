#include <ICEClass.h>

#include "bitstream.h" // bitstream source: doppler_4x4led_pwm.v

ICEClass ice40;

void setup() {
  ice40.upload((const unsigned char *)&bitstream_bin, bitstream_bin_len);
  delay(100);
  ice40.initSPI();
}

float t = 0.0f;
unsigned char plasma[16] = { 0, };

void loop() {
  // generate some waves,
  for(int j=0; j<4; j++) {
    for(int i=0; i<4; i++) {
      float fi = (float)i;
      float fj = (float)j;
      float c0 = sin((t * 3.0 + fj * 7.5) / 12.0);
      float c1 = cos((t * 3.6 + fi * 8.0) / 11.0);
      float a =
        cos((t + fi * 1.7 + 4.0 * c0) / 10.3) +
        sin((t + fj * 1.3 + 5.0 * c1 - 1.0 * c0) / 9.5);
      a = sin(a * 6.0 + t);
      int g = (int)(128.0f + 140.0f * a);
      if (g < 0) g = 0;
      if (g > 255) g = 255;
      plasma[(j * 4) + i] = g;
    }
  }

  // send it to the fpga with SPI
  for(int j=0; j<8; j++) {
    ice40.sendSPI16( (plasma[(j*2)+0] << 8) + plasma[(j*2)+1] );
  }

  t += 0.1f;
  delay(10);
}
