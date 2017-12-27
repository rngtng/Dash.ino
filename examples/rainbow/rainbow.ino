#include <Dash.h>

Dash dash = Dash();

void setup()
{
  dash.init()
}

void loop()
{
   for (byte color = 0; color < 8; color++) {
    for (byte led = 0; led < 4; led++) {
      dash.led_ctrl(led, color);
      delay(150);
    }
  }
}
