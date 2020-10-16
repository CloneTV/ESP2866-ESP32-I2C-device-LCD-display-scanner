
/*
i2cdetect.cpp - Arduino library for scanning I2C bus for devices
*/

/* Edit options config.h */
#include "config.h"

static const uint8_t first = DEF_FIRST_ADDR;
static const uint8_t last = DEF_LAST_ADDR;
static const char *i2cnames[16] = {
  "Motor Driver",
  "ADXL345 Input 3-Axis Digital Accelerometer",
  "HMC5883 3-Axis Digital Compass",
  "Touch Sensor",
  "BH1750FVI digital Light Sensor",
  "LCM1602 LCD Adapter",
  "PCF8574 8-Bit I/O Expander",
  "BH1750FVI digital Light Sensor",
  "TSL2561 Ambient Light Sensor",
  "BMP180/280 barometric pressure sensor",
  "ADS1115 Module 16-Bit",
  "SPI-to-UART",
  "AT24C32 EEPROM",
  "ADXL345 Input 3-Axis Digital Accelerometer",
  "DS3231 real-time clock",
  "1306 OLED"
};

static const char * i2cname(uint8_t & addr) {
  switch (addr) {
    case 0x0A: return i2cnames[0];
    case 0x0F: return i2cnames[0];
    case 0x1D: return i2cnames[1];
    case 0x1E: return i2cnames[2];
    case 0x5A: return i2cnames[3];
    case 0x5B: return i2cnames[3];
    case 0x5C: return i2cnames[4];
    case 0x5D: return i2cnames[3];
    case 0x20: return i2cnames[5];
    case 0x21: return i2cnames[6];
    case 0x22: return i2cnames[6];
    case 0x23: return i2cnames[7];
    case 0x24: return i2cnames[6];
    case 0x25: return i2cnames[6];
    case 0x26: return i2cnames[6];
    case 0x27: return i2cnames[5];
    case 0x3C: return i2cnames[15];
    case 0x3D: return i2cnames[15];
    case 0x39: return i2cnames[8];
    case 0x40: return i2cnames[9]; 
    case 0x48: return i2cnames[10];
    case 0x49: return i2cnames[11];
    case 0x4A: return i2cnames[10];
    case 0x4B: return i2cnames[10];
    case 0x50: return i2cnames[12]; 
    case 0x53: return i2cnames[13];
    case 0x68: return i2cnames[14];
    case 0x7A: return i2cnames[15];
    case 0x76: return i2cnames[9];
    case 0x77: return i2cnames[9];
    case 0x78: return i2cnames[15];
    default:
      return nullptr;
  }
}

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
        lcdfun(address, i2cname(address));
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
