#include "Arduino.h"
#include "dash.h"

LED DashClass::leds[] =
{
  {25, 24, 19, 0}, //1 { PE_4, PE_3, PC_4, 0 },
  { 0,  2,  6, 0}, //3 { PA_6, PA_5, PC_4, 0 } ,
  {22, 21,  1, 0}, //2 { PE_1, PE_0, PA_7, 0 },
  {12, 11, 13, 0}  //4 { PC_3, PC_2, PC_1, 0 },
};

KEY DashClass::keys[] =
{
  {23, 0},
  {14, 0},
  {10, 0},
  {20, 0}
};

DashClass::DashClass()
{
  //   LED leds[4] = {
  //     {25, 24, 19, 0},
  //     { 0,  2,  6, 0},
  //     {22, 21,  1, 0},
  //     {12, 11, 13, 0}
  //   };
  //
  //   KEY keys[4]  = {
  //     {23, 0},
  //     {14, 0},
  //     {10, 0},
  //     {20, 0}
  //   };
}

//void key_handler(uint32_t key_num, uint32_t event) {
//  byte led_num;
//  switch (key_num) {
//    case 23:
//      led_num = 0;
//      break;
//    case 14:
//      led_num = 1;
//      break;
//    case 10:
//      led_num = 2;
//      break;
//    case 20:
//      led_num = 3;
//      break;
//  }
//  Dash.led(led_num, (Dash.leds[led_num].state + 1) % 8);
//}

void DashClass::led_init(uint8_t led_num)
{
  pinMode(leds[led_num].r, OUTPUT);
  pinMode(leds[led_num].g, OUTPUT);
  pinMode(leds[led_num].b, OUTPUT);
}

void DashClass::key_init(uint8_t key_num)
{
  //  if (keys[key_num].pin != 14) {
  //    pinMode(keys[key_num].pin, INPUT_IRQ_FALL);
  //    digitalSetIrqHandler(keys[key_num].pin, &key_handler);
  //  }
  //  else {
  pinMode(keys[key_num].pin, INPUT_PULLUP);
  //  }
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
  return analogRead(PIN_BAT);
}

void DashClass::off()
{
  pinMode(PIN_PWR, OUTPUT);
}

DashClass Dash;
