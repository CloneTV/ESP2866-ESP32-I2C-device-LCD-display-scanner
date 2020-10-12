
/*
i2cdetect.cpp - Arduino library for scanning I2C bus for devices
*/

#if (defined(ARDUINO) && (ARDUINO >= 100))
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

/* Edit options config.h */
#include "config.h"

static const uint8_t first = DEF_FIRST_ADDR;
static const uint8_t last = DEF_LAST_ADDR;

void i2cscan(lci2c_cb lcdfun) {

  uint8_t i, address, error;
# if defined (SERIAL_PRINT)
  char buff[10]{};
# endif

  S_PRINT_("   ");
  for (i = 0; i < 16; i++) {
    S_SPRINTF_(buff, "%3x", i);
    S_PRINT_(buff);
  }
  for (address = 0; address <= 119; address++) {
    if (address % 16 == 0) {
      S_SPRINTF_(buff, "\n%02x:", (address & 0xF0));
      S_PRINT_(buff);
    }
    if (address >= first && address <= last) {
      Wire.beginTransmission(address);
      error = Wire.endTransmission();
      if (error == 0) {
        /* device found */
        S_SPRINTF_(buff, " %02x", address);
        S_PRINT_(buff);
        lcdfun(address);
      } else if (error == 4) {
        /* other error */
        S_PRINT_(" XX");
      } else {
        /* 
         * error = 2: received NACK on transmit of address 
         * error = 3: received NACK on transmit of data
         */
        S_PRINT_(" --");
      }
    } else {
      /* address not scanned */
      S_PRINT_("   ");
    }
  }
  S_PRINT_("\n\n");
}
