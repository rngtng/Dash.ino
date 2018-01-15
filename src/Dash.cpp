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

void dash_key_handler(uint32_t data) {
  uint8_t key_num;
  for (key_num = 0; key_num < 4; key_num++) {
    uint32_t state = Dash.key(key_num);
    if (key_num == K2 && state == 50) {
      Dash.led(key_num, RED);
      sys_reset();
    } else if (key_num == K4 && state == 50) {
      Dash.led(key_num, RED);
      Dash.off();
    } else {
      Dash.key_handler(key_num, state);
    }
  }
}

void dash_led_handler(uint32_t data) {
  uint8_t led_num;
  Dash.next_frame();
  for (led_num = 0; led_num < 4; led_num++) {
    Dash.frame_led(led_num);
  }
}

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

void DashClass::begin()
{
  uint8_t led_num;
  for (led_num = 0; led_num < 4; led_num++) {
    printf("led %d init:\r\n", led_num);
    led_init(led_num);
    led(led_num, OFF);
    printf("key %d init:\r\n", led_num);
    key_init(led_num);
  }
  GTimer.begin(1, 5, dash_led_handler);
}

void DashClass::begin_key(void (*handler)(uint8_t, int32_t))
{
  key_handler = handler;
  GTimer.begin(0, 1 * 1000 * 50, dash_key_handler);
}

void DashClass::stop()
{
  GTimer.stop(0);
  GTimer.stop(1);
}

void DashClass::led(uint8_t led_num, uint8_t rgb, uint8_t brightness)
{
  leds[led_num].state = rgb;
  leds[led_num].brightness = brightness;
}

void DashClass::raw_led(uint8_t led_num, uint8_t rgb)
{
  digitalWrite(leds[led_num].r, (~rgb >> 2) & 1);
  digitalWrite(leds[led_num].g, (~rgb >> 1) & 1);
  digitalWrite(leds[led_num].b, (~rgb >> 0) & 1);
}

int32_t DashClass::key(uint8_t key_num)
{
  if (raw_key(key_num)) {
    if (keys[key_num].state < 0) {
      keys[key_num].state = 0;
    }
    ++keys[key_num].state;
  }
  else {
    if (keys[key_num].state > 0) {
      keys[key_num].state = 0;
    }
    --keys[key_num].state;
  }
  return keys[key_num].state;
}


bool DashClass::raw_key(uint8_t key_num)
{
  return (digitalRead(keys[key_num].pin) == 0);
}

uint32_t DashClass::battery()
{
  return analogRead(PIN_BAT);
}

void DashClass::off()
{
  pinMode(PIN_PWR, OUTPUT);
}

void DashClass::frame_led(uint8_t led_num)
{
  raw_led(led_num, (dash_frame < leds[led_num].brightness) ? leds[led_num].state : OFF);
}

void DashClass::next_frame()
{
  dash_frame++;
  if (dash_frame > FULL) {
    dash_frame = 0;
  }
}

DashClass Dash;
