

#define DEF_FIRST_ADDR 0x03
#define DEF_LAST_ADDR  0x77

#define I2C_DISPLAY 1
#define DISPLAY_CURSOR 0
#define SERIAL_PRINT 1

// ------------------------------- //

#if defined (SERIAL_PRINT)
#  if defined(ESP2866)
#    define S_INIT_() Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY); while (!Serial) { delay(50); }
#  else
#    define S_INIT_() Serial.begin(115200); while (!Serial) { delay(50); }
#  endif
#  define S_PRINT_(A) Serial.print(A)
#  define S_PRINTF_(A,...) Serial.printf(A, __VA_ARGS__)
#  define S_SPRINTF_(A,B,...) sprintf(A, B, __VA_ARGS__)
#else
#  define S_INIT_()
#  define S_PRINT_(A)
#  define S_PRINTF_(A,...)
#  define S_SPRINTF_(A,B,...)
#endif

#if (defined(ARDUINO) && (ARDUINO >= 100))
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif

#include "I2CDefine.h"

#if !defined (FPSTR)
#  define FPSTR(A) A
#endif

#include <Wire.h> 
#include "I2CLCD.h"
#include "I2CScan.h"
