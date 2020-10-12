
/* Edit options config.h */
#include "config.h"

static const uint8_t scl_PIN = 5;
static const uint8_t sda_PIN = 4;

#if defined(I2C_DISPLAY)
  LiquidCrystal_I2C lcd__(0x27, 16, 2);
  I2CLCD i2clcd = I2CLCD(&lcd__);
#else
  I2CLCD i2clcd = I2CLCD();
#endif

void setup()
{
  S_INIT_();
  S_PRINT_("Scanning I2C address range 0x03-0x77\n\n");
  Wire.begin(sda_PIN, scl_PIN);
  i2clcd.init(sda_PIN, scl_PIN);
}

void loop() {
  i2clcd.beginScan();
  i2cscan(
    [=](uint8_t & addr) { i2clcd.print(addr); }
  );
  i2clcd.endScan();
  delay(3000);
# if defined(I2C_DISPLAY)
  yield();
  delay(3000);
# endif
}
