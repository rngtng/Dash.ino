#include "Arduino.h"
#include "dash.h"

const RGB DashClass::leds[] = {
  {25, 24, 19},
  { 0,  2,  6},
  {22, 21,  1},
  {12, 11, 13}
};

const int DashClass::keys[]  = { 23, 14, 10, 20 };

void DashClass::led_init(uint8_t led_num)
{
  pinMode(leds[led_num].r, OUTPUT);
  pinMode(leds[led_num].g, OUTPUT);
  pinMode(leds[led_num].b, OUTPUT);
}

void DashClass::key_init(uint8_t key_num)
{
  pinMode(keys[key_num], INPUT_PULLUP);
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
  return digitalRead(DashClass::keys[key_num]) == 0;
}

int DashClass::battery()
{
  return analogRead(A2);
}

