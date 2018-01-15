#ifndef _DASH_H_
#define _DASH_H_

#include <GTimer.h>
#include <sys_api.h>

#define OFF    B000
#define BLACK  B000
#define RED    B100
#define GREEN  B010
#define YELLOW B110
#define BLUE   B001
#define PURPLE B101
#define CYAN   B011
#define WHITE  B111

#define L1 0
#define L2 1
#define L3 2
#define L4 3

#define K1 0
#define K2 1
#define K3 2
#define K4 3


#define FULL 8

typedef struct
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t state;
  uint8_t brightness;
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
    void begin();
    void begin_key(void (*handler)(uint8_t, int32_t));
    void stop();

    void led(uint8_t led_num, uint8_t rgb, uint8_t brightness = FULL);
    int32_t key(uint8_t key_num);

    void raw_led(uint8_t led_num, uint8_t rgb);
    bool raw_key(uint8_t key_num);

    uint32_t battery();
    void off();

  private:
    uint8_t dash_frame = 0;

    void led_init(uint8_t led_num);
    void key_init(uint8_t key_num);
    friend void dash_key_handler(uint32_t data);
    friend void dash_led_handler(uint32_t data);
    void frame_led(uint8_t led_num);
    void next_frame();
};

extern DashClass Dash;

#endif
