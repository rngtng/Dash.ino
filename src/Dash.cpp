#include "Arduino.h"
#include "dash.h"

const RGB Dash::leds[] = {
  {25, 24, 19},
  { 0,  2,  6},
  {22, 21,  1},
  {12, 11, 13}
};

const int Dash::keys[]  = { 23, 14, 10, 20 };

void Dash::led_init(uint8_t led_num)
{
  pinMode(leds[led_num].r, OUTPUT);
  pinMode(leds[led_num].g, OUTPUT);
  pinMode(leds[led_num].b, OUTPUT);
}

void Dash::key_init(uint8_t key_num)
{
  pinMode(keys[key_num], INPUT_PULLUP);
}

void Dash::init()
{
  byte i;
  for (i = 0; i < 4; i++) {
    led_init(i);
    led_ctrl(i, OFF);
    printf("led %d inited\r\n", i);
    key_init(i);
    printf("key %d inited\r\n", i);
  }

//  pinMode(pwr_en, OUTPUT);
//  printf("p \r\n");
//  digitalWrite(pwr_en, 1);
//  printf("p1 \r\n");
}

void Dash::led_off()
{
  byte i;
  for (i = 0; i < 4; i++) {
    led_ctrl(i, OFF);
  }
}

void Dash::led_ctrl(uint8_t led_num, uint8_t rgb)
{
  digitalWrite(leds[led_num].r, (~rgb >> 2) & 1);
  digitalWrite(leds[led_num].g, (~rgb >> 1) & 1);
  digitalWrite(leds[led_num].b, (~rgb >> 0) & 1);
}

