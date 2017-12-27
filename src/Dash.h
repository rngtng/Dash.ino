#ifndef _DASH_H_
#define _DASH_H_

#define RED   B100
#define GREEN B010
#define BLUE  B001
#define OFF   B000

typedef struct {
  byte r;
  byte g;
  byte b;
} RGB;

class Dash
{
  public:
    static const int pwr_en = 15;

    static const RGB leds[4];

    static const int keys[4];

    //  pinMode(led4_g, OUTPUT);
    //  pinMode(led4_r, OUTPUT);
    //  pinMode(led1_g, OUTPUT);
    //  pinMode(led1_r, OUTPUT);
    //  pinMode(key1, INPUT_PULLUP);
    Dash() {
      
    };
    void init();
    void led_ctrl(uint8_t led_num, uint8_t rgb);
    void led_off();

  private:
    void led_init(uint8_t led_num);
    void key_init(uint8_t key_num);
};

#endif
