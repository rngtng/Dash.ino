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

#define DASH_TIMER 4

#define FULL 8
#define KEEP_BRIGHTNESS_UNCHANGED 10

typedef struct
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t color;
  uint8_t brightness;
} LED;

typedef struct
{
  uint8_t pin;
  int32_t state;
} KEY;

typedef struct
{
  uint32_t k1;
  uint32_t k2;
  uint32_t k3;
  uint32_t k4;
} DashKeyState;

class DashClass
{
  public:
    static const uint8_t PIN_BAT = A2;
    static const uint8_t PIN_PWR = 15;
    static const uint8_t PIN_FKT = 18;

    static LED leds[4];
    static KEY keys[4];
    void (*custom_keys_handler)(DashKeyState);

    void begin();
    void stop();

    void all_led(uint8_t rgb, uint8_t brightness = KEEP_BRIGHTNESS_UNCHANGED);
    void led(uint8_t led_num, uint8_t rgb, uint8_t brightness = KEEP_BRIGHTNESS_UNCHANGED);
    uint32_t key(uint8_t key_num);

    void raw_led(uint8_t led_num, uint8_t rgb);
    bool raw_key(uint8_t key_num);

    uint32_t battery();
    void reset();
    void off();

  private:
    uint8_t  led_frame = 0;
    uint32_t key_frame = 0;

    friend void dash_timer_handler(uint32_t data);
    void led_init(uint8_t led_num);
    void key_init(uint8_t key_num);
    void leds_handler();
    void keys_handler();
    void default_keys_handler(DashKeyState key_state);
};

extern DashClass Dash;

#endif
