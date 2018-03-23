#include "Arduino.h"
#include "dash.h"

LED DashClass::leds[] =
{
  {25, 24, 19, WHITE, FULL}, //1 { PE_4, PE_3, PC_4, 0 },
  { 0,  2,  6, WHITE, FULL}, //3 { PA_6, PA_5, PC_4, 0 } ,
  {22, 21,  1, WHITE, FULL}, //2 { PE_1, PE_0, PA_7, 0 },
  {12, 11, 13, WHITE, FULL}  //4 { PC_3, PC_2, PC_1, 0 },
};

KEY DashClass::keys[] =
{
  {23, 0},
  {14, 0},
  {10, 0},
  {20, 0}
};

void dash_timer_handler(uint32_t data) {
  Dash.keys_handler();
  Dash.leds_handler();
}

void DashClass::begin()
{
  uint8_t led_num;
  for (led_num = L1; led_num <= L4; led_num++) {
    printf("led %d init:\r\n", led_num);
    led_init(led_num);
    printf("key %d init:\r\n", led_num);
    key_init(led_num);
  }
  GTimer.begin(DASH_TIMER, 5, dash_timer_handler);
}

void DashClass::stop()
{
  GTimer.stop(DASH_TIMER);
}

void DashClass::all_led(uint8_t rgb, uint8_t brightness)
{
  uint8_t led_num;
  for (led_num = 0; led_num < 4; led_num++) {
    led(led_num, rgb, brightness);
  }
}

void DashClass::led(uint8_t led_num, uint8_t rgb, uint8_t brightness)
{
  leds[led_num].color = rgb;
  if (brightness >= 0 && brightness <= FULL) {
    leds[led_num].brightness = brightness;
  }
}

void DashClass::raw_led(uint8_t led_num, uint8_t rgb)
{
  digitalWrite(leds[led_num].r, (~rgb >> 2) & 1);
  digitalWrite(leds[led_num].g, (~rgb >> 1) & 1);
  digitalWrite(leds[led_num].b, (~rgb >> 0) & 1);
}

uint32_t DashClass::key(uint8_t key_num)
{
  if (raw_key(key_num)) {
    if (keys[key_num].state == LOW) {
      keys[key_num].state = millis();
      return RISING;
    }
    return (millis() - keys[key_num].state);
  }
  else {
    if (keys[key_num].state != LOW) {
      keys[key_num].state = LOW;
      return FALLING;
    }
    return LOW;
  }
}


bool DashClass::raw_key(uint8_t key_num)
{
  return (digitalRead(keys[key_num].pin) == 0);
}

uint32_t DashClass::battery()
{
  return analogRead(PIN_BAT);
}

void DashClass::reset()
{
  sys_reset();
}

void DashClass::off()
{
  pinMode(PIN_PWR, OUTPUT);
}

/* ==================== private==================== */

void DashClass::led_init(uint8_t led_num)
{
  pinMode(leds[led_num].r, OUTPUT);
  pinMode(leds[led_num].g, OUTPUT);
  pinMode(leds[led_num].b, OUTPUT);
}

void DashClass::key_init(uint8_t key_num)
{
  pinMode(keys[key_num].pin, INPUT_PULLUP);
}

void DashClass::leds_handler() {
  uint8_t led_num;
  if (++led_frame > FULL) {
    led_frame = 0;
  }
  for (led_num = 0; led_num < 4; led_num++) {
    raw_led(led_num, (led_frame < leds[led_num].brightness) ? leds[led_num].color : OFF);
  }
}

void DashClass::keys_handler() {
  if (++key_frame > 1000) {
    key_frame = 0;
    DashKeyState key_state = { key(K1), key(K2), key(K3), key(K4) };

    default_keys_handler(key_state);
    if (custom_keys_handler) {
      custom_keys_handler(key_state);
    }
  }
}

void DashClass::default_keys_handler(DashKeyState key_state) {
  if (key_state.k2 > 5000) {
    led(L2, RED);
    stop();
    reset();
  } else if (key_state.k4 > 5000) {
    led(L4, RED);
    stop();
    off();
  }
}

DashClass Dash;
