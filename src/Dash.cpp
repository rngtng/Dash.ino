#include "Arduino.h"
#include "dash.h"

LED DashClass::leds[] = {
  {25, 24, 19, 0},
  { 0,  2,  6, 0},
  {22, 21,  1, 0},
  {12, 11, 13, 0}
};

KEY DashClass::keys[]  = {
  {23, 0},
  {14, 0},
  {10, 0},
  {20, 0}
};

DashClass::DashClass() {
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
  byte led_num;
  for (led_num = 0; led_num < 4; led_num++) {
    printf("led %d init:\r\n", led_num);
    led_init(led_num);
    led(led_num, OFF);
    printf("key %d init:\r\n", led_num);
    key_init(led_num);
  }

  //  printf("power enable: \r\n");
  //  pinMode(pwr_en, OUTPUT);
  //  printf("p \r\n");
  //  digitalWrite(pwr_en, 1);
}

void DashClass::led(uint8_t led_num, uint8_t rgb)
{
  leds[led_num].state = rgb;
  digitalWrite(leds[led_num].r, (~rgb >> 2) & 1);
  digitalWrite(leds[led_num].g, (~rgb >> 1) & 1);
  digitalWrite(leds[led_num].b, (~rgb >> 0) & 1);
}

void DashClass::all_led(uint8_t rgb)
{
  byte led_num;
  for (led_num = 0; led_num < 4; led_num++) {
    led(led_num, rgb);
  }
}

bool DashClass::key(uint8_t key_num)
{
  keys[key_num].state = digitalRead(keys[key_num].pin);
  return keys[key_num].state == 0;
}

int DashClass::battery()
{
  return analogRead(A2);
}

DashClass Dash;
