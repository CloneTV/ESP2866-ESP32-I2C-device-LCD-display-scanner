#if !defined (I2C_LCD_H)
#define I2C_LCD_H 1

# include "ESP2866_LCD1602_I2C.h"
typedef void (*lci2c_cb)(uint8_t&);

# if defined(I2C_DISPLAY)
class I2CLCD {
  private:
    uint8_t lastpos = 0U,
            lastaddr = 0U;
    uint32_t lastscan = 0U;
    ESP2866_LCD1602_I2C<> *lci2c;

  public:
    I2CLCD() {
      lci2c = new ESP2866_LCD1602_I2C<>();
    }
    ~I2CLCD() {
      delete lci2c;
    }
    void init() {
      if (!lci2c->begin()) {
#       if defined(LED_BUILTIN)
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, HIGH);
#       endif
        S_PRINT_("-- Erorr initialize I2C LCD 1602\n");
        return;
      }
      lci2c->backlight();
      lci2c->cursor(true);
      lci2c->blink(true);
    }
    void beginScan() {
      if (!static_cast<bool>(lci2c))
        return;

      if (lastscan == (UINT32_MAX - 1))
        lastscan = 1U;
      else
        ++lastscan;
      lastpos = 0U;
      lci2c->clear();
#     if (defined(DISPLAY_CURSOR) && (DISPLAY_CURSOR > 0))
      lci2c->cursor(true);
      lci2c->blink(true);
#     endif
    }
    void endScan() {
#     if (defined(DISPLAY_CURSOR) && (DISPLAY_CURSOR > 0))
      if (!static_cast<bool>(lci2c))
        return;
      lci2c->blink(false);
      lci2c->cursor(false);
#     endif
    }
    void print(uint8_t & addr) {
      if (!static_cast<bool>(lci2c))
        return;
      lci2c->home();
      lci2c->printf("I2C: 0x%X [%u] ", lastaddr, lastscan);
      lci2c->cursor(lastpos, 1);
      lci2c->printf("%X,", addr);
      lastaddr = addr;
      lastpos = ((lastpos > 12) ? 0U : (lastpos + 3U));
    }
};
# else

class I2CLCD {
  public:
    I2CLCD() {}
    I2CLCD(void*) {}
    ~I2CLCD() {}
    void init() {}
    void beginScan() {}
    void endScan() {}
    void print(uint8_t & addr) {}
};
# endif
#endif
