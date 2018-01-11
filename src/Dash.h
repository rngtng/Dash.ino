#ifndef _DASH_H_
#define _DASH_H_

#include <GTimer.h>
#include <sys_api.h>

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
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t state;
} LED;

typedef struct
{
  uint8_t pin;
  int32_t state;
} KEY;

class DashClass
{
  public:
    static const uint8_t PIN_BAT = A2;
    static const uint8_t PIN_PWR = 15;

    static LED leds[4];
    static KEY keys[4];
    void (*key_handler)(uint8_t, int32_t);

    //  pinMode(led4_g, OUTPUT);
    //  pinMode(led4_r, OUTPUT);
    //  pinMode(led1_g, OUTPUT);
    //  pinMode(led1_r, OUTPUT);
    //  pinMode(key1, INPUT_PULLUP);
    void begin(void (*handler)(uint8_t, int32_t));
    void led(uint8_t led_num, uint8_t rgb);
    void all_led(uint8_t rgb);
    int32_t key(uint8_t key_num);
    bool raw_key(uint8_t key_num);
    uint32_t battery();
    void off();

  private:
    void led_init(uint8_t led_num);
    void key_init(uint8_t key_num);
    friend void timer_handler(uint32_t data);
};

extern DashClass Dash;

#endif
