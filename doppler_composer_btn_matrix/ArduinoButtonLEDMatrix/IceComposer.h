#ifndef ICECOMP_h
#define ICECOMP_h

#include <ICEClass.h>
#include "/Users/svenbraun/Documents/GitHub/Doppler_FPGA_Firmware/doppler_composer_btn_matrix/button_matrix.h"



#define COMPOSER_ICE_CDONE      3
#define COMPOSER_ICE_RESET      4
#define COMPOSER_ICE_CS         5


class IceComposer : public ICEClass {

  public:
        
  IceComposer(){};

        
  void initSPI(){
        ice_cs = COMPOSER_ICE_CS;
        pinMode (COMPOSER_ICE_CS, OUTPUT);
        pinMode (PIN_SPI_SCK,     OUTPUT);
        pinMode (PIN_SPI_MOSI,    OUTPUT);
        pinMode (PIN_SPI_MISO,    INPUT);

        SPIfpga = &SPI;
        SPIfpga->begin();
        pinPeripheral(PIN_SPI_MISO,   PIO_SERCOM_ALT);    // TODO: check in variant may buggy ????
    };

    void reset_inout() {
        //pinMode(ICE_CLK,     INPUT_PULLUP);
        //pinMode(ICE_CDONE,   INPUT_PULLUP);
        //pinMode(ICE_MOSI,    INPUT_PULLUP);
        pinMode(COMPOSER_ICE_RESET,  OUTPUT);
        //pinMode(ICE_CS,      OUTPUT);
        digitalWrite(COMPOSER_ICE_CS, HIGH);
    };


    bool upload(){
        upload(button_matrix_bin,sizeof(button_matrix_bin));
    }
    
    bool upload(const unsigned char * bitstream , const unsigned int bitstream_size){
        // ensure via are in right mode
        // pinPeripheral(ICE_MISO,   PIO_DIGITAL);
        pinPeripheral(PIN_SPI_MOSI,   PIO_DIGITAL);
        pinPeripheral(PIN_SPI_SCK,    PIO_DIGITAL);
        
        pinMode(PIN_SPI_SCK,     OUTPUT);
        pinMode(PIN_SPI_MOSI,    OUTPUT);
        pinMode(COMPOSER_ICE_RESET,  OUTPUT);
        pinMode(COMPOSER_ICE_CS,      OUTPUT);
        
        // enable reset
        digitalWrite(COMPOSER_ICE_RESET, LOW);
        
        // start clock high
        digitalWrite(PIN_SPI_SCK, HIGH);
        
        // select SRAM programming mode
        digitalWrite(COMPOSER_ICE_CS, LOW);
        delay(10);
        
        // release reset
        digitalWrite(COMPOSER_ICE_RESET, HIGH);
        delay(100);     // TODO: check time! for Waiting FPGA is self init!

        // Begin HardwareSPI
        initSPI();
        SPIfpga->beginTransaction(SPISettings(SPI_FPGA_SPEED, MSBFIRST, SPI_MODE0));
        SPIfpga->transfer(0x00);    // 8 clocks
        //const unsigned int size = sizeof(BITSTREAM);
        for (int k = 0; k < bitstream_size; k++) {
            SPIfpga->transfer(bitstream[k]);
        }
        SPIfpga->endTransaction();
        for(int i = 0 ; i < 8 ; i++){
            SPIfpga->transfer(0x00);
        }
        // End HardwareSPI

        bool cdone_high = digitalRead(COMPOSER_ICE_CDONE) == HIGH;
        reset_inout();
        return cdone_high;
    }



};

#endif // ICECOMP_h
