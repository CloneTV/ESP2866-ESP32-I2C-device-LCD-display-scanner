#if !defined (I2C_LCD_H)
#define I2C_LCD_H 1

# include <LiquidCrystal_I2C.h>
typedef void (*lci2c_cb)(uint8_t&);

# if defined(I2C_DISPLAY)
class I2CLCD {
  private:
    uint8_t lastpos = 0U,
            lastaddr = 0U;
    uint32_t lastscan = 0U;
    LiquidCrystal_I2C *lci2c;

  public:
    I2CLCD(LiquidCrystal_I2C *cls) {
      lci2c = cls;
    }
    ~I2CLCD() {
      lci2c->clear();
    }
    void init(const uint8_t & sda_p, const uint8_t & scl_p) {
      lci2c->begin(sda_p, scl_p);
      lci2c->backlight();
      lci2c->clear();
      lci2c->cursor_on();
      lci2c->blink_on();
    }
    void beginScan() {
      if (lastscan == (UINT32_MAX - 1))
        lastscan = 1U;
      else
        ++lastscan;
      lastpos = 0U;
      lci2c->clear();
#     if (defined(DISPLAY_CURSOR) && (DISPLAY_CURSOR > 0))
      lci2c->cursor_on();
      lci2c->blink_on();
#     endif
    }
    void endScan() {
#     if (defined(DISPLAY_CURSOR) && (DISPLAY_CURSOR > 0))
      lci2c->blink_off();
      lci2c->cursor_off();
#     endif
    }
    void print(uint8_t & addr) {
      lci2c->home();
      lci2c->printf("I2C: 0x%X [%u] ", lastaddr, lastscan);
      lci2c->setCursor(lastpos, 1);
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
    void init(const uint8_t & sda_p, const uint8_t & scl_p) {}
    void beginScan() {}
    void endScan() {}
    void print(uint8_t & addr) {}
};
# endif
#endif
