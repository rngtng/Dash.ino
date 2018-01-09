#ifndef _DASH_H_
#define _DASH_H_

#define OFF    B000
#define RED    B100
#define GREEN  B010
#define YELLOW B110
#define BLUE   B001
#define PURPLE B101
#define CYAN   B011
#define WHITE  B111

typedef struct
{
  byte r;
  byte g;
  byte b;
  byte state;
} LED;

typedef struct
{
  byte pin;
  byte state;
} KEY;

class DashClass
{
  public:
    DashClass();

    static const int PIN_BAT = A2;
    static const int PIN_PWR = 15;

    static LED leds[4];
    static KEY keys[4];

    //  pinMode(led4_g, OUTPUT);
    //  pinMode(led4_r, OUTPUT);
    //  pinMode(led1_g, OUTPUT);
    //  pinMode(led1_r, OUTPUT);
    //  pinMode(key1, INPUT_PULLUP);
    void begin();
    void led(uint8_t led_num, uint8_t rgb);
    void all_led(uint8_t rgb);
    bool key(uint8_t key_num);
    int battery();
    void off();

  private:
    void led_init(uint8_t led_num);
    void key_init(uint8_t key_num);
    // friend void key_handler(uint32_t key_num, uint32_t event);
};

extern DashClass Dash;

#endif
